#include <JeeLib.h>
#include <IOexpander.h>
#include <Wire.h>
#include <inttypes.h>
#include <IRremote.h>
#include <Encoder.h>

ISR(WDT_vect) { Sleepy::watchdogEvent(); }


enum{ABFRAGE, M_ANSCHALTEN, M_ANSCHALTEN_PHASE2, M_AUSSCHALTEN, M_AUSSCHALTEN_PHASE2,
      M_LAUTER, M_LEISER, M_KALIBRIEREN, M_KALIBRIEREN_PHASE2, M_KALIBRIEREN_PHASE3,
      B_ANSCHALTEN, B_ANSCHALTEN_PHASE2, B_ANSCHALTEN_PHASE3, B_AUSSCHALTEN, B_AUSSCHALTEN_PHASE2,
      S_ANSCHALTEN, S_ANSCHALTEN_PHASE2, S_AUSSCHALTEN, O_ANSCHALTEN, O_AUSSCHALTEN,
      EINGANG_WAEHLEN, HAUSMEISTER, TASK_LIMIT};
enum{RPI, DOCK, PC, NONE};
enum{SWITCH_ON, ON, SWITCH_OFF, OFF};

byte mStatus = OFF, m_anzuschalten = 0, m_auszuschalten = 0, m_kalibrieren = 0,
      bStatus = OFF, b_anzuschalten = 0, b_auszuschalten = 0,
      sStatus = OFF, s_anzuschalten = 0, s_auszuschalten = 0, oStatus, o_anzuschalten, o_auszuschalten,
      eingang = 3, eingang_zu_waehlen = 2, handlungsbedarf = 0;
int mVolume = 20, mVolume_error = 0; //Zwischen 0 und 107

Scheduler scheduler (TASK_LIMIT);

Encoder Lautstaerke(3, 5);

int state = 0;
int count = 0;
int direct = 0;

IOexpander c(0x20);
IOexpander d(0x21);
IOexpander e(0x24);

//Pins auf Arduino
int Lautstaerke_PWM = 8;

//Pins fuer Fernsteuerungsbox, Port Expander c, 0x20
int Lautstaerke_plus = 3;
int Lautstaerke_minus = 1;
int Luefter = 2;
int bass_Schalter = 6;
int bass_Status = 7;

//Pins fuer Fernsteuerungsbox, Port Expander d, 0x21
int LED_Stromt1 = 0;
int LED_Stromt2 = 1;
int LED_Stromt3 = 2;
int LED_Stromt4 = 3;

int LED_Eingang1 = 4;
int LED_Eingang2 = 5;
int LED_Eingang3 = 6;

int LED_Alarm = 7;

int Taster_Strom1 = 11;
int Taster_Strom2 = 10;
int Taster_Strom3 = 9;
int Taster_Strom4 = 8;

int Taster_Beleuchtung = 12;

int Taster_Eingang1 = 15;
int Taster_Eingang2 = 14;
int Taster_Eingang3 = 13;

uint8_t c_input0 = 0;
uint8_t c_input1 = 0;
uint16_t c_input = 0;
uint16_t c_input_last = 129;

uint8_t d_input0 = 0;
uint8_t d_input1 = 0;
uint16_t d_input = 0;
uint16_t d_input_last = 0;

//Pins fuer Relaisbox, Port Expander e, 0x24
int Relais1 = 8;
int Relais2 = 9;
int Relais3 = 10;
int Relais4 = 11;

int Relais_Weiche = 7;

int LED_Relaisbox = 15;

IRsend irsend;

