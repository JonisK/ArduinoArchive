template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#define DEBUG

// const int size = 4;
// volatile byte index = 0;
// volatile int deltas[size];
// volatile int last_call_pos = 0;
// volatile int reading = 0;
// volatile int delta = 0;
volatile byte next_read = 0;

volatile int x_1_raw;
volatile int x_2_raw;

float y_1 = 0.0;
float y_2 = 0.0;
float u_1 = 0.0;
float u_2 = 0.0;
float e_1 = 0.0;
float e_2 = 0.0;
float w_1 = 0.0;
float w_2 = 0.0;
float x_1 = 0.0;
float x_2 = 0.0;
float x_3 = 0.0;
float x_4 = 0.0;

float a_0 = 10.0;
float a_1 = sqrt(4.0*a_0);
float k_1 = 1000.0;
float m_2 = 0.03;
float g = 9.81;
float x_s2 = 0.08;
float J_2 = m_2 * x_s2 * x_s2;
float d_phi = 3E-4;
float gravity, friction, setvalue;
float k_vel = 1.7517;
int offset_vel = 700;
byte inertia = 56;

float step = 1.9;
float m = 90.0;
byte mode = 1;


int y_pin = A0;
int vel_pin = A1;
int w_pin = A5;
byte plus_1 = 3;
byte minus_1 = 4;
byte plus_2 = 5;
byte minus_2 = 6;

long last_call = 0;
long time = 0;

void setup()
{

  Serial.begin(115200);

	pinMode (y_pin, INPUT);
	pinMode (w_pin, INPUT);
	pinMode (plus_1, OUTPUT);
	pinMode (minus_1, OUTPUT);
	pinMode (plus_2, OUTPUT);
	pinMode (minus_2, OUTPUT);

	//deltas[size-1]=0;

	noInterrupts();
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  OCR2A = 156;              // 10ms between each analog read, 16 Mhz, prescaler 1024
  TCCR2B |= (1 << CS22);    // 1024 prescaler 
  TCCR2B |= (1 << CS21);
  TCCR2B |= (1 << CS20);
  TIMSK2 |= (1 << OCIE2A);  // enable timer compare interrupt
  interrupts();

}

void loop()
{

  /* add main program code here */
  y_1 = 0.17578 * x_1_raw;
	w_1 = generate_w();
	time = millis() - last_call;
// 	int sum_pos = 0;
// 	for (int i = 0; i<size; i++) {
// 		sum_pos += deltas[i];
// 		//Serial.println(deltas[i]);
// 	}
	//x_2 = 175780.0 * ((float) sum_pos) / ((float) size*16380);
	x_2 = k_vel * ((float) (x_2_raw - offset_vel));
  x_1 = y_1;
	#ifdef DEBUG
// 		Serial.print("reading: "); Serial.println(reading);
// 		Serial.print("delta: "); Serial.println(delta);
// 		Serial.print("last_call_pos: "); Serial.println(last_call_pos);
// 		Serial.print("sum_pos: "); Serial.println(sum_pos);
// 		Serial.print("float_sum_pos: "); Serial.println((float) sum_pos);
// 		Serial.print("sample: "); Serial.println((float) size*16380);
	#endif
	last_call = millis();
	e_1 = w_1-x_1;
	gravity = m_2*x_s2*g*sin(x_1 * (PI/180));
	friction = d_phi * x_2;
	setvalue = J_2 * (a_0*e_1 /*- a_1*x_2*/);
	u_1 = setvalue /*+ gravity*/ /*+ friction*/;
	#ifdef DEBUG
		Serial << "{TIMEPLOT|data|time|T|" << time << "}\n";
		Serial << "{TIMEPLOT|data|w|T|" << w_1 << "}\n";
		Serial << "{TIMEPLOT|data|x_1|T|" << x_1 << "}\n";
		Serial << "{TIMEPLOT|data|x_2|T|" << x_2 << "}\n";
		Serial << "{TIMEPLOT|data|e|T|" << e_1 << "}\n";
		Serial << "{TIMEPLOT|data|gravity|T|" << gravity << "}\n";
		Serial << "{TIMEPLOT|data|friction|T|" << friction << "}\n";
		Serial << "{TIMEPLOT|data|setvalue|T|" << setvalue << "}\n";
		Serial << "{TIMEPLOT|data|u|T|" << u_1 << "}\n";
		Serial << "{TIMEPLOT|data|u_real|T|" << 56+((int) (k_1*abs(u_1))) << "}\n";
	#endif
	if (u_1<0.0) {
		digitalWrite(plus_1, LOW);
		digitalWrite(minus_1, HIGH);
	}
	else if (u_1>0.0) {
		digitalWrite(plus_1, HIGH);
		digitalWrite(minus_1, LOW);
	}
	else {
		digitalWrite(plus_1, LOW);
		digitalWrite(minus_1, LOW);
	}
	analogWrite(9, 56+((int) (k_1*abs(u_1))));
	u_2 = 0;
	if (u_2<0.0) {
		digitalWrite(plus_2, LOW);
		digitalWrite(minus_2, HIGH);
	}
	else if (u_2>0.0) {
		digitalWrite(plus_2, HIGH);
		digitalWrite(minus_2, LOW);
	}
	else {
		digitalWrite(plus_2, LOW);
		digitalWrite(minus_2, LOW);
	}
	analogWrite(10, 56+((int) (k_1*abs(u_2))));
}

float generate_w() {
	if (m<1.1) mode = 1;
	else if (m>178.9) mode = 0;
	if (mode == 1) {
		m += step;
		return m;
	}
	else{
		m -= step;
		return m;
	}
}

ISR(TIMER2_COMPA_vect)          // Analog Read Routine. No analogRead()s outside!
{
	if (next_read == 0) {
		x_1_raw = analogRead(y_pin);
		next_read = 1;
	}
	else {
		x_2_raw = analogRead(vel_pin);
		next_read = 0;
	}
// 	reading = analogRead(y_pin);
// 
// 	delta = reading - last_call_pos;
// 	/*if (delta >= 30) {
// 		delta = 30;
// 	}
// 	else if (delta <= -30) {
// 		delta = -30;
// 	}*/
// 	deltas[index] = delta;
// 	last_call_pos = reading;
// 	index++;
// 	if (index == size) {
// 		index = 0;
// 	}
} 