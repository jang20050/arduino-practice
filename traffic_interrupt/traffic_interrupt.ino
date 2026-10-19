// 신호등 (7, 8, 9번 핀 LED) + 2번 핀 버튼 인터럽트
// 버튼을 누르고 있는 동안 3개 LED가 모두 켜지고, 떼면 다시 신호등 동작

const int LED_PINS[] = {7, 8, 9};   // 빨강, 노랑, 초록 순서
const int LED_COUNT = 3;
const int BUTTON_PIN = 2;           // 인터럽트 0번 (UNO 기준)

// 버튼 배선 방식
//  true  : 버튼 한쪽 = 2번 핀, 다른 쪽 = GND (저항 없음, 내부 풀업 사용)
//  false : 버튼 한쪽 = 5V, 다른 쪽 = 2번 핀 + 10kΩ 저항으로 GND (풀다운)
const bool BUTTON_TO_GND = false;

const unsigned long LIGHT_TIME[] = {3000, 1000, 3000};  // 각 LED가 켜져 있는 시간(ms)

volatile bool allOn = false;         // 인터럽트에서 바꾸는 변수는 volatile

bool isPressed() {
  int level = digitalRead(BUTTON_PIN);
  return BUTTON_TO_GND ? (level == LOW) : (level == HIGH);
}

void allLeds(int state) {
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], state);
  }
}

// 버튼을 누를 때와 뗄 때 모두 호출됨
void buttonISR() {
  allOn = isPressed();
  if (allOn) {
    allLeds(HIGH);  // 누르는 즉시 전부 켜기
  }
}

// delay() 대신 사용: 기다리는 도중에 버튼이 눌리면 바로 빠져나옴
bool waitOrPressed(unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms) {
    if (allOn) return true;
  }
  return false;
}

void setup() {
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  pinMode(BUTTON_PIN, BUTTON_TO_GND ? INPUT_PULLUP : INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, CHANGE);
}

void loop() {
  // 버튼을 누르고 있는 동안: 3개 모두 켜진 상태로 대기
  if (allOn) {
    allLeds(HIGH);
    while (isPressed()) {
      // 손을 뗄 때까지 기다림
    }
    delay(20);        // 뗄 때 생기는 떨림(채터링) 무시
    allOn = isPressed();
    return;           // 떼면 빨강부터 다시 신호등 시작
  }

  // 신호등 동작
  for (int i = 0; i < LED_COUNT; i++) {
    allLeds(LOW);
    digitalWrite(LED_PINS[i], HIGH);
    if (waitOrPressed(LIGHT_TIME[i])) {
      return;  // 버튼이 눌리면 신호등 중단 → 위의 "모두 켜기"로
    }
  }
}
