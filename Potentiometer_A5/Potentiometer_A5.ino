// 아두이노 우노: A5, A4 핀에 연결한 가변저항 2개 값을 시리얼 모니터로 출력
const int POT_PIN1 = A5; // 가변저항1 핀
const int POT_PIN2 = A4; // 가변저항2 핀

void setup() {      // 한번만 실행
  Serial.begin(9600);   // 시리얼 통신 시작 (속도 9600)
}

void loop() {       // 무한히 반복
  int value1 = analogRead(POT_PIN1);         // 가변저항1 값 읽기 (0~1023)
  int value2 = analogRead(POT_PIN2);         // 가변저항2 값 읽기 (0~1023)
  float voltage1 = value1 * 5.0 / 1023.0;    // 가변저항1 값을 전압(0~5V)으로 바꾸기
  float voltage2 = value2 * 5.0 / 1023.0;    // 가변저항2 값을 전압(0~5V)으로 바꾸기

  Serial.print("가변저항1 값: ");
  Serial.print(value1);
  Serial.print(" (");
  Serial.print(voltage1);
  Serial.print(" V)   가변저항2 값: ");
  Serial.print(value2);
  Serial.print(" (");
  Serial.print(voltage2);
  Serial.println(" V)");

  delay(200);                                // 0.2초 기다리기
}