//Codes
unsigned int power[] = {3450, 3450, 850, 2600, 850, 900, 850, 850, 850, 2600, 850, 900, 800, 900, 850, 850, 850, 900, 850, 850, 850, 900, 850, 2550, 900, 850, 850, 2600, 850, 2600, 850, 900, 850, 2550, 900, 2550, 900, 2550, 900, 2550, 900, 2550, 900, 2550, 900, 850, 850};
unsigned int volumeUp[] = {3450, 3450, 850, 2600, 850, 900, 850, 850, 850, 2600, 850, 900, 800, 900, 850, 850, 850, 2600, 850, 900, 850, 850, 850, 2600, 850, 900, 850, 2550, 900, 2550, 900, 850, 850, 2600, 850, 2600, 850, 2600, 850, 900, 850, 2550, 900, 2550, 900, 850, 850};
unsigned int volumeDown[] = {3450, 3400, 900, 2550, 900, 850, 850, 850, 900, 2550, 900, 850, 850, 2600, 850, 850, 850, 2600, 900, 800, 900, 850, 850, 2600, 850, 850, 900, 2550, 900, 2550, 900, 850, 850, 2600, 850, 850, 900, 2550, 900, 850, 850, 2600, 850, 2600, 850, 850, 900};
unsigned int VCR1[] = {3450, 3400, 900, 2550, 900, 850, 850, 850, 900, 2550, 900, 850, 850, 900, 800, 2600, 850, 2600, 900, 2550, 900, 2550, 900, 2550, 900, 850, 850, 2600, 850, 2600, 850, 900, 850, 2550, 900, 2550, 900, 850, 850, 900, 850, 850, 850, 900, 800, 850, 900};
unsigned int CD[] = {3500, 3400, 900, 2550, 900, 850, 850, 900, 800, 2600, 850, 900, 850, 2600, 850, 2600, 850, 900, 800, 2600, 850, 2600, 900, 2550, 900, 850, 850, 2600, 850, 2600, 850, 900, 850, 2550, 900, 850, 850, 900, 800, 2600, 850, 900, 850, 850, 850, 850, 900};
unsigned int TAPE[] = {3500, 3400, 850, 2600, 900, 800, 900, 850, 850, 2600, 900, 800, 900, 850, 850, 850, 900, 2550, 900, 2550, 900, 2550, 900, 2550, 900, 850, 850, 2550, 900, 2550, 900, 850, 900, 2550, 900, 2550, 900, 2550, 900, 850, 850, 850, 900, 850, 850, 850, 900};
unsigned int mute[] = {3450, 3450, 850, 2600, 850, 900, 850, 850, 850, 2600, 850, 900, 850, 2550, 900, 2550, 900, 2550, 900, 850, 850, 900, 800, 2650, 800, 900, 850, 2600, 850, 2600, 850, 900, 800, 2600, 850, 900, 850, 900, 800, 900, 850, 2600, 850, 2550, 900, 850, 850};



void setup()
{
  Serial.begin(9600);
  Serial.println("Fernsteuerungsbox am Start");
  delay(100);
  attachInterrupt(0, ereignis, FALLING);
  
  c.init();
  c.pinMode(Lautstaerke_plus, OUTPUT);
  c.pinMode(Lautstaerke_minus, OUTPUT);
  c.pinMode(Luefter, OUTPUT);
  c.pinMode(bass_Schalter, OUTPUT);
  c.pinMode(bass_Status, INPUT);
  
  //pinMode(Lautstaerke_PWM, OUTPUT);
  c.digitalWrite(Lautstaerke_plus, LOW);
  c.digitalWrite(Lautstaerke_minus, HIGH);
  
  d.init();
  d.pinMode(LED_Stromt1, OUTPUT);
  d.pinMode(LED_Stromt2, OUTPUT);
  d.pinMode(LED_Stromt3, OUTPUT);
  d.pinMode(LED_Stromt4, OUTPUT);
  d.pinMode(LED_Alarm, OUTPUT);  
  d.pinMode(LED_Eingang1, OUTPUT);
  d.pinMode(LED_Eingang2, OUTPUT);
  d.pinMode(LED_Eingang3, OUTPUT);
  d.pinMode(Taster_Strom1, INPUT);
  d.pinMode(Taster_Strom2, INPUT);
  d.pinMode(Taster_Strom3, INPUT);
  d.pinMode(Taster_Strom4, INPUT);
  d.pinMode(Taster_Beleuchtung, INPUT);
  d.pinMode(Taster_Eingang1, INPUT);
  d.pinMode(Taster_Eingang2, INPUT);
  d.pinMode(Taster_Eingang3, INPUT);
  
  e.init();
  e.pinMode(Relais1, OUTPUT);
  e.pinMode(Relais2, OUTPUT);
  e.pinMode(Relais3, OUTPUT);
  e.pinMode(Relais4, OUTPUT);
  e.pinMode(Relais_Weiche, OUTPUT);
  e.pinMode(LED_Relaisbox, OUTPUT);
  
  //c.digitalWrite(Lautstaerke_plus, HIGH);
  //c.digitalWrite(Lautstaerke_plus, LOW);
  d.digitalWrite(LED_Alarm, HIGH);
  d.digitalWrite(LED_Alarm, LOW);
  
  Lautstaerke.write(mVolume); 
 
  scheduler.timer(HAUSMEISTER, 3);
  scheduler.timer(EINGANG_WAEHLEN, 3);
  Serial.println("Initialisierung abgeschlossen");
  delay(100);
}

