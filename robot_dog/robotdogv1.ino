#include <Arduino.h>
#include <Servo.h>
#include <Arduino_APDS9960.h>

Servo tail_servo;
Servo up_down_servo;
Servo left_right_servo;

int led_pin = 5;
int touch_pin = 3;
int tail_servo_pin = 8;
int up_down_servo_pin = 7;
int left_right_servo_pin = 6; 

const int motor1pin1  = 9;
const int motor1pin2  = 10;
const int motor2pin1  = 11;
const int motor2pin2  = 12;

int pos = 0; 
int signal1  = 0; 

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
  }
  APDS.setGestureSensitivity(80);

  tail_servo.attach(tail_servo_pin);
  left_right_servo.attach(left_right_servo_pin);

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  
  pinMode(touch_pin, INPUT);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  if (APDS.gestureAvailable()) {
    int gesture = APDS.readGesture();

    switch (gesture) {
      case GESTURE_UP:
        Serial.println("Detected UP gesture");
        head_up();
        break;

      case GESTURE_DOWN:
        Serial.println("Detected DOWN gesture");
        head_down();
        break;

      case GESTURE_LEFT:
        Serial.println("Detected LEFT gesture");
        left();
        break;

      case GESTURE_RIGHT:
        Serial.println("Detected RIGHT gesture");
        right();
        break;

      default:
        stop1();
        break;
    }
  }
  
  signal1 = digitalRead(touch_pin);
  if(signal1 == HIGH){
    digitalWrite(led_pin, HIGH);
    tail();
  }else{
    digitalWrite(led_pin, LOW);
  }
}

void left(){
    Serial.println("left");
    for (pos = 75; pos >= 20; pos -= 1) {
      left_right_servo.write(pos);
      delay(5);
    }
    digitalWrite(motor1pin1,LOW);
    digitalWrite(motor1pin2,HIGH);
    digitalWrite(motor2pin1,LOW);
    digitalWrite(motor2pin2,HIGH);
   
    delay(1000);
    stop1();
    for (pos = 20; pos <= 75; pos += 1) {
      left_right_servo.write(pos);
      delay(5);
    }
    
}

void right(){
    Serial.println("right");
    for (pos = 75; pos <= 130; pos += 1) {
      left_right_servo.write(pos);
      delay(5);
    }
    digitalWrite(motor1pin1,HIGH);
    digitalWrite(motor1pin2,LOW);
    digitalWrite(motor2pin1,HIGH);
    digitalWrite(motor2pin2,LOW);

    delay(1000);
    stop1();
    for (pos = 130; pos >= 75; pos -= 1) {
      left_right_servo.write(pos);
      delay(5);
    }
}

void stop1(){
    Serial.println("Stop! ");  
    digitalWrite(motor1pin1,LOW);
    digitalWrite(motor1pin2,LOW);
    digitalWrite(motor2pin1,LOW);
    digitalWrite(motor2pin2,LOW);
}

void head_down() {
  up_down_servo.attach(up_down_servo_pin);  
  for (pos = 90; pos <= 120; pos += 1) {
    up_down_servo.write(pos);
    delay(5);
  }
  for (pos = 120; pos >= 90; pos -= 1) {
    up_down_servo.write(pos);
    delay(5);
  }
  up_down_servo.detach();    
}

void head_up() {
  up_down_servo.attach(up_down_servo_pin);  
  for (pos = 90; pos >= 60; pos -= 1) {
    up_down_servo.write(pos);
    delay(5);
  }
  for (pos = 60; pos <= 90; pos += 1) {
    up_down_servo.write(pos);
    delay(5);
  }
  up_down_servo.detach();      
}

void tail() {
  for (pos = 75; pos >= 60; pos -= 1) {
    tail_servo.write(pos);
    delay(3);
  }
  for (pos = 60; pos <= 75; pos += 1) {
    tail_servo.write(pos);
    delay(3);
  }
  for (pos = 75; pos <= 90; pos += 1) {
    tail_servo.write(pos);
    delay(3);
  }
  for (pos = 90; pos >= 75; pos -= 1) {
    tail_servo.write(pos);
    delay(3);
  }
}
