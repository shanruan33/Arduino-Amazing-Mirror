//gesture sensor library file
#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;

//LED library file and LED set up
#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    120
CRGB leds[NUM_LEDS];



//distance sensor set up
// defines pins numbers
const int trigPin = 3;
const int echoPin = 2;
// defines variables
long duration;
int distance;
int brightness = 0; // 0 <= brightness <= 255

void setup() {
  // set up LED lights and show it in monitor window
   FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
   Serial.begin(115200);

  // set up gesture sensor and show it in monitor window
  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

    apds.enableProximity(true);
    apds.enableGesture(true);

  // set up distance sensor
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 

  //start the LEDs
   for(int i = 0; i<NUM_LEDS; i++){
       leds[i] = CRGB(60,60,60);   
       FastLED.show();
    }
}

void loop() {

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

// //Disco ---- other versions of the lighting
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

  //Color temperature ---- other versions of the lighting
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

// when user approaching the mirror, LEDs light up
  if(distance >= 50 && distance <= 180 && brightness < 5){
    for(int i=0;i<=150;i++){
      brightness++;
      delay(20);
      FastLED.setBrightness(brightness);
      FastLED.show();
      if(brightness == 150) break;
    }
  }
// when user leaving the mirror, LED light down and turn off
  if(distance > 180 && distance < 2000 && brightness > 5){
    for(int i=0;i<=256;i++){
      brightness--;
      delay(20);
      FastLED.setBrightness(brightness);
      FastLED.show();
      if(brightness == 0 ) break;
    }
  }
  
  // show the gesture sensor signals in monitor window
    uint8_t gesture = apds.readGesture();
    if(gesture == APDS9960_DOWN) Serial.println("v");
    if(gesture == APDS9960_UP) Serial.println("^");
    if(gesture == APDS9960_LEFT) Serial.println("<");
    if(gesture == APDS9960_RIGHT) Serial.println(">");

  // connect gesture with the brightness of LEDs, when move between left and right, brightness goes down, when move up and down, brightness goes up
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



}
