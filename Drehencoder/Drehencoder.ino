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
  
  if (state[1] != state[0]) {
    //Serial.println("Looking for second state change");
    //Serial.println(state[0]);
    //Serial.println(state[1]);
    //Serial.print(digitalRead(up));
    //Serial.println(digitalRead(down));
   
    for (int i=0; i<50; i++) {
      state[2] = (digitalRead(up)<<1) | digitalRead(down);
     
      if ((state[2] != state[1])&&(state[2] != state[0])) {
        state[2] = statenow;
        analyseState();
        break;
      }
      delay(1);
      for (int i=0; i<3; i++) {
        state[i] = 3;
      }
    }
  delay(1);
  } 
}

void analyseState() {
  //Serial.println("Second change found");
  statetre = state[0]<<4 | state[1]<<2 | state[2];
  Serial.println(statetre);
  
  if (statetre==7 || statetre==30 || statetre==33 || statetre==56) {
    Serial.println("up");
  }
  else if (statetre==11 || statetre==18 || statetre==45 || statetre==52) {
    Serial.println("down");
  }
}
