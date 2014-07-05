template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }
	
#include <I2C.h>
#include <SdFat.h>
#include <SdFatUtil.h> // define FreeRam()
#define SD_CHIP_SELECT  SS  // SD chip select pin
#define LOG_INTERVAL  1000  // mills between entries
//#define ECHO_TO_SERIAL   1  // echo data to serial port if nonzero
#define WAIT_TO_START    1  // Wait for serial input in setup()

#define CPU_FREQ 8000000
#define DEBUG2
#define DEBUG3

//Variablen fuer SD-Card, SD
// file system object
SdFat sd;

// text file for logging
ofstream logfile;

#ifdef DEBUG
// Serial print stream
ArduinoOutStream cout(Serial);
#endif

// buffer to format data - makes it eaiser to echo to Serial
char buf[100];

// store error strings in flash to save RAM
#define error(s) sd.errorHalt_P(PSTR(s))

//Konstanten fuer Beschleunigungssensor 1, ACC1
const byte ID_ACC1 = 0xEE;
const byte ACC1_ADDRESS = B0011000;
const byte ACC1_CTRL1 = B00100000;
const byte ACC1_CTRL4 = B00100011;
//const byte ACC1_READ = B00110001; //Adresse + Read Bit
//const byte ACC1_WRITE = B00110000; //Adresse + Write Bit

//Konstanten fuer Beschleunigungssensor 2, ACC2
const byte ID_ACC2 = 0xDD;
const byte ACC2_ADDRESS = B0011001;
const byte ACC2_CTRL1 = 0x20;
//const byte ACC2_CTRL2 = 0x21;
//const byte ACC2_CTRL3 = 0x22;
const byte ACC2_CTRL4 = 0x23;
//const byte ACC2_CTRL5 = 0x24;
//const byte ACC2_CTRL6 = 0x25;

//Konstanten fuer ACC1 und ACC2
const byte ACC_CONT = B10000000; //Automatisches Inkrementieren der Registeradresse
const byte ACC_STATUS = 0x27;
const byte ACC_X_L = 0x28;
//const byte OUT_X_H = 0x29;
//const byte OUT_Y_L = 0x2A;
//const byte OUT_Y_H = 0x2B;
//const byte OUT_Z_L = 0x2C;
//const byte OUT_Z_H = 0x2D;

//Variablen fuer ACC1 und ACC2
byte ACC_stat = 0;
byte ACC_low = 0;
int ACC_raw[3] = {0,0,0};
uint8_t ACC_raw2[6] = {0,0,0,0,0,0};


//Konstanten fuer Magnetometer, MAG
const byte ID_MAG = 0xBB;
const byte MAG_ADDRESS = B0011110;
const byte MAG_CRA = 0x00;
const byte MAG_CRB = 0x01;
const byte MAG_MR = 0x02;
const byte MAG_X_H = 0x03;
const byte MAG_SR = 0x09;

//Variablen fuer MAG
byte MAG_high = 0;
int MAG_raw[3] = {0,0,0};
uint8_t MAG_raw2[6] = {0,0,0,0,0,0};

//Konstanten fuer Temperatursensor, THM
const byte ID_THM = 0x77;
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
const uint8_t ACC1_1_init = B10101111;

// ACC1_2
// Bit 0		:	1
// Bit 1-3	: 011, ID
// Bit 4-7	:	ACC_dataLost()
// Bit 8-15	: 8bit Y_L
// Bit 16-31:	16bit Z
// ACC1_2;
const uint8_t ACC1_2_init = B10111111;

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
const uint8_t MAG_2_init = B11111111;


//Allgemeine Variablen
byte i=0;
unsigned long time_last = 0;
uint8_t counter = 0;

//Temp
unsigned long temp;
unsigned long temp2;
uint32_t time_before_temp;
uint32_t time_temp;
uint32_t time_before_read;
uint32_t time_before_start;
uint32_t time_before_dataLost;
uint32_t time_dataAvailable;
uint32_t time_dataRead;
uint32_t time_dataLost;

