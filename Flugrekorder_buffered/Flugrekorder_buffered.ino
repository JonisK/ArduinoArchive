template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#define CPU_FREQ 8000000	
#include <I2C.h>

#include <BufferedWriter.h>
#include <SdFat.h>
#include <SdFatUtil.h> // define FreeRam()
#define SD_CHIP_SELECT  SS  // SD chip select pin
#define LOG_INTERVAL  1000  // mills between entries
//#define ECHO_TO_SERIAL   1  // echo data to serial port if nonzero
#define WAIT_TO_START    1  // Wait for serial input in setup()
// led to indicate overrun occured, set to -1 if no led.
const int8_t RED_LED_PIN = 8;
// interval between timer interrupts in microseconds
const uint16_t TICK_TIME_USEC = 1000;
// number of ticks between data points
const uint16_t TICK_LOG_COUNT = 5;
// interval in usec between data points.
const uint32_t LOG_INTERVAL_USEC = (uint32_t)TICK_TIME_USEC * TICK_LOG_COUNT;
// Maximum time between sync() calls in milliseconds.  If MAX_SYNC_TIME_MSEC is
// set to zero, sync will only be called when a character is typed to stop the
// program.  This allows the fastest possible rate.
const uint32_t MAX_SYNC_TIME_MSEC = 1000;
// To get the fastest rate set LOG_DATA_IN_HEX true and MAX_SYNC_TIME_MSEC zero.
const bool LOG_DATA_IN_HEX = false;

#include <TimerTwo.h>



//#define DEBUG
#define DEBUG2

enum {TIME_0, TIME_1, TIME_2, TIME_3, ACC_0, ACC_1, ACC_2, ACC_3, ACC_4, ACC_5, ACC_6, MAG_0, MAG_1, MAG_2, MAG_3, MAG_4, MAG_5, MAG_6 };

//Variablen fuer SD-Card, SD
// file system object
SdFat sd;
// file for logging data
SdFile file;
// fast text formatter
BufferedWriter bw;
//------------------------------------------------------------------------------
// store error strings in flash
#define error(s) sd.errorHalt_P(PSTR(s));
//------------------------------------------------------------------------------
// ring buffer for binary ADC data
// 328 cpu
const uint16_t RING_DIM = 400;
uint8_t ring[RING_DIM];
volatile uint16_t head = 0;
volatile uint16_t tail = 0;
//------------------------------------------------------------------------------


//Konstanten für Beschleunigungssensor 1, ACC1
const byte ACC1_ADDRESS = B0011000;

//Konstanten fuer Beschleunigungssensor 2, ACC2
const byte ACC2_ADDRESS = B0011001;

//Konstanten fuer ACC1 und ACC2
const byte ACC_CONT = B10000000; //Automatisches Inkrementieren der Registeradresse
const byte ACC_CTRL1 = B00100000;
const byte ACC_CTRL4 = B00100011;
const byte ACC_STATUS = 0x27;
const byte ACC_X_L = 0x28;

//Variablen fuer ACC1 und ACC2
byte ACC_stat = 0;
byte ACC_low = 0;
uint8_t ACC_raw[6] = {0,0,0,0,0,0};


//Konstanten fuer Magnetometer, MAG
const byte MAG_ADDRESS = B0011110;
const byte MAG_CRA = 0x00;
const byte MAG_CRB = 0x01;
const byte MAG_MR = 0x02;
const byte MAG_X_H = 0x03;
const byte MAG_SR = 0x09;

//Variablen fuer MAG
byte MAG_high = 0;
uint8_t MAG_raw[6] = {0,0,0,0,0,0};

//Konstanten fuer Temperatursensor, THM
const byte MAG_THM_H = 0x31;
const byte MAG_THM_L = 0x32;

//Variablen fuer THM
byte THM_high = 0;
unsigned int THM_raw = 0;
unsigned int THM_last = 0;

//Allgemeine Konstanten
const byte readByteCount = 6;
const byte THM_readByteCount = 2;
const byte singleByte = 1;
const byte rTrue = 1;
const byte rFalse = 1;
const byte LED = 8;
//Structs
// TIME
// Bit 0		:	1
// Bit 1-3	: 001, ID
// Bit 4-7	: 4bit Zaehler
// Bit 8-31	: millis(), laeuft nach 4 Stunden ueber
//uint32_t TIME;
const uint8_t TIME_init = B10010000;

// ACC1_1
// Bit 0		:	1
// Bit 1-3	: 010, ID
// Bit 4-7	: 1111
// Bit 8-23	: 16bit X
// Bit 24-31:	8bit Y_H
//uint32_t ACC1_1;
const uint8_t ACC_1_init = B10101111;

// ACC1_2
// Bit 0		:	1
// Bit 1-3	: 011, ID
// Bit 4-7	:	ACC_dataLost()
// Bit 8-15	: 8bit Y_L
// Bit 16-31:	16bit Z
// ACC1_2;
const uint8_t ACC1_2_init = B10110000;

