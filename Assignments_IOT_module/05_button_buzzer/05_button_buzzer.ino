const int button = 22;
const int buzzer = 21;

int val;
void setup() {
  Serial.begin(115200);
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  val = digitalRead(button);
  Serial.println(val);
  if(val == 1)
  {
    digitalWrite(buzzer, 1);
    Serial.println("Button is pressed......i.e. buzzer is turned on for 5 seconds.");
    delay(5000);
  }
  else
  {
    digitalWrite(buzzer, 0);
    delay(500);
  }
}
