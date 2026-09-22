# Smart Medication Management System

An IoT-based automated medication dispensing system designed to help users manage scheduled medication, dispense doses automatically, and provide remote monitoring and caregiver notifications.

---

## Features

- Automated pill dispensing based on scheduled alarm times
- Configurable medication dose quantity
- Manual pill dispensing using push buttons
- IR sensor-based pill dispensing verification
- 16×2 LCD display for system information
- RGB LED and buzzer for status and medication alerts
- Wi-Fi connectivity using ESP8266
- Remote monitoring and control using Blynk IoT
- Caregiver notifications for medication events
- NTP-based time synchronization
- Multiple operating modes for configuration and normal operation

---

## Tools and Technologies

### Hardware

- **ESP8266** – Main microcontroller
- **SG90 Servo Motor** – Pill dispensing mechanism
- **IR Sensor** – Pill dispensing detection
- **16×2 LCD with I2C** – System information display
- **Push Buttons** – User input and configuration
- **RGB LED** – Visual status indication
- **Buzzer** – Audible alerts
- **RTC Module** – Timekeeping support

### Software

- **Arduino IDE**
- **C/C++**
- **Blynk IoT Platform**
- **NTP (Network Time Protocol)**

### Development Environment

- Breadboard/PCB for prototyping
- USB power supply
- Wi-Fi router for network connectivity

---

## System Architecture

The system is divided into three main layers:

1. **Hardware Layer**
2. **Software Layer**
3. **Cloud Integration Layer**

