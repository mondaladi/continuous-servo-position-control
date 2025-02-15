/*
  Continuous Servo Position Control - Angle-Based Version
  Author: Aditya Mondal
  License: GNU General Public License v3.0

  Inspired by Sandrolab's work:
  https://github.com/sandrolab/continuous-servo-pot-control

  Unlike the original potentiometer-based control method, this version takes direct angle input 
  from the user and moves the servo for a calculated duration to approximate the desired position.
*/

#include <ESP32Servo.h>

// Servo object
Servo myservo;

// Constants for servo control
const int STOP_SIGNAL = 1500;  // Neutral signal to stop servo movement
const int CW_SIGNAL = 1400;    // Signal for clockwise rotation
const int CCW_SIGNAL = 1575;   // Signal for counterclockwise rotation

// Timing settings
const long CW_TIME_FACTOR = 700L;  // Time factor for CW movement (ms per degree)
const long CCW_TIME_FACTOR = 800L; // Time factor for CCW movement (ms per degree)

// Movement control variables
bool isMoving = false;
unsigned long moveStartTime = 0;
unsigned long moveDuration = 0;
int targetAngle = 0;  // Stores the target angle

const int SERVO_PIN = 21; // GPIO pin connected to the servo

void setup() {
  Serial.begin(115200);
  
  myservo.attach(SERVO_PIN, 1000, 2000);  // Attach the servo with PWM range 1000-2000 µs
  stopServo();  // Ensure the servo is stopped
  Serial.println("Enter angle between -180 and 180: ");
}

void loop() {
  if (Serial.available() > 0 && !isMoving) {
    int inputAngle = Serial.parseInt();

    // Flush the input buffer to remove unwanted characters
    while (Serial.available() > 0) {
      Serial.read();  
    }

    // Validate the input angle
    if (inputAngle < -180 || inputAngle > 180) {
      Serial.print("\nTarget Angle: ");
      Serial.println(inputAngle);
      Serial.println("Invalid angle!");
      return;
    }

    targetAngle = inputAngle;
    handleServoMovement(targetAngle);
  }

  checkAndStopServo();
}

// Function to initiate servo movement
void handleServoMovement(int angle) {
  Serial.print("\nTarget Angle: ");
  Serial.println(angle);

  if (angle == 0) {
    Serial.println("No movement required.");
    return;
  }

  // Calculate duration and set direction
  if (angle > 0) {
    moveDuration = (abs(angle) * CW_TIME_FACTOR) / 180;
    myservo.writeMicroseconds(CW_SIGNAL);
  } else {
    moveDuration = (abs(angle) * CCW_TIME_FACTOR) / 180;
    myservo.writeMicroseconds(CCW_SIGNAL);
  }

  Serial.print("Movement Duration: ");
  Serial.print(moveDuration);
  Serial.println(" ms");

  // Start movement
  isMoving = true;
  moveStartTime = millis();
}

// Function to stop the servo
void stopServo() {
  myservo.writeMicroseconds(STOP_SIGNAL);
}

// Function to check if the movement duration has elapsed and stop the servo
void checkAndStopServo() {
  if (isMoving && (millis() - moveStartTime >= moveDuration)) {
    stopServo();
    isMoving = false;
    Serial.println("Movement Executed");
  }
}
