#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "WiFi Name";
char pass[] = "password";
char auth[] = "Auth Token";

int red_led = 16;
int green_led = 5;
int yellow_led = 4;
  
void setup(){
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);

  pinMode(red_led, HIGH);
  pinMode(green_led, HIGH);
  pinMode(yellow_led, HIGH);

}
 
void loop(){
  Blynk.run();
}

BLYNK_WRITE(V1){
   Serial.println("Red");
   digitalWrite(green_led, LOW);
   digitalWrite(yellow_led, LOW);
   digitalWrite(red_led, HIGH);
}

BLYNK_WRITE(V2)
{
   Serial.println("Yellow");
   digitalWrite(green_led, LOW);
   digitalWrite(red_led, LOW);
   digitalWrite(yellow_led, HIGH);
}

BLYNK_WRITE(V3)
{
   Serial.println("Green");
   digitalWrite(yellow_led, LOW);
   digitalWrite(red_led, LOW);
   digitalWrite(green_led, HIGH);
}