void setup() {
	#ifdef DEBUG
	Serial.begin(115200);
	#endif
	#ifdef DEBUG2
	Serial.begin(115200);
	#endif
//        #ifdef DEBUG3
//        Serial.begin(115200);
//        #endif
	//LED
	pinMode(LED, OUTPUT);
	//SD Karte initialisieren
	#ifdef DEBUG
	// pstr stores strings in flash to save RAM
	cout << endl << pstr("FreeRam: ") << FreeRam() << endl;
	#endif
	// initialize the SD card at SPI_HALF_SPEED to avoid bus errors with
	if (!sd.begin(SD_CHIP_SELECT, SPI_FULL_SPEED)) sd.initErrorHalt();
	
	// create a new file in root, the current working directory
	char name[] = "LOGGER00.CSV";
	for (uint8_t i = 0; i < 100; i++) {
		name[6] = i/10 + '0';
		name[7] = i%10 + '0';
		if (sd.exists(name)) continue;
		logfile.open(name);
		break;
	}
	if (!logfile.is_open()) error("file.open");
	
	#ifdef DEBUG
	cout << pstr("Logging to: ") << name << endl;
	cout << pstr("Type any character to stop\n\n");
	#endif
	
	// format header in buffer
	obufstream bout(buf, sizeof(buf));
	bout << pstr("millis");
	bout << pstr(": Logger wurde gestartet.");
	logfile << buf << endl;
	
	#ifdef ECHO_TO_SERIAL
	cout << buf << endl;
	#endif  // ECHO_TO_SERIAL
	
	//I2C Bus starten
	I2c.begin();
	I2c.setSpeed(1);
  I2c.pullup(1);
	
	//Ersten Beschleunigungssensor initialisieren
	#ifdef DEBUG
		Serial.println(F("Ersten Beschleunigungssensor initialisieren"));
	#endif
        I2c.write(ACC1_ADDRESS, ACC1_CTRL1, (uint8_t) B00110111); //Normal, 400Hz, XYZ enabled
        I2c.write(ACC1_ADDRESS, ACC1_CTRL4, (uint8_t) B00110000); //Wertebereich +-24g
//	Wire.beginTransmission(ACC1_ADDRESS);
//	Wire.write(ACC1_CTRL1);
//	Wire.write(B00110111);  //Normal, 400Hz, XYZ enabled
//	Wire.endTransmission(rTrue);
//	Wire.beginTransmission(ACC1_ADDRESS);
//	Wire.write(ACC1_CTRL4);
//	Wire.write(B00110000);  //Wertebereich +-24g
//	Wire.endTransmission(rTrue);
	
	//Zweiten Beschleunigungssensor initialisieren
	#ifdef DEBUG
		Serial.println(F("Zweiten Beschleunigungssensor initialisieren"));
	#endif
//	Wire.beginTransmission(ACC2_ADDRESS);
//	Wire.write(ACC2_CTRL1);
//	Wire.write(B01110111);  //Normal, 400Hz, XYZ enabled
//	Wire.endTransmission(rTrue);
//	Wire.beginTransmission(ACC2_ADDRESS);
//	Wire.write(ACC2_CTRL4);
//	Wire.write(B00111000); //Wertebereich +-16g
//	Wire.endTransmission(rTrue);
	
	//Magnetometer initialisieren
	#ifdef DEBUG
		Serial.println(F("Magnetometer initialisieren"));
	#endif
        I2c.write(MAG_ADDRESS, MAG_CRA, (uint8_t) B10011100);
        I2c.write(MAG_ADDRESS, MAG_MR, (uint8_t) B00000000);
//  	Wire.beginTransmission(MAG_ADDRESS);
//  	Wire.write(MAG_CRA);
//  	Wire.write(B10011100);  //Temp enabled, 220 Hz
//  	Wire.endTransmission(rTrue);
//  	Wire.beginTransmission(MAG_ADDRESS);
//  	Wire.write(MAG_MR);
//  	Wire.write(B00000000); //Continuous Conversion mode
//  	Wire.endTransmission(rTrue);
	
	#ifdef DEBUG
	Serial.println(F("Initialisierung abgeschlossen"));
	#endif
}

