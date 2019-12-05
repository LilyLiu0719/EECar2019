#include<SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h> 

//#define RST_PIN      A0        // RFID resetpin
//#define SS_PIN       13       // RFID selection pin
//MFRC522 mfrc522(SS_PIN, RST_PIN);
//SoftwareSerial BT(4,2);   //bluetooth RX,TX

#define R2  3  // Define Second Right Sensor Pin
#define R1  5  // Define First Right Sensor Pin
#define M   6  // Define Middle Sensor Pin
#define L1  9  // Define First Left Sensor Pin
#define L2  10  // Define Second Leftt Sensor Pin

#define IN1  A1  //定義 I1 接腳（左）
#define IN2  A2  //定義 I2 接腳（左）
#define IN3  A3  //定義 I3 接腳（右）
#define IN4  A4  //定義 I4 接腳（右）
#define ENA  A0  //定義 ENA (PWM調速) 接腳
#define ENB  A5  //定義 ENB (PWM調速) 接腳
const byte speed = 200;

void setup() {
  // put your setup code here, to run once:
//  BT.begin(9600); //bluetooth initialization
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(R1, INPUT); 
  pinMode(R2, INPUT);
  pinMode(M,  INPUT);
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
}

void loop() {
//  //馬達電壓
//    analogWrite(ENA, speed);
//    analogWrite(ENB, speed);
//    // 轉五秒 
//    digitalWrite(IN1, HIGH);
//    digitalWrite(IN2, LOW);
//    digitalWrite(IN3, HIGH);
//    digitalWrite(IN4, LOW);
//    delay(5000);
//    // 轉五秒 
//    digitalWrite(IN2, HIGH);
//    digitalWrite(IN1, LOW);
//    digitalWrite(IN4, HIGH);
//    digitalWrite(IN3, LOW);
//    delay(5000);
  Tracking();
}

void MotorWriting(double vR, double vL) {
  if (vR >= 0) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH); //這邊的Motor第幾個對應到的High/Low是助教的車對應到的，請自己測試自己車該怎麼填!
  } 
  else if (vR < 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    vR = -vR; //因為analogWrite只吃正數，所以如果本來是負數，就要乘-1
  }
  if (vL >= 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH); //這邊的Motor第幾個對應到的High/Low是助教的車對應到的，請自己測試自己車該怎麼填!
  } 
  else if (vL < 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    vL = -vL; //因為analogWrite只吃正數，所以如果本來是負數，就要乘-1
  }
  analogWrite(ENA, vL);
  analogWrite(ENB, vR);
}
//
//void Tracking() {
//  int r1 = digitalRead(R1);
//  int r2 = digitalRead(R2);
//  int m = digitalRead(M);
//  int l2 = digitalRead(L2);
//  int l1 = digitalRead(L1);
//  if ((r1 == HIGH) && (r2 == LOW) && (m == LOW) && (l2 == LOW) && (l1 == LOW)) {
//      MotorWriting(-150, 250);    // big right turn
//  } 
//  else if ((r1 == HIGH) && (r2 == HIGH) && (m == LOW) && (l2 == LOW) && (l1 == LOW)) {
//      MotorWriting(-120, 250); // right turn
//  } 
//  else if ((r1 == HIGH) && (r2 == HIGH) && (m == HIGH) && (l2 == LOW) && (l1 == LOW)) {
//      MotorWriting(-50, 150);     // smaller right turn
//  } 
//  else if ((r1 == LOW) && (r2 == HIGH) && (m == LOW) && (l2 == LOW) && (l1 == LOW)) {
//      MotorWriting(50, 150);      // even smaller right turn
//  } 
//  else if ((r1 == LOW) && (r2 == HIGH) && (m == HIGH) && (l2 == LOW) && (l1 == LOW)) {
//      MotorWriting(100, 200);     // even smaller right turn
//  } 
//  else if ((r1 == LOW) && (r2 == HIGH) && (m == HIGH) && (l2 == HIGH) && (l1 == LOW)) {
//      MotorWriting(200, 200); // center
//  } 
//  else if ((r1 == LOW) && (r2 == LOW) && (m == HIGH) && (l2 == LOW) && (l1 == LOW)) {
//      MotorWriting(200, 200);     // center
//  } 
//  else if ((r1 == LOW) && (r2 == LOW) && (m == HIGH) && (l2 == HIGH) && (l1 == LOW)) {
//      MotorWriting(200, 100);     // even smaller left turn
//  } 
//  else if ((r1 == LOW) && (r2 == LOW) && (m == LOW) && (l2 == HIGH) && (l1 == LOW)) {
//      MotorWriting(150, 50);      // even smaller left turn
//  }
//  else if ((r1 == LOW) && (r2 == LOW) && (m == HIGH) && (l2 == HIGH) && (l1 == HIGH)) {
//      MotorWriting(150, -50);     // smaller left turn
//  } 
//  else if ((r1 == LOW) && (r2 == LOW) && (m == LOW) && (l2 == HIGH) && (l1 == HIGH)) {
//      MotorWriting(250, -120); // left turn
//} 
//  else if ((r1 == LOW) && (r2 == LOW) && (m == LOW) && (l2 == LOW) && (l1 == HIGH)) {
//      MotorWriting(250, -150);    // big left turn
//  } 
//  else if ((r1 == LOW) && (r2 == LOW) && (m == LOW) && (l2 == LOW) && (l1 == LOW)) {
//      MotorWriting(50, 50);
//  } 
//  else {
//    MotorWriting(-60, -60);
//  }
// }




void Tracking(){
  int r1 = digitalRead(R1);
  int r2 = digitalRead(R2);
  int m = digitalRead(M);
  int l2 = digitalRead(L2);
  int l1 = digitalRead(L1);
  double error = 1*l1 + 0.5*l2 - 0.75*(l1 == l2) - 0.25*(m == l2)-(1*r1 + 0.5*r2 - 0.75*(r1 == r2) - 0.25*(m == r2)); //Total error from sensor outputs//其中，1、0.5、0.75、0.25都是權重係數，可以自己調整~
  double vR = 150 + 100*error;
  double vL = 150 - 100*error; //根據車身偏移量指數，調配MotorWriting需要的值，一樣可以自由調整數字及調配方式
  MotorWriting(int(vR),int(vL)); //Feedback to motors
  }





 
