bool blinking = false;
unsigned long previousMillis = 0;
const long interval = 500; // milliseconds
const int ledPin = LED_BUILTIN;
unsigned long startTime;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  startTime = millis();
  Serial.println("=== Arduino Nano Diagnostic Test Start ===");
}

void loop() {
  // Handle serial commands
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.equalsIgnoreCase("START")) {
      blinking = true;
      Serial.println("Blinking started.");
    } else if (command.equalsIgnoreCase("STOP")) {
      blinking = false;
      digitalWrite(ledPin, LOW);
      Serial.println("Blinking stopped.");
    } else if (command.equalsIgnoreCase("STATUS")) {
      Serial.print("Blinking is ");
      Serial.println(blinking ? "ON" : "OFF");
    } else if (command.equalsIgnoreCase("MEASURE_VOLTAGE")) {
      int analogVal = analogRead(A0);  // Simulate voltage reading
      float voltage = (analogVal / 1023.0) * 5.0;
      Serial.print("Voltage on A0: ");
      Serial.print(voltage, 2);
      Serial.println(" V");
    } else if (command.equalsIgnoreCase("UPTIME")) {
      unsigned long uptimeSeconds = (millis() - startTime) / 1000;
      Serial.print("Uptime: ");
      Serial.print(uptimeSeconds);
      Serial.println(" seconds");
    } else {
      Serial.print("Unknown command: ");
      Serial.println(command);
    }
  }

  // Handle LED blinking
  if (blinking) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(ledPin, !digitalRead(ledPin));
    }
  }
}
