#define LED_PIN 13
#define ANALOG_PIN A0
#define BAUD_RATE 9600

unsigned long lastBlinkTime = 0;
unsigned long blinkInterval = 1000;  // milliseconds

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(ANALOG_PIN, INPUT);
  Serial.begin(BAUD_RATE);
  while (!Serial);  // Wait for serial to connect (for some boards)
  Serial.println("=== Arduino Nano Diagnostic Test Start ===");
}

void loop() {
  // Feature 1: Blink onboard LED with timestamp
  if (millis() - lastBlinkTime >= blinkInterval) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    Serial.print("[LED_BLINK] Time: ");
    Serial.print(millis());
    Serial.print(" ms - LED is now ");
    Serial.println(digitalRead(LED_PIN) ? "ON" : "OFF");
    lastBlinkTime = millis();
  }

  // Feature 2: Serial receive and echo back
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    Serial.print("[SERIAL_RX] Received: ");
    Serial.println(input);
    Serial.print("[SERIAL_TX] Echoing back: ");
    Serial.println(input);
  }

  // Feature 3: Timer use demonstration (using millis)
  static unsigned long lastTimerLog = 0;
  if (millis() - lastTimerLog >= 5000) {  // Every 5 seconds
    Serial.print("[TIMER] 5 seconds elapsed at ");
    Serial.print(millis());
    Serial.println(" ms");
    lastTimerLog = millis();
  }

  // Feature 4: Analog voltage read and log
  static unsigned long lastAnalogRead = 0;
  if (millis() - lastAnalogRead >= 2000) {  // Every 2 seconds
    int analogValue = analogRead(ANALOG_PIN);
    float voltage = (analogValue * 5.0) / 1023.0;
    Serial.print("[ANALOG_READ] A0 value: ");
    Serial.print(analogValue);
    Serial.print(" -> Voltage: ");
    Serial.print(voltage, 2);
    Serial.println(" V");
    lastAnalogRead = millis();
  }
}