```text
┌─────────────────────────────────────────────┐
│             Cloud Integration Layer         │
│                                             │
│       Blynk IoT          NTP Server         │
│           │                   │             │
└───────────┼───────────────────┼─────────────┘
            │                   │
            ▼                   ▼
┌─────────────────────────────────────────────┐
│                Software Layer               │
│                                             │
│ Scheduling │ State Management │ Dispensing  │
│ Timekeeping │ User Interaction │ Alerts     │
└──────────────────────┬──────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────┐
│                 Hardware Layer              │
│                                             │
│ ESP8266 │ Servo │ IR │ LCD │ Buttons        │
│ RGB LED │ Buzzer                            │
└─────────────────────────────────────────────┘




1. Hardware Layer
ESP8266 Microcontroller

The ESP8266 acts as the central controller of the system. It manages:

Sensor inputs
Actuator outputs
Medication scheduling
Dispensing logic
User interactions
Wi-Fi connectivity
Communication with the Blynk IoT platform
SG90 Servo Motor

The SG90 servo controls the mechanical pill dispensing mechanism. It rotates according to predefined angles to release the required quantity of medication.

The dispensing mechanism uses approximately 40° of rotation per dose, depending on the configured dose and mechanical arrangement.

IR Sensor

The IR sensor detects the passage of dispensed pills by sensing interruptions in the infrared beam.

This provides feedback to determine whether the medication was successfully dispensed.

16×2 I2C LCD

The LCD displays real-time system information including:

Current time
Next scheduled alarm
Dose quantity
System state
Configuration information

The LCD communicates with the ESP8266 using the I2C interface.

Push Buttons

Three push buttons allow the user to interact with the system.

They are used for:

Manual medication dispensing
Setting medication times
Setting medication dose quantities

The buttons use internal pull-up resistors for input handling.

RGB LED

The RGB LED provides visual feedback about the current system status.

Color	Status
Blue	Normal / Idle
Green	Successful dispensing
Red	Missed dose
Buzzer

The buzzer provides audible feedback during:

Scheduled medication alarms
Dispensing operations
Medication alerts
Missed-dose conditions
2. Software Layer
Firmware

The firmware is developed using C/C++ with the Arduino framework and runs on the ESP8266.

The firmware is responsible for:

Hardware control
Time management
Alarm scheduling
Dose management
Servo control
IR sensor monitoring
User interaction
Blynk communication
Libraries

The project uses the following libraries:

WiFi – Provides Wi-Fi connectivity
Blynk IoT – Enables communication with the Blynk cloud platform
LiquidCrystal_I2C – Controls the 16×2 I2C LCD
ESP32Servo – Provides servo motor control and is used with the ESP8266 project setup
time.h – Provides time-related functions and supports NTP-based time synchronization

Note: The project uses an ESP8266 microcontroller. The ESP32Servo library is used in the implementation for servo control and is compatible with the project setup.

3. State Management

The system operates using three primary states:

NORMAL

The default operating state.

In this state, the system:

Displays current system information
Monitors the medication schedule
Checks for scheduled alarms
Handles automatic dispensing
Monitors user inputs
SET_TIME

Allows the user to configure medication alarm times.

SET_DOSE

Allows the user to configure the quantity of medication to be dispensed.

                 ┌───────────────┐
                 │     NORMAL    │
                 │ Default State │
                 └───────┬───────┘
                         │
              User Button Input
                    ┌────┴────┐
                    ▼         ▼
             ┌──────────┐ ┌──────────┐
             │ SET_TIME │ │ SET_DOSE │
             └──────────┘ └──────────┘
4. Medication Scheduling and Dispensing

The system periodically checks the current time against the configured medication alarm times.

When a scheduled medication time is reached:

The system triggers the medication alarm.
The buzzer provides an audible alert.
The servo motor activates the dispensing mechanism.
The IR sensor checks whether the pill has been dispensed.
The RGB LED indicates the dispensing status.
The event is sent to the Blynk IoT platform.
Dispensing Flow
Scheduled Time Reached
          │
          ▼
     Trigger Alarm
          │
          ▼
     Activate Buzzer
          │
          ▼
     Rotate Servo
          │
          ▼
     Pill Dispensing
          │
          ▼
     IR Sensor Check
        /       \
       /         \
  Detected    Not Detected
     │              │
     ▼              ▼
 Successful       Missed /
 Dispensing       Failed
     │              │
     ▼              ▼
 Green LED       Red LED
     │              │
     └──────┬───────┘
            ▼
       Blynk Event
5. Manual Dispensing

The user can manually initiate medication dispensing using the dedicated push button.

The manual dispensing process follows the same basic mechanism:

Button Press
     │
     ▼
Dispensing Triggered
     │
     ▼
Servo Activated
     │
     ▼
Pill Released
     │
     ▼
IR Sensor Verification
     │
     ▼
Status Displayed
6. Cloud Integration Layer
Blynk IoT

The ESP8266 connects to the Blynk IoT platform through Wi-Fi.

Blynk is used for:

Remote monitoring
Remote dispensing control
Medication status updates
Event logging
Caregiver notifications

The system generates events such as:

pill_taken
pill_missed

These events can be monitored through the Blynk platform and used to notify the user or caregiver.

7. NTP Time Synchronization

The system uses an NTP server to obtain accurate network time for medication scheduling.

             Wi-Fi
ESP8266 ─────────────────► pool.ntp.org
                              │
                              ▼
                       Network Time
                              │
                              ▼
                    Medication Scheduler

The system is configured for India Standard Time (IST), UTC+5:30.

NTP synchronization helps ensure that scheduled medication alarms are based on an accurate system clock.

8. Complete System Workflow
                         ┌─────────────── ┐
                         │    ESP8266     │
                         │ Main Controller│
                         └───────┬─────── ┘
                                 │
          ┌──────────────────────┼──────────────────────┐
          │                      │                      │
          ▼                      ▼                      ▼
      Sensors              User Inputs              Wi-Fi
          │                      │                      │
          │                      │              ┌───────┴───────┐
          │                      │              │               │
          │                      │              ▼               ▼
          │                      │         Blynk IoT       NTP Server
          │                      │              │               │
          └──────────────┬───────┘              │               │
                         ▼                      │               │
                  Control Logic ◄───────────────┴───────────────┘
                         │
             ┌───────────┼───────────┐
             │           │           │
             ▼           ▼           ▼
           Servo        LCD        Alerts
             │           │           │
             ▼           ▼           ▼
         Dispensing    Status      Buzzer /
                                   RGB LED



Circuit / Hardware Setup
<img width="410" height="163" alt="image" src="https://github.com/user-attachments/assets/0e078177-8a9d-4c71-ac4c-0c5054515732" />
<img width="535" height="564" alt="image" src="https://github.com/user-attachments/assets/a7177f4d-4af5-49f4-bb01-d688ebc51501" />

<img width="403" height="412" alt="image" src="https://github.com/user-attachments/assets/025f0378-307c-48ca-bceb-ba3a9096cc19" />

Blynk Interface
<img width="540" height="1170" alt="image" src="https://github.com/user-attachments/assets/0b7bb0ff-1f76-4f4d-8e65-26828270ceef" />
