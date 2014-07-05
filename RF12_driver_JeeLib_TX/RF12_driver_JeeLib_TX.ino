#include <JeeLib.h>

int counter = 0;

void setup () {
  Serial.begin(57600);
  Serial.println(" ");
  Serial.println("Setup");

  // node 11, group 17, 868 MHz
  rf12_initialize(10, RF12_433MHZ, 212);

}

void loop () {
  ++counter;
  //counter=5;

  while (!rf12_canSend()) {
    rf12_recvDone();
  }
  //rf12_onOff((uint8_t) counter);
  rf12_sendStart(0, &counter, sizeof counter);
 
  //delay(100);
  
  Serial.print("sende: ");
  Serial.println(counter);
  //Serial.println( rf12_control(0x0000) );
  Serial.flush();

  delay(2000);
  
  
 
}


