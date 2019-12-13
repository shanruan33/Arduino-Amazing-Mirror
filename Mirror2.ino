//gesture sensor
#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;

//LED
#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    120
CRGB leds[NUM_LEDS];

//#define BRIGHTNESS  20

//distance sensor
// defines pins numbers
const int trigPin = 3;
const int echoPin = 2;
// defines variables
long duration;
int distance;
int brightness = 0; // 0 <= brightness <= 255

void setup() {
  // put your setup code here, to run once:
   FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
   Serial.begin(115200);

  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

    apds.enableProximity(true);
    apds.enableGesture(true);


    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 

   for(int i = 0; i<NUM_LEDS; i++){
       leds[i] = CRGB(60,60,60);   
       FastLED.show();
    }
}

void loop() {
  // put your main code here, to run repeatedly:

   // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
// Calculating the distance
  distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  if(distance < 2000) Serial.println(distance);
  else Serial.println("Invalid");

// //Disco
//  int k = 0;
//  while(true){
//    int i = k % NUM_LEDS;
//    int r = k % 256;
//    int g = (int) (1.5 * k) % 256;
//    int b = (int) (2.5 * k) % 256;
//    leds[i] = CRGB(r,g,b);
//    FastLED.show();
//    k++;
//  }

  //Color temperature
//  int m = 0;
//  while(distance<10){
//    digitalWrite(trigPin, LOW);
//    delayMicroseconds(2);
//    digitalWrite(trigPin, HIGH);
//    delayMicroseconds(10);
//    digitalWrite(trigPin, LOW);
//    duration = pulseIn(echoPin, HIGH);
//    distance= duration*0.034/2;
//    Serial.print("Distance: ");
//    Serial.println(distance);
//    
//    int r = 255;
//    int g = 135 + (m % 6) * 24;
//    int b = 15 + (m % 6) * 48;
//    for(int i = 0; i<NUM_LEDS; i++){
//       leds[i] = CRGB(r,g,b);   
//       FastLED.show();
//    }
//    delay(100);
//    m++;
//  }


  if(distance >= 50 && distance <= 180 && brightness < 5){
    for(int i=0;i<=150;i++){
      brightness++;
      delay(20);
      FastLED.setBrightness(brightness);
      FastLED.show();
      if(brightness == 150) break;
    }
  }

  if(distance > 180 && distance < 2000 && brightness > 5){
    for(int i=0;i<=256;i++){
      brightness--;
      delay(20);
      FastLED.setBrightness(brightness);
      FastLED.show();
      if(brightness == 0 ) break;
    }
  }
  
    uint8_t gesture = apds.readGesture();
    if(gesture == APDS9960_DOWN) Serial.println("v");
    if(gesture == APDS9960_UP) Serial.println("^");
    if(gesture == APDS9960_LEFT) Serial.println("<");
    if(gesture == APDS9960_RIGHT) Serial.println(">");


    if(gesture == APDS9960_DOWN) {
      if(brightness > 235) brightness = 255;
      else brightness += 20;
    }
    if(gesture == APDS9960_UP) {
      if(brightness > 235) brightness = 255;
      else brightness += 20;
    } 
    if(gesture == APDS9960_LEFT) {
      if(brightness < 20) brightness = 0;
      else brightness -= 20;
    }
    if(gesture == APDS9960_RIGHT) {
      if(brightness < 20) brightness = 0;
      else brightness -= 20;
    }
    Serial.println(brightness);

    //if(brightness < 10) break();
    
    FastLED.setBrightness(brightness);
    FastLED.show();

    
//


//
//   for(int j = 20; j < 300; j++){
//      FastLED.setBrightness(j);
//      FastLED.show();
//      FastLED.delay(100);
//      //Serial.println(j);
//    }


}
