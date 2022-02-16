const int LDR = 26;
const int LED = 25;

int val;
//bool val;
void setup() {
  Serial.begin(115200);
  pinMode(LDR, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  val = analogRead(LDR);
  Serial.println(val);
  if(val >= 1500)
  {
    digitalWrite(LED, 1);
    delay(1000);
  }
  else
  {
    digitalWrite(LED, 0);
    delay(1000);
  }
}
