// 11번 핀 LED가 점점 밝아졌다가 점점 어두워지기를 반복

const int LED_PIN = 11;         // PWM(~) 핀이어야 밝기 조절 가능
const int STEP_DELAY = 10;      // 한 단계마다 기다리는 시간(ms), 클수록 천천히

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // 점점 밝아짐 (0 → 255)
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(LED_PIN, brightness);
    delay(STEP_DELAY);
  }

  // 점점 어두워짐 (255 → 0)
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(LED_PIN, brightness);
    delay(STEP_DELAY);
  }
}
