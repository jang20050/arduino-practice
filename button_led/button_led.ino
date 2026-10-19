// 버튼을 누르고 있으면 LED 켜짐, 떼면 꺼짐
// 버튼: 한쪽 다리 = 2번 핀, 다른 쪽 다리 = GND (내부 풀업 사용, 저항 필요 없음)

const int BUTTON_PIN = 2;
const int LED_PIN = 13;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 안 누르면 HIGH, 누르면 LOW
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {  // 눌림
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Pressed");
  } else {                                // 안 눌림
    digitalWrite(LED_PIN, LOW);
    Serial.println("Released");
  }
  delay(50);
}