void loop() {
	#ifdef DEBUG2
		Serial << "{TIMEPLOT|data|Interval|T|" << millis()-time_last << "}\n";
		Serial << "{TIMEPLOT|data|Free Ram|T|" << FreeRam() << "}\n";
		time_last = millis();
	#endif
		
	// use buffer stream to format line
	obufstream bout(buf, sizeof(buf));
	
        time_before_temp = micros();
        temp = (uint32_t) ( ((uint8_t) ((TIME_init| ((++counter) & 0x0F))) << 24) | millis());
        time_temp = micros() - time_before_temp;
        #ifdef DEBUG3
                  Serial << "{TIMEPLOT|data|TIME_time_compose|T|" << time_temp << "}\n";
        #endif
        
        #ifdef DEBUG2
                  Serial << "{TIMEPLOT|data|time_compose|T|" << temp << "}\n";
        #endif

	//Daten einlesen
	//ACC1

        time_before_start=micros();
	if( 1 /*ACC_dataAvailable(ACC1_ADDRESS)*/) {
                time_dataAvailable = micros() - time_before_start;
		PINB = 1; //LED blinken lassen
		bout << "ACC1," << millis();  //belegt 13 Eintraege in buf
		#ifdef DEBUG
			Serial.println(F("ACC1 hat neue Daten"));
		#endif
                time_before_read = micros();
		I2c.read(ACC1_ADDRESS, (uint8_t) (ACC_CONT | ACC_X_L) , (uint8_t) 6, ACC_raw2);
                time_dataRead = micros() - time_before_read;
                
                time_before_temp = micros();
                temp = (((uint8_t) ACC1_1_init) * 16777216) + (((uint8_t) ACC_raw2[0]) * 65536) + (((uint8_t) ACC_raw2[1]) * 256) + ((uint8_t) ACC_raw2[2]);
                temp2 = 0;
								temp2 = (ACC1_2_init * 16777216) | ((ACC_raw2[3]) << 16) | (ACC_raw2[4] << 8) | ACC_raw2[5];
                time_temp = micros() - time_before_temp;
                #ifdef DEBUG2
                          Serial << "{TIMEPLOT|data|ACC1_1_compose|T|" << temp << "}\n";
                          Serial << "{TIMEPLOT|data|ACC1_2_compose|T|" << temp2 << "}\n";
                          /*Serial << "{TIMEPLOT|data|ACC1_2A_compose|T|" << ((uint16_t) (temp2 >> 16)) << "}\n";
                          Serial << "{TIMEPLOT|data|ACC1_2B_compose|T|" << ((uint16_t) temp2) << "}\n";*/
													/*Serial << "{MESSAGE|data|" << ACC1_1_init << "," << ACC_raw2[0] << "," << ACC_raw2[1] << "," << ACC_raw2[2] << "}";
													Serial << "{MESSAGE|data|" << (temp >> 24) << "}";
													Serial << "{MESSAGE|data|" << ((temp << 8) >> 24) << "}";
													Serial << "{MESSAGE|data|" << ((temp << 16) >> 24) << "}";
													Serial << "{MESSAGE|data|" << ((temp << 24) >> 24) << "}";*/
													Serial << "{MESSAGE|data|" << ACC1_2_init << "," << ACC_raw2[3] << "," << ACC_raw2[4] << "," << ACC_raw2[5] << "}";
													Serial << "{MESSAGE|data|" << (temp2 >> 24) << "}";
													Serial << "{MESSAGE|data|" << (((temp2 << 8) >> 24)) << "}";
													Serial << "{MESSAGE|data|" << ((temp2 << 16) >> 24) << "}";
													Serial << "{MESSAGE|data|" << ((temp2 << 24) >> 24) << "}";
                #endif
                #ifdef DEBUG3
                          Serial << "{TIMEPLOT|data|TIME_ACC1_compose|T|" << time_temp << "}\n";
                #endif
                
		for (i=0; i<5; i+=2) {  //belegt 9 Eintraege in buf
			bout << "," << (int16_t) (ACC_raw2[i] | (ACC_raw2[i+1] << 8));
			#ifdef DEBUG2
				/*Serial << "{TIMEPLOT|data|ACC1_" << i << "|T|" << ((int16_t) (ACC_raw2[i] | (ACC_raw2[i+1] << 8))) << "}\n";
			  Serial << "{MESSAGE|data|" << ACC_raw2[i] << "," << (uint8_t) ACC_raw2[i+1] << "}";*/
      #endif
		}
                time_before_dataLost = micros();
                uint8_t dataLost = ACC_dataLost();
                time_dataLost = micros() - time_before_dataLost;
                
		bout << "," << (unsigned int) dataLost << endl;  //belegt 3 Eintraege
		
                #ifdef DEBUG3
                  Serial << "{TIMEPLOT|data|ACC_dataRead|T|" << time_dataRead << "}\n";
                #endif
		#ifdef ECHO_TO_SERIAL
		cout << buf;
		#endif  // ECHO_TO_SERIAL
		
		// log data and flush to SD
		//logfile << buf << flush;
	}
	
	//ACC2
//  	if(ACC_dataAvailable(ACC2_ADDRESS)) {
//  		PINB = 1; //LED blinken lassen
//  		bout << "ACC2," << millis();  //belegt 13 Eintraege in buf
//  		#ifdef DEBUG
//  			Serial.println(F("ACC2 hat neue Daten"));
//  		#endif
//  		if(ACC_dataRead(ACC2_ADDRESS)) {
//  			for (i=0; i<3; i++) {  //belegt 9 Eintraege
//  				bout << "," << (ACC_raw[i] >> 4);
//  				#ifdef DEBUG2
//  					Serial << "{TIMEPLOT|data|ACC2_" << i << "|T|" << (ACC_raw[i] >> 4) << "}\n";
//  				#endif
//  			}
//  		}
//  		bout << "," << (unsigned int) ACC_dataLost() << endl; //belegt 3 Eintraege
//  		
//  		#ifdef ECHO_TO_SERIAL
//  		cout << buf << endl;
//  		#endif  // ECHO_TO_SERIAL
//  		
//  		// log data and flush to SD
//  		//logfile << buf << flush;
//  	}
//  	
  	/*//MAG und THM
  	if( 1 / *MAG_dataAvailable()* / ) {
  		PINB = 1; //LED blinken lassen
  		bout << "MAG," << millis();  //belegt 12 Eintraege in buf
  		#ifdef DEBUG
  			Serial.println(F("MAG hat neue Daten"));
  		#endif
                time_before_read = micros();
  		I2c.read(MAG_ADDRESS, MAG_X_H , (uint8_t) 6, MAG_raw2);
                time_dataRead = micros() - time_before_read;
                
                time_before_temp = micros();
                temp = (uint32_t) ((MAG_1_init << 24) | (MAG_raw2[1] << 16) | (MAG_raw2[0] << 8) | MAG_raw2[3]);
                temp2 = (uint32_t) ((MAG_2_init << 24) | (MAG_raw2[2] << 16) | (MAG_raw2[5] << 8) | MAG_raw2[4]);
                time_temp = micros() - time_before_temp;
                #ifdef DEBUG2
                          Serial << "{TIMEPLOT|data|MAG_1_compose|T|" << temp << "}\n";
                          Serial << "{TIMEPLOT|data|MAG_2_compose|T|" << temp2 << "}\n";
                #endif
                #ifdef DEBUG3
                          Serial << "{TIMEPLOT|data|TIME_MAG_compose|T|" << time_temp << "}\n";
                #endif
                
			for (i=0; i<5; i+=2) {  //belegt 9 Eintraege
				bout << "," << (int16_t) ((MAG_raw2[i] << 8) | MAG_raw2[i+1]);
				#ifdef DEBUG2
					Serial << "{TIMEPLOT|data|MAG_" << i << "|T|" << (int16_t) ((MAG_raw2[i] << 8) | MAG_raw2[i+1]) << "}\n";
				#endif
			}
			bout << "," << "THM" << "," << THM_raw << endl;  //belegt 8 Eintraege
			#ifdef DEBUG2
				Serial << "{TIMEPLOT|data|THM|T|" << THM_raw << "}\n";
			#endif
  		#ifdef DEBUG3
                  Serial << "{TIMEPLOT|data|MAG_dataRead|T|" << time_dataRead << "}\n";
                #endif
  		#ifdef ECHO_TO_SERIAL
  		cout << buf << endl;
  		#endif  // ECHO_TO_SERIAL
//  		
//  		// log data and flush to SD
//  		//logfile << buf << flush;
  	}
  	*/

	
	
	// log data and flush to SD
	logfile << buf << flush;
	
	#ifdef DEBUG
	// check for error
	if (!logfile) error("write data failed");
	#endif
	
	#ifdef ECHO_TO_SERIAL
	cout << buf;
	#endif  // ECHO_TO_SERIAL
	
	#ifdef DEBUG
	if (Serial.available()) {
		logfile.close();
		cout << pstr("Done!");
		while(1);
	}
	#endif
}
	
