

#include <IOexpander.h>
#include <Wire.h>;
#include <inttypes.h>;
#include <IRremote.h>

int state = 0;
int count = 0;
int direct = 0;

IOexpander c(0x20);
IOexpander d(0x21);
IOexpander e(0x24);

int mainAmp = 0;
int mAVolume = 0; //Zwischen 0 und 107
int mAInput = 1; //1 für CD, 2 für VCR1, 3 für TAPE

int bassAmp = 0;
int subwoofer = 0;
int other = 0;

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
}

void loop()
{
  //Read state
  //Serial.println("Versuche Status auszulesen");
  Wire.requestFrom(0x20, 0x02);
  c_input0 = Wire.read();
  //Serial.print(d_input0);
  c_input1 = Wire.read();
  //Serial.println(d_input1);  
  c_input = (c_input0 << 8) | c_input1;
  //Serial.println(c_input);
  
  Wire.requestFrom(0x21, 0x02);
  d_input0 = Wire.read();
  //Serial.print(d_input0);
  d_input1 = 0; //Wire.read();
  //Serial.println(d_input1);
  d_input = (d_input0 << 8) | d_input1;
  //Serial.println(d_input);
  //Serial.println();

  //Serial.println(c.digitalRead( bass_Status ));  
  //Serial.println(digiRead(c_input, bass_Status));
//  if (c_input != c_input_last) {
//    if (count > 5000) {
//      if (digiRead(c_input, bass_Status) == 0) {
//        e.digitalWrite(Relais2, LOW);
//        d.digitalWrite(LED_Stromt2, LOW);
//        bassAmp = 0;
//      }
//      count = 0;
//    }
//    else count++;
//    c_input_last = c_input;
//  }
      
   
  if (d_input != d_input_last) { 
    if (digiRead(d_input, Taster_Strom1) == 1) {
      //Serial.println("Taster_Strom1 HIGH");
      if (mainAmp == 0) {
        e.digitalWrite(Relais1, HIGH);
        delay(1200);
        irsend.sendRaw(power, 47, 38);
        d.digitalWrite(LED_Stromt1, HIGH);
        mainAmp = 1;
      }
      else {
        irsend.sendRaw(power, 47, 38);
        delay(1000);
        e.digitalWrite(Relais1, LOW);
        d.digitalWrite(LED_Stromt1, LOW);
        mainAmp = 0;
      }
    }
   
    if (digiRead(d_input, Taster_Strom2) == 1) {
      //Serial.println("Taster_Strom2 HIGH");
      if (bassAmp == 0) {
        e.digitalWrite(Relais2, HIGH);
        delay(300);
        c.digitalWrite(bass_Schalter, HIGH);
        Serial.println("Bass Schalter");
        delay(5000);
        c.digitalWrite(bass_Schalter, LOW);
        d.digitalWrite(LED_Stromt2, HIGH);
        bassAmp = 1;
      }
      else {
        c.digitalWrite(bass_Schalter, HIGH);
        delay(50);
        c.digitalWrite(bass_Schalter, LOW);
        delay(300);
        e.digitalWrite(Relais2, LOW);
        d.digitalWrite(LED_Stromt2, LOW);
        bassAmp = 0;
      }
    }
    
    if (digiRead(d_input, Taster_Strom3) == 1) {
      //Serial.println("Taster_Strom3 HIGH");
      if (subwoofer == 0) {
        e.digitalWrite(Relais3, HIGH);
        delay(750);
        d.digitalWrite(LED_Stromt3, HIGH);
        subwoofer = 1;
      }
      else {
        e.digitalWrite(Relais3, LOW);
        d.digitalWrite(LED_Stromt3, LOW);
        subwoofer = 0;
      }
    }
    
    if (digiRead(d_input, Taster_Strom4) == 1) {
      //Serial.println("Taster_Strom4 HIGH");
      if (other == 0) {
        e.digitalWrite(Relais4, HIGH);
        d.digitalWrite(LED_Stromt4, HIGH);
        other = 1;
      }
      else {
        e.digitalWrite(Relais4, LOW);
        d.digitalWrite(LED_Stromt4, LOW);
        other = 0;
      }
    }
    
    if (digiRead(d_input, Taster_Eingang1) == 1) {
      //Serial.println("Taster_Eingang1 HIGH");
      irsend.sendRaw(CD, 47, 38);
      d.digitalWrite(LED_Eingang1, HIGH);
      d.digitalWrite(LED_Eingang2, LOW);
      d.digitalWrite(LED_Eingang3, LOW);
    }
    
    if (digiRead(d_input, Taster_Eingang2) == 1) {
    //Serial.println("Taster_Eingang1 HIGH");
    irsend.sendRaw(VCR1, 47, 38);
    d.digitalWrite(LED_Eingang1, LOW);
    d.digitalWrite(LED_Eingang2, HIGH);
    d.digitalWrite(LED_Eingang3, LOW);
    }
    
    if (digiRead(d_input, Taster_Eingang3) == 1) {
    //Serial.println("Taster_Eingang1 HIGH");
    irsend.sendRaw(TAPE, 47, 38);
    d.digitalWrite(LED_Eingang1, LOW);
    d.digitalWrite(LED_Eingang2, LOW);
    d.digitalWrite(LED_Eingang3, HIGH);
    }
    
    d_input_last = d_input;
  }

//e.digitalWrite(Relais1, HIGH);
//delay(500);
//e.digitalWrite(Relais2, HIGH);
//delay(500);
//e.digitalWrite(Relais3, HIGH);
//delay(500);
//e.digitalWrite(Relais_Weiche, HIGH);
//delay(3600000);

}
int digiRead(uint16_t state, int pin) {
  state = state << (15-pin);
  state = state >> 15;
//  Serial.print("digiRead: ");
//  Serial.print(pin);
//  Serial.print(" - ");
//  Serial.println(state);
  return state;
}

//mainAmp

int getStatus() {
  return mainAmp;
}
void mAVolDelta(int val1) {
  if (val1>=0) direct = 1;
  else {
    direct = -1;
    val1 = -val1;
  }
  for (val1; val1>0; val1--) {
    if (direct == 1) irsend.sendRaw(volumeUp, 47, 38);
    else irsend.sendRaw(volumeDown, 47, 38);
    mAVolume = mAVolume + direct;
    if (mAVolume < 0) mAVolume = 0;
    else if (mAVolume >= 0) mAVolume = 81;
    delay(200);
  }
}
void mAVolAbs(int val, int calibration) {
  if (calibration) {
    irsend.sendRaw(mute, 47, 38);
    if (val < 41) mAVolDelta(-81);
    else mAVolDelta(81);
    irsend.sendRaw(mute, 47, 38);
    delay(100);
  }
  mAVolDelta(val-mAVolume);
}
  
