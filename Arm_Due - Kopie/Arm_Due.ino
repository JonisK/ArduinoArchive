template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#define DEBUG

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

float a_0 = -10.0;
float a_1 = sqrt(4.0*a_0);
float k_1 = 10000.0;
float m_2 = 0.03;
float g = 9.81;
float x_s2 = 0.08;
float J_2 = m_2 * x_s2 * x_s2;
float d_phi = 3E-4;
float gravity, friction, setvalue;

long last_call = 0;
long time2 = 0;

float step = 1.9;
float m = 90.0;
byte mode = 1;


int x_1_pin = A0;
int x_2_pin = A1;
int x_3_pin = A2;
int x_4_pin = A3;
int w_1_pin = A4;
int w_2_pin = A5;
byte plus_1 = 3;
byte minus_1 = 4;
byte plus_2 = 6;
byte minus_2 = 7;

//Hardwarefaktoren:
float m_angle = 0.043945; //180 Grad durch 4096 Schritte des ADC
float m_velocity = -0.2;	//180 Grad pro Sekunde durch 920 Schritte Auslenkung bei dieser Geschwindigkeit
float m_meridian = 2006.0; //Neutralspannung der Differenzierer
int m_inertia = 224; //Moment, um die Haftreibung zu ueberwinden


void setup()
{
	Serial.begin(115200);
	
  pinMode (x_1_pin, INPUT);
	pinMode (x_2_pin, INPUT);
	pinMode (x_3_pin, INPUT);
	pinMode (x_4_pin, INPUT);
  pinMode (w_1_pin, INPUT);
	pinMode (w_2_pin, INPUT);
  pinMode (plus_1, OUTPUT);
  pinMode (minus_1, OUTPUT);
  pinMode (plus_2, OUTPUT);
  pinMode (minus_2, OUTPUT);
	
	analogReadResolution(12);
	analogWriteResolution(12);
}

void loop()
{

  x_1 = m_angle * analogRead(x_1_pin);
	x_2 = (analogRead(x_2_pin) - m_meridian)/m_velocity;
	x_3 = m_angle *analogRead(x_3_pin);
	x_4 = (analogRead(x_4_pin) - m_meridian)/m_velocity;
  w_1 = generate_w();
	w_2 = generate_w();
  time2 = millis() - last_call;

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
	e_2 = w_2-x_3;
  gravity = m_2*x_s2*g*sin(x_1 * (PI/180));
  friction = d_phi * x_2;
  setvalue = J_2 * (a_0*e_1 - a_1*x_2);
  u_1 = setvalue + gravity + friction;
	
	gravity = m_2*x_s2*g*sin(x_3 * (PI/180));
	friction = d_phi * x_4;
	setvalue = J_2 * (a_0*e_2 - a_1*x_4);
	u_2 = setvalue + gravity + friction;
	
  #ifdef DEBUG
  Serial << "{TIMEPLOT|data|time|T|" << time2 << "}\n";
  Serial << "{TIMEPLOT|data|w|T|" << w_1 << "}\n";
	Serial << "{TIMEPLOT|data|w|T|" << w_2 << "}\n";
  Serial << "{TIMEPLOT|data|x_1|T|" << x_1 << "}\n";
  Serial << "{TIMEPLOT|data|x_2|T|" << x_2 << "}\n";
	Serial << "{TIMEPLOT|data|x_1|T|" << x_3 << "}\n";
	Serial << "{TIMEPLOT|data|x_2|T|" << x_4 << "}\n";
  Serial << "{TIMEPLOT|data|e|T|" << e_2 << "}\n";
  Serial << "{TIMEPLOT|data|gravity|T|" << gravity << "}\n";
  Serial << "{TIMEPLOT|data|friction|T|" << friction << "}\n";
  Serial << "{TIMEPLOT|data|setvalue|T|" << setvalue << "}\n";
  Serial << "{TIMEPLOT|data|u|T|" << u_2 << "}\n";
  Serial << "{TIMEPLOT|data|u_real|T|" << 224+((int) (k_1*abs(u_2))) << "}\n";
  #endif
	u_1=0;
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
  analogWrite(6, 224+((int) (k_1*abs(u_1))));
	
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
  analogWrite(7, 224+((int) (k_1*abs(u_2))));

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
