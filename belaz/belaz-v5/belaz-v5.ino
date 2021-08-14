#include <EnableInterrupt.h>

#define SERIAL_PORT_SPEED 115200
#define RC_NUM_CHANNELS  4

#define RC_CH1  0
#define RC_CH2  1
#define RC_CH3  2
#define RC_CH4  3

#define RC_CH1_INPUT  A0
#define RC_CH2_INPUT  A1
#define RC_CH3_INPUT  A2
#define RC_CH4_INPUT  A3

int ch1_val;
int ch2_val;
int ch3_val;
int ch4_val;

int motor_a1 = 8;
int motor_a2 = 9;
int motor_ae = 10;
int motor_be = 11;
int motor_b1 = 12;
int motor_b2 = 13;

int motor_f1 = 7;
int motor_f2 = 2;
int motor_r1 = 3;
int motor_r2 = 4;
int motor_fe = 5;
int motor_re = 6; 

uint16_t rc_values[RC_NUM_CHANNELS];
uint32_t rc_start[RC_NUM_CHANNELS];
volatile uint16_t rc_shared[RC_NUM_CHANNELS];

void rc_read_values() {
  noInterrupts();
  memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  interrupts();
}

void calc_input(uint8_t channel, uint8_t input_pin) {
  if (digitalRead(input_pin) == HIGH) {
    rc_start[channel] = micros();
  } else {
    uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
    rc_shared[channel] = rc_compare;
  }
}

void calc_ch1() { calc_input(RC_CH1, RC_CH1_INPUT); }
void calc_ch2() { calc_input(RC_CH2, RC_CH2_INPUT); }
void calc_ch3() { calc_input(RC_CH3, RC_CH3_INPUT); }
void calc_ch4() { calc_input(RC_CH4, RC_CH4_INPUT); }

void setup() {
  Serial.begin(SERIAL_PORT_SPEED);

  pinMode(motor_a1, OUTPUT);
  pinMode(motor_a2, OUTPUT);
  pinMode(motor_b1, OUTPUT);
  pinMode(motor_b2, OUTPUT);

  pinMode(motor_ae, OUTPUT);
  pinMode(motor_be, OUTPUT);
  
  analogWrite(motor_ae, 100);
  analogWrite(motor_be, 100);  

  pinMode(motor_f1, OUTPUT);
  pinMode(motor_f2, OUTPUT);
  pinMode(motor_r1, OUTPUT);
  pinMode(motor_r2, OUTPUT);

  pinMode(motor_fe, OUTPUT);
  pinMode(motor_re, OUTPUT);
  
  analogWrite(motor_fe, 150);
  analogWrite(motor_re, 150);  

  pinMode(RC_CH1_INPUT, INPUT);
  pinMode(RC_CH2_INPUT, INPUT);
  pinMode(RC_CH3_INPUT, INPUT);
  pinMode(RC_CH4_INPUT, INPUT);

  enableInterrupt(RC_CH1_INPUT, calc_ch1, CHANGE);
  enableInterrupt(RC_CH2_INPUT, calc_ch2, CHANGE);
  enableInterrupt(RC_CH3_INPUT, calc_ch3, CHANGE);
  enableInterrupt(RC_CH4_INPUT, calc_ch4, CHANGE);
}

void loop() {
  rc_read_values();

  ch1_val = rc_values[RC_CH1];
  ch2_val = rc_values[RC_CH2];
  ch3_val = rc_values[RC_CH3];
  ch4_val = rc_values[RC_CH4];
  
  if (ch1_val >1700) {
    f_right();
    Serial.print("-----------CH1 - Right - ");
    Serial.println(ch1_val);
  }

  if (ch1_val > 1200 && ch1_val < 1700) {
    f_stopturn();
    Serial.print("-----------CH1 - Not Turn - "); 
    Serial.println(ch1_val);
  }

  if (ch1_val > 10 && ch1_val < 1100) {
    f_left();
    Serial.print("-----------CH1 - Left - "); 
    Serial.println(ch1_val);     
  }

  // for real turning
  if (ch2_val >1700) {
    r_right();
    Serial.print("-----------CH2 - Right - ");
    Serial.println(ch2_val);
  }

  if (ch2_val > 1200 && ch2_val < 1700) {
    r_stopturn();
    Serial.print("-----------CH2 - Not Turn - "); 
    Serial.println(ch2_val);
  }

  if (ch2_val > 10 && ch2_val < 1100) {
    r_left();
    Serial.print("-----------CH2 - Left - ");
    Serial.println(ch2_val);
  }

// for forward - backward

  if (ch3_val >1800) {
    front();
    Serial.print("CH3 - Forward - "); 
    Serial.println(ch3_val);
  }

  if (ch3_val > 1200 && ch3_val < 1800) {
    stop1();
    Serial.print("CH3 - Stop - "); 
    Serial.println(ch3_val);
  }

  if (ch3_val > 10 && ch3_val < 1200) {
     back();
     Serial.print("CH3 - Backward - "); 
     Serial.println(ch3_val);
  }
 
  delay(200);
}

void front(){
    digitalWrite(motor_a1,LOW);
    digitalWrite(motor_a2,HIGH);
    digitalWrite(motor_b1,LOW);
    digitalWrite(motor_b2,HIGH);
}

void back(){
    digitalWrite(motor_a1,HIGH);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_b1,HIGH);
    digitalWrite(motor_b2,LOW);
}

void stop1(){
    digitalWrite(motor_a1,LOW);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_b1,LOW);    
    digitalWrite(motor_b2,LOW);
}

void f_left(){
    digitalWrite(motor_f1,HIGH);
    digitalWrite(motor_f2,LOW);
}

void f_right(){
    digitalWrite(motor_f1,LOW);
    digitalWrite(motor_f2,HIGH);
}

void r_left(){
    digitalWrite(motor_r1,HIGH);
    digitalWrite(motor_r2,LOW);
}

void r_right(){
    digitalWrite(motor_r1,LOW);
    digitalWrite(motor_r2,HIGH);
}

void f_stopturn(){
    digitalWrite(motor_f1,LOW);
    digitalWrite(motor_f2,LOW);
}

void r_stopturn(){    
    digitalWrite(motor_r1,LOW);
    digitalWrite(motor_r2,LOW);
}
