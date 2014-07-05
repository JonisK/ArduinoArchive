
//ISR(WDT_vect) { Sleepy::watchdogEvent(); }

//#include <IOexpander.h>

#include <JeeLib.h>
#include <Wire.h>
#include <inttypes.h>
#include <IRremote.h>
#include <Encoder.h>
#include <EEPROM.h>

#define NO_PORTB_PINCHANGES // to indicate that port b will not be used for pin change interrupts
#define NO_PORTC_PINCHANGES // to indicate that port c will not be used for pin change interrupts
#define NO_PIN_STATE        // to indicate that you don't need the pinState
#define NO_PIN_NUMBER       // to indicate that you don't need the arduinoPin
#include <PinChangeInt.h>





enum{ABFRAGE, M_ANSCHALTEN, M_ANSCHALTEN_PHASE2, M_AUSSCHALTEN, M_AUSSCHALTEN_PHASE2, EINGANG_WAEHLEN,
	B_ANSCHALTEN, B_ANSCHALTEN_PHASE2, B_ANSCHALTEN_PHASE3, B_AUSSCHALTEN, B_AUSSCHALTEN_PHASE2, B_AUSSCHALTEN_PHASE3,
	S_ANSCHALTEN, S_AUSSCHALTEN, O_ANSCHALTEN, O_AUSSCHALTEN, I_ANSCHALTEN, I_AUSSCHALTEN,
	LAUTSTAERKE, LAUTER, LEISER, M_LAUTSTAERKE_SCHALTEN, M_LAUTER, M_LEISER, B_LAUTSTAERKE_SCHALTEN, B_LAUTER, B_LEISER,
FERNBEDIENUNG, HAUSMEISTER, LEDS_ANSCHALTEN, LEDS_AUSSCHALTEN, TASK_LIMIT};
enum{RPI, DOCK, COMP, NONE};
enum{SWITCH_ON, ON, SWITCH_OFF, OFF, STANDBY};
enum{M, B, NOTHING};

byte  mStatus = OFF, m_anzuschalten = 0, m_auszuschalten = 0,
eingang = 3, eingang_zu_waehlen, eStatus = OFF, e_anzuschalten = 0, e_auszuschalten = 0, handlungsbedarf = 0,
bStatus = OFF, b_anzuschalten = 0, b_auszuschalten = 0,
sStatus = OFF, s_anzuschalten = 0, s_auszuschalten = 0,
oStatus = OFF, o_anzuschalten = 0, o_auszuschalten = 0,
iStatus = ON, lStatus = B,
m_kalibrieren = 0, mVol_steps = 125, mVol_default = 10,
b_kalibrieren = 0, bVol_steps = 108, bVol_default = 72;

int   mVolume = mVol_default, mVolume_error = 0, //Zwischen 0 und 125
bVolume = bVol_default, bVolume_error = 0, //Zwischen 0 und 108
adresse_eingang = 0x00A0, adresse_lStatus = 0x00A1;

long time = 0;

Encoder Lautstaerke(3, 5);
IRsend irsend;
IRrecv irrecv(7);

decode_results results;

Scheduler scheduler (TASK_LIMIT);

byte c = 0x20, d = 0x21, e = 0x24;

byte dringlichkeit = 0, belegung = 0;
volatile byte interrupt = 0;
byte index = mVol_steps + mVol_default;
byte b_index = bVol_steps + bVol_default;
unsigned int temp;
unsigned int codeTime = 0;
byte wait = 0;

//Pins auf Arduino
byte b_durchschalten = 8;
byte intertrans = 6;

