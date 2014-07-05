template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#define NO_PORTB_PINCHANGES
#include <PinChangeInt.h>
#include <Servo.h>
#include <EncoderAuto.h>
#include <JeeLib.h>


struct Position {
  float x;
  float y;
  float alpha;
  float vel_left;
  float vel_right;
};

Position pos = {0.0, 0.0, 0.0, 0.0, 0.0};

enum {UPDATE, NAVIGATE, UPDATE_VEL, DRIVE_AT, TASK_MANAGER, TASK_LIMIT};

Scheduler sch(TASK_LIMIT);

Encoder eleft(3, 5), eright(2,4);
Servo left, right;

unsigned long last_update = 0;
float step_length = 2.25802;
float gauge = 137.0;
long left_last = 0, right_last = 0;
float delta_linear_left, delta_linear_right, delta_linear;
float m_alpha;
float x_error, y_error, alpha_error, linear;
float set_vel_left, set_vel_right;
int default_vel_left = 92, default_vel_right = 98;
int index = 0;

volatile unsigned long interval_left = 0, interval_right = 0;
volatile unsigned long last_update_left = 0, last_update_right = 0;
volatile long last_read_left = 0, last_read_right = 0;

volatile byte left_has_been_active = 4, right_has_been_active = 4;


float x_goal = 200.0, y_goal = 150.0;

float k1 = 1.0;
float k2 = 40.0;
float k3 = 0.1;


void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(6, HIGH);
  digitalWrite(16, HIGH);
  PCintPort::attachInterrupt(16, &leftClick, CHANGE);
  PCintPort::attachInterrupt(6, &rightClick, CHANGE);
  
  noInterrupts();
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  OCR2A = 225;              // 115.2 ms pass if counted up 4 times, 8Mhz, Prescaler 1024
  TCCR2B |= (1 << CS22);    // 1024 prescaler 
  TCCR2B |= (1 << CS21);
  TCCR2B |= (1 << CS20);
  TIMSK2 |= (1 << OCIE2A);  // enable timer compare interrupt
  interrupts();
  
  left.attach(9);
  right.attach(10);
  
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  for (int i=0; i<1000; i++) {
    PINB = 0x20;
  }
  sch.timer(UPDATE, 1);
  sch.timer(TASK_MANAGER, 4);
  
}

void loop() {
  switch(sch.poll()) {
    case UPDATE:
//      interval = millis() - last_update;
//      last_update = millis();
//      Serial.print("Intervall: ");
//      Serial.println(interval);
      delta_linear_left = (eleft.read()-left_last) * step_length;
      left_last = eleft.read();
      delta_linear_right = (eright.read()-right_last) * step_length;
      right_last = eright.read();
      Serial.print("Encoder links: ");
      Serial.println(eleft.read());
      Serial.print("Encoder rechts: ");
      Serial.println(eright.read());
      delta_linear = (delta_linear_left + delta_linear_right) / 2;
      Serial.print("delta_liear: ");
      Serial.println(delta_linear);
      m_alpha = atan2( (delta_linear_right - delta_linear_left), gauge );
      pos.x += delta_linear * cos(pos.alpha + m_alpha/2);
      pos.y += delta_linear * sin(pos.alpha + m_alpha/2);
      Serial << "{XYPLOT|data|position|" << pos.x << "|" << pos.y << "}\n";
      pos.alpha += m_alpha;
      Serial << "{TIMEPLOT|data|alpha|T|" << pos.alpha << "}\n";
      Serial << "{TIMEPLOT|data|m_alpha|T|" << m_alpha << "}\n";
//      pos.vel_left = delta_linear_left / interval;
//      pos.vel_right = delta_linear_right / interval;
      Serial << "{TIMEPLOT|data|vel_left|T|" << pos.vel_left << "}\n";
      Serial << "{TIMEPLOT|data|vel_right|T|" << pos.vel_right << "}\n";
      
      delay(10);
      break;
    case NAVIGATE:
      x_error = x_goal - pos.x;
      y_error = y_goal - pos.y;
      Serial << "{XYPLOT|data|error|" << x_error << "|" << y_error << "}\n";
      if (x_error==0 && y_error==0) break;
      alpha_error = atan2(y_goal, x_goal) - pos.alpha;
      Serial << "{TIMEPLOT|data|alpha_error|T|" << alpha_error << "}\n";
      linear = sqrt(x_error*x_error + y_error*y_error);
      Serial << "{TIMEPLOT|data|linear|T|" << linear << "}\n";
      
      //sch.timer(DRIVE_AT, 0);
      break;
//    case TEST_DRIVE:
//      linear = 
    case DRIVE_AT:
      set_vel_left = k1*linear + k2*alpha_error;
      left.write(default_vel_left - ((int) (k3*(set_vel_left - pos.vel_left))));
      Serial.print("Left:  ");
      Serial.println(default_vel_left + ((int) (k3*(set_vel_left - pos.vel_left))));
      set_vel_right = k1*linear - k2*alpha_error;
      right.write(default_vel_right + ((int) (k3*(set_vel_right - pos.vel_right))));
      Serial.print("Right: ");
      Serial.println(default_vel_right - ((int) (k3*(set_vel_right - pos.vel_right))));
      delay(5);
      break;
    case TASK_MANAGER:
      if (index == 0) {
        sch.timer(NAVIGATE, 0);
      }
      sch.timer(UPDATE, 0);
      sch.timer(DRIVE_AT, 0);
      
      index++;
      if (index >= 0 ) index = 0;
      sch.timer(TASK_MANAGER, 1);
      break;
  }
}  
      
void leftClick() {
  interval_left = micros() - last_update_left;
  last_update_left = micros();
  if (eleft.read() > last_read_left) pos.vel_left = step_length / (interval_left/1000000.0);
  else pos.vel_left = -step_length / (interval_left/1000000.0);
  last_read_left = eleft.read();
  left_has_been_active = 4;
//  for (int i=0; i<1000; i++) {
//    PINB = 0x20;
//  }
}
void rightClick() {
  interval_right = micros() - last_update_right;
  last_update_right = micros();
  if (eright.read() > last_read_right) pos.vel_right = step_length / (interval_right/1000000.0);
  else pos.vel_right = -step_length / (interval_right/1000000.0);
  last_read_right = eright.read();
  right_has_been_active = 4;
//    for (int i=0; i<1000; i++) {
//      PINB = 0x20;
//    }
}
ISR(TIMER2_COMPA_vect)          // timer compare interrupt service routine
{
  if (left_has_been_active > 0) left_has_been_active--;
  else pos.vel_left = 0.0;
  if (right_has_been_active > 0) right_has_been_active--;
  else pos.vel_right = 0.0;
}
      
