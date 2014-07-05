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
  volatile float vel_left;
  volatile float vel_right;
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
int u_left = default_vel_left, u_right = default_vel_right;
const int vel_size = 20;

volatile unsigned long interval_left = 0, interval_right = 0;
volatile unsigned long last_update_left = 0, last_update_right = 0;
volatile long last_read_left = 0, last_read_right = 0;
volatile float last_left[vel_size], last_right[vel_size];
volatile byte index_left = 0, index_right = 0;
volatile int total_left=0, total_right=0;

volatile byte left_has_been_active = 0, right_has_been_active = 0;


float x_goal = 2000.0, y_goal = 1500.0;

float k1 = 1.0;
float k2 = 1.0;
float k3 = 1.0;
float k4 = 0.3;
float k5 = 0.01;
float k6 = 0.1;


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
  
  for (byte i=0; i<vel_size; i++) {
    last_left[i]=0.0;
    last_right[i]=0.0;
  }
  
  left.attach(9);
  right.attach(10);
  
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  for (int i=0; i<1000; i++) {
    PINB = 0x20;
  }
  Serial << "{XYPLOT|data|goal|" << x_goal << "|" << y_goal << "}\n";
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
//      Serial.print("Encoder links: ");
//      Serial.println(eleft.read());
//      Serial.print("Encoder rechts: ");
//      Serial.println(eright.read());
      delta_linear = (delta_linear_left + delta_linear_right) / 2;
//      Serial.print("delta_liear: ");
//      Serial.println(delta_linear);
      m_alpha = atan2( (delta_linear_right - delta_linear_left), gauge );
      pos.x += delta_linear * cos(pos.alpha + m_alpha/2);
      pos.y += delta_linear * sin(pos.alpha + m_alpha/2);
      Serial << "{XYPLOT|data|position|" << pos.x << "|" << pos.y << "}\n";
      pos.alpha += m_alpha;
      if(pos.alpha >= PI) {
        pos.alpha -= 2*PI;
      }
      else if (pos.alpha < -PI) {
        pos.alpha += 2*PI;
      }
      Serial << "{TIMEPLOT|data|alpha|T|" << pos.alpha << "}\n";
      Serial << "{TIMEPLOT|data|m_alpha|T|" << m_alpha << "}\n";
//      pos.vel_left = delta_linear_left / interval;
//      pos.vel_right = delta_linear_right / interval;
      Serial << "{TIMEPLOT|data|vel_left|T|" << pos.vel_left << "}\n";
      Serial << "{TIMEPLOT|data|vel_right|T|" << pos.vel_right << "}\n";
      
      //delay(10);
      break;
    case NAVIGATE:
      x_error = x_goal - pos.x;
      y_error = y_goal - pos.y;
      Serial << "{XYPLOT|data|error|" << x_error << "|" << y_error << "}\n";
      if (x_error==0 && y_error==0) break;
      alpha_error = atan2(y_error, x_error) - pos.alpha;
      //float temp = atan2(y_goal, x_goal);
      Serial << "{TIMEPLOT|data|atan2|T|" << atan2(y_error, x_error) << "}\n";
      Serial << "{TIMEPLOT|data|alpha_error|T|" << alpha_error << "}\n";
      linear = k5*sqrt(x_error*x_error + y_error*y_error);
      if (linear > 45.0) {
        linear = 45.0;
      }
      else if (linear < -45.0) {
        linear = -45.0;
      }
      Serial << "{TIMEPLOT|data|linear|T|" << linear << "}\n";
      
      //sch.timer(DRIVE_AT, 0);
      break;
//    case TEST_DRIVE:
//      linear = 
    case DRIVE_AT:
      set_vel_left = k1*linear - k2*alpha_error;
      Serial << "{TIMEPLOT|data|set_vel_left|T|" << set_vel_left << "}\n";
      u_left += ((int) (k6*((k3*(set_vel_left - k4*pos.vel_left)))));
      if (u_left > (default_vel_left+45)) u_left = default_vel_left+45;
      else if (u_left < (default_vel_left-45)) u_left = default_vel_left-45;
      left.write(u_left);
      Serial << "{TIMEPLOT|data|u_left|T|" << u_left << "}\n";
      
      set_vel_right = k1*linear + k2*alpha_error;
      Serial << "{TIMEPLOT|data|set_vel_right|T|" << set_vel_right << "}\n";
      u_right -= ((int) (k6*((k3*(set_vel_right - k4*pos.vel_right)))));
      if (u_right > (default_vel_right+45)) u_right = default_vel_right+45;
      else if (u_right < (default_vel_right-45)) u_right = default_vel_right-45;
      right.write(u_right);
      Serial << "{TIMEPLOT|data|u_right|T|" << u_right << "}\n";
      //delay(5);
      break;
    case TASK_MANAGER:
//      if (index == 0) {
//        sch.timer(NAVIGATE, 0);
//      }
      sch.timer(UPDATE, 0);
      sch.timer(DRIVE_AT, 0);
      
      index++;
      if (index >= 10 ) {
        index = 0;
        sch.timer(NAVIGATE, 0);
      }
      sch.timer(TASK_MANAGER, 5);
      break;
  }
}  
      
void leftClick() {
  interval_left = millis() - last_update_left;
  last_update_left = millis();
  if (eleft.read() > last_read_left) last_left[index_left] = ((float) (step_length / interval_left)) / 1000.0;
  else last_left[index_left] = -((float) (step_length / interval_left)) / 1000.0;
  if (last_left[index_left] > 300.0) {
    last_left[index_left] = 240.0;
  }
  else if (last_left[index_left] < -300.0) {
    last_left[index_left] = -240.0;
  }
  for (byte i=0; i<vel_size; i++) {
    total_left += last_left[i];
  }
  pos.vel_left = ((float) (total_left+1)) / (float) vel_size;
  total_left = 0;
  if (index_left >= vel_size-1) index_left = 0; else index_left++;

  last_read_left = eleft.read();
  left_has_been_active = 8;
//  for (int i=0; i<1000; i++) {
//    PINB = 0x20;
//  }
}
void rightClick() {
  interval_right = millis() - last_update_right;
  last_update_right = millis();
  if (eright.read() > last_read_right) last_right[index_right] = (step_length / interval_right) / 1000.0;
  else last_right[index_right] = -(step_length / interval_right) / 1000.0;
  if (last_right[index_right] > 300.0) {
    last_right[index_right] = 240.0;
  }
  else if (last_right[index_right] < -300.0) {
    last_right[index_right] = -240.0;
  }
  for (byte j=0; j<vel_size; j++) {
    total_right += last_right[j];
  }
  pos.vel_right = ((float) (total_right+1)) / (float) vel_size;
  total_right = 0;
  if (index_right >= vel_size-1) index_right = 0; else index_right++;
  
  last_read_right = eright.read();
  right_has_been_active = 8;
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
