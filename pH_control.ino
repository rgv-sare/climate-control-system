#include <Stepper.h>

// pH sensor pin
const int pH_sensor_pin = A0;

// L298N motor driver pins
const int motor_pin1 = 2;
const int motor_pin2 = 3;
const int motor_pin3 = 4;
const int motor_pin4 = 5;

// Steps per revolution
const int steps_per_revolution = 200; // Modify this value according to your stepper motor

// Creating an object for the Creality stepper
Stepper stepper(steps_per_revolution, motor_pin1, motor_pin2, motor_pin3, motor_pin4);

void setup() {
  // Motor speed
  stepper.setSpeed(60); // Adjust the speed as desired (in RPM)

  // Serial communication
  Serial.begin(9600); // Initialize the serial monitor for debugging
}

void loop() {
  // Reads pH value from the sensor
  int pH_raw = analogRead(pH_sensor_pin);
  float pH_value = (float)pH_raw / 1023 * 14; // Converts the raw value to pH (0-14)
  Serial.print("pH Value: "); // Prints "pH Value: " on the serial monitor
  Serial.println(pH_value);   // Prints the pH value on the serial monitor

  // Determines motor direction based on pH value
  if (pH_value < 7) {
    // Rotates stepper motor 0.5 revolutions clockwise if < 7
    Serial.println("Rotating 0.5 revolutions clockwise");
    stepper.step(steps_per_revolution / 2);
  } else if (pH_value > 7) {
    // Rotate stepper motor 0.5 revolutions counterclockwise if > 7
    Serial.println("Rotating 0.5 revolutions counterclockwise");
    stepper.step(-steps_per_revolution / 2);
  }

  // Waits for 2s before taking the next reading
  delay(200); // You can adjust the delay (in milliseconds)
}

