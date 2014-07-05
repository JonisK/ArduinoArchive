int u = 19;

void setup()
{

	Serial.begin(115200);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	digitalWrite(3, HIGH);
	digitalWrite(4, LOW);
}

void loop()
{
	u++;
	Serial.println(u);
  analogWrite(9, u);

	delay(5000);

}
