#include <JeeLib.h>

int counter = 0;
int poti = 0;
char tweet[10];

void setup () {
  Serial.begin(57600);
  Serial.println(" ");
  Serial.println("Setup");
	
	pinMode(A0, OUTPUT);
	pinMode(A1, INPUT);
	pinMode(A2, OUTPUT);
	
	digitalWrite(A0, LOW);
	digitalWrite(A2, HIGH);

  // node 11, group 17, 868 MHz
  rf12_initialize(10, RF12_433MHZ, 212);
	//while(1);
	//rf12_control(0x9807);
}

void loop () {
  ++counter;
	poti = analogRead(A1);
	
	if (Serial.available()) {
		char th = Serial.read();
// 		for(int i = 0; i<10; i++) {
// 			tweet[i] = Serial.read();
// 			if (Serial.available() == 0) break;
// 		}
		
		 while (!rf12_canSend()) {
			 rf12_recvDone();
		 }
		 
		 //rf12_onOff((uint8_t) counter);
		 rf12_sendStart(0, &th, 1);
		 
		 //delay(100);
		 
		 Serial.print("sende: ");
		 Serial.println(th);
		 Serial.println( rf12_control(0x0000) );
		 Serial.flush();

		 //delay(1000);
	}

 
}