//byte ACC_dataAvailable(byte ACC_ADDRESS) {
//        ACC_stat = I2c.read(ACC_ADDRESS, ACC_STATUS, (uint8_t) 1);
//	Wire.beginTransmission(ACC_ADDRESS);
//	Wire.write(ACC_STATUS);
//	Wire.endTransmission(false);
//	Wire.requestFrom(ACC_ADDRESS, singleByte);
//	ACC_stat = Wire.read();
//	return bitRead(ACC_stat,3);
//}

//void ACC_dataRead(byte ACC_ADDRESS) {
//        I2c.read(ACC_ADDRESS, (uint8_t) (ACC_CONT | ACC_X_L) , (uint8_t) 6, ACC_raw2);
//        for (i=0; i<6; i++) {
//          ACC_raw2[i] = I2c.receive();
//        }
//	Wire.beginTransmission(ACC_ADDRESS);
//	Wire.write(ACC_CONT | ACC_X_L);
//	Wire.endTransmission(false);
//	Wire.requestFrom(ACC_ADDRESS, readByteCount);
//	i = 0;
//	while(Wire.available() > 1){
//		//ACC_low = Wire.read();
//		ACC_raw[i] = Wire.read() | (Wire.read()<<8);
//		i++;
//	}
//}

byte ACC_dataLost() {
	return (ACC_stat >> 4);
}

