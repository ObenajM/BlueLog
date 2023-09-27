#include <Arduino.h>

// put function declarations here:
//int myFunction(int, int);
#ifndef LED_BUILTIN
  #define LED_BUILTIN 13
#endif

void setup() {
  // put your setup code here, to run once:
 pinMode(LED_BUILTIN,OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

// put function definitions here:
