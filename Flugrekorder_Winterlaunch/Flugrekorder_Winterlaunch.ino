// 2013/12/12  by Jonis Kiesbye
//
// Flugrekorder - Diese Version fliegt beim Winterlaunch 14.12.2013
//
// This example logs an Accelerometer at 400 Hz and a Magnetometer at 200 Hz
// 
// Erratum: Last axis of the magnetometer periodically puts out a value that seems off

#include <I2C.h>
#include <BufferedWriter.h>
#include <SdFat.h>

#define SD_CHIP_SELECT  SS  // SD chip select pin

const uint32_t MAX_SYNC_TIME_MSEC = 1000;

// Variablen fuer SD-Card, SD
// file system object
SdFat sd;
// file for logging data
SdFile file;
// fast text formatter
BufferedWriter bw;


//Konstanten für Beschleunigungssensor, ACC
const uint8_t ACC_ADDRESS = B0011000;
const uint8_t ACC_CTRL1 = B00100000;
const uint8_t ACC_CTRL4 = B00100011;
const uint8_t ACC_X_L_CONT = B10101000; // address of the first data register with a leading 1 so the address gets incremented automatically for the next reads

//Variablen fuer ACC
uint8_t ACC_raw[6] = {0,0,0,0,0,0};

//Konstanten fuer Magnetometer, MAG
const uint8_t MAG_ADDRESS = B0011110;
const uint8_t MAG_CRA = 0x00;
const uint8_t MAG_MR = 0x02;
const uint8_t MAG_X_H = 0x03;

//Variablen fuer MAG
uint8_t MAG_raw[6] = {0,0,0,0,0,0};
volatile uint8_t read_MAG = 0;

//Allgemeine Konstanten
const uint8_t LED = 8;
const uint8_t div_power = 1;
const uint8_t RING_DIM = 64;

//Allgemeine Variablen
volatile uint16_t overflow = 0;

// ring buffer for binary ADC data
// 328 cpu
// the ring buffers take up a fourth of the total memory on the 328p!
volatile uint32_t ring_time[RING_DIM];
volatile int16_t ring_ACC[RING_DIM][3];
volatile int16_t ring_MAG[(RING_DIM >> div_power)][3];
volatile uint16_t ring_overflow[RING_DIM];
volatile uint8_t head = 0;
volatile uint8_t tail = 0;
volatile uint8_t next;


// number of points in the ring buffer
inline uint8_t ringAvailable() {
	return (head >= tail ? 0 : RING_DIM) + head - tail;
}
//------------------------------------------------------------------------------
// next value for head/tail
inline uint8_t ringNext(uint8_t ht) {
	return ht < (RING_DIM - 1) ? ht + 1 : 0;
}
//------------------------------------------------------------------------------


// interrupt routine for ADC read.
ISR(TIMER2_COMPA_vect) {

	// check for ring full
	next = ringNext(head);
	if (next != tail) {
		// log data
		ring_time[head] = micros();
		I2c.read(ACC_ADDRESS, ACC_X_L_CONT, (uint8_t) 6, ACC_raw);
		ring_ACC[head][0] = ACC_raw[0] | (ACC_raw[1] << 8);	//Einlesen ohne for, um ein paar ns zu sparen
		ring_ACC[head][1] = ACC_raw[2] | (ACC_raw[3] << 8);
		ring_ACC[head][2] = ACC_raw[4] | (ACC_raw[5] << 8);
		// only read out the magnetometer every 2nd pass
		// its max sample rate is only 220 Hz vs 1000 Hz for the accelerometer
		if ((head % 2) == 0)	{
			I2c.read(MAG_ADDRESS, MAG_X_H , (uint8_t) 6, MAG_raw);
			ring_MAG[(head >> div_power)][0] = (MAG_raw[0] << 8) | MAG_raw[1];
			ring_MAG[(head >> div_power)][1] = (MAG_raw[2] << 8) | MAG_raw[3];
			ring_MAG[(head >> div_power)][2] = (MAG_raw[4] << 8) | MAG_raw[5];
		}
		ring_overflow[head] = overflow;
		
		if (head % 20 == 0) PINB = 1; //LED blinken lassen
		
		head = next;
	}
	else {
		// keep track of overruns
		overflow++;
	}
	
}

void shutdown() {
	// Flight Recording Termination Jumper has been put into place
	// Cease operation and close the log file
	TIMSK2 = 0;
	bw.writeBuf();
	file.close();
	digitalWrite(LED, LOW);
	cli();
	
	while (1);
}