//byte MAG_dataAvailable() {
//	Wire.beginTransmission(MAG_ADDRESS);
//	Wire.write(MAG_SR);
//	Wire.endTransmission(rFalse);
//	Wire.requestFrom(MAG_ADDRESS, singleByte, rTrue);
//	if (Wire.available()) {
//		return bitRead(Wire.read(),0);
//	}
//	else return 0;
//}
//
//void MAG_dataRead() {
//  
//	Wire.beginTransmission(MAG_ADDRESS);
//	Wire.write(MAG_X_H);
//	Wire.endTransmission(rFalse);
//	Wire.requestFrom(MAG_ADDRESS, readByteCount, rTrue);
//	i = 0;
//	while(Wire.available() > 1){
//		MAG_high = Wire.read();
//		MAG_raw[i] = Wire.read() | (MAG_high<<8);
//		i++;
//	}
//	Wire.beginTransmission(MAG_ADDRESS);
//	Wire.write(MAG_THM_H);
//	Wire.endTransmission(false);
//	Wire.requestFrom(MAG_ADDRESS, THM_readByteCount, rTrue);
//	while(Wire.available()) {
//		THM_raw = (Wire.read() << 4) | (Wire.read() >> 4);
//		if (THM_raw > 200 | THM_raw < 0)	{
//			THM_raw = THM_last;
//		}
//		else THM_last = THM_raw;
//	}
//	return 1;
//}
