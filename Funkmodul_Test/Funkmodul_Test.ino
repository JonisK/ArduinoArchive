#include <SPI.h>

const int SlaveSelect = 10;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setBitOrder(MSBFIRST);
  pinMode(SS, OUTPUT);
  delay(100);
}

void loop() {
//  while(1) {
//    readByte(0x00);
//    delay(2000);
//  }
  writeByte(0xC0, 0xE0);
  writeByte(0x80, 0xD7);
  writeByte(0x82, 0x39);
  writeByte(0xA6, 0x40);
  writeByte(0xC6, 0x47);
  writeByte(0x94, 0xA0);
  writeByte(0xC2, 0xAC);
  writeByte(0xCA, 0x81);
  writeByte(0xC4, 0x83);
  writeByte(0x98, 0x50);
  writeByte(0xE0, 0x00);
  writeByte(0xC8, 0x00);
  writeByte(0xC4, 0x00);
  readByte(0x00);
  writeByte(0x82, 0x39);
  
  for(int i=128; i<256; i+=1) {
    Serial.println(i, HEX);
    readByte(i);
    Serial.println();
    delay(50);
  }
  delay(45000);
}  
  
void writeByte(byte thisAdress, byte thisValue) {
  //Initialisierung
//  Serial.println("writeByte-Funktion wurde aufgerufen");
//  Serial.print("Gegebene Adresse: ");
//  Serial.println(thisAdress, HEX);
//  Serial.print("Gegebene Daten: ");
//  Serial.println(thisValue, BIN);
//  Serial.print("Gegebenes Geraet: ");
//  Serial.println(thisSS, DEC);
  
  byte init = 0;
  
  //Zu sendende Daten vorbereiten
  init = thisAdress;
  //Serial.print("Zu sendendes Ansteuerungsbyte: ");
  //Serial.println(init, BIN);
  
  //SPI Fenster beginnen
  //Serial.println("SPI Kommunikationsfenster wird geoeffnet");
  digitalWrite(SlaveSelect, LOW);
  //delay(1);
  
  //Serial.println("Ansteuerungsbyte wird gesendet.");
  SPI.transfer(init);
  //delay(1);
  
  //Serial.println("Daten werden gesendet.");
  SPI.transfer(thisValue);
  //delay(1);
  
  //SPI Fenster schliessen
  //Serial.println("SPI Kommunikationsfenster wird geschlossen");
  digitalWrite(SlaveSelect, HIGH);
  
  Serial.println("Daten geschrieben. Funktion wird beendet.");
}


//Liest einen einzigen Registerwert, der mit einer uebergebenen
//Adresse spezifiziert wird, aus.
byte readByte(byte thisAdress) {
  //Initialisierung
  //Serial.println("readByte-Funktion wurde aufgerufen");
  //Serial.print("Gegebene Adresse: ");
  //Serial.println(thisAdress, HEX);
  //Serial.print("Gegebenes Geraet: ");
  //Serial.println(thisSS, DEC);
  
  byte value1 = 0;
  byte value2 = 0;
  byte init = 0;
  
  //Zu sendende Daten vorbereiten
  init = thisAdress;
  //Serial.print("Zu sendendes Ansteuerungsbyte: ");
  //Serial.println(init, BIN);
  
  //SPI Fenster beginnen
  //Serial.println("SPI Kommunikationsfenster wird geoeffnet");
  digitalWrite(SlaveSelect, LOW);
  //delay(1);
  
  //Serial.println("Ansteuerungsbyte wird gesendet.");
  value1 = SPI.transfer(init);
  //delay(10);
  
  //Serial.println("Daten werden empfangen.");
  value2 = SPI.transfer(0x00);
  
  //SPI Fenster schliessen
  //Serial.println("SPI Kommunikationsfenster wird geschlossen");
  digitalWrite(SlaveSelect, HIGH);
  
  Serial.print("Empfangene Daten: ");
  Serial.print(value1, HEX);
  Serial.println(value2, HEX);
  delay(1);
  
  //Serial.println("Daten werden weitergegeben, Funktion wird beendet.");
  return(value1);
}


  
  
