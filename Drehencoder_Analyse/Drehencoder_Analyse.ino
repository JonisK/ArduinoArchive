int up = 9;
int down = 8;
int state[3] = {3, 3, 3};
int statepre = 0;
int statenow = 0;
int statetre = 0;

void setup() {
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH);
  
  Serial.begin(9600);
}

void loop() {
  state[0] = state[1];
  state[1] = (digitalRead(up)<<1) | digitalRead(down);
  
  Serial.println(state[0]);
  Serial.println(state[1]);
  Serial.print(digitalRead(up));
  Serial.println(digitalRead(down));
  
  Serial.println("----");
  
  delay(100);
 
}


