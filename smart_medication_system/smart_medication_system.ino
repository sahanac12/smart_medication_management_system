#define BLYNK_TEMPLATE_ID "TMPL3Ycz_PqiO"
#define BLYNK_TEMPLATE_NAME "Smart Medicare System"
#define BLYNK_AUTH_TOKEN "xi-kGoLGGW3Qo8jhTjhapMxahwGodI5O"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <time.h>
#include <ESP32Servo.h>

// WiFi credentials
char ssid[] = "";
char pass[] = "";

// Pins
const int buttonPin = 22;
const int servoPin = 14;
const int buzzerPin = 21;

// Objects
Servo myServo;
bool lastButtonState = HIGH;
int currentAngle = 0;

BlynkTimer timer;

// Store 3 schedules
int startHour[3] = {-1, -1, -1};
int startMinute[3] = {-1, -1, -1};
bool actionDoneToday[3] = {false, false, false}; // One flag per time slot

void setup() {
  Serial.begin(115200);

  // Servo setup
  ESP32PWM::allocateTimer(0);
  myServo.setPeriodHertz(50);
  myServo.attach(servoPin, 500, 2400);
  myServo.write(0);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Time sync
  configTime(19800, 0, "pool.ntp.org", "time.nist.gov");

  // Check time every second
  timer.setInterval(1000L, checkTime);

  Serial.println("System Ready - Press button to increase angle");
}

// TimeInput V0
BLYNK_WRITE(V0) {
  TimeInputParam t(param);
  if (t.hasStartTime()) {
    startHour[0] = t.getStartHour();
    startMinute[0] = t.getStartMinute();
    actionDoneToday[0] = false;
    Serial.printf("Time 1 set: %02d:%02d\n", startHour[0], startMinute[0]);
  }
}

// TimeInput V1
BLYNK_WRITE(V1) {
  TimeInputParam t(param);
  if (t.hasStartTime()) {
    startHour[1] = t.getStartHour();
    startMinute[1] = t.getStartMinute();
    actionDoneToday[1] = false;
    Serial.printf("Time 2 set: %02d:%02d\n", startHour[1], startMinute[1]);
  }
}

// TimeInput V2
BLYNK_WRITE(V2) {
  TimeInputParam t(param);
  if (t.hasStartTime()) {
    startHour[2] = t.getStartHour();
    startMinute[2] = t.getStartMinute();
    actionDoneToday[2] = false;
    Serial.printf("Time 3 set: %02d:%02d\n", startHour[2], startMinute[2]);
  }
}

// Check all 3 schedules
void checkTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to get time");
    return;
  }

  int currHour = timeinfo.tm_hour;
  int currMin = timeinfo.tm_min;
  int currSec = timeinfo.tm_sec;

  for (int i = 0; i < 3; i++) {
    if (startHour[i] == -1) continue; // Skip if not set

    if (currHour == startHour[i] && currMin == startMinute[i] && currSec < 5 && !actionDoneToday[i]) {
      Serial.printf("Time slot %d matched! Rotating servo.\n", i + 1);
      
      currentAngle += 45;
      if (currentAngle > 180) currentAngle = 0;
      myServo.write(currentAngle);

      // Beep buzzer
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);

      actionDoneToday[i] = true;
    }
  }

  // Reset all flags at midnight
  if (currHour == 0 && currMin == 0 && currSec < 5) {
    for (int i = 0; i < 3; i++) {
      actionDoneToday[i] = false;
    }
  }
}

void loop() {
  Blynk.run();
  timer.run();

  int currentButtonState = digitalRead(buttonPin);

  // Manual button press
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    Serial.println("Button pressed!");

    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);

    currentAngle += 45;
    if (currentAngle > 180) currentAngle = 0;

    Serial.printf("Moving servo to %d degrees\n", currentAngle);
    myServo.write(currentAngle);

    delay(300); // Debounce
  }

  lastButtonState = currentButtonState;
}