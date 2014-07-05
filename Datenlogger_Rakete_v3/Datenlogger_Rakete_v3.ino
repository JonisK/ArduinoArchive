//Programm, das den Beschleunigungssensor LIS331HH ueber
//SPI ausliest und die Daten auf einer microSD Karte speichert.
//Wird entwickelt, um Beschleunigungsdaten eines Raketenfluges
//aufzuzeichnen, welche die Basis fuer Simulationen einer
//Flugregelung darstellen koennten.
//
//erstellt am 28.02.12
//
//Konventionen:
//
//MOSI: pin 11
//MISO: pin 12
//SCK: pin 13
//SS(sensor): pin 10
//SS(SD): pin 4
//
//Alle Datenleitungen ueber Pegelwandler auf 3,3V wandeln, 
//MISO nicht wandeln!


#include <SPI.h>
#define SCALE 0.000732421875

const int SS_Sensor = 10;
const int SS_SD = 4;

const byte ACC_READ = B10000000;
const byte ACC_CONT_READ = B11000000;
const byte ACC_WRITE = B00000000;
const byte ACC_CONT_WRITE = B01000000;

const byte CTRL_REG1 = B00100000;
const byte CTRL_REG2 = B00100001;
const byte CTRL_REG3 = B00100010;
const byte CTRL_REG4 = B00100011;
const byte CTRL_REG5 = B00100100;
const byte STATUS_REG = B0100111;
const byte OUT_X_L = 0x28;
const byte OUT_X_H = 0x29;
const byte OUT_Y_L = 0x2A;
const byte OUT_Y_H = 0x2B;
const byte OUT_Z_L = 0x2C;
const byte OUT_Z_H = 0x2D;

double data[3];
double maxdata[3];
int rawdata[3];
int rawmax[3];

void setup() {
  //Serielle Verbindung aufbauen
  Serial.begin(9600);
  Serial.println("Datenlogger_Rakete");
  
  //SP Interface einrichten
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.setBitOrder(MSBFIRST);
  
  //Beschleunigungssensor einrichten
  pinMode(SS_Sensor, OUTPUT);
  
  verifiedWrite(CTRL_REG1, B00111111, SS_Sensor);
  //verifiedWrite(CTRL_REG2, B00000000, SS_Sensor);
  //verifiedWrite(CTRL_REG3, B00000000, SS_Sensor);
  verifiedWrite(CTRL_REG4, B00110000, SS_Sensor);
  //verifiedWrite(CTRL_REG5, B00000000, SS_Sensor);
  
  for(int i=0; i<3; i++) {
    data[i] = 0;
    rawdata[i] = 0;
  }
  
  //SD-Karte einrichten
  pinMode(SS_SD, OUTPUT);

  
  Serial.println("Initialisierung abgeschlossen");
}

void loop() {
  for(int i=0; i<3; i++) {
    maxdata[i] = 0;
    rawmax[i] = 0;
  }
  int j = 0;
  while (j<2000) {
    //Sensor nach neuen Daten fragen
    if(dataAvailable() == 1) {
      //Neue Daten uebertragen
      if (!readData()) {
        Serial.println("Daten wurden nicht korrekt gelesen");
      }
      
      for (int k=0; k<3; k++) {
        if ( abs(maxdata[k]) < abs(data[k]) ) {
          maxdata[k] = data[k];
          rawmax[k] = rawdata[k];
        }
      }
      
      //String aus den neuen Daten bilden
      //Serial.println(xAccel, BIN);
      
  
      //String an geoeffnete Datei anhaengen
      j++;
    }  
  }
  Serial.println();
  Serial.println("----------------------");
  Serial.println();
  Serial.print("X: ");
  Serial.print(maxdata[0], DEC);
  Serial.println(" g");
  Serial.print("Y: ");
  Serial.print(maxdata[1], DEC);
  Serial.println(" g");
  Serial.print("Z: ");
  Serial.print(maxdata[2], DEC);
  Serial.println(" g");
  Serial.println();
  Serial.println(rawmax[0], BIN);
  Serial.println(rawmax[1], BIN);
  Serial.println(rawmax[2], BIN);
}

