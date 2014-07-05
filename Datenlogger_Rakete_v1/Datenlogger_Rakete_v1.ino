//Programm, das den Beschleunigungssensor LIS331HH über
//SPI ausliest und die Daten auf einer microSD Karte speichert.
//Wird entwickelt, um Beschleunigungsdaten eines Raketenfluges
//aufzuzeichnen, welche die Basis für Simulationen einer
//Flugregelung darstellen könnten.
//
//erstellt am 28.02.12
//
//Konventionen:
//
//MOSI: pin 13
//MISO: pin 11
//SCK: pin 12
//SS(sensor): pin 10
//SS(SD): pin 4
//
//Alle Datenleitungen über Pegelwandler auf 3,3V wandeln!


#include <SPI.h>

const int SS_Sensor = 10;
const int SS_SD = 4;

const byte ACC_READ = B10000000;
const byte ACC_CONT_READ = B11000000;
const byte ACC_WRITE = B00000000;
const byte ACC_CONT_WRITE = B01000000;
const byte CTRL_REG1 = B00000000;
const byte CTRL_REG2 = B00000001;
const byte CTRL_REG3 = B00000010;
const byte CTRL_REG4 = B00000011;
const byte CTRL_REG5 = B00000100;


void setup() {
  //Serielle Verbindung aufbauen
  Serial.begin(9600);
  Serial.println("Datenlogger_Rakete");
  
  //SP Interface einrichten
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  SPI.setBitOrder(MSBFIRST);
  
  //Beschleunigungssensor einrichten
  pinMode(SS_Sensor, OUTPUT);
  
  writeByte(CTRL_REG1, B00100111, SS_Sensor);
  writeByte(CTRL_REG2, B00000000, SS_Sensor);
  writeByte(CTRL_REG3, B00000000, SS_Sensor);
  writeByte(CTRL_REG4, B00110000, SS_Sensor);
  writeByte(CTRL_REG5, B00000000, SS_Sensor);
  
  //SD-Karte einrichten
  pinMode(SS_SD, OUTPUT);

  
  Serial.println("Initialisierung abgeschlossen");
}

void loop() {
  //Sensor nach neuen Daten fragen
  //if()
    //Neue Daten übertragen
    
    //String aus den neuen Daten bilden

    //String an geöffnete Datei anhängen
    
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
  Serial.print("Zu sendendes Ansteuerungsbyte: ");
  Serial.println(init, BIN);
  
  //SPI Fenster beginnen
  Serial.println("SPI Kommunikationsfenster wird geoeffnet");
  digitalWrite(thisSS, LOW);
  
  Serial.println("Ansteuerungsbyte wird gesendet.");
  SPI.transfer(init);
  
  Serial.println("Daten werden gesendet.");
  SPI.transfer(thisValue);
  
  //SPI Fenster schließen
  Serial.println("SPI Kommunikationsfenster wird geschlossen");
  digitalWrite(thisSS, HIGH);
  
  Serial.println("Funktion wird beendet.");
}

//Testfunktion
void verifiedWrite(byte thisAdress, byte thisValue, int thisSS) {
  Serial.println("verifiedWrite wurde aufgerufen.");
  Serial.println("Daten werden geschrieben.");
  writeByte(thisAdress, thisValue, thisSS);
  Serial.println("Daten werden gelesen.");
  byte readValue = readByte(thisAdress, thisSS);
  if (thisValue == readValue) {
    Serial.println("Daten wurden korrekt geschrieben.");
  }
  else {
    Serial.println("Fehlschlag!");
  }
}

//Liest einen einzigen Registerwert, der mit einer übergebenen
//Adresse spezifiziert wird, aus.
byte readByte(byte thisAdress, int thisSS) {
  //Initialisierung
  Serial.println("readByte-Funktion wurde aufgerufen");
  Serial.print("Gegebene Adresse: ");
  Serial.println(thisAdress, HEX);
  Serial.print("Gegebenes Geraet: ");
  Serial.println(thisSS, DEC);
  
  byte value = 0;
  byte init = 0;
  
  //Zu sendende Daten vorbereiten
  init = thisAdress | ACC_READ;
  Serial.print("Zu sendendes Ansteuerungsbyte: ");
  Serial.println(init, BIN);
  
  //SPI Fenster beginnen
  Serial.println("SPI Kommunikationsfenster wird geoeffnet");
  digitalWrite(thisSS, LOW);
  
  Serial.println("Ansteuerungsbyte wird gesendet.");
  SPI.transfer(init);
  
  Serial.println("Daten werden empfangen.");
  value = SPI.transfer(0x00);
  Serial.print("Empfangene Daten: ");
  Serial.println(value, BIN);
  
  //SPI Fenster schließen
  Serial.println("SPI Kommunikationsfenster wird geschlossen");
  digitalWrite(thisSS, HIGH);
  
  Serial.println("Daten werden weitergegeben, Funktion wird beendet.");
  return(value);
}

//Liest alle Beschleunigungsdaten (Register 40-45) aus und
//gibt sie in einem Array mit 3 Integers zurück.
unsigned int readData() {

}