void loop()
{
  switch(scheduler.pollWaiting()){
    case ABFRAGE:
//      Serial.println("Versuche Status auszulesen");
//      delay(100);
      Wire.requestFrom(0x20, 0x08);
      c_input0 = Wire.read();
      //Serial.print(d_input0);
      c_input1 = Wire.read();
      //Serial.println(d_input1);  
      c_input = (c_input0 << 8) | c_input1;
      //Serial.println(c_input);
      
      Wire.requestFrom(0x21, 0x08);
      d_input0 = Wire.read();
      //Serial.print(d_input0);
      d_input1 = 0; //Wire.read();
      //Serial.println(d_input1);
      d_input = (d_input0 << 8) | d_input1;
//      Serial.println(d_input);
//      delay(100);
      //Serial.println();
      
      
      
      //LOGIK
      if (d_input != d_input_last) { 
        if (bitRead(d_input, Taster_Strom1) == 1 && bitRead(d_input_last, Taster_Strom1) == 0) {
//          Serial.println("Warteschlange");
//          delay(100);
          if (mStatus < 2) m_auszuschalten = 1; else m_anzuschalten = 1;
        }
        if (bitRead(d_input, Taster_Strom2) == 1 && bitRead(d_input_last, Taster_Strom2) == 0) {
          if (bStatus < 2) b_auszuschalten = 1; else b_anzuschalten = 1;
        }
        if (bitRead(d_input, Taster_Strom3) == 1 && bitRead(d_input_last, Taster_Strom3) == 0) {
          if (sStatus < 2) s_auszuschalten = 1; else s_anzuschalten = 1;
        }
        if (bitRead(d_input, Taster_Strom4) == 1 && bitRead(d_input_last, Taster_Strom4) == 0) {
          if (oStatus < 2) o_auszuschalten = 1; else o_anzuschalten = 1;
        }
        if (bitRead(d_input, Taster_Eingang1) == 1 && bitRead(d_input_last, Taster_Eingang1) == 0) {
          eingang_zu_waehlen = RPI;
          handlungsbedarf = 1;
        }
        if (bitRead(d_input, Taster_Eingang2) == 1 && bitRead(d_input_last, Taster_Eingang2) == 0) {
          eingang_zu_waehlen = DOCK;
          handlungsbedarf = 1;
        }
        if (bitRead(d_input, Taster_Eingang3) == 1 && bitRead(d_input_last, Taster_Eingang3) == 0) {
          eingang_zu_waehlen = PC;
          handlungsbedarf = 1;
        }
      }
      
      if (m_anzuschalten == 1 && mStatus == OFF) {
//        Serial.println("Anschalten im naechsten Takt");
//        delay(100);
        scheduler.timer(M_ANSCHALTEN, 0);
      }
      if (m_auszuschalten == 1 && mStatus == ON) scheduler.timer(M_AUSSCHALTEN, 0);
      
      if (b_anzuschalten == 1 && bStatus == OFF) scheduler.timer(B_ANSCHALTEN, 0);
      if (b_auszuschalten == 1 && bStatus == ON) scheduler.timer(B_AUSSCHALTEN, 0);
      
      if (s_anzuschalten == 1 && sStatus == OFF) scheduler.timer(S_ANSCHALTEN, 0);
      if (s_auszuschalten == 1 && sStatus == ON) scheduler.timer(S_AUSSCHALTEN, 0);
      
      if (o_anzuschalten == 1 && oStatus == OFF) scheduler.timer(O_ANSCHALTEN, 0);
      if (o_auszuschalten == 1 && oStatus == ON) scheduler.timer(O_AUSSCHALTEN, 0);
      
      if (((eingang_zu_waehlen != eingang) || handlungsbedarf == 1 ) && (mStatus == ON)) {
        scheduler.timer(EINGANG_WAEHLEN, 0);
        handlungsbedarf = 0;
      }
      mVolume_error = Lautstaerke.read() - mVolume;
      if (mVolume_error > 0) {
        scheduler.timer(M_LAUTER, 0);
      }
      if (mVolume_error < 0) {
        scheduler.timer(M_LEISER, 0);
      }
      
      if (m_kalibrieren == 1) {
        if (Lautstaerke.read() > mVolume) {
//          for (byte j = 0; j < (Lautstaerke.read() - mVolume); j++) {
//            scheduler.timer(M_LAUTER, 2*j);
//          }
          if(Lautstaerke.read() > 162) Lautstaerke.write(81);
          scheduler.timer(M_LAUTER, 0);
        }
        else if (Lautstaerke.read() < mVolume){
//          for (byte j = 0; j < (mVolume - Lautstaerke.read()); j++) {
//            scheduler.timer(M_LEISER, 2*j);
//          }
          if((Lautstaerke.read() < 0) && (Lautstaerke.read() >= -30)) Lautstaerke.write(0);
          if(Lautstaerke.read() < -30) {
            m_kalibrieren = 1;
            scheduler.timer(M_KALIBRIEREN, 0);
          }
          scheduler.timer(M_LEISER, 0);
        }
      }
      Serial.println(Lautstaerke.read());
      delay(100);
      d_input_last = d_input;
      //scheduler.timer(ABFRAGE, 1);
      break;
    case M_ANSCHALTEN:
//      Serial.println("Anschalten");
//      delay(100);
      mStatus = SWITCH_ON;
      m_anzuschalten = 0;
      e.digitalWrite(Relais1, HIGH);
      d.digitalWrite(5+eingang, HIGH);
      scheduler.timer(M_ANSCHALTEN_PHASE2, 10);
      break;
    case M_ANSCHALTEN_PHASE2:
      irsend.sendRaw(power, 47, 38);
      d.digitalWrite(LED_Stromt1, HIGH);
      mStatus = ON;
      scheduler.timer(EINGANG_WAEHLEN, 15);
      break;
    case M_AUSSCHALTEN:
      mStatus = SWITCH_OFF;
      m_auszuschalten = 0;
      irsend.sendRaw(power, 47, 38);
      d.digitalWrite(LED_Eingang1, LOW);
      d.digitalWrite(LED_Eingang2, LOW);
      d.digitalWrite(LED_Eingang3, LOW);
      scheduler.timer(M_AUSSCHALTEN_PHASE2, 10);
      break;
    case M_AUSSCHALTEN_PHASE2:
      e.digitalWrite(Relais1, LOW);
      d.digitalWrite(LED_Stromt1, LOW);
      mStatus = OFF;
      break;
    case M_LAUTER:
      irsend.sendRaw(volumeUp, 47, 38);
      mVolume++;
      delay(20);
      scheduler.timer(ABFRAGE, 0);
      break;
    case M_LEISER:
      irsend.sendRaw(volumeDown, 47, 38);
      mVolume--;
      delay(20);
      scheduler.timer(ABFRAGE, 0);
      break;
    case M_KALIBRIEREN:
      for (byte i=0; i<81; i++) {
        scheduler.timer(M_LEISER, 2*i);
      }
      scheduler.timer(M_KALIBRIEREN_PHASE2, 163);
      break;
    case M_KALIBRIEREN_PHASE2:
      mVolume = 0;
      Lautstaerke.write(0);
      for (byte i=0; i<10; i++) {
        scheduler.timer(M_LAUTER, 2*i);
      }
      scheduler.timer(M_KALIBRIEREN_PHASE3, 21);
      break;
    case M_KALIBRIEREN_PHASE3:
      m_kalibrieren = 0;    
      break;
    case B_ANSCHALTEN:
      bStatus = SWITCH_ON;
      b_anzuschalten = 0;
      e.digitalWrite(Relais2, HIGH);
      scheduler.timer(B_ANSCHALTEN_PHASE2, 3);
      break;
    case B_ANSCHALTEN_PHASE2:
      c.digitalWrite(bass_Schalter, HIGH);
      scheduler.timer(B_ANSCHALTEN_PHASE3, 2);
      break;
    case B_ANSCHALTEN_PHASE3:
      c.digitalWrite(bass_Schalter, LOW);
      d.digitalWrite(LED_Stromt2, HIGH);
      bStatus = ON;
      break;
    case B_AUSSCHALTEN:
      bStatus = SWITCH_OFF;
      b_auszuschalten = 0;
      c.digitalWrite(bass_Schalter, HIGH);
      scheduler.timer(B_AUSSCHALTEN_PHASE2, 4);
      break;
    case B_AUSSCHALTEN_PHASE2:
      c.digitalWrite(bass_Schalter, LOW);
      e.digitalWrite(Relais2, LOW);
      d.digitalWrite(LED_Stromt2, LOW);
      bStatus = OFF;
      break;
    case S_ANSCHALTEN:
      sStatus = SWITCH_ON;
      s_anzuschalten = 0;
      e.digitalWrite(Relais3, HIGH);
      scheduler.timer(S_ANSCHALTEN_PHASE2, 7);
      break;
    case S_ANSCHALTEN_PHASE2:
      d.digitalWrite(LED_Stromt3, HIGH);
      sStatus = ON;
      break;
    case S_AUSSCHALTEN:
      sStatus = SWITCH_OFF;
      s_auszuschalten = 0;
      e.digitalWrite(Relais3, LOW);
      d.digitalWrite(LED_Stromt3, LOW);
      sStatus = OFF;
      break;
    case O_ANSCHALTEN:
      o_anzuschalten = 0;
      e.digitalWrite(Relais4, HIGH);
      d.digitalWrite(LED_Stromt4, HIGH);
      oStatus = ON;
      break;
    case O_AUSSCHALTEN:
      e.digitalWrite(Relais4, LOW);
      d.digitalWrite(LED_Stromt4, LOW);
      oStatus = OFF;
      break;
      
    case EINGANG_WAEHLEN:
      switch (eingang_zu_waehlen) {
        case RPI:
          irsend.sendRaw(CD, 47, 38);
          d.digitalWrite(LED_Eingang1, HIGH);
          d.digitalWrite(LED_Eingang2, LOW);
          d.digitalWrite(LED_Eingang3, LOW);
          break;
        case DOCK:
          irsend.sendRaw(VCR1, 47, 38);
          d.digitalWrite(LED_Eingang1, LOW);
          d.digitalWrite(LED_Eingang2, HIGH);
          d.digitalWrite(LED_Eingang3, LOW);
          break;
        case PC:
          irsend.sendRaw(TAPE, 47, 38);
          d.digitalWrite(LED_Eingang1, LOW);
          d.digitalWrite(LED_Eingang2, LOW);
          d.digitalWrite(LED_Eingang3, HIGH);
          break;
        case NONE:
          d.digitalWrite(LED_Eingang1, LOW);
          d.digitalWrite(LED_Eingang2, LOW);
          d.digitalWrite(LED_Eingang3, LOW);
      }
      eingang = eingang_zu_waehlen;
      break;
    case HAUSMEISTER:
      scheduler.timer(ABFRAGE, 0);
      scheduler.timer(HAUSMEISTER, 1);
  }
}

void ereignis() {
  scheduler.timer(ABFRAGE, 0);
}
void encoder() {
  scheduler.timer(ABFRAGE, 0);
}

//mainAmp
//void mAVolDelta(int val1) {
//  if (val1>=0) direct = 1;
//  else {
//    direct = -1;
//    val1 = -val1;
//  }
//  for (val1; val1>0; val1--) {
//    if (direct == 1) irsend.sendRaw(volumeUp, 47, 38);
//    else irsend.sendRaw(volumeDown, 47, 38);
//    mAVolume = mAVolume + direct;
//    if (mAVolume < 0) mAVolume = 0;
//    else if (mAVolume >= 0) mAVolume = 81;
//    delay(200);
//  }
//}
//void mAVolAbs(int val, int calibration) {
//  if (calibration) {
//    irsend.sendRaw(mute, 47, 38);
//    if (val < 41) mAVolDelta(-81);
//    else mAVolDelta(81);
//    irsend.sendRaw(mute, 47, 38);
//    delay(100);
//  }
//  mAVolDelta(val-mAVolume);
//}
//  


