#include <Servo.h>

// Servo object
Servo myservo;

// Servo control signals (in microseconds)
const int STOP_SIGNAL = 1500;  // Neutral signal to stop servo
const int CW_SIGNAL = 1350;    // Clockwise rotation speed
const int CCW_SIGNAL = 1600;   // Counterclockwise rotation speed

// Timing factors (milliseconds per degree)
const long CW_TIME_FACTOR = 825L;  // Time per degree for CW rotation
const long CCW_TIME_FACTOR = 925L; // Time per degree for CCW rotation

// Movement control variables
bool isMoving = false;           // Flag to track servo movement
unsigned long moveStartTime = 0; // Stores the start time of movement
unsigned long moveDuration = 0;  // Duration for which the servo should move
int targetAngle = 0;             // Target angle input by the user

void setup() {
  Serial.begin(9600);
  myservo.attach(6);  // Attach the servo to pin 6
  stopServo();        // Ensure the servo is stopped
  Serial.println("Enter angle between -180 and 180: ");
}

void loop() {
  // Check if data is available in the serial buffer and if the servo is not already moving
  if (Serial.available() > 0 && !isMoving) {
    int inputAngle = Serial.parseInt();

    // Flush the input buffer to remove any extra characters
    while (Serial.available() > 0) {
      Serial.read();  
    }

    // Validate the input angle range
    if (inputAngle < -180 || inputAngle > 180) {
      Serial.print("\nTarget Angle: ");
      Serial.println(inputAngle);
      Serial.println("Invalid angle!");
      return;
    }

    targetAngle = inputAngle;
    handleServoMovement(targetAngle);
  }

  checkAndStopServo(); // Check if the movement duration has elapsed and stop the servo
}

// Function to handle servo movement based on the target angle
void handleServoMovement(int angle) {
  Serial.print("\nTarget Angle: ");
  Serial.println(angle);

  if (angle == 0) {
    Serial.println("No movement required.");
    return;
  }

  // Calculate movement duration and set rotation direction
  if (angle > 0) {
    moveDuration = (abs(angle) * CW_TIME_FACTOR) / 180; // Convert angle to movement duration
    myservo.writeMicroseconds(CW_SIGNAL);
  } else {
    moveDuration = (abs(angle) * CCW_TIME_FACTOR) / 180;
    myservo.writeMicroseconds(CCW_SIGNAL);
  }

  Serial.print("Movement Duration: ");
  Serial.print(moveDuration);
  Serial.println(" ms");

  // Start movement tracking
  isMoving = true;
  moveStartTime = millis();
}

// Function to stop the servo by sending a neutral signal
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