void writeByte(byte thisAdress, byte thisValue, int thisSS) {
  //Initialisierung
  Serial.println("writeByte-Funktion wurde aufgerufen");
  Serial.print("Gegebene Adresse: ");
  Serial.println(thisAdress, HEX);
  Serial.print("Gegebene Daten: ");
  Serial.println(thisValue, BIN);
  Serial.print("Gegebenes Geraet: ");
  Serial.println(thisSS, DEC);
  
  byte init = 0;
  
  //Zu sendende Daten vorbereiten
  init = thisAdress | ACC_WRITE;
  //Serial.print("Zu sendendes Ansteuerungsbyte: ");
  //Serial.println(init, BIN);
  
  //SPI Fenster beginnen
  //Serial.println("SPI Kommunikationsfenster wird geoeffnet");
  digitalWrite(thisSS, LOW);
  //delay(1);
  
  //Serial.println("Ansteuerungsbyte wird gesendet.");
  SPI.transfer(init);
  //delay(1);
  
  //Serial.println("Daten werden gesendet.");
  SPI.transfer(thisValue);
  //delay(1);
  
  //SPI Fenster schliessen
  //Serial.println("SPI Kommunikationsfenster wird geschlossen");
  digitalWrite(thisSS, HIGH);
  
  Serial.println("Daten geschrieben. Funktion wird beendet.");
}

//Testfunktion
void verifiedWrite(byte thisAdress, byte thisValue, int thisSS) {
  Serial.println("verifiedWrite wurde aufgerufen.");
  Serial.println("Daten werden geschrieben.");
  writeByte(thisAdress, thisValue, thisSS);
  delay(100);
  Serial.println("Daten werden gelesen.");
  byte readValue = readByte(thisAdress, thisSS);
  if (thisValue == readValue) {
    Serial.println("Daten wurden korrekt geschrieben.");
  }
  else {
    Serial.println("Fehlschlag!");
  }
}

//Liest einen einzigen Registerwert, der mit einer √ºbergebenen
//Adresse spezifiziert wird, aus.
byte readByte(byte thisAdress, int thisSS) {
  //Initialisierung
  //Serial.println("readByte-Funktion wurde aufgerufen");
  //Serial.print("Gegebene Adresse: ");
  //Serial.println(thisAdress, HEX);
  //Serial.print("Gegebenes Geraet: ");
  //Serial.println(thisSS, DEC);
  
  byte value = 0;
  byte init = 0;
  
  //Zu sendende Daten vorbereiten
  init = thisAdress | ACC_READ;
  //Serial.print("Zu sendendes Ansteuerungsbyte: ");
  //Serial.println(init, BIN);
  
  //SPI Fenster beginnen
  //Serial.println("SPI Kommunikationsfenster wird geoeffnet");
  digitalWrite(thisSS, LOW);
  //delay(1);
  
  //Serial.println("Ansteuerungsbyte wird gesendet.");
  SPI.transfer(init);
  //delay(10);
  
  //Serial.println("Daten werden empfangen.");
  value = SPI.transfer(0x00);
  //Serial.print("Empfangene Daten: ");
  //Serial.println(value, BIN);
  //delay(1);
  
  //SPI Fenster schliessen
  //Serial.println("SPI Kommunikationsfenster wird geschlossen");
  digitalWrite(thisSS, HIGH);
  
  //Serial.print("Empfangene Daten: ");
  //Serial.println(value, BIN);
  
  //Serial.println("Daten werden weitergegeben, Funktion wird beendet.");
  return(value);
}

//Liest alle Beschleunigungsdaten (Register 40-45) aus und
//gibt sie in einem Array mit 3 Integers zurueck.
int readData() {
  byte xAccLo = readByte(OUT_X_L, SS_Sensor);
  byte xAccHi = readByte(OUT_X_H, SS_Sensor);
  
  byte yAccLo = readByte(OUT_Y_L, SS_Sensor);
  byte yAccHi = readByte(OUT_Y_H, SS_Sensor);
  
  byte zAccLo = readByte(OUT_Z_L, SS_Sensor);
  byte zAccHi = readByte(OUT_Z_H, SS_Sensor);
  
  
  
  data[0] = (xAccLo | (xAccHi << 8)) * SCALE;
  data[1] = (yAccLo | (yAccHi << 8)) * SCALE;
  data[2] = (zAccLo | (zAccHi << 8)) * SCALE;
  rawdata[0] = (xAccLo | (xAccHi << 8));
  rawdata[1] = (yAccLo | (yAccHi << 8));
  rawdata[2] = (zAccLo | (zAccHi << 8));
  
  
  return 1;
}

int dataAvailable() {
  byte temp = readByte(STATUS_REG, SS_Sensor);
  temp = temp << 4;
  temp = temp >> 7;
  return temp;
}


