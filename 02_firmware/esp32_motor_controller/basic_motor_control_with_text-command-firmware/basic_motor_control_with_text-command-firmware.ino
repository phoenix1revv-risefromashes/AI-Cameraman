// MOTOR 1 SLOW FORWARD LOOP
// ESP32 + BTS7960
// Pins: RPWM = 14, LPWM = 27

const int RPWM = 14;
const int LPWM = 27;

const int freq = 1000;
const int resolution = 8;

void setup() {
  Serial.begin(115200);

  ledcAttach(RPWM, freq, resolution);
  ledcAttach(LPWM, freq, resolution);

  Serial.println("Motor 1 slow forward loop started");
}

void loop() {
  // Forward slow
  ledcWrite(RPWM, 60);   // speed: 0-255
  ledcWrite(LPWM, 0);

  Serial.println("Forward slow");
  delay(3000);

  // Stop
  ledcWrite(RPWM, 0);
  ledcWrite(LPWM, 0);

  Serial.println("Stop");
  delay(1000);
}
