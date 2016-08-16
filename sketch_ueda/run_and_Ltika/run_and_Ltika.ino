#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

#define AEN 10
#define APHASE 9
#define BEN 6
#define BPHASE 5
#define MODE 2

YunServer server;

  
void setup() {
  Bridge.begin();
  Console.begin();

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(BEN, OUTPUT);
  pinMode(BPHASE, OUTPUT);
  pinMode(AEN, OUTPUT);
  pinMode(APHASE, OUTPUT);
  pinMode(MODE, OUTPUT);
  digitalWrite(MODE, HIGH);

  server.listenOnLocalhost();
  server.begin();

}


void loop() { 

  YunClient client = server.accept();

  if (client) {

    process(client);
    Console.println("accses");

    client.stop();
  }
  Ltika();
  delay(50);
}

void process(YunClient client) {

  String command = client.readStringUntil('/');
  Console.println(command);
  if (command == "FORWARD") {
    Console.println("Forward");
    digitalWrite(APHASE, HIGH);
    digitalWrite(BPHASE, HIGH);
    analogWrite(AEN, 30);
    analogWrite(BEN, 30);
  }
  if (command == "BACK") {
    Console.println("Back");
    digitalWrite(BPHASE, LOW);
    analogWrite(BEN, 35);
    digitalWrite(APHASE, LOW);
    analogWrite(AEN, 35);
    delay(300);
  }
  if (command == "STOP") {
    Console.println("Stop");
    motor_stop();
  }
  
  if (command == "LEFT"){
    Console.println("Left");
    digitalWrite(BPHASE, HIGH);
    analogWrite(BEN, 50);
    digitalWrite(APHASE, LOW);
    analogWrite(AEN, 50);
  }
  if (command == "RIGHT"){
    Console.println("Right");
    digitalWrite(APHASE, HIGH);
    analogWrite(AEN, 50);
    digitalWrite(BPHASE, LOW); 
    analogWrite(BEN, 50);
  }
}
void motor_stop(){
  analogWrite(AEN,0);
  analogWrite(APHASE,0);
  analogWrite(BEN,0);
  analogWrite(BPHASE,0);
}

void Ltika(){

  int val_L;//進行方向左側のフォトインタラプタの値
  int val_R;//進行方向右側のフォトインタラプタの値

  val_L = analogRead(0) ; //アナログ0番ピンからセンサ値を読み込み
  Serial.println(val_L) ; // シリアルモニターへ表示
  val_R = analogRead(1) ; //アナログ1番ピンからセンサ値を読み込み

  Serial.println(val_L) ; // シリアルモニターへ表示
  if (val_L >20 && val_R >20) {
      Console.println("Stop");
      motor_stop();
      digitalWrite(13, HIGH);
   }else{
     digitalWrite(13, LOW);
   }
}

