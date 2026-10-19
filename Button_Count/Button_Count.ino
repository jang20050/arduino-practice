// 아두이노 우노: A0 버튼을 누른 횟수를 시리얼 모니터로 출력, 5번 누를 때마다 A5 LED 켜기/끄기
// millis()로 디바운싱 + 현재값/과거값 비교로 "누르는 순간"만 감지
const int BUTTON_PIN = A0;             // 버튼 핀
const int LED_PIN = A5;                // LED 핀
const unsigned long DEBOUNCE_MS = 50;  // 디바운스 시간 (50ms 동안 값이 유지돼야 인정)

int lastReading = HIGH;                // 과거값: 바로 전에 읽은 값 (풀업이라 처음엔 HIGH)
int buttonState = HIGH;                // 확정된 버튼 상태 (노이즈 걸러진 값)
unsigned long lastChangeTime = 0;      // 읽은 값이 마지막으로 바뀐 시각
int pressCount = 0;                    // 버튼 누른 횟수
int ledState = LOW;                    // LED 상태

void setup() {      // 한번만 실행
  Serial.begin(9600);                 // 시리얼 통신 시작 (속도 9600)
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 버튼 핀을 입력모드로 (내부 풀업저항 사용)
  pinMode(LED_PIN, OUTPUT);           // LED 핀을 출력모드로
}

void loop() {       // 무한히 반복
  int reading = digitalRead(BUTTON_PIN);       // 현재값 읽기

  if (reading != lastReading) {                // 현재값이 과거값과 다르면 (흔들림 포함)
    lastChangeTime = millis();                 // 바뀐 시각 기록
  }

  if (millis() - lastChangeTime > DEBOUNCE_MS) { // 값이 50ms 넘게 그대로면 진짜 변화로 인정
    if (reading != buttonState) {              // 확정 상태가 바뀌었으면
      buttonState = reading;

      if (buttonState == LOW) {                // HIGH → LOW: 누르는 순간
        pressCount++;                          // 횟수 1 증가

        Serial.print("Button pressed: ");
        Serial.print(pressCount);
        Serial.println(" times");

        if (pressCount % 5 == 0) {             // 5번 누를 때마다 (5, 10, 15...)
          ledState = !ledState;                // LED 켜기/끄기 바꾸기
          digitalWrite(LED_PIN, ledState);
          Serial.println("LED toggled");
        }
      }
    }
  }

  lastReading = reading;                       // 현재값을 과거값으로 저장
}
