#include <Servo.h>
Servo myservo;

int ledPin = 12;
int servoPin = 9;
int inputPin = 5;

int pirState = LOW;
bool expr = true;

int val = 0;
int pos = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
  myservo.attach(servoPin);
  Serial.begin(9600);  
}

void loop(){
  val = digitalRead(inputPin);
  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
    
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      if (expr == false){
        happy();
        expr = true;
      }
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW);
    if (pirState == HIGH){
      Serial.println("Motion ended!");
      if(expr == true){
        digitalWrite(ledPin, LOW);
        sad();
        expr = false;
      }
      pirState = LOW;
    }
  }
}

void happy(){
  for (pos = 30; pos <= 160; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
}

void sad(){
  for (pos = 160; pos >= 30; pos -= 1) { 
    myservo.write(pos);
    delay(15);
  }
}