// ACC2_1
// Bit 0		:	1
// Bit 1-3	: 100, ID
// Bit 4-7	:	1111
// Bit 8-19	: 12bit X
// Bit 20-31:	12bit Y
//uint32_t ACC2_1;
const uint8_t ACC2_1_init = B11001111;

// ACC2_2
// Bit 0		:	1
// Bit 1-3	: 101, ID
// Bit 4-7	:	ACC_dataLost()
// Bit 8-19	: 12bit Z
// Bit 20-31:	0xFFF
//uint32_t ACC2_2;
const uint8_t ACC2_2_init = B11001111;

// MAG_1
// Bit 0		:	1
// Bit 1-3	: 110, ID
// Bit 4-7	:	1111
// Bit 8-19	: 12bit X
// Bit 20-31:	12bit Y
//uint32_t MAG_1;
const uint8_t MAG_1_init = B11101111;

// MAG_2
// Bit 0		:	1
// Bit 1-3	: 111, ID
// Bit 4-7	:	0000
// Bit 8-19	: 12bit Z
// Bit 20-31:	12bit THM
//uint32_t MAG_1;
const uint8_t MAG_2_init = B11110000;

//Allgemeine Variablen
byte i = 0;
volatile uint32_t this_time = 0;
volatile uint8_t order = 0;
volatile uint8_t counter = 0;
volatile uint8_t k = 0;

//Temp
volatile uint32_t cycle_time = 0;
volatile uint32_t cycle_time_pre = 0;
volatile uint32_t ACC_time = 0;
volatile uint32_t ACC_time_pre = 0;

// number of points in the ring buffer
inline uint16_t ringAvailable() {
	return (head >= tail ? 0 : RING_DIM) + head - tail;
}
//------------------------------------------------------------------------------
// next value for head/tail
inline uint16_t ringNext(uint16_t ht) {
	return ht < (RING_DIM - 1) ? ht + 1 : 0;
}
//------------------------------------------------------------------------------
// interrupt routine for ADC read.
ISR(TIMER2_COMPA_vect) {
	
	// ticks until time to log a data point
	static uint16_t ticks = 0;
	
	// return if not time to log data
	if (ticks-- > 1) return;
	
	// reset tick count
	ticks = TICK_LOG_COUNT;
	
	// check for ring full
	uint16_t next = ringNext(head);
	if (next != tail) {
		// log data
		switch (order) {
			case TIME_0:
				ring[head] = (uint8_t) ( TIME_init | ((++counter) & 0x0F));
				this_time = millis();
				cycle_time_pre = micros();
				order++;
				break;
			case TIME_1:
				ring[head] = this_time & 0x00FF0000;
				order++;
				break;
			case TIME_2:
				ring[head] = this_time & 0x0000FF00;
				order++;
				break;
			case TIME_3:
				ring[head] = this_time & 0x000000FF;
				order++;
				break;
			case ACC_0:
				ACC_time_pre = micros();
				I2c.read(ACC1_ADDRESS, (uint8_t) (ACC_CONT | ACC_X_L), (uint8_t) 6, ACC_raw);
				ring[head] = ACC_1_init;
				order++;
				break;
			case ACC_1:
				ring[head] = ACC_raw[k++];
				order++;
				break;
			case ACC_2:
				ring[head] = ACC_raw[k++];
				order++;
				break;
			case ACC_3:
				ring[head] = ACC_raw[k++];
				order++;
				break;
			case ACC_4:
				ring[head] = ACC_raw[k++];
				order++;
				break;
			case ACC_5:
				ring[head] = ACC_raw[k++];
				order++;
				break;
			case ACC_6:
				ring[head] = ACC_raw[k++];
				order++;
				k = 0;
				ACC_time = micros() - ACC_time_pre;
				break;
			case MAG_0:
				I2c.read(MAG_ADDRESS, MAG_X_H , (uint8_t) 6, MAG_raw);
				ring[head] = MAG_1_init;
				order++;
				break;
			case MAG_1:
				ring[head] = MAG_raw[k++];
				order++;
				break;
			case MAG_2:
				ring[head] = MAG_raw[k++];
				order++;
				break;
			case MAG_3:
				ring[head] = MAG_raw[k++];
				order++;
				break;
			case MAG_4:
				ring[head] = MAG_raw[k++];
				order++;
				break;
			case MAG_5:
				ring[head] = MAG_raw[k++];
				order++;
				break;
			case MAG_6:
				ring[head] = MAG_raw[k++];
				order = 0;
				k = 0;
				PINB = 1; //LED blinken lassen
				cycle_time = micros() - cycle_time_pre;
				break;
			default:
				order = 0;
				break;
		}
		/*if (order) {
			ring[head] = analogRead(A1);
			order = 0;
		}
		else {
			ring[head] = millis();
			order = 1;
		}*/
		head = next;
	} 
	else {
		//do something about these overruns!
	}
}

