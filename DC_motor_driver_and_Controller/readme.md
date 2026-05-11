# PIC32-Based Closed-Loop Motor Controller
## Overview
This repository contains the firmware and hardware design for a rudimentary closed-loop DC motor control system. Designed for precision-dependent applications like telescope motion control, the system utilizes a PIC32MK1024MCM100 microcontroller to implement a real-time PI (Proportional-Integral) control algorithm. 
The system dynamically adjusts motor speed based on feedback from a MOC7811 optical slot sensor, ensuring stable rotation even under varying load conditions. 
Hardware Specifications
The controller is built with a focus on electrical isolation and power efficiency:
    • Microcontroller: PIC32MK MCM Curiosity Pro (100-pin). 
    • Motor Driver: Custom MOSFET-based driver featuring an IRLZ44N N-Channel MOSFET. 
    • Electrical Isolation: 2602 Optocoupler to separate low-voltage control signals from high-power motor noise. 
    • Feedback Sensor: MOC7811 Slot Sensor for RPM calculation via pulse timing. 
    • Communication: UART6 interface for real-time monitoring at 115200 bps. 
System Architecture
The system operates on a closed-loop feedback mechanism:
    1. Input: A target RPM is set via a serial terminal. 
    2. Sensing: The MOC7811 generates pulses as the motor shaft rotates. 
    3. Processing: The PIC32 computes actual RPM using Timer3 to measure the interval between pulses. 
    4. Control: A PI algorithm calculates the error and updates the PWM duty cycle through the Output Compare (OC5) module. 
    5. Actuation: The PWM signal drives the IRLZ44N MOSFET through the 2602 optocoupler to regulate motor power. 
Firmware Details
The firmware is developed in Embedded C using a bare-metal approach (no external RTOS or frameworks). 
Key Modules:
    • Timer2: Configured in 32-bit mode to generate 100 Hz interrupts for the periodic PI loop. 
    • INT3: External interrupt used for high-precision slot pulse counting. 
    • UART6: Implements a circular command buffer with STx/ETx delimiters for robust command processing. 
    • OC5: Handles PWM generation with high-resolution duty cycle updates. 
Control Parameters
The system was tuned experimentally to balance responsiveness and stability: 
    • Proportional Gain ($K_p$): 0.0188. 
    • Integral Gain ($K_i$): 0.3. 
    • Feedforward Model: A second-order polynomial was derived using Python curve fitting to improve open-loop prediction: 
      $$Duty = 7.8673e\text{-}05 \cdot x^2 - 8.5837e\text{-}02 \cdot x + 74.730$$
Performance & Results
    • Accuracy: The system maintains stable rotation at target speeds (e.g., 900 RPM) with minimal steady-state error. 
    • Load Regulation: Successfully maintains target RPM across a load range of 0.1A to 2.5A, significantly outperforming open-loop systems. 
    • Safety: Opto-isolation effectively prevents back-EMF spikes from reaching the microcontroller logic. 
Future Enhancements
    • Integration of an H-Bridge for bidirectional control. 




I took a referece to do this project. That report is added in the repository - DEVELOPMENT_OF_A_PIC32-BASED_MOTOR_CONTROLLER_PROJECT_REPORT.pdf

    • Upgrade to a high-resolution encoder for sub-degree positional accuracy. 
    • Implementation of ramping profiles for smooth acceleration/deceleration. 
