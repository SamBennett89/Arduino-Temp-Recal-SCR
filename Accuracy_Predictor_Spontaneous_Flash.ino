# include <Average.h>

// pin numbers
const int buttonPin[]       = {2, 3, 4};
const int ledPin[]          = {8, 9, 10};
const int promptLedPin      = 11;
const int SCRPin            = 21;

// order of conditions
int condition[]             = {1, 0, 2, 0, 2, 1, 1, 2, 0};

// prediciton accuracy arrays
int accuracy[][30]         = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}};
int accuracyHistory[]       = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int accuracyOverall[][30]  = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

// delay times
int durationAdaptation      = 150;
int durationOnOff           = 10;
int durationDebounce        = 200;
int durationTrialEnd        = 5000;
int promptRange             = 4000;
int promptMinimum           = 4000;
int delayTime[]             = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 50, 50};
int delayHistory[]          = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// number of trials per cond / button presses per trial
int numTrials               = 30;
int numButtonPress[]        = {5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10};
int buttonPressHistory[]    = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// timers
unsigned long lastButtonTime    = 0;
unsigned long elapsedTime[]     = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int buttonTimeAvg               = 0;

// counters
int b  = 0;
int t  = 0;
int c  = 0;
int id = 0;

// array identifier
int acc   = 0;
int bp    = 0;
int dt    = 0;

// buttonstate checkers
boolean buttonState        = true;
int buttonNumber           = 0;
int buttonNumberIncorrect  = 0;

void setup() {
  for(int i = 0; i < 3; i++){
    pinMode(buttonPin[i], INPUT_PULLUP);
    pinMode(ledPin[i], OUTPUT); 
  }
  pinMode(promptLedPin, OUTPUT);
  pinMode(SCRPin, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  for(c = 0; c < 9; c++){
    t = 0;
    trial();
  }
  digitalWrite(promptLedPin, HIGH);
  delay(10000);
  digitalWrite(promptLedPin, LOW);
}

void trial() {
  while(t < numTrials){
    b = 0;
    while(b < numButtonPress[bp]){
      buttonRead();
    }
    while(b == numButtonPress[bp]){
      if(delayTime[dt] > 0){
        flashBefore();
      }
      else{
        buttonRead();
      }
    }
    while(b == numButtonPress[bp] + 1){
      digitalWrite(promptLedPin, HIGH);
      delay(promptMinimum + random(promptRange));
      digitalWrite(promptLedPin, LOW);
      for(int i = 0; i < 15; i++){
      elapsedTime[i] = 0;
      }
      t++;
      if(t < numTrials){
      selectDelay();
      selectNumButtonPress();
      if(delayTime[dt] == 0){
        selectAcc();
      }
      }
      b++; 
    }  
  }
  while(t == numTrials){
    for(int i = 0; i < 5; i++){
      delay(durationTrialEnd/10);
      digitalWrite(promptLedPin, HIGH);
      delay(durationTrialEnd/10);
      digitalWrite(promptLedPin, LOW);
    }
    for(int i = 0; i < 30; i++){
      accuracyHistory[i] = 0;
    }
    for(int i = 0; i < 30; i++){
      delayHistory[i] = 0;
    }
    for(int i = 0; i < 30; i++){
      buttonPressHistory[i] = 0;
    }
    t++;  
  }
}

void buttonRead() {
  for(buttonNumber = 0; buttonNumber < 3; buttonNumber++) {
    buttonState = digitalRead(buttonPin[buttonNumber]);
    if(buttonState == false){
      buttonPress();
    }
  }
}

void buttonPress() {
  printTime();
  lastButtonTime = millis();
  if(b == 0){
    Serial.print(t+1); 
    Serial.print(",");
    Serial.print(condition[c]+1);
    Serial.print(",");
  }
  if(b < numButtonPress[bp]){
    delay(durationAdaptation);
    for(int i = 0; i < 3; i++){
      digitalWrite(ledPin[i], HIGH);
    }
    delay(durationOnOff);
    for(int i = 0; i < 3; i++){
      digitalWrite(ledPin[i], LOW);
    }
    delay(durationDebounce);
  }
  if(b == numButtonPress[bp]){
    if(accuracy[condition[c]][acc] == 1){
      Serial.println(accuracy[condition[c]][acc]);
      digitalWrite(SCRPin, HIGH);
      digitalWrite(ledPin[buttonNumber], HIGH);
      delay(durationOnOff);
      digitalWrite(ledPin[buttonNumber], LOW);
      delay(durationDebounce);
      digitalWrite(SCRPin, LOW);
      
    }
    if(accuracy[condition[c]][acc] == 0) {
      do{
        buttonNumberIncorrect = random(3);
      }
      while(buttonNumberIncorrect == buttonNumber);
      Serial.println(accuracy[condition[c]][acc]);
      digitalWrite(SCRPin, HIGH);
      digitalWrite(ledPin[buttonNumberIncorrect], HIGH);
      delay(durationOnOff);
      digitalWrite(ledPin[buttonNumberIncorrect], LOW);
      delay(durationDebounce);
      digitalWrite(SCRPin, LOW);
    }
  }
  b++;
}

void printTime(){
  if(b > 0){
    elapsedTime[b-1] = millis() - lastButtonTime;
    Serial.print(elapsedTime[b-1]);
    Serial.print(","); 
  }
}

void flashBefore(){
  for(int i = 0; i < numButtonPress[bp] - 1; i++){
    buttonTimeAvg += elapsedTime[i];
  }
  buttonTimeAvg = buttonTimeAvg / (numButtonPress[bp] - 1);
  do{
    elapsedTime[b-1] = millis();
  }
  while(elapsedTime[b-1] < (buttonTimeAvg - delayTime[dt]));
  if(elapsedTime[b-1] == (buttonTimeAvg - delayTime[dt])){
    buttonNumberIncorrect = random(3);
    Serial.println("-");
    digitalWrite(SCRPin, HIGH);
    digitalWrite(ledPin[buttonNumberIncorrect], HIGH);
    delay(durationOnOff);
    digitalWrite(ledPin[buttonNumberIncorrect], LOW);
    delay(durationDebounce);
    digitalWrite(SCRPin, LOW);
  }
  if(elapsedTime[b-1] > 2000){
    buttonNumberIncorrect = random(3);
    Serial.println("-");
    digitalWrite(SCRPin, HIGH);
    digitalWrite(ledPin[buttonNumberIncorrect], HIGH);
    delay(durationOnOff);
    digitalWrite(ledPin[buttonNumberIncorrect], LOW);
    delay(durationDebounce);
    digitalWrite(SCRPin, LOW);
  }
  b++;
}

void selectNumButtonPress(){
  do{
    bp = random(30);
  }
  while(buttonPressHistory[bp] == 1);
  buttonPressHistory[bp] = 1;
}

void selectDelay(){
  do{
    dt = random(30);
  }
  while(delayHistory[dt] == 1);
  delayHistory[dt] = 1;
}

void selectAcc(){
  do{
    acc = random(30);
  }
  while(accuracyHistory[acc] == 1);
  accuracyOverall[c][b] = accuracy[condition[c]][acc];
  accuracyHistory[acc] = 1;
}
