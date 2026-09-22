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

# System Architecture

The system is divided into three main layers:

1. Hardware Layer
2. Software Layer
3. Cloud Integration Layer

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
│ ESP8266 │ Servo │ IR │ LCD │ Buttons       │
│ RGB LED │ Buzzer │ RTC                     │
└─────────────────────────────────────────────┘
