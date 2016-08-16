#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

#define AEN 10
#define APHASE 9
#define BEN 6
#define BPHASE 11
#define MODE 2

YunServer server;

int URPWM = 3; // PWM Output 0－25000US，Every 50US represent 1cm
int URTRIG=5; // PWM trigger pin
int stop1 = 1; // 動作flag
int flag1 = 0; // 前後で動作しているか
int flag2 = 0; // 緑のランプが点灯しているか

uint8_t EnPwmCmd[4]={0x44,0x02,0xbb,0x01};    // distance measure command

void setup() {
Bridge.begin();
Console.begin();
Serial.begin(9600);                         // Sets the baud rate to 9600

pinMode(BEN, OUTPUT);
pinMode(BPHASE, OUTPUT);
pinMode(AEN, OUTPUT);
pinMode(APHASE, OUTPUT);
pinMode(MODE, OUTPUT);
pinMode(4,INPUT) ;    //タクトスイッチに接続ピンをデジタル入力に設定
pinMode(13, OUTPUT);
pinMode(12, OUTPUT);
digitalWrite(MODE, HIGH);
digitalWrite(12, HIGH);
  server.listenOnLocalhost();
  server.begin();
  PWM_Mode_Setup();
}

void loop() { 

  YunClient client = server.accept();
  
  if (client) {

    process(client);
    Console.println("accses");

    client.stop();
  }
  PWM_Mode();

  if (digitalRead(4) == HIGH && stop1 == 1) {     //スイッチの状態を調べる
      motor_forward();      //スイッチが押されているならLEDを点灯
      delay(250);
    } 
    else if (digitalRead(4) == HIGH && stop1 == 0){
      motor_stop();       //スイッチが押されていないならLEDを消灯
      delay(250);
    }

  delay(20);
}

void PWM_Mode_Setup() {
   
  pinMode(URTRIG,OUTPUT);                     // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG,HIGH);                  // Set to HIGH
   
  pinMode(URPWM, INPUT);                      // Sending Enable PWM mode command
   
  for(int i=0;i<4;i++)
  {
      Serial.write(EnPwmCmd[i]);
  } 
}
  
void PWM_Mode() {                              // a low pull on pin COMP/TRIG  triggering a sensor reading
  
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);               // reading Pin PWM will output pulses
  
  unsigned long DistanceMeasured=pulseIn(URPWM,LOW);

  if(DistanceMeasured>=1000 && stop1 == 0){
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    if(flag2 == 1){
      analogWrite(AEN, 60);
      analogWrite(BEN, 60);
      flag2 = 0;
    }
  }
  
  if(DistanceMeasured>=500 && DistanceMeasured<1000 && stop1 == 0)
  {              // the reading is invalid.
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    if(flag1 == 1){
      analogWrite(AEN, 30);
      analogWrite(BEN, 30);
      flag2 = 1;
    }
  }
  else if(DistanceMeasured<500 && stop1 == 0)
  {
    motor_stop();
  }
 
}

void process(YunClient client) {

  String command = client.readStringUntil('/');
  Console.println(command);
  if (command == "FORWARD") {
    Console.println("Forward");
    motor_forward();
  }
  if (command == "BACK") {
    Console.println("Back");
    digitalWrite(BPHASE, HIGH);
    analogWrite(BEN, 60);
    digitalWrite(APHASE, HIGH);
    analogWrite(AEN, 60);
    flag1 = 1;
    stop1 = 0;
  }
  if (command == "STOP") {
    Console.println("Stop");
    motor_stop();
  }
  if (command == "LEFT"){
    Console.println("Left");
    digitalWrite(BPHASE, LOW);
    analogWrite(BEN, 50);
    digitalWrite(APHASE, HIGH);
    analogWrite(AEN, 50);
    flag1 = 0;
    flag2 = 0;
    stop1 = 0;
  }
  if (command == "RIGHT"){
    Console.println("Right");
    digitalWrite(APHASE, LOW);
    analogWrite(AEN, 50);
    digitalWrite(BPHASE, HIGH); 
    analogWrite(BEN, 50);
    flag1 = 0;
    flag2 = 0;
    stop1 = 0;
  }
}

void motor_forward(){
  digitalWrite(APHASE, LOW);
  digitalWrite(BPHASE, LOW);
  analogWrite(AEN, 60);
  analogWrite(BEN, 60);
  flag1 = 1;
  stop1 = 0;
}

void motor_stop(){
  analogWrite(AEN,0);
  analogWrite(APHASE,0);
  analogWrite(BEN,0);
  analogWrite(BPHASE,0);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  flag1 = 0;
  flag2 = 0;
  stop1 = 1;
}
