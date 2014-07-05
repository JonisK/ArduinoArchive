#include <Wire.h>

#include <SdFat.h>
#include <SdFatUtil.h> // define FreeRam()
#define SD_CHIP_SELECT  SS  // SD chip select pin
#define LOG_INTERVAL  1000  // mills between entries
#define ECHO_TO_SERIAL   1  // echo data to serial port if nonzero
#define WAIT_TO_START    1  // Wait for serial input in setup()

#define DEBUG

//Variablen fuer SD-Card, SD
// file system object
SdFat sd;

// text file for logging
ofstream logfile;

#IF DEBUG
  // Serial print stream
  ArduinoOutStream cout(Serial);
#ENDIF

// buffer to format data - makes it eaiser to echo to Serial
char buf[80];

// store error strings in flash to save RAM
#define error(s) sd.errorHalt_P(PSTR(s))

//Konstanten für Beschleunigungssensor 1, ACC1
const byte ACC1_ADDRESS = B0011000;
const byte ACC1_CTRL1 = B00100000;
const byte ACC1_CTRL4 = B00100011;
//const byte ACC1_READ = B00110001; //Adresse + Read Bit
//const byte ACC1_WRITE = B00110000; //Adresse + Write Bit

//Konstanten fuer Beschleunigungssensor 2, ACC2
const byte ACC2_ADDRESS = B0011001;
const byte ACC2_CTRL1 = 0x20;
//const byte ACC2_CTRL2 = 0x21;
//const byte ACC2_CTRL3 = 0x22;
const byte ACC2_CTRL4 = 0x23;
//const byte ACC2_CTRL5 = 0x24;
//const byte ACC2_CTRL6 = 0x25;

//Konstanten fuer ACC1 und ACC2
const byte ACC_CONT = B10000000; //Automatisches Inkrementieren der Registeradresse
const byte STATUS_REG = 0x27;
const byte OUT_X_L = 0x28;
//const byte OUT_X_H = 0x29;
//const byte OUT_Y_L = 0x2A;
//const byte OUT_Y_H = 0x2B;
//const byte OUT_Z_L = 0x2C;
//const byte OUT_Z_H = 0x2D;

//Variablen fuer ACC1 und ACC2
byte ACC_low = 0;
unsigned int ACC_raw[3] = {0,0,0};


//Konstanten fuer Magnetometer, MAG
const byte MAG_ADDRESS = B0111110;
const byte MAG_CRA = 0x00;
const byte MAG_CRB = 0x01;
const byte MAG_MR = 0x02;
const byte MAG_X_H = 0x03;
const byte MAG_SR = 0x09;

//Variablen fuer MAG
byte MAG_high = 0;
unsigned int MAG_raw[3] = {0,0,0};

//Konstanten fuer Temperatursensor, THM
const byte MAG_THM_H = 0x31;
const byte MAG_THM_L = 0x32;

//Variablen fuer THM

//Allgemeine Konstanten

//Allgemeine Variablen
byte i=0;

//Temp

void setup() {
  #IF DEBUG
    Serial.begin(115200);
  #ENDIF
  //SD Karte initialisieren
  #IF DEBUG
    // pstr stores strings in flash to save RAM
    cout << endl << pstr("FreeRam: ") << FreeRam() << endl;
  #ENDIF
  // initialize the SD card at SPI_HALF_SPEED to avoid bus errors with
  if (!sd.begin(SD_CHIP_SELECT, SPI_HALF_SPEED)) sd.initErrorHalt();
  
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
  
  #IF DEBUG
    cout << pstr("Logging to: ") << name << endl;
    cout << pstr("Type any character to stop\n\n");
  #ENDIF
  
  // format header in buffer
  obufstream bout(buf, sizeof(buf));
  bout << pstr("millis");
  bout << pstr(": Logger wurde gestartet.");
  logfile << buf << endl;
  
  #IF ECHO_TO_SERIAL
    cout << buf << endl;
  #ENDIF  // ECHO_TO_SERIAL
  
  //I2C Bus starten
  Wire.begin();
  
  //Beschleunigungssensor initialisieren
  Wire.beginTransmission(ACC1_ADDRESS);
  Wire.write(CTRL_REG1);
  Wire.write(B00110111);  //Normal, 400Hz, XYZ enabled
  Wire.endTransmission(true);
  Wire.beginTransmission(ACC1_ADDRESS);
  Wire.write(CTRL_REG4);
  Wire.write(B00110000);  //Wertebereich +-24g
  Wire.endTransmission(true);
  
  //Zweiten Beschleunigungssensor initialisieren
  Wire.beginTransmission(ACC2_ADDRESS);
  Wire.write(ACC2_CTRL1);
  Wire.write(B01110111);  //Normal, 400Hz, XYZ enabled
  Wire.endTransmission(true);
  Wire.beginTransmission(ACC2_ADDRESS);
  Wire.write(ACC2_CTRL4);
  Wire.write(B00110000); //Wertebereich +-16g
  Wire.endTransmission(true);
  
  //Magnetometer initialisieren
  Wire.beginTransmission(MAG_ADDRESS);
  Wire.write(MAG_CRA);
  Wire.write(B10011100);  //Temp enabled, 220 Hz
  Wire.endTransmission(true);
  Wire.beginTransmission(MAG_ADDRESS);
  Wire.write(MAG_MR);
  Wire.write(B00000000); //Continuous Conversion mode
  Wire.endTransmission(true);
  
  //Temperatursensor initialisieren
}

