// 가변저항(A0)을 돌리면 네오픽셀 8구(10번 핀)에 게이지가 채워짐
// 라이브러리: Adafruit NeoPixel (라이브러리 매니저에서 설치)

#include <Adafruit_NeoPixel.h>

const int PIXEL_PIN = 10;   // 네오픽셀 신호선(DIN)
const int NUM_PIXELS = 8;   // LED 개수
const int POT_PIN = A0;     // 가변저항 가운데 다리

Adafruit_NeoPixel strip(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(50);  // 전체 밝기 (0~255), 너무 밝으면 줄이기
  strip.show();             // 처음엔 모두 끄기
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(POT_PIN);  // 0 ~ 1023

  // 0 ~ 8개로 변환 (구간을 고르게 나누기 위해 NUM_PIXELS + 1 사용)
  int level = (long)potValue * (NUM_PIXELS + 1) / 1024;

  for (int i = 0; i < NUM_PIXELS; i++) {
    if (i < level) {
      // 게이지 색: 앞쪽은 초록 → 뒤쪽으로 갈수록 빨강
      int red = map(i, 0, NUM_PIXELS - 1, 0, 255);
      int green = 255 - red;
      strip.setPixelColor(i, strip.Color(red, green, 0));
    } else {
      strip.setPixelColor(i, 0);  // 끄기
    }
  }
  strip.show();

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Level: ");
  Serial.println(level);

  delay(20);
}
