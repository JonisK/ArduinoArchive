#include <JeeLib.h>

int counter;

void setup() {
  Serial.begin(57600); 
  Serial.println();
  Serial.println("Setup");

  // node 10, group 212, 868 MHz
  rf12_initialize(10, RF12_433MHZ, 212);
}

void loop() {

  if (rf12_recvDone()){    
    if (rf12_crc == 0) {
      //counter= rf12_data[0] | (rf12_data[1] << 8); 
      Serial.print("empfange: ");
			for (int i = 0; i<1; i++) {
				Serial.print((char) rf12_data[0]);
			}
			Serial.println();
			Serial.flush();
      //Serial.println(counter,DEC);
    }
  }
}
