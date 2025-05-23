const int ledPin = 13;
bool blinking = false;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.equalsIgnoreCase("START")) {
      blinking = true;
      Serial.println("Started blinking.");
    } else if (command.equalsIgnoreCase("STOP")) {
      blinking = false;
      digitalWrite(ledPin, LOW);
      Serial.println("Stopped blinking.");
    } else if (command.equalsIgnoreCase("STATUS")) {
      Serial.print("Status: LED is ");
      Serial.println(blinking ? "ON" : "OFF");
    } else if (command.equalsIgnoreCase("MEASURE_VOLTAGE")) {
      int raw = analogRead(A0);
      float voltage = raw * (5.0 / 1023.0);
      Serial.print("Voltage A0: ");
      Serial.println(voltage, 2);
    } else {
      Serial.print("Unknown command: ");
      Serial.println(command);
    }
  }

  if (blinking) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
}
