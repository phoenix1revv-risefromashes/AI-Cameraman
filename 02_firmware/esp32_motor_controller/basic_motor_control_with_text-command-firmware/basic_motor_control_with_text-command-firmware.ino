// =====================================
// SIMPLE BTS7960 MOTOR TEST
// =====================================

// Motor control pins
const int RPWM = 14;
const int LPWM = 27;

// Enable pins
const int R_EN = 25;
const int L_EN = 26;

void setup() {

  Serial.begin(115200);

  // Set pins as outputs
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);

  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);

  // Enable BTS7960
  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);

  Serial.println("Motor test started");
}

void loop() {

  // =========================
  // FORWARD
  // =========================
  Serial.println("FORWARD");

  analogWrite(RPWM, 30);
  analogWrite(LPWM, 0);

  delay(4000);

  // =========================
  // STOP
  // =========================
  Serial.println("STOP");

  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);

  delay(2000);

  // =========================
  // REVERSE
  // =========================
  Serial.println("REVERSE");

  analogWrite(RPWM, 0);
  analogWrite(LPWM, 30);

  delay(4000);

  // =========================
  // STOP
  // =========================
  Serial.println("STOP");

  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);

  delay(3000);
}