void shutdown() {
	// Flight Recording Termination Jumper has been put into place
	// Cease operation and close the log file
	digitalWrite(RED_LED_PIN, LOW);
	TimerTwo::stop();
	bw.writeBuf();
	if (!file.close()) error("file.close");
	cli();
	PgmPrintln("Stopped!");
	while (1);
}

void setup() {
	#ifdef DEBUG
	Serial.begin(115200);
	#endif
	#ifdef DEBUG2
	Serial.begin(115200);
	#endif
	//LED
	if (RED_LED_PIN >=0) {
		pinMode(RED_LED_PIN, OUTPUT);
		digitalWrite(RED_LED_PIN, LOW);
	}
	//Ausschalter
	pinMode(3, INPUT_PULLUP);
	pinMode(4, OUTPUT);
	digitalWrite(4, LOW);
	//Timer und Interrupts konfigurieren
	// set tick time
	if (!TimerTwo::init(TICK_TIME_USEC)
	|| TICK_TIME_USEC != TimerTwo::period()) {
		// TICK_TIME_USEC is too large or period rounds to a different value
		#ifdef DEBUG
			error("TimerTwo::init");
		#endif
	}
	noInterrupts();
	attachInterrupt(1, shutdown, LOW);
	interrupts();
	#ifdef DEBUG
		PgmPrint("FreeRam: ");
		Serial.println(FreeRam());
		PgmPrint("Log Interval: ");
		Serial.print(LOG_INTERVAL_USEC);
		PgmPrintln(" usec");
	#endif
	
	//SD Karte initialisieren

	// initialize the SD card
	if (!sd.begin(SD_CHIP_SELECT, SPI_FULL_SPEED)) sd.initErrorHalt();
	
	// create a new file
	char name[13];
	strcpy_P(name, PSTR("BFAST00.LOG"));
	for (uint8_t n = 0; n < 100; n++) {
		name[5] = '0' + n / 10;
		name[6] = '0' + n % 10;
		if (file.open(name, O_WRITE | O_CREAT | O_EXCL)) break;
	}
	if (!file.isOpen()) error("file.open");
	
	file.write_P(PSTR("Log Interval usec: "));
	file.println(LOG_INTERVAL_USEC);
	
	bw.init(&file);
	
	#ifdef DEBUG
		PgmPrint("Logging to: ");
		Serial.println(name);
		PgmPrintln("Put the flight recording termination jumper in place to stop.");
	#endif
	
	//I2C Bus starten
	I2c.begin();
	I2c.setSpeed(1);
	I2c.pullup(1);
	
	//Ersten Beschleunigungssensor initialisieren
	#ifdef DEBUG
		Serial.println(F("Ersten Beschleunigungssensor initialisieren"));
	#endif
	I2c.write(ACC1_ADDRESS, ACC_CTRL1, (uint8_t) B00110111); //Normal, 400Hz, XYZ enabled
	I2c.write(ACC1_ADDRESS, ACC_CTRL4, (uint8_t) B00110000); //Wertebereich +-24g
	
	
	//Magnetometer initialisieren
	#ifdef DEBUG
		Serial.println(F("Magnetometer initialisieren"));
	#endif
	I2c.write(MAG_ADDRESS, MAG_CRA, (uint8_t) B10011100); //Temp enabled, 220 Hz
	I2c.write(MAG_ADDRESS, MAG_MR, (uint8_t) B00000000); //Continuous Conversion mode
	
	#ifdef DEBUG
		Serial.println(F("Initialisierung abgeschlossen"));
		delay(10);
	#endif
	
	// start calls to ISR
	TimerTwo::start();
}

// cluster for last sync
uint32_t syncCluster = 0;

// time of last sync
uint32_t syncTime = 0;

void loop() {
	// 16-bit memory read is not atomic so disable interrupts
  cli();
  uint16_t n = ringAvailable();
  sei();
  
  for (uint16_t i = 0; i < n; i++) {
    // get data point
    uint8_t d = ring[tail];

    // disable interrupts since 16-bit store is not atomic
    cli();
    tail = ringNext(tail);
    sei();
    
    // format the data point
		/*if ((d >> 4) = 0x09) bw.putCRLF();*/
		bw.putNum(d);
		bw.putCRLF();
		
		#ifdef DEBUG2
			Serial.println(cycle_time);
			Serial.println(ACC_time);
		#endif
  }
  // check for write error
  if (file.writeError) error("write");

  // never sync if zero
  if (MAX_SYNC_TIME_MSEC == 0) return;
  
  if (syncCluster == file.curCluster()
    && (millis() - syncTime) < MAX_SYNC_TIME_MSEC) return;
    
  if (!file.sync()) error("file.sync");
  syncCluster = file.curCluster();
  syncTime = millis();	
}