#define ledPin 13
volatile byte counter = 0;
void setup()
{
  pinMode(ledPin, OUTPUT);
  
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;

  OCR2A = 225;            // compare match register 16MHz/256/2Hz
  //TCCR2B |= (1 << WGM12);   // CTC mode
  TCCR2B |= (1 << CS22);    // 256 prescaler 
  TCCR2B |= (1 << CS21);
  TCCR2B |= (1 << CS20);
  TIMSK2 |= (1 << OCIE2A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
}

ISR(TIMER2_COMPA_vect)          // timer compare interrupt service routine
{
  if (counter < 4) counter++;
  else {
   counter = 0;
   digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin
  }
}

void loop()
{
  // your program here...
  while (1) {}
}
