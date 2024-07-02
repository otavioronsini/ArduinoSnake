#define PINO_VRX A0
#define PINO_VRY A1
#define PINO_SW  2

void setup() {
  Serial.begin(9600);

  pinMode(PINO_SW, INPUT_PULLUP);
}

void loop() {
  int valorVRX = analogRead(PINO_VRX);
  int valorVRY = analogRead(PINO_VRY);

  int valorSW = digitalRead(PINO_SW);

  Serial.print("X: ");
  Serial.print(valorVRX);
  Serial.print(" | Y: ");
  Serial.print(valorVRY);
  Serial.print(" | SW: ");
  Serial.println(valorSW);

  delay(100);
}
