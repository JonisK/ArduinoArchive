template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

void setup()
{

  Serial.begin(115200);
	delay(100);
	Serial.println("It's Due speaking");
	analogReadResolution(12);
}

void loop()
{

  /* add main program code here */

	for (int i=A0; i<A4; i++) {
		Serial << "{TIMEPLOT|data|"<< i << "|T|" << analogRead(i) << "}\n";
		//delay(1);
	}
}
