template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#define MOTOR_ON

int y_pin = A1;
int reading = 0;
int minimum = 720;
int maximum = 700;
int index = 0;
byte plus_1 = 3;
byte minus_1 = 4;
byte plus_2 = 5;
byte minus_2 = 6;
int interval = 50;

void setup()
{
	Serial.begin(115200);
  pinMode(y_pin, INPUT);
	pinMode (plus_1, OUTPUT);
	pinMode (minus_1, OUTPUT);
	pinMode (plus_2, OUTPUT);
	pinMode (minus_2, OUTPUT);
// 	noInterrupts();
//   TCCR2A = 0;
//   TCCR2B = 0;
//   TCNT2  = 0;
//   OCR2A = 156;              // 10ms between each analog read, 16 Mhz, prescaler 1024
//   TCCR2B |= (1 << CS22);    // 1024 prescaler 
//   TCCR2B |= (1 << CS21);
//   TCCR2B |= (1 << CS20);
//   TIMSK2 |= (1 << OCIE2A);  // enable timer compare interrupt
//   interrupts();

}

void loop()
{
	reading = analogRead(y_pin);
	Serial << "{TIMEPLOT|data|analogRead|T|" << reading << "}\n";
	if (reading > maximum ) maximum = reading;
	else if ( reading < minimum ) minimum = reading;
  if (index == interval) {
	#ifdef MOTOR_ON
		digitalWrite(plus_1, LOW);
		digitalWrite(minus_1, HIGH);
		digitalWrite(plus_2, LOW);
		digitalWrite(minus_2, HIGH);
				
		analogWrite(9, 255);
		analogWrite(10, 0);
	#endif // MOTOR_ON
		
	}
	if ( index == 2*interval) {
	#ifdef MOTOR_ON
		digitalWrite(plus_1, HIGH);
		digitalWrite(minus_1, LOW);
		digitalWrite(plus_2, HIGH);
		digitalWrite(minus_2, LOW);
		
		analogWrite(9, 255);
		analogWrite(10, 0);
	#endif // MOTOR_ON
		
		Serial.print(minimum);
		Serial.print("  -  ");
		Serial.println(maximum);
		
		index = 0;
	}
	index++;
	delay(10);

}

// ISR(TIMER2_COMPA_vect)          // timer compare interrupt service routine
// {
// 	reading = analogRead(y_pin);
// } 
