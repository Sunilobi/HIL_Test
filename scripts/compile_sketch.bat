bool blinking = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();  // remove whitespace/newlines

    if (command == "START") {
      blinking = true;
      Serial.println("Blinking started");
    }
    else if (command == "STOP") {
      blinking = false;
      digitalWrite(LED_BUILTIN, LOW);  // turn off LED immediately
      Serial.println("Blinking stopped");
    }
  }

  if (blinking) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
  else {
    // Just stay idle or do other stuff here
  }
}
