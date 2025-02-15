# Continuous Servo Position Control

## Purpose
This code is designed to control the position of a **continuous rotation servo**, which does not have a built-in feedback mechanism.  
Unlike standard servos, continuous rotation servos interpret signals as **speed and direction** rather than absolute position.  

In this project:  
- **Servo Used:** SG90 continuous rotation servo  
- **Microcontrollers:** Arduino Nano & ESP32 (logic adaptable to other microcontrollers)  

---

## Working Principle
Since continuous rotation servos do not provide position feedback, **precise position control is not possible**.  
Instead, the code **calculates movement duration** based on the input angle and rotates the servo accordingly.  
This works under the assumption that the servo **maintains a consistent speed** for a given pulse width.  

### **How It Works**
- The user inputs an **angle between -180 and 180 degrees**.
- The code determines how long the servo should rotate in the required direction.
- **Clockwise (CW) and Counterclockwise (CCW) speeds are calibrated separately**.
- The servo rotates for the calculated duration and then **stops**.
- **This does not move the servo to an absolute position** but rather adds/subtracts the specified angle from the current position.

---

## Calibration Guide
Different hardware setups (e.g., supply voltage, microcontroller, servo model) may require **calibration** of:  
✔ **CW speed**  
✔ **CCW speed**  
✔ **Stop value**  
✔ **Time factors**  

### **Step 1: Finding Rotation Speed and Stop Value**
Use the **`servo_test.ino`** code to find the correct values:
- Identify the **stop signal** where the servo remains stationary.
- Determine **CW and CCW pulse widths** where the servo moves at equal speeds in both directions.

### **Step 2: Understanding the Code Logic**
For a simpler explanation of the logic, refer to **`basic_idea.ino`**.  
This file demonstrates the **core idea** of estimating servo position through timed movements.  

The improved versions (**`ConServo_PosCon_Nano.ino`** and **`ConServo_PosCon_ESP32.ino`**) introduce:
- ✅ **Non-blocking delays**
- ✅ **Better user input handling**
- ✅ **Modular functions**
- ✅ **Separate equations for CW and CCW control**

### **Step 3: Implementing Position Control**
Once you have acquired the **CW and CCW speed values**, use:
- **`ConServo_PosCon_Nano.ino`** for **Arduino Nano**
- **`ConServo_PosCon_ESP32.ino`** for **ESP32**

Modify the **CW/CCW rotation speeds and time factors** according to your servo's response.  
By fine-tuning these values, you can achieve **better accuracy in position estimation** despite the lack of feedback control.

---

## Acknowledgments  
This project was **inspired by** [Sandrolab's Continuous Servo Pot Control](https://github.com/sandrolab/continuous-servo-pot-control).  

While the original project controlled a continuous servo using a **potentiometer** to gradually change speed,  
this implementation takes **direct angle inputs** and calculates movement duration based on predefined timing factors.  

- **Original Repository:** [GitHub - Sandrolab](https://github.com/sandrolab/continuous-servo-pot-control)  
- **Video Demonstration:** [YouTube](https://youtu.be/qKCKjXpQUgU)  

---

## License
This project is licensed under the **GNU General Public License v3.0**.  
See the [LICENSE](LICENSE.txt) file for details.
