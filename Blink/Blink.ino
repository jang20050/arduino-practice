// 아두이노 우노 A0핀에 연결한 LED 깜빡이기
void setup() {      // 한번만 실행
  pinMode(A0, OUTPUT);   // A0핀 핀모드를 출력모드로
}

void loop() {       // 무한히 반복
  digitalWrite(A0, HIGH); // A0핀을 5V로
  delay(1000);            // 1000ms(1초) 대기
  digitalWrite(A0, LOW);  // A0핀을 0V로
  delay(1000);            // 1000ms(1초) 대기
}