void setup() {
	//LED
	pinMode(LED, OUTPUT); // turn pin 8 into an output. An attached LED will blink during reads
	digitalWrite(LED, LOW);
	//Ausschalter
	pinMode(3, INPUT_PULLUP); // enable Pullup on pin 3. Connecting it to GND will close the file and stop the program
	pinMode(4, OUTPUT); // set pin 4 LOW so we can connect it via a jumper to pin 3 and close the file
	digitalWrite(4, LOW);

	//SD Karte initialisieren
	if (!sd.begin(SD_CHIP_SELECT, SPI_FULL_SPEED)) sd.initErrorHalt();
	
	// create a new file
	char name[13];
	strcpy_P(name, PSTR("LOG00.CSV"));
	for (uint8_t n = 0; n < 100; n++) {
		name[3] = '0' + n / 10;
		name[4] = '0' + n % 10;
		if (file.open(name, O_WRITE | O_CREAT | O_EXCL)) break;
	}
	
	bw.init(&file);

	
	//I2C Bus starten
	I2c.begin();
	I2c.setSpeed(1);
	I2c.pullup(1);
	
	//Ersten Beschleunigungssensor initialisieren
	#ifdef DEBUG
	Serial.println(F("Ersten Beschleunigungssensor initialisieren"));
	#endif
	I2c.write(ACC_ADDRESS, ACC_CTRL1, (uint8_t) B00110111); // normal mode, 400Hz, XYZ enabled
	I2c.write(ACC_ADDRESS, ACC_CTRL4, (uint8_t) B00110000); // +-24g
	
	
	//Magnetometer initialisieren
	#ifdef DEBUG
	Serial.println(F("Magnetometer initialisieren"));
	#endif
	I2c.write(MAG_ADDRESS, MAG_CRA, (uint8_t) B00011100); // temp disabled, 220 Hz
	I2c.write(MAG_ADDRESS, MAG_MR, (uint8_t) B00000000); // continuous conversion mode
	
	//Timer und Interrupts konfigurieren
	cli();
	TCCR2A = (1 << WGM21); // CTC mode. Counter returns to zero after compare match
	TCCR2B = 0;
	TCNT2  = 0;	//start to count from zero
	OCR2A = 156; // 2.5 ms, 400 Hz, 8 Mhz, Prescaler 128				//142;	// 2.272 ms, 440 Hz, 8 MHz, Prescaler 128				
	TCCR2B |= (1 << CS22);    // 128 prescaler
	//TCCR2B |= (1 << CS21);
	TCCR2B |= (1 << CS20);
	TIMSK2 |= (1 << OCIE2A);  // enable timer compare interrupt
	
	attachInterrupt(1, shutdown, LOW);
	sei();
}

// cluster for last sync
uint32_t syncCluster = 0;

// time of last sync
uint32_t syncTime = 0;

void loop() {
	cli();
	uint8_t n = ringAvailable();
	sei();
	
	// write a new line to the file
	for (uint8_t i = 0; i < n; i++) {
		bw.putNum(ring_time[tail]); // putNum takes everything from byte to long
		bw.putChar(','); // separate every value with a comma
		
		// insert the sensor readings
		bw.putNum(ring_ACC[tail][0]);
		bw.putChar(',');
		bw.putNum(ring_ACC[tail][1]);
		bw.putChar(',');
		bw.putNum(ring_ACC[tail][2]);
		bw.putChar(',');
		
		// even if there are no new readings we will store the old ones multiple times
		// at least we won't get inconsistencies that way
		bw.putNum(ring_MAG[(tail >> div_power)][0]);
		bw.putChar(',');
		bw.putNum(ring_MAG[(tail >> div_power)][1]);
		bw.putChar(',');
		bw.putNum(ring_MAG[(tail >> div_power)][2]);
		bw.putChar(',');

		bw.putNum(ring_overflow[tail]);
		
		bw.putCRLF(); // next run will start in a new line of the output file
		
		cli();
		tail = ringNext(tail); // and the next run will also start in a new position of the ring buffer
		sei();
	}
	
	// never sync if zero
	if (MAX_SYNC_TIME_MSEC == 0) return;
	
	if (syncCluster == file.curCluster()
	&& (millis() - syncTime) < MAX_SYNC_TIME_MSEC) return;
	
	if (!file.sync());
	syncCluster = file.curCluster();
	syncTime = millis();
}