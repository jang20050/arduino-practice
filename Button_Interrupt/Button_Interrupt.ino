// 아두이노 우노: 인터럽트 핀(2번)에 연결한 버튼을 누를 때와 뗄 때마다 A5 LED 토글
// 우노에서 attachInterrupt를 쓸 수 있는 핀은 2번, 3번뿐 (A0는 안 됨)
const int BUTTON_PIN = 2;               // 버튼 핀 (인터럽트 0번)
const int LED_PIN = A5;                 // LED 핀
const unsigned long DEBOUNCE_MS = 50;   // 디바운스 시간

// 인터럽트 함수 안에서 바뀌는 변수는 volatile을 붙여야 loop에서 제대로 읽힘
volatile int ledState = LOW;               // LED 상태
volatile int lastButtonState = HIGH;       // 과거값: 마지막으로 인정한 버튼 상태
volatile unsigned long lastInterruptTime = 0; // 마지막으로 인정한 인터럽트 시각
volatile bool changed = false;             // 인터럽트가 처리됐는지 loop에 알려주는 깃발

void buttonISR() {  // 버튼 핀 값이 바뀔 때마다 자동으로 실행되는 인터럽트 함수
  unsigned long now = millis();
  if (now - lastInterruptTime > DEBOUNCE_MS) {   // 50ms 안의 흔들림은 무시
    int reading = digitalRead(BUTTON_PIN);       // 현재값 읽기
    if (reading != lastButtonState) {            // 현재값이 과거값과 다르면 (누름 또는 뗌)
      lastButtonState = reading;
      ledState = !ledState;                      // LED 켜기/끄기 바꾸기
      digitalWrite(LED_PIN, ledState);
      changed = true;
      lastInterruptTime = now;
    }
  }
}

void setup() {      // 한번만 실행
  Serial.begin(9600);                 // 시리얼 통신 시작 (속도 9600)
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 버튼 핀을 입력모드로 (내부 풀업저항 사용)
  pinMode(LED_PIN, OUTPUT);           // LED 핀을 출력모드로
  // 버튼 핀 값이 바뀔 때(CHANGE: 누를 때 + 뗄 때) buttonISR 실행
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, CHANGE);
}

void loop() {       // 무한히 반복
  if (changed) {                      // 인터럽트에서 토글했으면 출력 (Serial은 인터럽트 함수 안에서 쓰면 안 됨)
    changed = false;
    Serial.print(lastButtonState == LOW ? "Button pressed" : "Button released");
    Serial.println(ledState == HIGH ? " -> LED ON" : " -> LED OFF");
  }
}
