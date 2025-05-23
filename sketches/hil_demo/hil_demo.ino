bool blinking = false;
unsigned long previousMillis = 0;
const long interval = 500; // milliseconds
const int ledPin = LED_BUILTIN;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
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
    } else {
      Serial.print("Unknown command: ");
      Serial.println(command);
    }
  }

  // Handle LED blinking if active
  if (blinking) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(ledPin, !digitalRead(ledPin));
    }
  }
}
