// 아두이노 우노: A0 버튼 동작에 따라 A5 LED 제어
// 따닥(더블클릭) → LED 켜기 / 길게 누르기 → LED 끄기 / 한번 짧게 누르기 → 아무 일도 안 함
const int BUTTON_PIN = A0;               // 버튼 핀
const int LED_PIN = A5;                  // LED 핀
const unsigned long DEBOUNCE_MS = 50;    // 디바운스 시간
const unsigned long DOUBLE_MS = 400;     // 첫 번째 클릭 후 이 시간 안에 또 누르면 더블클릭
const unsigned long LONG_MS = 1000;      // 이 시간 넘게 누르고 있으면 길게 누르기

int lastReading = HIGH;                  // 과거값: 바로 전에 읽은 값
int buttonState = HIGH;                  // 확정된 버튼 상태
unsigned long lastChangeTime = 0;        // 읽은 값이 마지막으로 바뀐 시각
unsigned long pressStartTime = 0;        // 버튼을 누르기 시작한 시각
unsigned long lastReleaseTime = 0;       // 짧은 클릭 후 버튼을 뗀 시각
int clickCount = 0;                      // 짧게 누른 횟수 (더블클릭 판별용)
bool longHandled = false;                // 이번 누름이 이미 길게 누르기로 처리됐는지

void setup() {      // 한번만 실행
  Serial.begin(9600);                 // 시리얼 통신 시작 (속도 9600)
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 버튼 핀을 입력모드로 (내부 풀업저항 사용)
  pinMode(LED_PIN, OUTPUT);           // LED 핀을 출력모드로
}

void loop() {       // 무한히 반복
  unsigned long now = millis();               // 현재 시각
  int reading = digitalRead(BUTTON_PIN);      // 현재값 읽기

  if (reading != lastReading) {               // 현재값이 과거값과 다르면
    lastChangeTime = now;                     // 바뀐 시각 기록
  }
  lastReading = reading;                      // 현재값을 과거값으로 저장

  if (now - lastChangeTime > DEBOUNCE_MS && reading != buttonState) { // 진짜 변화로 인정
    buttonState = reading;

    if (buttonState == LOW) {                 // 누르는 순간
      pressStartTime = now;
      longHandled = false;
    } else {                                  // 떼는 순간
      if (!longHandled) {                     // 길게 누르기가 아니었으면 짧은 클릭
        clickCount++;
        lastReleaseTime = now;

        if (clickCount == 2) {                // 시간 안에 두 번 → 더블클릭
          digitalWrite(LED_PIN, HIGH);        // LED 켜기
          Serial.println("Double click -> LED ON");
          clickCount = 0;
        }
      }
    }
  }

  // 누르고 있는 동안 LONG_MS가 지나면 길게 누르기 (떼기 전에 바로 반응)
  if (buttonState == LOW && !longHandled && now - pressStartTime >= LONG_MS) {
    longHandled = true;
    clickCount = 0;                           // 진행 중이던 클릭은 취소
    digitalWrite(LED_PIN, LOW);               // LED 끄기
    Serial.println("Long press -> LED OFF");
  }

  // 한 번 클릭 후 DOUBLE_MS 안에 다시 안 누르면 그냥 한 번 클릭 → 아무 일도 안 함
  if (clickCount == 1 && buttonState == HIGH && now - lastReleaseTime > DOUBLE_MS) {
    clickCount = 0;
    Serial.println("Single click -> nothing");
  }
}
