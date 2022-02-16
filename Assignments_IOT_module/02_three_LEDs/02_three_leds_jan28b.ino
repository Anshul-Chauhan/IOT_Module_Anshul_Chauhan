const int RED_LED = 15;
const int BLUE_LED = 16;
const int YELLOW_LED = 17;

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  Serial.println("RED LED on.");
  delay(2000);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  Serial.println("BLUE LED on.");
  delay(2000);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  Serial.println("YELLOW LED on.");
  delay(2000);
}
