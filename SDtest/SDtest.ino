#include "SD.h"

const int chipSelect = 4;

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	Serial.begin(9600);
	
	// make sure that the default chip select pin is set to
	// output, even if you don't use it:
	pinMode(10, OUTPUT);
	
	// see if the card is present and can be initialized:
	if (!SD.begin(chipSelect)) {
	Serial.println("Card failed, or not present");
	// don't do anything more:
	return;
	}
	Serial.println("card initialized.");

}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	// make a string for assembling the data to log:
	String dataString = "";
	
	// read three sensors and append to the string:
	for (int analogPin = 0; analogPin < 3; analogPin++) {
		int sensor = analogRead(analogPin);
		dataString += String(sensor);
		if (analogPin < 2) {
			dataString += ","; 
		}
	}
	
	// open the file. note that only one file can be open at a time,
	// so you have to close this one before opening another.
	File dataFile = SD.open("datalog.txt", FILE_WRITE);
	
	// if the file is available, write to it:
	if (dataFile) {
		dataFile.println(dataString);
		dataFile.close();
		// print to the serial port too:
		Serial.println(dataString);
	}  
	// if the file isn't open, pop up an error:
	else {
		Serial.println("error opening datalog.txt");
	} 
}

