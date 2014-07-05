#include <JeeLib.h>
//ISR(WDT_vect) { Sleepy::watchdogEvent(); }

#include <IOexpander.h>
#include <Wire.h>
#include <inttypes.h>
#include <IRremote.h>

#include <Encoder.h>

#define NO_PORTB_PINCHANGES // to indicate that port b will not be used for pin change interrupts
#define NO_PORTC_PINCHANGES // to indicate that port c will not be used for pin change interrupts
#define NO_PIN_STATE        // to indicate that you don't need the pinState
#define NO_PIN_NUMBER       // to indicate that you don't need the arduinoPin
#include <PinChangeInt.h>





enum{ABFRAGE, M_ANSCHALTEN, M_ANSCHALTEN_PHASE2, M_AUSSCHALTEN, M_AUSSCHALTEN_PHASE2, EINGANG_WAEHLEN, 
      B_ANSCHALTEN, B_ANSCHALTEN_PHASE2, B_ANSCHALTEN_PHASE3, B_AUSSCHALTEN, B_AUSSCHALTEN_PHASE2, B_AUSSCHALTEN_PHASE3,
      S_ANSCHALTEN, S_ANSCHALTEN_PHASE2, S_AUSSCHALTEN, O_ANSCHALTEN, O_AUSSCHALTEN,
      LAUTSTAERKE, M_LAUTSTAERKE_SCHALTEN, M_LAUTER, M_LEISER, B_LAUTSTAERKE_SCHALTEN, B_LAUTER, B_LEISER,
      FERNBEDIENUNG, HAUSMEISTER, LEDS_ANSCHALTEN, LEDS_AUSSCHALTEN, TASK_LIMIT};
enum{RPI, DOCK, PC, NONE};
enum{SWITCH_ON, ON, SWITCH_OFF, OFF, STANDBY};
enum{M, B, NOTHING};

byte  mStatus = OFF, m_anzuschalten = 0, m_auszuschalten = 0,
      eingang = 3, eingang_zu_waehlen = 2, eStatus = OFF, e_anzuschalten = 0, e_auszuschalten = 0, handlungsbedarf = 0,
      bStatus = OFF, b_anzuschalten = 0, b_auszuschalten = 0,
      sStatus = OFF, s_anzuschalten = 0, s_auszuschalten = 0, 
      oStatus = OFF, o_anzuschalten = 0, o_auszuschalten = 0,
      lStatus = B,
      m_kalibrieren = 0, mVol_steps = 125, mVol_default = 10,
      b_kalibrieren = 0, bVol_steps = 108, bVol_default = 72;
      
int   mVolume = mVol_default, mVolume_error = 0, //Zwischen 0 und 125
      bVolume = bVol_default, bVolume_error = 0; //Zwischen 0 und 108



Encoder Lautstaerke(3, 5);
IRsend irsend;
IRrecv irrecv(7);

decode_results results;

Scheduler scheduler (TASK_LIMIT);

IOexpander c(0x20);
IOexpander d(0x21);
IOexpander e(0x24);

byte dringlichkeit = 0;
byte index = mVol_steps + mVol_default;
byte b_index = bVol_steps + bVol_default;
byte reg, temp;

//Pins auf Arduino
byte b_durchschalten = 8;
byte intertrans = 6;

//Pins fuer Fernsteuerungsbox, Port Expander c, 0x20
byte Lautstaerke_plus = 3;
byte Lautstaerke_minus = 1;
byte Luefter = 2;
byte bass_Schalter = 6;
byte bass_Status = 7;
byte Taster_Encoder = 8;
byte Schalter_LFE = 9;
byte LED_Lautstaerke1 = 10;
byte LED_Lautstaerke2 = 11;
byte Ethernet_Strom = 5;

//Pins fuer Fernsteuerungsbox, Port Expander d, 0x21
byte LED_Stromt1 = 0;
byte LED_Stromt2 = 1;
byte LED_Stromt3 = 2;
byte LED_Stromt4 = 3;

