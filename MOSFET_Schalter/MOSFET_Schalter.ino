byte Schalter = 2;
byte Treiber = 3;
byte Lampe = 13;
byte angeschaltet = 0;

void setup()
{

  pinMode(Schalter, INPUT);
  digitalWrite(Schalter, HIGH);
  pinMode(Treiber, OUTPUT);
  pinMode(Lampe, OUTPUT);

}

void loop()
{

  if(digitalRead(Schalter) == 0) {
	  if (angeschaltet) {
		  digitalWrite(Treiber, LOW);
		  digitalWrite(Lampe, LOW);
		  angeschaltet = 0;
	  }
	  else {
		  digitalWrite(Treiber, HIGH);
		  digitalWrite(Lampe, HIGH);
		  angeschaltet = 1;
	  }
	  delay(700);
	  
  }

}
