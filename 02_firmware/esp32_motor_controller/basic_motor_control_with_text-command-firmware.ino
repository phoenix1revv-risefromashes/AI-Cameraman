// Single Motor USB Text Command Test
// Commands:
// f = forward
// b = backward
// s = stop
//
// BTS7960 notes:
// R_EN and L_EN are connected directly to 5V.
// ESP32 controls only RPWM and LPWM.

#define RPWM 14
#define LPWM 15

const int MOTOR_SPEED = 200;

void setup() {
  Serial.begin(115200);

  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);

  stopMotor();

  Serial.println("ESP32 SINGLE MOTOR TEST READY");
  Serial.println("Commands: f = forward, b = backward, s = stop");
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    if (command == 'f') {
      forwardMotor();
      Serial.println("Motor: FORWARD");
    }
    else if (command == 'b') {
      backwardMotor();
      Serial.println("Motor: BACKWARD");
    }
    else if (command == 's') {
      stopMotor();
      Serial.println("Motor: STOP");
    }
  }
}

void forwardMotor() {
  analogWrite(RPWM, MOTOR_SPEED);
  analogWrite(LPWM, 0);
}

void backwardMotor() {
  analogWrite(RPWM, 0);
  analogWrite(LPWM, MOTOR_SPEED);
}

void stopMotor() {
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
}
