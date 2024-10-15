#include <Servo.h>

// Pin definitions
#define POT_PIN A0   // Potentiometer connected to A0
#define SERVO_PIN 10 // Servo connected to digital pin 10

// Variables
int potValue;          // Stores potentiometer reading (0-1023)
int servoSpeed = 0;    // Speed of servo (derived from potValue)
int maxSpeed = 10;     // Maximum speed value (adjustable)
int servoPos = 90;     // Initial servo position

Servo myServo;

void setup() {
  // Attach the servo to the defined pin
  myServo.attach(SERVO_PIN);

  // Set initial servo position
  myServo.write(servoPos);

  // Begin serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the potentiometer value (range: 0 to 1023)
  potValue = analogRead(POT_PIN);

  // Map the potentiometer value to a speed range (0 to maxSpeed)
  servoSpeed = map(potValue, 0, 1023, 0, maxSpeed);

  // Print the potentiometer and speed values for debugging
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(" | Servo Speed: ");
  Serial.println(servoSpeed);

  // Move the servo based on the current speed
  if (servoSpeed > 0) {
    // Increase or decrease position based on current speed
    servoPos += servoSpeed;

    // Wrap the position to stay within the servo's range (0 to 180 degrees)
    if (servoPos > 180) {
      servoPos = 0;
    }

    // Move the servo to the new position
    myServo.write(servoPos);

    // Print the current position for debugging
    Serial.print("Servo Position: ");
    Serial.println(servoPos);
  }

  // Small delay to control the servo movement speed
  delay(20 - servoSpeed);  // The higher the speed, the shorter the delay
}
