#include <Servo.h>

Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(6);  // Attach the continuous rotation servo to pin 6
  myservo.writeMicroseconds(1500);  // Ensure the servo starts in a stopped state
  
  Serial.println("Enter angle between -180 and 180: ");
}

void loop() {
  if (Serial.available() > 0) {
    int angle = Serial.parseInt();  // Read the angle input from Serial Monitor

    angle = constrain(angle, -180, 180);  // Ensure the angle stays within valid limits
    long rotationTime = (abs(angle) * 500L) / 90;  // Calculate rotation time (90° = 500ms)
    Serial.print("Delay = ");
    Serial.println(rotationTime);

    if (angle > 0) {
      // Rotate clockwise for the calculated duration
      myservo.writeMicroseconds(1425);  // Set servo speed for clockwise rotation
      delay(rotationTime);  // Rotate for the calculated time
      myservo.writeMicroseconds(1500);  // Stop the servo after movement
    }
    else if (angle < 0) {
      // Rotate counterclockwise for the calculated duration
      myservo.writeMicroseconds(1525);  // Set servo speed for counterclockwise rotation
      delay(rotationTime);  // Rotate for the calculated time
      myservo.writeMicroseconds(1500);  // Stop the servo after movement
    }
    else {
      // Stop the servo immediately if the input angle is 0
      myservo.writeMicroseconds(1500);
    }

    // Indicate that movement execution is complete
    Serial.println("Movement Executed");
  }
}
