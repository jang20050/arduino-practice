// 아두이노 우노: A0 핀에 연결한 버튼을 누르면 13번 핀 LED 켜짐, 떼면 꺼짐
const int BUTTON_PIN = A0; // 버튼 핀
const int LED_PIN = 13;    // LED 핀

void setup() {      // 한번만 실행
  Serial.begin(9600);                 // 시리얼 통신 시작 (속도 9600)
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 버튼 핀을 입력모드로 (내부 풀업저항 사용)
  pinMode(LED_PIN, OUTPUT);           // LED 핀을 출력모드로
}

void loop() {       // 무한히 반복
  int state = digitalRead(BUTTON_PIN); // 버튼 상태 읽기

  if (state == LOW) {                  // 풀업이라 누르면 LOW(0V)
    digitalWrite(LED_PIN, HIGH);       // LED 켜기
    Serial.println("Button pressed");
  } else {                             // 안 누르면 HIGH(5V)
    digitalWrite(LED_PIN, LOW);        // LED 끄기
    Serial.println("Button released");
  }

  delay(200);                          // 0.2초 기다리기
}