byte LED_Eingang1 = 4;
byte LED_Eingang2 = 5;
byte LED_Eingang3 = 6;

byte LED_Alarm = 7;

byte Taster_Strom1 = 11;
byte Taster_Strom2 = 10;
byte Taster_Strom3 = 9;
byte Taster_Strom4 = 8;

byte Taster_Beleuchtung = 12;

byte Taster_Eingang1 = 15;
byte Taster_Eingang2 = 14;
byte Taster_Eingang3 = 13;

uint8_t c_input0 = 0;
uint8_t c_input1 = 0;
uint16_t c_input = 0;
uint16_t c_input_last = 129;
uint16_t c_ledmask = 0x0C00, c_dir = 0x0380;
uint16_t c_leds = 0;

uint8_t d_input0 = 0;
uint8_t d_input1 = 0;
uint16_t d_input = 0;
uint16_t d_input_last = 0;
uint16_t d_ledmask = 0x00FF;
uint16_t d_leds = 0;
uint16_t d_dir = 0xFF00;

//Pins fuer Relaisbox, Port Expander e, 0x24
byte Relais1 = 8;
byte Relais2 = 9;
byte Relais3 = 10;
byte Relais4 = 11;

byte Relais_Weiche = 7;

byte LED_Relaisbox = 15;


//Codes, alle sind 64,65ms lang
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
  attachInterrupt(0, &ereignis, FALLING);
  pinMode(intertrans, OUTPUT);
  digitalWrite(intertrans, HIGH);
  PCintPort::attachInterrupt(intertrans, &encoder, CHANGE);
  
  irrecv.enableIRIn();
  
  c.init();
  c.pinMode(Lautstaerke_plus, OUTPUT);
  c.pinMode(Lautstaerke_minus, OUTPUT);
  c.pinMode(Luefter, OUTPUT);
  c.pinMode(bass_Schalter, OUTPUT);
  c.pinMode(bass_Status, INPUT);
  //c.pinMode(Taster_Encoder, INPUT);
  //c.pinMode(Schalter_LFE, INPUT);
  c.pinMode(LED_Lautstaerke1, OUTPUT);
  c.pinMode(LED_Lautstaerke2, OUTPUT);
  c.pinMode(Ethernet_Strom, OUTPUT);
  
  pinMode(b_durchschalten, OUTPUT);
  c.digitalWrite(Lautstaerke_plus, LOW);
  c.digitalWrite(Lautstaerke_minus, HIGH);
  
//  d.init();
//  d.pinMode(LED_Stromt1, OUTPUT);
//  d.pinMode(LED_Stromt2, OUTPUT);
//  d.pinMode(LED_Stromt3, OUTPUT);
//  d.pinMode(LED_Stromt4, OUTPUT);
//  d.pinMode(LED_Alarm, OUTPUT);  
//  d.pinMode(LED_Eingang1, OUTPUT);
//  d.pinMode(LED_Eingang2, OUTPUT);
//  d.pinMode(LED_Eingang3, OUTPUT);
//  d.pinMode(Taster_Strom1, INPUT);
//  d.pinMode(Taster_Strom2, INPUT);
//  d.pinMode(Taster_Strom3, INPUT);
//  d.pinMode(Taster_Strom4, INPUT);
//  d.pinMode(Taster_Beleuchtung, INPUT);
//  d.pinMode(Taster_Eingang1, INPUT);
//  d.pinMode(Taster_Eingang2, INPUT);
//  d.pinMode(Taster_Eingang3, INPUT);
  
  Wire.beginTransmission(0x21);
  Wire.write(0x06);
  Wire.write(d_dir);
  Wire.endTransmission();
  
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
  
  writeBit(0x21, LED_Stromt3, HIGH);
  
  if (lStatus == M) scheduler.timer(M_LAUTSTAERKE_SCHALTEN, 0);
  else if (lStatus == B) scheduler.timer(B_LAUTSTAERKE_SCHALTEN, 0);
  
  scheduler.timer(HAUSMEISTER, 0);
