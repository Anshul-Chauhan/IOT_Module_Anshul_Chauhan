const int LED_PIN  = 15;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED on.");
  delay(2000);

  digitalWrite(LED_PIN, LOW);
  Serial.println("LED off.");
  delay(2000);
}
