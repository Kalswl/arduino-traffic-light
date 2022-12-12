#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 4);


#define C_R_LED A5  //car_trafficLight
#define C_Y_LED A4  //car_trafficLight
#define C_G_LED A3  //car_trafficLight
#define H_R_LED 9   //human_trafficLight
#define H_G_LED 8   //human_trafficLight
#define SW 13       // butten


Servo servo;  // Servo 클래스 타입 servo
//한번만 실행 : 핀 가능 설정(함수)


int arrayLed[8] = { 23, 25, 27, 29, 31, 33, 35, 37 };
int a = 53, b = 48, c = 47, d = 51, e = 50, f = 49, g = 52;
int COUNT;
int sw_state = digitalRead(SW);
int distance = 0;


int echoPin = 6;
int trigPin = 7;
int buzzer = 12;
char charValue[] = "0XSecond";
char charValue1[] = "cm";



void setup() {
  pinMode(C_R_LED, OUTPUT);
  pinMode(C_G_LED, OUTPUT);
  pinMode(H_R_LED, OUTPUT);
  pinMode(H_G_LED, OUTPUT);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  servo.attach(A0);



  //초음파센서
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //피에조스피커
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  for (int i = 7; i > -1; i--) {
    pinMode(arrayLed[i], OUTPUT);
  }
  lcd.init();       // I2C LCD 초기화
  lcd.backlight();  // LCD 백라이트를 켜기
}



//무한 루프: 실제 작업코드 실행
void loop() {




  //초음파센서 distance 구하는 조건
  float duration, distance;
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = ((float)(340 * duration) / 10000) / 2;

  Serial.println(distance);




  if (distance < 10 && distance > 0 || sw_state == LOW) {  // sw_state 스위치가 low


    for (int i = 0; i < 4; i++) {
      lcd.begin(16, 2);


      servo.write(90);  //서보모터 90도


      lcd.setCursor(0, 0);
      lcd.print("STOP RED LIGHT");
      lcdDisplay1(C_R_LED, H_G_LED, 1, 1, 8, 3);  //신호등 색, 신호등 색, LED HIHG/LOW, LED HIHG/LOW, 반복 횟수 i, 횟수 제한 i ~ j


      lcd.setCursor(0, 0);
      lcd.print("Yellow Light");
      lcdDisplay1(C_Y_LED, H_G_LED, 1, 1, 3, 0);  //차량 노란색


      servo.write(0);  // 서보모터 0

      lcd.setCursor(0, 0);

      lcd.print("Go Green Light");
      lcdDisplay1(C_G_LED, H_R_LED, 1, 1, 8, 0);  //차량 초록색
    }
  }

  else {
    lcd.setCursor(0, 0);
    lcd.print("Yellow Light");
    lcdDisplay1(C_Y_LED, H_G_LED, 1, 1, 3, 0);  //차량 노란색, 보행자 초록색

    servo.write(0);
  }
}



void lcdDisplay1(char a, char b, int c, int d, int e, int j) {  //a, b = 신호등 이름 입력 c,d HIGH or LOW j 반복 횟수 제한 차량 LED{a,c}, 보행자 LED{b,d}, int i, int j

  if (e == 8) {

    for (int i = 7; i > -1; i--) {
      digitalWrite(arrayLed[i], LOW);
    }
  }
  if (e == 3) {

    for (int i = 2; i > -1; i--) {
      digitalWrite(arrayLed[i], LOW);
    }

    for (int i = 7; i > 2; i--) {
      digitalWrite(arrayLed[i], HIGH);
    }
  }

  for (int i = e; i > j; i--) {

    float duration, distance;
    digitalWrite(trigPin, HIGH);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = ((float)(340 * duration) / 10000) / 2;

    Serial.println(distance);




    if (distance < 5 && (b != H_G_LED)) {

      tone(buzzer, 262, 500);  //500: 음의 높낮이(주파수), 1000: 음의 지속시간(1초)


    }

    else {
      noTone(buzzer);
    }    


    lcd.setCursor(0, 1);
    charValue[1] = i + '0';
    lcd.print(charValue);

    lcd.setCursor(0, 2);
    lcd.print(distance);  // 0XSecond 1번째 X 위치에 i를 문자로 변경
    lcd.print(charValue1);

lcd.setCursor(0, 3); // human
    lcd.print("Aaa");

    digitalWrite(a, c);
    digitalWrite(b, d);
    digitalWrite(arrayLed[i], HIGH);




    seg_time(i);  //세븐 세그먼트 숫자 표시
    delay(1000);
  }


  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
}


void seg_time(int COUNT)  //세븐 세그먼트 case문으로 받아 실행

{


  switch (COUNT) {

    case 0:  //when count value is zero show”0” on disp
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      analogWrite(g, 0);

      delay(1000);
      break;

    case 1:  // when count value is 1 show”1” on disp
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);

      digitalWrite(g, 0);
      ;
      delay(500);
      break;

    case 2:  // when count value is 2 show”2” on disp
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, 1);
      delay(500);
      break;

    case 3:  // when count value is 3 show”3” on disp
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, 1);
      delay(500);
      break;

    case 4:  // when count value is 4 show”4” on disp
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, 1);
      delay(500);
      break;

    case 5:  // when count value is 5 show”5” on disp
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, 1);
      delay(500);
      break;

    case 6:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, 1);
      delay(500);
      break;

    case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, 0);
      delay(500);
      break;

    case 8:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, 1);
      break;
  }
}

