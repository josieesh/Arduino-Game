#include <Arduino.h>
double threshold =0;
volatile double sensorValue = 0;

void setup() {
 threshold = 1000.0 / analogRead(A0);
  Serial.begin (9600);
  Serial.println (threshold);
}

void loop() {
  sensorValue = 1000.0 / analogRead(A0);
  Serial.println(sensorValue);
  if (sensorValue > threshold) {
    Serial.println ("above threshold");
  }
  else
    Serial.println ("below");
  delay(500);

}