//  scheduler.timer(EINGANG_WAEHLEN, 3);
//  Serial.println("Initialisierung abgeschlossen");
//  delay(100);
}

void loop()
{
  switch(scheduler.poll()){
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
      
      if (irrecv.decode(&results)) {
        Serial.println(results.value, HEX);
        irrecv.resume(); // Receive the next value
        dringlichkeit = 8;
      }
     
      //LOGIK
      if (c_input != c_input_last) { 
        if (bitRead(c_input, Taster_Encoder) == 1 && bitRead(c_input_last, Taster_Encoder) == 0) {
          if ((lStatus == B) || (lStatus == NOTHING )) {
            scheduler.timer(M_LAUTSTAERKE_SCHALTEN, 0);
          }
          else {
            scheduler.timer(B_LAUTSTAERKE_SCHALTEN, 0);
          }
        }
        if (bitRead(c_input, Schalter_LFE) != bitRead(c_input_last, Schalter_LFE)) {
          if (bitRead(c_input, Schalter_LFE) == 1) {}
        }  
      }
      if ((bitRead(c_input, bass_Status) == 0) && (bStatus != SWITCH_ON) && (bStatus != SWITCH_OFF)) {
        scheduler.timer(B_ANSCHALTEN_PHASE2, 0);
      }
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
        if (mStatus < 2 ) {
          if (bitRead(d_input, Taster_Eingang1) == 1 && bitRead(d_input_last, Taster_Eingang1) == 0) {
            eingang_zu_waehlen = RPI;
            handlungsbedarf = 1;
          }
          if ((bitRead(d_input, Taster_Eingang2) == 1) && (bitRead(d_input_last, Taster_Eingang2)) == 0) {
            eingang_zu_waehlen = DOCK;
            handlungsbedarf = 1;
          }
          if (bitRead(d_input, Taster_Eingang3) == 1 && bitRead(d_input_last, Taster_Eingang3) == 0) {
            eingang_zu_waehlen = PC;
            handlungsbedarf = 1;
          }
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
      c_input_last = c_input;
      d_input_last = d_input;
      //scheduler.timer(ABFRAGE, 1);
      break;
    case M_ANSCHALTEN:
//      Serial.println("Anschalten");
//      delay(100);
      mStatus = SWITCH_ON;
      m_anzuschalten = 0;
      e.digitalWrite(Relais1, HIGH);
      //d.digitalWrite(5+eingang, HIGH);
      scheduler.timer(M_ANSCHALTEN_PHASE2, 11);
      break;
    case M_ANSCHALTEN_PHASE2:
      irsend.sendRaw(power, 47, 38);
      d.digitalWrite(LED_Stromt1, HIGH);
      mStatus = ON;
      scheduler.timer(EINGANG_WAEHLEN, 15);
      delay(65);
      irrecv.enableIRIn();
      break;
    case M_AUSSCHALTEN:
      mStatus = SWITCH_OFF;
      m_auszuschalten = 0;
      irsend.sendRaw(power, 47, 38);
      eingang_zu_waehlen = 3;
      scheduler.timer(EINGANG_WAEHLEN, 0);
      scheduler.timer(M_AUSSCHALTEN_PHASE2, 10);
      delay(65);
      irrecv.enableIRIn();
      break;
    case M_AUSSCHALTEN_PHASE2:
      e.digitalWrite(Relais1, LOW);
      d.digitalWrite(LED_Stromt1, LOW);
      mStatus = OFF;
      break;
    case EINGANG_WAEHLEN:
      switch (eingang_zu_waehlen) {
        case RPI:
          irsend.sendRaw(CD, 47, 38);
          irrecv.enableIRIn();
          d.digitalWrite(LED_Eingang1, HIGH);
          d.digitalWrite(LED_Eingang2, LOW);
          d.digitalWrite(LED_Eingang3, LOW);
          break;
        case DOCK:
          irsend.sendRaw(VCR1, 47, 38);
          irrecv.enableIRIn();
          d.digitalWrite(LED_Eingang1, LOW);
          d.digitalWrite(LED_Eingang2, HIGH);
          d.digitalWrite(LED_Eingang3, LOW);
          break;
        case PC:
          irsend.sendRaw(TAPE, 47, 38);
          irrecv.enableIRIn();
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
//    case M_KALIBRIEREN:
//      for (byte i=0; i<10; i++) {
//        scheduler.timer(M_LEISER, i);
//      }
//      scheduler.timer(M_KALIBRIEREN_PHASE2, 120);
//      break;
//    case M_KALIBRIEREN_PHASE2:
//      mVolume = 0;
//      Lautstaerke.write(0);
//      for (byte i=0; i<10; i++) {
//        scheduler.timer(M_LAUTER, 2*i);
//      }
//      scheduler.timer(M_KALIBRIEREN_PHASE3, 30);
//      break;
//    case M_KALIBRIEREN_PHASE3:
//      m_kalibrieren = 0;    
//      break;
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
      c.digitalWrite(Luefter, HIGH);
      bStatus = ON;
      break;
    case B_AUSSCHALTEN:
      bStatus = SWITCH_OFF;
      b_auszuschalten = 0;
      c.digitalWrite(bass_Schalter, HIGH);
      scheduler.timer(B_AUSSCHALTEN_PHASE2, 2);
      break;
    case B_AUSSCHALTEN_PHASE2:
      c.digitalWrite(bass_Schalter, LOW);
      e.digitalWrite(Relais2, LOW);
      d.digitalWrite(LED_Stromt2, LOW);
      scheduler.timer(B_AUSSCHALTEN_PHASE3, 5);
      break;
    case B_AUSSCHALTEN_PHASE3:
      c.digitalWrite(Luefter, LOW);
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
      c.digitalWrite(Ethernet_Strom, HIGH);
      b_kalibrieren = 1;
      scheduler.timer(LAUTSTAERKE, 0);
      oStatus = ON;
      break;
    case O_AUSSCHALTEN:
      o_auszuschalten = 0;
      e.digitalWrite(Relais4, LOW);
      d.digitalWrite(LED_Stromt4, LOW);
      c.digitalWrite(Ethernet_Strom, LOW);
      oStatus = OFF;
      break;
      
    case LAUTSTAERKE:
      if (lStatus == M) {
        if (m_kalibrieren == 0) {
          mVolume_error = Lautstaerke.read() - mVolume;
          Serial.println(mVolume_error);
          delay(20);
          if (mVolume_error > 0) {
            scheduler.timer(M_LAUTER, 0);
          }
          else if ((mVolume_error < 0) && (mVolume_error > -50)) {
            scheduler.timer(M_LEISER, 0);
          }
          else if (mVolume_error <= -50) {
            m_kalibrieren = 1;
            scheduler.timer(LAUTSTAERKE, 0);
          }
        }
        else {
          if (index > mVol_default) {
            scheduler.timer(M_LEISER, 0);
            index--;
          }
          else if ((index <= mVol_default) && (index > 0)) {  
            scheduler.timer(M_LAUTER, 0);
            index--;
          }
          else if (index == 0) {
            index = mVol_steps + mVol_default;
            mVolume = mVol_default;
            Lautstaerke.write(mVol_default);
            m_kalibrieren = 0;
          }
        }
      }
      else if (lStatus == B) {
        if (b_kalibrieren == 0) {
          bVolume_error = Lautstaerke.read() - bVolume;
          Serial.println(bVolume_error);
          delay(20);
          if (bVolume_error > 0) {
            scheduler.timer(B_LAUTER, 0);
          }
          else if ((bVolume_error < 0) && (bVolume_error > -50)) {
            scheduler.timer(B_LEISER, 0);
          }
          else if (bVolume_error <= -50) {
            b_kalibrieren = 1;
            scheduler.timer(LAUTSTAERKE, 0);
          }
        }
        else {
          if (b_index > bVol_default) {
            scheduler.timer(B_LEISER, 0);
            b_index--;
          }
          else if ((b_index <= bVol_default) && (b_index > 0)) {  
            scheduler.timer(B_LAUTER, 0);
            b_index--;
          }
          else if (b_index == 0) {
            b_index = bVol_steps + bVol_default;
            bVolume = bVol_default;
            Lautstaerke.write(bVol_default);
            b_kalibrieren = 0;
          }
        }
      }
      break;
    case M_LAUTSTAERKE_SCHALTEN:
      lStatus = M;
      c.digitalWrite(LED_Lautstaerke1, HIGH);
      c.digitalWrite(LED_Lautstaerke2, LOW);
      Lautstaerke.write(mVolume);
    case M_LAUTER:
      irsend.sendRaw(volumeUp, 47, 38);
      mVolume++;
      //delay(20);
      scheduler.timer(FERNBEDIENUNG, 1);
      scheduler.timer(LAUTSTAERKE, 1);
      break;
    case M_LEISER:
      irsend.sendRaw(volumeDown, 47, 38);
      mVolume--;
      //delay(20);
      scheduler.timer(FERNBEDIENUNG, 1);
      scheduler.timer(LAUTSTAERKE, 1);
      break;
    case B_LAUTSTAERKE_SCHALTEN:
      lStatus = B;
      c.digitalWrite(LED_Lautstaerke1, LOW);
      c.digitalWrite(LED_Lautstaerke2, HIGH);
      Lautstaerke.write(bVolume);
      break;
    case B_LAUTER:
      c.digitalWrite(Lautstaerke_plus, HIGH);
      c.digitalWrite(Lautstaerke_minus, LOW);
      for(int i=0; i<8000; i++) {
        PORTB ^= 1;
        delayMicroseconds(5);
        PORTB &= ~1;
        delayMicroseconds(1);
      }
      bVolume++;
      scheduler.timer(LAUTSTAERKE, 1);
      break;
    case B_LEISER:
      c.digitalWrite(Lautstaerke_plus, LOW);
      c.digitalWrite(Lautstaerke_minus, HIGH);
      for(int i=0; i<8000; i++) {
        PORTB ^= 1;
        delayMicroseconds(5);
        PORTB &= ~1;
        delayMicroseconds(1);
      }
      bVolume--;
      scheduler.timer(LAUTSTAERKE, 1);
      break; 
    case FERNBEDIENUNG:
      irrecv.enableIRIn();
      dringlichkeit = 20;
      break;
    case HAUSMEISTER:
      scheduler.timer(ABFRAGE, 0);
      if (dringlichkeit > 0) {
        scheduler.timer(HAUSMEISTER, 1);
        dringlichkeit--;
      }
      else {
        scheduler.timer(HAUSMEISTER, 10);
      }
      break;
  }
}
//byte readBit(byte addr, byte bitnumber) {
//  //reg = (bitnumber > 7) ? 0x00 : 0x01;
//  Wire.requestFrom(addr, 
void writeBit(byte addr, byte bitnumber, boolean data) {
  Serial.println("writeBit");
  reg = (bitnumber > 7) ? 0x01 : 0x00;
  Serial.println(reg);
  Wire.requestFrom(addr, reg);
  temp = Wire.read();
  Serial.println(temp);
  temp = bitWrite(temp, bitnumber%8, data);
  Serial.println(temp);
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(temp);
  Wire.endTransmission();
  Serial.println("Finished!\n");
}

void ereignis() {
  scheduler.timer(ABFRAGE, 0);
}
void encoder() {
  scheduler.timer(LAUTSTAERKE, 0);
}
