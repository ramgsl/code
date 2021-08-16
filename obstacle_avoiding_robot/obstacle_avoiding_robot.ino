#include <NewPing.h>
NewPing sonar(A0, A1, 1000);

const int PWMA = 9;
const int AIN2 = 8;
const int AIN1 = 7;

const int BIN1 = 4;
const int BIN2 = 3;
const int PWMB = 2;

int dist = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}

void loop() {
  dist = readPing();
  Serial.println(dist);
  if (dist<20) {
    back();
    left();
  }else{
  forward();
  }
}

int readPing() {
  delay(100);
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}

void forward(){
  Serial.println("Forward"); 
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 130);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, 130);
  delay(300);
}

void back(){
  Serial.println("Back"); 
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 130);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 130);
  delay(300);
}

void left(){
  Serial.println("Left"); 
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 130);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 130);
  delay(300);
}