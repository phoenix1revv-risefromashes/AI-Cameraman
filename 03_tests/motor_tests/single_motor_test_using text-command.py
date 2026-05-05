#define RPWM 18
#define LPWM 19

void setup() {
  Serial.begin(115200);

  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);

  stopMotor();

  Serial.println("Motor 1 command test ready");
  Serial.println("Type f = forward, b = backward, s = stop, x = stop forever");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == '\n' || command == '\r') {
      return;
    }

    if (command == 'f') {
      Serial.println("FORWARD");
      forward();
    }
    else if (command == 'b') {
      Serial.println("BACKWARD");
      backward();
    }
    else if (command == 's') {
      Serial.println("STOP");
      stopMotor();
    }
    else if (command == 'x') {
      Serial.println("STOP FOREVER");
      stopMotor();
      while (true) {
        delay(1000);
      }
    }
    else {
      Serial.println("Unknown command. Use f, b, s, or x.");
    }
  }
}

void forward() {
  digitalWrite(LPWM, LOW);
  digitalWrite(RPWM, HIGH);
}

void backward() {
  digitalWrite(RPWM, LOW);
  digitalWrite(LPWM, HIGH);
}

void stopMotor() {
  digitalWrite(RPWM, LOW);
  digitalWrite(LPWM, LOW);
}
