#include <Scheduler.h>
#include <VM_Boards.h>

void setup()
{
	Serial.begin(115200);
  pinMode(13, OUTPUT);

}

void loop()
{

  /* add main program code here */
	digitalWrite(13, HIGH);
	Serial.println("HIGH");
	delay(1000);
	digitalWrite(13, LOW);
	Seial.println("LOW");
	delay(500);
}
