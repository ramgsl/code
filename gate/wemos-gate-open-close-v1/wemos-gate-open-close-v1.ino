#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "WEMOS_Motor.h"

//Motor shield default I2C Address: 0x30
Motor M1(0x30, _MOTOR_A, 1000);

int close_pin = 2;
int open_pin = 0;

int close_pin_status = 2;
int open_pin_status = 2;

char ssid[] = "DarKnight";
char pass[] = "JonnyDepp@pirates#4";
char auth[] = "gINvOrQpcH4bTOOmDmXFF9XuIfJQtsBn";

void setup(){
  Serial.begin(57600);
  Blynk.begin(auth, ssid, pass);
  delay(1000);
  pinMode(open_pin, INPUT);
  pinMode(close_pin, INPUT);
  delay(10000);
}

void loop(){
  Blynk.run();
}

BLYNK_WRITE(V0){
  open_gate();
}

BLYNK_WRITE(V1){
  close_gate();
}

void close_gate(){
  while(true){
    if(close_pin_status == 0){
      break;
    }
    close_pin_status = digitalRead(close_pin);
    Serial.print("close_pin_status: ");
    Serial.println(close_pin_status);
    if(close_pin_status == 0){
      M1.setmotor(_STOP);
      delay(50);
      break;
    }
    if(close_pin_status == 1){
      Serial.println("Closing the Gate...");
      M1.setmotor(_CW, 255);
      delay(500);
      M1.setmotor(_STOP);
    }
  }
  M1.setmotor(_STANDBY);
  digitalWrite(open_pin, LOW);
  digitalWrite(close_pin, LOW);
}

void open_gate(){
  while(true){
    if(open_pin_status == 0){
      break;
    }
    open_pin_status = digitalRead(open_pin);
    Serial.print("open_pin_status: ");
    Serial.println(open_pin_status);
    if(open_pin_status == 0){
      M1.setmotor(_STOP);
      delay(50);
      break;
    }
    if(open_pin_status == 1){
      Serial.println("Open the Gate...");
      M1.setmotor(_CCW, 255);
      delay(500);
      M1.setmotor(_STOP);
    }
  }
  M1.setmotor(_STANDBY);
  digitalWrite(open_pin, LOW);
  digitalWrite(close_pin, LOW);
}