//Pins fuer Fernsteuerungsbox, Port Expander c, 0x20
byte Lautstaerke_minus = 1;
byte Luefter = 2;
byte Lautstaerke_plus = 3;
byte Ethernet_Strom = 5;
byte bass_Schalter = 6;
byte bass_Status = 7;
byte Taster_Encoder = 8;
byte Schalter_LFE = 9;
byte LED_Lautstaerke1 = 10;
byte LED_Lautstaerke2 = 11;
byte Taster = 12;
byte LED_Status = 13;

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
uint16_t c_input_last = 0x0081;
uint16_t c_ledmask = 0x0C00;
uint16_t c_leds = 0;
uint8_t c_dir0 = 0x80;
uint8_t c_dir1 = 0x13;
//uint16_t c_dir = 0x1380;

uint8_t d_input0 = 0;
uint8_t d_input1 = 0;
uint16_t d_input = 0;
uint16_t d_input_last = 0;
uint16_t d_ledmask = 0x00FF;
uint16_t d_leds = 0;
uint8_t d_dir0 = 0x00;
uint8_t d_dir1 = 0xFF;
//uint16_t d_dir = 0xFF00;

uint8_t e_input0 = 0;
uint8_t e_input1 = 0;
uint16_t e_input = 0;
uint8_t e_dir0 = 0x00;
uint8_t e_dir1 = 0x00;

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
	Wire.begin();
	Serial.begin(115200);
	Serial.println("Fernsteuerungsbox am Start");
	delay(100);
	attachInterrupt(0, &ereignis, FALLING);
	pinMode(intertrans, OUTPUT);
	digitalWrite(intertrans, HIGH);
	PCintPort::attachInterrupt(intertrans, &encoder, CHANGE);
	irrecv.enableIRIn();
	
	//  c1.init();
	//  c.pinMode(Lautstaerke_plus, OUTPUT);
	//  c.pinMode(Lautstaerke_minus, OUTPUT);
	//  c.pinMode(Luefter, OUTPUT);
	//  c.pinMode(bass_Schalter, OUTPUT);
	//  c.pinMode(bass_Status, INPUT);
	//  //c.pinMode(Taster_Encoder, INPUT);
	//  //c.pinMode(Schalter_LFE, INPUT);
	//  c.pinMode(LED_Lautstaerke1, OUTPUT);
	//  c.pinMode(LED_Lautstaerke2, OUTPUT);
	//  c.pinMode(Ethernet_Strom, OUTPUT);
	//
	//
	//  c.digitalWrite(Lautstaerke_plus, LOW);
	//  c.digitalWrite(Lautstaerke_minus, HIGH);
	//  Serial.println("mark");
	//  delay(20);
	Wire.beginTransmission(c);
	Wire.write(0x06);
	Wire.write(c_dir0);
	Wire.write(c_dir1);
	Wire.endTransmission();
	//
	pinMode(b_durchschalten, OUTPUT);

	Wire.beginTransmission(d);
	Wire.write(0x06);
	Wire.write(d_dir0);
	Wire.write(d_dir1);
	Wire.endTransmission();

	Wire.beginTransmission(e);
	Wire.write(0x06);
	Wire.write(e_dir0);
	Wire.write(e_dir1);
	Wire.endTransmission();

	writeBit(0x20, Lautstaerke_plus, HIGH);
	writeBit(0x20, Lautstaerke_plus, LOW);
	writeBit(0x21, LED_Alarm, HIGH);
	writeBit(0x21, LED_Alarm, LOW);
	
	Wire.requestFrom(0x20, 2);
	c_input0 = Wire.read();
	c_input1 = Wire.read();
	c_input = (c_input1 << 8) | c_input0;
	//Serial.println(c_input);

	Wire.requestFrom(0x21, 2);
	d_input0 = Wire.read();
	d_input1 = Wire.read();
	d_input = (d_input1 << 8) | d_input0;

	eingang_zu_waehlen = EEPROM.read(adresse_eingang);
	lStatus = EEPROM.read(adresse_lStatus);
	
	if (lStatus == M) scheduler.timer(M_LAUTSTAERKE_SCHALTEN, 0);
	else if (lStatus == B) scheduler.timer(B_LAUTSTAERKE_SCHALTEN, 0);
	
	scheduler.timer(HAUSMEISTER, 100);
	//  scheduler.timer(EINGANG_WAEHLEN, 300);
	Serial.println("Initialisierung abgeschlossen");
	delay(50);
}

