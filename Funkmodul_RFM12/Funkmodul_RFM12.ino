#include <SPI.h>
const byte TRX1_SS = 10;
const byte TRX2_SS = 4;
void setup()
{
	Serial.begin(115200);
	
	SPI.begin();
	SPI.setDataMode(SPI_MODE3);
	SPI.setClockDivider(SPI_CLOCK_DIV8);
	pinMode(TRX1_SS, OUTPUT);
	pinMode(TRX2_SS, OUTPUT);
	pinMode(2, INPUT_PULLUP); // nIRQ connected
	digitalWrite(TRX1_SS, HIGH);
	digitalWrite(TRX2_SS, HIGH);
	delay(100);
	
	// Transceivermodul 1
	//writeByte(0xC0, 0xE0, TRX1_SS);
	
	// 1000 0000, 1100 1000 | Sendepuffer an, Empfangspuffer aus, 12,5pF Kapazität
	writeByte(0x80, 0xC8, TRX1_SS);
  
	// 1000 0010, 0111 1001 | Empfänger aus, Basisband an, Sender an, Synthesizer an
	//											| Quarz an, Brownout aus, Wakeup aus, Clockausgang auf LOW
	writeByte(0x82, 0x79, TRX1_SS);
	
	// 1010 0110, 0100 0000 | Frequenzeinstellung F=1600, f=434MHz
	writeByte(0xA6, 0x40, TRX1_SS);
	
	// 1100 0110, 0100 0111 | Bitrate 4800 Baud/s
	//											| empfohlen: Empfängerbandbreite 67kHz, Hub 45kHz, PLL-Bandbreite 0
  writeByte(0xC6, 0x47, TRX1_SS);
  
  
  // Empfängereinstellung
  // writeByte(0x94, 0xA0);
  // writeByte(0xC2, 0xAC);
  
	// 1100 1010, 1000 0010 | FIFO-Steuerung, Interrupt bei 8bit,
	//											| Syncmuster 2Byte, FIFO nach erkanntem Syncmuster füllen,
	//											| FIFO feigegeben, hochsensitiver POR aktiv
	writeByte(0xCA, 0x82, TRX1_SS);
	
	// 1100 0100, 1111 0111 | Automatische Frequuenznachregelung AFC, alles auf default
  writeByte(0xC4, 0xF7, TRX1_SS);
	
	// 1001 1000, 0010 0000 | Senderkonfiguration, FSK nicht invertiert, 45kHz Frequenzhub
	//											| Maximale Leistung
  writeByte(0x98, 0x20, TRX1_SS);
	
	// 1110 0000, 0000 0000 | Zeitgeber für Wakeup
  // writeByte(0xE0, 0x00, TRX1_SS);
	
	// Automatisch zyklischer Empfänger
  // writeByte(0xC8, 0x00, TRX1_SS);
  
	//writeByte(0xC4, 0x00, TRX1_SS);
	
	
	// Transceivermodul 2

	// 1000 0000, 1100 1000 | Sendepuffer an, Empfangspuffer aus, 12,5pF Kapazität
	writeByte(0x80, 0xC8, TRX2_SS);
	
	// 1000 0010, 0111 1001 | Empfänger aus, Basisband an, Sender an, Synthesizer an
	//											| Quarz an, Brownout aus, Wakeup aus, Clockausgang auf LOW
	writeByte(0x82, 0x79, TRX2_SS);
	
	// 1010 0110, 0100 0000 | Frequenzeinstellung F=1600, f=434MHz
	writeByte(0xA6, 0x40, TRX2_SS);
	
	// 1100 0110, 0100 0111 | Bitrate 4800 Baud/s
	//											| empfohlen: Empfängerbandbreite 67kHz, Hub 45kHz, PLL-Bandbreite 0
	writeByte(0xC6, 0x47, TRX2_SS);
	
	
	// Empfängereinstellung
	// writeByte(0x94, 0xA0);
	// writeByte(0xC2, 0xAC);
	
	// 1100 1010, 1000 0010 | FIFO-Steuerung, Interrupt bei 8bit,
	//											| Syncmuster 2Byte, FIFO nach erkanntem Syncmuster füllen,
	//											| FIFO feigegeben, hochsensitiver POR aktiv
	writeByte(0xCA, 0x82, TRX2_SS);
	
	// 1100 0100, 1111 0111 | Automatische Frequuenznachregelung AFC, alles auf default
	writeByte(0xC4, 0xF7, TRX2_SS);
	
	// 1001 1000, 0010 0000 | Senderkonfiguration, FSK nicht invertiert, 45kHz Frequenzhub
	//											| Maximale Leistung
	writeByte(0x98, 0x20, TRX2_SS);
}

void loop()
{
	// Status auslesen
  readByte(0x00, TRX1_SS);
	
	// Senden
	Serial.println("Daten senden");
	writeByte(0xB8, 0xAA, TRX1_SS);
	writeByte(0xB8, 0xAA, TRX1_SS);
	writeByte(0xB8, 0xAA, TRX1_SS);
	writeByte(0xB8, 0x2D, TRX1_SS);
	writeByte(0xB8, 0xD4, TRX1_SS);
	writeByte(0xB8, 0x34, TRX1_SS);
	writeByte(0xB8, 0x35, TRX1_SS);
	writeByte(0xB8, 0x36, TRX1_SS);
	
	delay(500);

}

void writeByte(byte thisAdress, byte thisValue, byte this_SS) {
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
	digitalWrite(this_SS, LOW);
	//delay(1);
	
	//Serial.println("Ansteuerungsbyte wird gesendet.");
	SPI.transfer(init);
	//delay(1);
	
	//Serial.println("Daten werden gesendet.");
	SPI.transfer(thisValue);
	//delay(1);
	
	//SPI Fenster schliessen
	//Serial.println("SPI Kommunikationsfenster wird geschlossen");
	digitalWrite(this_SS, HIGH);
	
	// Serial.println("Daten geschrieben. Funktion wird beendet.");
}


//Liest einen einzigen Registerwert, der mit einer uebergebenen
//Adresse spezifiziert wird, aus.
byte readByte(byte thisAdress, byte this_SS) {
	//Initialisierung
	//Serial.println("readByte-Funktion wurde aufgerufen");
	//Serial.print("Gegebene Adresse: ");
	//Serial.println(thisAdress, HEX);
	//Serial.print("Gegebenes Geraet: ");
	//Serial.println(thisSS, DEC);
	
	byte value1 = 0;
	byte value2 = 0;
	byte value3 = 0;
	byte init = 0;
	
	//Zu sendende Daten vorbereiten
	init = thisAdress;
	//Serial.print("Zu sendendes Ansteuerungsbyte: ");
	//Serial.println(init, BIN);
	
	//SPI Fenster beginnen
	//Serial.println("SPI Kommunikationsfenster wird geoeffnet");
	digitalWrite(this_SS, LOW);
	//delay(10);
	
	//Serial.println("Ansteuerungsbyte wird gesendet.");
	value1 = SPI.transfer(init);
	//delay(10);
	
	//Serial.println("Daten werden empfangen.");
	value2 = SPI.transfer(0x00);
	
	value3 = SPI.transfer(0x00);
	
	//SPI Fenster schliessen
	//Serial.println("SPI Kommunikationsfenster wird geschlossen");
	delay(0);
	digitalWrite(this_SS, HIGH);
	
	Serial.print("Empfangene Daten: ");
	Serial.print(value1, HEX);
	Serial.print(value2, HEX);
	Serial.println(value3, HEX);
	delay(10);
	
	//Serial.println("Daten werden weitergegeben, Funktion wird beendet.");
	return value1;
}





