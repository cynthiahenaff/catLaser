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

void servosAttach() {
  servoX.attach(D5);
  servoY.attach(D6);
}

void servosDetach() {
  servoX.detach();
  servoY.detach();
}



bool runLoop = false;
BLYNK_WRITE(V0) {
  servosAttach();

  if (param.asInt() == 1) {
    servoX.write(90);
    servoY.write(5);
    digitalWrite (D7, HIGH);
    runLoop = true;
  } else {
    digitalWrite (D7, LOW);
    servoX.write(90);
    servoY.write(5);
    runLoop = false;
  }

  servosDetach();
}

void setup() {
  pinMode(D7, OUTPUT);

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

  servosAttach();

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

  servosDetach();

  int randomDelay = random(minFreeze, maxFreeze);
  delay(randomDelay);
}