void loop()
{
	switch(scheduler.poll()){
		case ABFRAGE:
		//Serial.println(millis() - time);
		if (interrupt == 1) {
			Wire.requestFrom(0x20, 2);
			c_input0 = Wire.read();
			c_input1 = Wire.read();
			c_input = (c_input1 << 8) | c_input0;
			//Serial.println(c_input);
			//Serial.println(c_input&c_dir);
			
			Wire.requestFrom(0x21, 2);
			d_input0 = Wire.read();
			d_input1 = Wire.read();
			d_input = (d_input1 << 8) | d_input0;
			//Serial.println(d_input);
			//Serial.println(d_input&d_dir);
			
			//LOGIK
			if ((c_input&c_dir) != (c_input_last&c_dir)) {
				//Serial.println("Entering C");
				//delay(20);
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
				if (bitRead(c_input, Taster) == 1 && bitRead(c_input_last, Taster) == 0) {
					if (oStatus < 2) {
						o_auszuschalten = 1; 
						writeBit(c, LED_Status, LOW);
					}
					else {
						o_anzuschalten = 1;
						writeBit(c, LED_Status, HIGH);
					}
					
				}
			}
			//      if ((bitRead(c_input, bass_Status) == 0) && (bStatus != SWITCH_ON) && (bStatus != SWITCH_OFF)) {
			//        scheduler.timer(B_ANSCHALTEN_PHASE2, 0);
			//      }
			if ((d_input&d_dir) != (d_input_last&d_dir)) {
				//Serial.println("Entering D");
				//delay(20);
				if (bitRead(d_input, Taster_Strom1) == 1 && bitRead(d_input_last, Taster_Strom1) == 0) {
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
						eingang_zu_waehlen = COMP;
						handlungsbedarf = 1;
					}
				}
			}

			c_input_last = c_input;
			d_input_last = d_input;
			//scheduler.timer(ABFRAGE, 100);
			interrupt = 0;
		}
		if (irrecv.decode(&results)) {
			Serial.println(results.value, HEX);
			switch (results.value) {
				case 0xA2AE493F:
				if (mStatus < 2) m_auszuschalten = 1;
				if (bStatus < 2) b_auszuschalten = 1;
				if (sStatus < 2) s_auszuschalten = 1;
				if (oStatus < 2) o_auszuschalten = 1;
				break;
				case 0x3699C9A3: if (mStatus < 2) m_auszuschalten = 1; else m_anzuschalten = 1; break;
				case 0x418E2267: if (bStatus < 2) b_auszuschalten = 1; else b_anzuschalten = 1; break;
				case 0xEFBEA043: if (sStatus < 2) s_auszuschalten = 1; else s_anzuschalten = 1; break;
				case 0xE812481F: if (oStatus < 2) o_auszuschalten = 1; else o_anzuschalten = 1; break;
				case 0x7B532583: eingang_zu_waehlen = RPI; handlungsbedarf = 1; break;
				case 0x958E13FF: eingang_zu_waehlen = DOCK; handlungsbedarf = 1; break;
				case 0x4441D1DB: eingang_zu_waehlen = COMP; handlungsbedarf = 1; break;
				case 0xAC4DC23F:
				case 0x28B2573F: scheduler.timer(LAUTER, 0); break;
				case 0xCF8D2B1B:
				case 0x3F18D91F: scheduler.timer(LEISER, 0); break;
				case 0x3424805B: irsend.sendRaw(mute, 47, 38); scheduler.timer(FERNBEDIENUNG, codeTime); break;
				case 0x33E2323F: if (eingang < 2) eingang_zu_waehlen = eingang + 1; else eingang_zu_waehlen = 0; handlungsbedarf = 1; break;
				case 0x49EC4A3:  if (eingang > 0) eingang_zu_waehlen = eingang - 1; else eingang_zu_waehlen = 2; handlungsbedarf = 1; break;
				case 0x4706927B: if ((lStatus == B) || (lStatus == NOTHING )) scheduler.timer(M_LAUTSTAERKE_SCHALTEN, 0); else scheduler.timer(B_LAUTSTAERKE_SCHALTEN, 0); belegung = 0; break;
				case 0x83910A1B:
				case 0x9513169F: irsend.sendNEC(0x77E1A0D0, 32); delay(codeTime); scheduler.timer(FERNBEDIENUNG, 0); break; //Weiterleitung Play/Pause
				case 0x8F8E083F: irsend.sendNEC(0x77E160D0, 32); delay(codeTime); scheduler.timer(FERNBEDIENUNG, 0); break; //Weiterleitung Forward
				case 0x511B29DF: irsend.sendNEC(0x77E190D0, 32); delay(codeTime); scheduler.timer(FERNBEDIENUNG, 0); break; //Weiterleitung Rewind
				case 0x6C8A219F: irsend.sendNEC(0x77E150D0, 32); delay(codeTime); scheduler.timer(FERNBEDIENUNG, 0); break; //Weiterleitung Lauter
				case 0xECC622BB: irsend.sendNEC(0x77E130D0, 32); delay(codeTime); scheduler.timer(FERNBEDIENUNG, 0); break; //Weiterleitung Leiser
				
				case 0x317CA6EE:  //Apple Remote Lauter Knopf wurde gedrueckt.
				switch(belegung) {
					case 0: irsend.sendNEC(0x77E150D0, 32); delay(codeTime); scheduler.timer(FERNBEDIENUNG, 0); break;
					case 1: scheduler.timer(LAUTER, 0); belegung = 0; break;
					case 2: if (mStatus < 2) m_auszuschalten = 1; else m_anzuschalten = 1; belegung = 0; break;
				}
				break;
				case 0x1051ABD0:  //Apple Remote Leiser Knopf
				switch(belegung) {
					case 0: irsend.sendNEC(0x77E130D0, 32); delay(codeTime); scheduler.timer(FERNBEDIENUNG, 0); break;
					case 1: scheduler.timer(LEISER, 0); belegung = 0; break;
					case 2: if (bStatus < 2) b_auszuschalten = 1; else b_anzuschalten = 1; belegung = 0; break;
				}
				break;
				case 0x748D5B4C:  //Apple Remote Links Knopf
				switch(belegung) {
					case 0: irsend.sendNEC(0x77E190D0, 32); delay(codeTime); scheduler.timer(FERNBEDIENUNG, 0); break;
					case 1: if (eingang > 0) eingang_zu_waehlen = eingang - 1; else eingang_zu_waehlen = 2; handlungsbedarf = 1; belegung = 0; break;
					case 2: if (sStatus < 2) s_auszuschalten = 1; else s_anzuschalten = 1; belegung = 0; break;
				}
				break;
				case 0xF1BEE9AC:  //Apple Remote Rechts Knopf
				switch(belegung) {
					case 0: irsend.sendNEC(0x77E160D0, 32); delay(codeTime); scheduler.timer(FERNBEDIENUNG, 0); break;
					case 1: if (eingang < 2) eingang_zu_waehlen = eingang + 1; else eingang_zu_waehlen = 0; handlungsbedarf = 1; belegung = 0; break;
					case 2: if (oStatus < 2) o_auszuschalten = 1; else o_anzuschalten = 1; belegung = 0; break;
				}
				break;
				case 0xD3042130:  //Play/Pause auf Apple Remote
				switch(belegung) {
					case 0: irsend.sendNEC(0x77E1A0D0, 32); delay(codeTime); scheduler.timer(FERNBEDIENUNG, 0); break;
					case 1: belegung = 2; break;
					case 2: if (iStatus == ON) scheduler.timer(I_AUSSCHALTEN, 0); else scheduler.timer(I_ANSCHALTEN, 0); belegung = 0; break;
				}
				break;
				case 0xCCE88BEE:    //Menu Taste auf Apple Remote
				switch (belegung) {
					case 0: belegung = 1; break;
					case 1: if ((lStatus == B) || (lStatus == NOTHING )) scheduler.timer(M_LAUTSTAERKE_SCHALTEN, 0); else scheduler.timer(B_LAUTSTAERKE_SCHALTEN, 0); belegung = 0; break;
					case 2: belegung = 0; break;
				}
				break;
				
				
			}
			irrecv.resume(); // Receive the next value
			dringlichkeit = 8;
		}
		if (m_anzuschalten == 1 && mStatus == OFF) scheduler.timer(M_ANSCHALTEN, 0);
		else if (m_auszuschalten == 1 && mStatus == ON) scheduler.timer(M_AUSSCHALTEN, 0);
		
		if (b_anzuschalten == 1 && bStatus == OFF) scheduler.timer(B_ANSCHALTEN, 0);
		else if (b_auszuschalten == 1 && bStatus == ON) scheduler.timer(B_AUSSCHALTEN, 0);
		
		if (s_anzuschalten == 1 && sStatus == OFF) scheduler.timer(S_ANSCHALTEN, 0);
		else if (s_auszuschalten == 1 && sStatus == ON) scheduler.timer(S_AUSSCHALTEN, 0);
		
		if (o_anzuschalten == 1 && oStatus == OFF) scheduler.timer(O_ANSCHALTEN, 0);
		else if (o_auszuschalten == 1 && oStatus == ON) scheduler.timer(O_AUSSCHALTEN, 0);
		
		if (((eingang_zu_waehlen != eingang) || handlungsbedarf == 1 ) && (mStatus == ON)) {
			scheduler.timer(EINGANG_WAEHLEN, 0);
			handlungsbedarf = 0;
		}
		break;
		case M_ANSCHALTEN:
		mStatus = SWITCH_ON;
		m_anzuschalten = 0;
		writeBit(e, Relais1, HIGH);
		writeBit(d, LED_Stromt1, HIGH);
		time = millis();
		scheduler.timer(M_ANSCHALTEN_PHASE2, 1200);
		break;
		case M_ANSCHALTEN_PHASE2:
		Serial.println(millis() - time);
		time = millis();
		irsend.sendRaw(power, 47, 38);
		delay(wait);
		irsend.sendRaw(power, 47, 38);
		Serial.println(millis() - time);
		mStatus = ON;
		scheduler.timer(EINGANG_WAEHLEN, 1800);
		//delay(codeTime);
		scheduler.timer(FERNBEDIENUNG, codeTime);
		break;
		case M_AUSSCHALTEN:
		mStatus = SWITCH_OFF;
		m_auszuschalten = 0;
		time = millis();
		irsend.sendRaw(power, 47, 38);
		delay(wait);
		irsend.sendRaw(power, 47, 38);
		Serial.println(millis() - time);
		writeBit(d, LED_Stromt1, LOW);
		eingang_zu_waehlen = 3;
		time = millis();
		scheduler.timer(EINGANG_WAEHLEN, 0);
		scheduler.timer(M_AUSSCHALTEN_PHASE2, 1000);
		//delay(codeTime);
		scheduler.timer(FERNBEDIENUNG, codeTime);
		break;
		case M_AUSSCHALTEN_PHASE2:
		Serial.println(millis() - time);
		writeBit(e, Relais1, LOW);
		mStatus = OFF;
		eingang_zu_waehlen = 2;
		break;
		case EINGANG_WAEHLEN:
		switch (eingang_zu_waehlen) {
			case RPI:
			irsend.sendRaw(CD, 47, 38);
			delay(2*wait);
			irsend.sendRaw(CD, 47, 38);
			writeBit(d, LED_Eingang1, HIGH);
			writeBit(d, LED_Eingang2, LOW);
			writeBit(d, LED_Eingang3, LOW);
			break;
			case DOCK:
			irsend.sendRaw(VCR1, 47, 38);
			delay(2*wait);
			irsend.sendRaw(VCR1, 47, 38);
			writeBit(d, LED_Eingang1, LOW);
			writeBit(d, LED_Eingang2, HIGH);
			writeBit(d, LED_Eingang3, LOW);
			break;
			case COMP:
			irsend.sendRaw(TAPE, 47, 38);
			delay(2*wait);
			irsend.sendRaw(TAPE, 47, 38);
			writeBit(d, LED_Eingang1, LOW);
			writeBit(d, LED_Eingang2, LOW);
			writeBit(d, LED_Eingang3, HIGH);
			break;
			case NONE:
			writeBit(d, LED_Eingang1, LOW);
			writeBit(d, LED_Eingang2, LOW);
			writeBit(d, LED_Eingang3, LOW);
			break;
		}
		eingang = eingang_zu_waehlen;
		EEPROM.write(adresse_eingang, eingang);
		//delay(codeTime);
		scheduler.timer(FERNBEDIENUNG, codeTime);
		break;
		case B_ANSCHALTEN:
		bStatus = SWITCH_ON;
		b_anzuschalten = 0;
		writeBit(e, Relais2, HIGH);
		writeBit(d, LED_Stromt2, HIGH);
		scheduler.timer(B_ANSCHALTEN_PHASE2, 300);
		break;
		case B_ANSCHALTEN_PHASE2:
		writeBit(c, bass_Schalter, HIGH);
		scheduler.timer(B_ANSCHALTEN_PHASE3, 200);
		break;
		case B_ANSCHALTEN_PHASE3:
		writeBit(c, bass_Schalter, LOW);
		writeBit(c, Luefter, HIGH);
		bStatus = ON;
		break;
		case B_AUSSCHALTEN:
		bStatus = SWITCH_OFF;
		b_auszuschalten = 0;
		writeBit(c, bass_Schalter, HIGH);
		writeBit(d, LED_Stromt2, LOW);
		scheduler.timer(B_AUSSCHALTEN_PHASE2, 200);
		break;
		case B_AUSSCHALTEN_PHASE2:
		writeBit(c, bass_Schalter, LOW);
		writeBit(e, Relais2, LOW);
		scheduler.timer(B_AUSSCHALTEN_PHASE3, 500);
		break;
		case B_AUSSCHALTEN_PHASE3:
		writeBit(c, Luefter, LOW);
		bStatus = OFF;
		break;
		case S_ANSCHALTEN:
		sStatus = SWITCH_ON;
		s_anzuschalten = 0;
		writeBit(e, Relais3, HIGH);
		writeBit(d, LED_Stromt3, HIGH);
		sStatus = ON;
		//scheduler.timer(S_ANSCHALTEN_PHASE2, 7);
		break;
		case S_AUSSCHALTEN:
		sStatus = SWITCH_OFF;
		s_auszuschalten = 0;
		writeBit(e, Relais3, LOW);
		writeBit(d, LED_Stromt3, LOW);
		sStatus = OFF;
		break;
		case O_ANSCHALTEN:
		o_anzuschalten = 0;
		writeBit(e, Relais4, HIGH);
		writeBit(d, LED_Stromt4, HIGH);
		writeBit(c, Ethernet_Strom, HIGH);
		scheduler.timer(LAUTSTAERKE, 0);
		oStatus = ON;
		break;
		case O_AUSSCHALTEN:
		o_auszuschalten = 0;
		writeBit(e, Relais4, LOW);
		writeBit(d, LED_Stromt4, LOW);
		writeBit(c, Ethernet_Strom, LOW);
		oStatus = OFF;
		break;
		case I_ANSCHALTEN:
		iStatus = ON;
		break;
		case I_AUSSCHALTEN:
		iStatus = OFF;
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
		case LAUTER:
		Lautstaerke.write(Lautstaerke.read() + 3);
		scheduler.timer(LAUTSTAERKE, 0);
		break;
		case LEISER:
		Lautstaerke.write(Lautstaerke.read() - 2);
		scheduler.timer(LAUTSTAERKE, 0);
		break;
		case M_LAUTSTAERKE_SCHALTEN:
		lStatus = M;
		writeBit(c, LED_Lautstaerke1, HIGH);
		writeBit(c, LED_Lautstaerke2, LOW);
		Lautstaerke.write(mVolume);
		EEPROM.write(adresse_lStatus, M);
		break;
		case M_LAUTER:
		irsend.sendRaw(volumeUp, 47, 38);
		mVolume++;
		//delay(20);
		scheduler.timer(LAUTSTAERKE, 100);
		//delay(codeTime);
		scheduler.timer(FERNBEDIENUNG, codeTime);
		break;
		case M_LEISER:
		irsend.sendRaw(volumeDown, 47, 38);
		mVolume--;
		//delay(20);
		scheduler.timer(LAUTSTAERKE, 100);
		//delay(codeTime);
		scheduler.timer(FERNBEDIENUNG, codeTime);
		break;
		case B_LAUTSTAERKE_SCHALTEN:
		lStatus = B;
		writeBit(c, LED_Lautstaerke1, LOW);
		writeBit(c, LED_Lautstaerke2, HIGH);
		Lautstaerke.write(bVolume);
		EEPROM.write(adresse_lStatus, B);
		break;
		case B_LAUTER:
		writeBit(c, Lautstaerke_plus, HIGH);
		writeBit(c, Lautstaerke_minus, LOW);
		for(int i=0; i<8000; i++) {
			PORTB ^= 1;
			delayMicroseconds(5);
			PORTB &= ~1;
			delayMicroseconds(1);
		}
		bVolume++;
		scheduler.timer(LAUTSTAERKE, 100);
		break;
		case B_LEISER:
		writeBit(c, Lautstaerke_plus, LOW);
		writeBit(c, Lautstaerke_minus, HIGH);
		for(int i=0; i<8000; i++) {
			PORTB ^= 1;
			delayMicroseconds(5);
			PORTB &= ~1;
			delayMicroseconds(1);
		}
		bVolume--;
		scheduler.timer(LAUTSTAERKE, 100);
		break;
		case FERNBEDIENUNG:
		irrecv.enableIRIn();
		dringlichkeit = 20;
		break;
		case HAUSMEISTER:
		scheduler.timer(ABFRAGE, 0);
		//time=millis();
		if (dringlichkeit > 0) {
			scheduler.timer(HAUSMEISTER, 100);
			dringlichkeit--;
		}
		else {
			scheduler.timer(HAUSMEISTER, 500);
		}
		break;
	}
}

void writeBit(byte addr, byte bitnumber, boolean data) {
	//Serial.println("writeBit");
	switch(addr) {
		case 0x20:
		//Serial.println(temp, BIN);
		temp = bitWrite(c_input, bitnumber, data);
		c_input_last = temp;
		break;
		case 0x21:
		//Serial.println(temp, BIN);
		temp = bitWrite(d_input, bitnumber, data);
		d_input_last = temp;
		break;
		case 0x24:
		e_input = bitWrite(e_input, bitnumber, data);
		temp = e_input;
		break;
	}
	//Serial.println(temp, BIN);
	byte temp0 = temp;
	//Serial.println(temp0, BIN);
	byte temp1 = temp >> 8;
	//Serial.println(temp1, BIN);
	Wire.beginTransmission(addr);
	Wire.write(0x00);
	Wire.write(temp0);
	Wire.write(temp1);
	Wire.endTransmission();
	//Serial.println("Finished!\n");
}

void ereignis() {
	scheduler.timer(ABFRAGE, 0);
	interrupt = 1;
}
void encoder() {
	scheduler.timer(LAUTSTAERKE, 0);
}
