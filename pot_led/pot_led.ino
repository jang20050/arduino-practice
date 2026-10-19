// 가변저항(A0)을 돌려서 11번 핀 LED 밝기 조절

const int POT_PIN = A0;   // 가변저항 가운데 다리
const int LED_PIN = 11;   // PWM(~) 핀

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);     // 시리얼 모니터로 값 확인용
}

void loop() {
  int potValue = analogRead(POT_PIN);               // 0 ~ 1023
  int brightness = map(potValue, 0, 1023, 0, 255);  // 0 ~ 255로 변환

  analogWrite(LED_PIN, brightness);

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Brightness: ");
  Serial.println(brightness);

  delay(10);
}
