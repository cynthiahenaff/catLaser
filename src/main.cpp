#define BLYNK_PRINT Serial

#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "secrets.h"


char auth[] = BLYNK_TOKEN;

char ssid[] = SSID;
char pass[] = PASSWORD;

int minFreeze = 200;
int maxFreeze = 2500;


Servo servoX;
Servo servoY;

bool runLoop = false;

WidgetLED led1(V1);

BLYNK_WRITE(V0) {   

  if (param.asInt() == 1) {
    servoX.write(90);
    servoY.write(5);
    digitalWrite (D7, HIGH);
    led1.on();
    runLoop = true;
  } else {
    digitalWrite (D7, LOW);
    led1.off();
    servoX.write(90);
    servoY.write(5);
    runLoop = false;
  }
  
}


void setup() {
  servoX.attach(D5);
  servoY.attach(D6);

 
  pinMode (D7, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Starting");
  Blynk.begin(auth, ssid, pass);
}

int oldX;
int oldY;

void loop() {

  Blynk.run();

  if (runLoop == false) {
    return;
  }
  
  int finalX = random(30, 150);

  if (finalX >= oldX) {
    for (int currentX = oldX; currentX <= finalX; currentX++) {
      servoX.write(currentX);
      delay(10);
    }
  }
  else {
    for (int currentX = oldX; currentX >= finalX; currentX--) {
      servoX.write(currentX);
      delay(10);
    }
  }
  oldX = finalX;

  int finalY = random(0, 40);

  if (finalY >= oldY) {
    for (int currentY = oldY; currentY <= finalY; currentY++) {
      servoY.write(currentY);
      delay(10);
    }
  }
  else {
    for (int currentY = oldY; currentY >= finalY; currentY--) {
      servoY.write(currentY);
      delay(10);
    }
  }
  oldY = finalY;

  int randomDelay = random(minFreeze, maxFreeze);
  delay(randomDelay);
 
  
}