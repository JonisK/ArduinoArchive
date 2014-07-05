//Raw Codes fuer den Technics Verstaerker SA-GX130D
//LED an den Ausgang 3 anschließen
//Vorwiderstand bei direktem Anschluss: 100 Ohm
//Vorwiderstand bei Betrieb mit BC547 Transistor: 47 Ohm

#include <IRremote.h>

IRsend irsend;

//Codes
unsigned int power[] = {3450, 3450, 850, 2600, 850, 900, 850, 850, 850, 2600, 850, 900, 800, 900, 850, 850, 850, 900, 850, 850, 850, 900, 850, 2550, 900, 850, 850, 2600, 850, 2600, 850, 900, 850, 2550, 900, 2550, 900, 2550, 900, 2550, 900, 2550, 900, 2550, 900, 850, 850};
unsigned int volumeUp[] = {3450, 3450, 850, 2600, 850, 900, 850, 850, 850, 2600, 850, 900, 800, 900, 850, 850, 850, 2600, 850, 900, 850, 850, 850, 2600, 850, 900, 850, 2550, 900, 2550, 900, 850, 850, 2600, 850, 2600, 850, 2600, 850, 900, 850, 2550, 900, 2550, 900, 850, 850};
unsigned int volumeDown[] = {3450, 3400, 900, 2550, 900, 850, 850, 850, 900, 2550, 900, 850, 850, 2600, 850, 850, 850, 2600, 900, 800, 900, 850, 850, 2600, 850, 850, 900, 2550, 900, 2550, 900, 850, 850, 2600, 850, 850, 900, 2550, 900, 850, 850, 2600, 850, 2600, 850, 850, 900};
unsigned int VCR1[] = {3450, 3400, 900, 2550, 900, 850, 850, 850, 900, 2550, 900, 850, 850, 900, 800, 2600, 850, 2600, 900, 2550, 900, 2550, 900, 2550, 900, 850, 850, 2600, 850, 2600, 850, 900, 850, 2550, 900, 2550, 900, 850, 850, 900, 850, 850, 850, 900, 800, 850, 900};
unsigned int CD[] = {3500, 3400, 900, 2550, 900, 850, 850, 900, 800, 2600, 850, 900, 850, 2600, 850, 2600, 850, 900, 800, 2600, 850, 2600, 900, 2550, 900, 850, 850, 2600, 850, 2600, 850, 900, 850, 2550, 900, 850, 850, 900, 800, 2600, 850, 900, 850, 850, 850, 850, 900};
unsigned int TAPE[] = {3500, 3400, 850, 2600, 900, 800, 900, 850, 850, 2600, 900, 800, 900, 850, 850, 850, 900, 2550, 900, 2550, 900, 2550, 900, 2550, 900, 850, 850, 2550, 900, 2550, 900, 850, 900, 2550, 900, 2550, 900, 2550, 900, 850, 850, 850, 900, 850, 850, 850, 900};
unsigned int mute[] = {3450, 3450, 850, 2600, 850, 900, 850, 850, 850, 2600, 850, 900, 850, 2550, 900, 2550, 900, 2550, 900, 850, 850, 900, 800, 2650, 800, 900, 850, 2600, 850, 2600, 850, 900, 800, 2600, 850, 900, 850, 900, 800, 900, 850, 2600, 850, 2550, 900, 850, 850};

void setup() {
}

void loop() {
  irsend.sendRaw(power, 47, 38);
  delay(2000);
  for (int i=0; i<20; i++) {
    irsend.sendRaw(volumeUp, 47, 38);
    delay(500);
  }
  for (int i=0; i<20; i++) {
    irsend.sendRaw(volumeDown, 47, 38);
    delay(500);
  }
  irsend.sendRaw(VCR1, 47, 38);
  delay(200);
  irsend.sendRaw(TAPE, 47, 38);
  delay(200);
  irsend.sendRaw(power, 47, 38);
  delay(2000000);
}

