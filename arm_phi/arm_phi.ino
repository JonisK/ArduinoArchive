template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }



float y = 0.0;
float u = 0.0;
float e = 0.0;
float w = 0.0;
float x_1 = 0.0;
float x_2 = 0.0;

float a_0 = 1.0;
float a_1 = sqrt(4.0*a_0);
float k_1 = 10000.0;
float m_2 = 0.03;
float g = 9.81;
float x_s2 = 0.08;
float J_2 = m_2 * x_s2 * x_s2;
float d_phi = 3E-3;
float gravity, friction, setvalue;


int y_pin = A0;
int w_pin = A5;
byte plus = 3;
byte minus = 4;

long last_call = 0;
long time = 0;

void setup()
{

  Serial.begin(115200);

	pinMode (y_pin, INPUT);
	pinMode (w_pin, INPUT);
	pinMode (plus, OUTPUT);
	pinMode (minus, OUTPUT);

}

void loop()
{

  /* add main program code here */
  y = 0.17578 * analogRead(y_pin);
	w = 0.17578 * analogRead(w_pin);
	time = millis() - last_call;
	Serial << "{TIMEPLOT|data|time|T|" << time << "}\n";
  x_2 = (y-x_1) / ((float) time);
  x_1 = y;
	last_call = millis();
	Serial << "{TIMEPLOT|data|w|T|" << w << "}\n";
	Serial << "{TIMEPLOT|data|x_1|T|" << x_1 << "}\n";
	Serial << "{TIMEPLOT|data|x_2|T|" << x_2 << "}\n";
	e = w-x_1;
	gravity = m_2*x_s2*g*sin(x_1 * (PI/180));
	friction = d_phi * x_2;
	setvalue = J_2 * (a_0*e - a_1*x_2);
	u = setvalue + gravity + friction;
	Serial << "{TIMEPLOT|data|e|T|" << e << "}\n";
	Serial << "{TIMEPLOT|data|gravity|T|" << gravity << "}\n";
	Serial << "{TIMEPLOT|data|friction|T|" << friction << "}\n";
	Serial << "{TIMEPLOT|data|setvalue|T|" << setvalue << "}\n";
	Serial << "{TIMEPLOT|data|u|T|" << u << "}\n";
	Serial << "{TIMEPLOT|data|u_real|T|" << ((int) (k_1*abs(u))) << "}\n";
	if (u<0.0) {
		digitalWrite(plus, LOW);
		digitalWrite(minus, HIGH);
	}
	else if (u>0.0) {
		digitalWrite(plus, HIGH);
		digitalWrite(minus, LOW);
	}
	else {
		digitalWrite(plus, LOW);
		digitalWrite(minus, LOW);
	}
	analogWrite(9, ((int) (k_1*abs(u))));
}