void loop() {

  // use buffer stream to format line
  obufstream bout(buf, sizeof(buf));
  
  //Daten einlesen
  //ACC1
  bout << "ACC1," << millis();  //belegt 13 Eintraege in buf
  if(ACC_dataAvailable(ACC1_ADDRESS)) {
    ACC_readData(&bout, ACC1_ADDRESS);  //belegt 9 Eintraege
    bout << ACC_dataLost(ACC1_ADDRESS) << endl;  //belegt 2 Eintraege
    
    // log data and flush to SD
    logfile << buf << flush;  
  }
  
  //ACC2
  bout << "ACC2," << millis();  //belegt 13 Eintraege in buf
  if(ACC_dataAvailable(ACC2_ADDRESS)) {
    ACC_readData(&bout, ACC2_ADDRESS);  //belegt 9 Eintraege
    bout << ACC_dataLost(ACC2_ADDRESS) << endl; //belegt 2 Eintraege
    
    // log data and flush to SD
    logfile << buf << flush;  
  }
  
  //MAG
  bout << "MAG," << millis();  //belegt 12 Eintraege in buf
  if(MAG_dataAvailable()) {
    MAG_readData(&bout);  //belegt 9 Eintraege
    bout << endl; //belegt 2 Eintraege
    
    // log data and flush to SD
    logfile << buf << flush;  
  }
  

  
  
  // log data and flush to SD
  logfile << buf << flush;
  
  #IF DEBUG
    // check for error
    if (!logfile) error("write data failed");
  #ENDIF
  
  #IF ECHO_TO_SERIAL
    cout << buf;
  #ENDIF  // ECHO_TO_SERIAL
  
  #IF DEBUG
    if (Serial.available()) {
    logfile.close();
    cout << pstr("Done!");
    while(1);
  #ENDIF
}

void ACC_dataRead(char *bout, byte ACC_ADDRESS) {
  Wire.beginTransmission(ACC_ADDRESS);
  Wire.write(ACC_CONT | OUT_X_L);
  Wire.endTransmission(false);
  Wire.requestFrom(ACC_ADDRESS, 6, true);
  i = 0;
  while(Wire.available() > 1){
    ACC_low = Wire.read();
    ACC_raw[i] = (Wire.read()<<8) | ACC_low;
    i++;
  }
  for (i=0; i<3; i++) {  //belegt 9 Eintraege in buf
    *bout << "," << ACC_raw[i];
  }
}

void MAG_dataRead(char *bout) {
  Wire.beginTransmission(MAG_ADDRESS);
  Wire.write(MAG_X_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MAG_ADDRESS, 6, true);
  i = 0;
  while(Wire.available() > 1){
    MAG_high = Wire.read();
    MAG_raw[i] = Wire.read() | (MAG_high<<8);
    i++;
  }
  for (i=0; i<3; i++) {  //belegt 9 Eintraege in buf
    *bout << "," << ACC_raw[i];
  }
  Wire.beginTransmission(MAG_ADDRESS);
  Wire.write(MAG_THM_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MAG_ADDRESS, 2, true);
  while(Wire.a
