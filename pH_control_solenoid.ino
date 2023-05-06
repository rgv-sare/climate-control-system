#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// GAOHOU pH sensor pins
const int pHsensorPin = A0;

// Relay pins
const int relay1 = 2;
const int relay2 = 3;
const int relay3 = 4;

// Timer variables
unsigned long relay3Timer = 0;
const unsigned long relay3Interval = 7200000; // change it to accomodate the delay in nutrients release

// pH value variable
float pHValue = 0;

void setup() {
  // Set up relay pins
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  
  // Set relay pins to LOW (off)
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);

  // Serial communication at 9600 baud
  Serial.begin(9600);
}

void loop() {
  // Reads the pH sensor value
  int sensorValue = analogRead(pHsensorPin);
  
  // Converts voltage to pH
  pHValue = (float)sensorValue * (5.0 / 1024) * 14;
  
  // Prints pH value to the serial monitor for debugging
  Serial.print("pH Value: ");
  Serial.println(pHValue);

  // Activates solenoids on a pH range (should be 6.5 - 7.0 for radishes)
  if (pHValue < 7) {
    digitalWrite(relay1, HIGH);
    delay(2000);
    digitalWrite(relay1, LOW);
  }
  else if (pHValue > 7) {
    digitalWrite(relay2, HIGH);
    delay(2000);
    digitalWrite(relay2, LOW);
  }

  // Activate solenoid3 every designated interval
  if (millis() - relay3Timer >= relay3Interval) {
    digitalWrite(relay3, HIGH);
    delay(5000);
    digitalWrite(relay3, LOW);
    relay3Timer = millis();
  }
  
  // Delay before taking the next reading
  delay(1000);
}
