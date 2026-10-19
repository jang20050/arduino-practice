// 아두이노 우노 3번핀에 연결한 LED 깜빡이기
void setup() {      // 한번만 실행
  pinMode(3, OUTPUT);   // 3번핀 핀모드를 출력모드로
}

void loop() {       // 무한히 반복
  digitalWrite(3, HIGH); // 3번핀을 5V로
  delay(1000);           // 1000ms(1초) 대기
  digitalWrite(3, LOW);  // 3번핀을 0V로
  delay(1000);           // 1000ms(1초) 대기
}
