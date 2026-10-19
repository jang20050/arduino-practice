// 아두이노 우노: A0, A2, A4 핀에 연결한 LED 3개를 1초씩 번갈아 켜기
const int LED_PIN1 = A0; // LED1 핀
const int LED_PIN2 = A2; // LED2 핀
const int LED_PIN3 = A4; // LED3 핀

void setup() {      // 한번만 실행
  pinMode(LED_PIN1, OUTPUT); // LED1 핀을 출력모드로
  pinMode(LED_PIN2, OUTPUT); // LED2 핀을 출력모드로
  pinMode(LED_PIN3, OUTPUT); // LED3 핀을 출력모드로
}

void loop() {       // 무한히 반복
  digitalWrite(LED_PIN1, HIGH); // LED1 켜기
  digitalWrite(LED_PIN2, LOW);  // LED2 끄기
  digitalWrite(LED_PIN3, LOW);  // LED3 끄기
  delay(1000);                  // 1초 기다리기

  digitalWrite(LED_PIN1, LOW);  // LED1 끄기
  digitalWrite(LED_PIN2, HIGH); // LED2 켜기
  digitalWrite(LED_PIN3, LOW);  // LED3 끄기
  delay(1000);                  // 1초 기다리기

  digitalWrite(LED_PIN1, LOW);  // LED1 끄기
  digitalWrite(LED_PIN2, LOW);  // LED2 끄기
  digitalWrite(LED_PIN3, HIGH); // LED3 켜기
  delay(1000);                  // 1초 기다리기
}
