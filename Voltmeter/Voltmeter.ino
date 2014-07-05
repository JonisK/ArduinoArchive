const int Measure = 3;
#define SCALE 0.00488758553275
int temp = 0;


//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	Serial.begin(9600);
	
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	temp = analogRead(Measure);
	Serial.print(temp*SCALE);
	Serial.print(" V | ");
	for(int i=temp; i>0; i-10) {
		Serial.print("-");
	}
	Serial.println();
}
