#include "main.h"

#define DEEP_SLEEP 30 // in minutes
#define BAUD_RATE 57600

void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println();
  runProgram();
  ESP.deepSleep(DEEP_SLEEP * 60 * 1000000); // x minutes in nanoseconds
}

void loop() {
}
