# smart_medication_management_system

System Architecture
The architecture is divided into three main layers: Hardware Layer, Software Layer, and Cloud Integration Layer, each contributing to the system’s functionality.
1.	Hardware Layer: 
o	ESP8266 Microcontroller: Acts as the central processing unit, managing all input/output operations, WiFi connectivity, and logic execution. Its dual-core processor and built-in WiFi module make it ideal for IoT applications.
o	Servo Motor (SG90): It controls the mechanical dispensing mechanism, rotating to release a precise number of pills (up to five per dispense) based on predefined angles (0° to 180°).
o	IR Sensor: It detects dispensed pills by sensing interruptions in its beam, providing feedback on whether medication was successfully dispensed.
o	LiquidCrystal I2C Display (16x2): A 16x2 LCD with an I2C interface (address 0x27) displays real-time information, including current time, next alarm, dose settings, and system status.
o	Push Buttons: Three buttons for manual dispense, time setting and dose setting with internal pull-up resistors allow users to interact with the system for manual dispensing and configuration.
o	RGB LED: Provides visual status indicators: blue for idle, green for successful dispensing, and red for missed doses.
o	Buzzer: Generates auditory alerts during dispensing events or alarms.

2.	Software Layer: 
o	Firmware: Written in C++ using the Arduino framework, the firmware runs on the ESP8266 and manages hardware interactions, timekeeping, and dispensing logic.
o	Libraries: 
▪	WiFi.h: Handles WiFi connectivity to connect to the internet for NTP and Blynk integration.
▪	BlynkSimpleEsp32.h: Facilitates communication with the Blynk IoT platform for remote monitoring and notifications.
▪	LiquidCrystal_I2C.h: Controls the LCD for displaying system information.
▪	ESP32Servo.h: Manages servo motor operations for precise dispensing.
▪	time.h: Enables NTP-based time synchronization, complementing the RTC module.
o	State Management: The system operates in three menu states—NORMAL (default operation), SET_TIME (for configuring alarm times), and SET_DOSE (for setting dose quantities)—controlled via button inputs.
o	Logic Flow: 
▪	Alarm Checking: Every 30 seconds, the system compares the current time with four predefined alarm times to trigger automatic dispensing.
▪	Dispensing: Servo rotates to dispense pills (40° per dose), with the IR sensor verifying each dispense. RGB LEDs and the buzzer provide feedback.
▪	User Interaction: Buttons allow manual dispensing and configuration of alarms and doses, with the LCD updating to reflect the current state.

3.	Cloud Integration Layer: 
o	Blynk IoT Platform: The ESP8266 connects to Blynk using a predefined authentication token, enabling remote monitoring. Events such as successful dispensing (“pill_taken”) or missed doses (“pill_missed”) are logged, and notifications are sent to users or caregivers via the Blynk app.
o	NTP Server: The system fetches accurate time from “pool.ntp.org” (configured for GMT+5:30, India) ensuring reliable scheduling.

<img width="467" height="170" alt="image" src="https://github.com/user-attachments/assets/ba886e17-4aa9-49b0-a751-286e5ada17f2" />
<img width="454" height="393" alt="image" src="https://github.com/user-attachments/assets/74926b77-8d83-4756-bd32-540be746b880" />



