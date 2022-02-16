const int LDR = 23;
const int LED = 19;

int val;
//bool val;
void setup() {
  Serial.begin(115200);
  pinMode(LDR, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  val = digitalRead(LDR);
  Serial.println(val);
  if(val == 1)
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
