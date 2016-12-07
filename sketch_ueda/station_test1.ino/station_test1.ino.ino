//***********************************************************
// サーボモーターを動かすプログラム
//***********************************************************
#include <Servo.h>  //サーボモーター用ライブラリを読み込み
#include <Console.h>   //ueda追記
#include <Bridge.h>    //ueda追記

Servo servo1; //サーボ用のオブジェクト1を作成
Servo servo2; //サーボ用のオブジェクト2を作成
Servo servo3; //サーボ用のオブジェクト3を作成
Servo servo4; //サーボ用のオブジェクト4を作成
int val; //サーボの角度を格納するための変数
int cds; //cdsセルの値
void setup()
{
 servo1.attach(9); //デジタル9番ピンをサーボの角度命令出力ピンとして設定
 servo2.attach(10); //デジタル10番ピンをサーボの角度命令出力ピンとして設定
 servo3.attach(11); //デジタル11番ピンをサーボの角度命令出力ピンとして設定
 servo4.attach(12); //デジタル12番ピンをサーボの角度命令出力ピンとして設定
 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
 digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 Bridge.begin();
 Console.begin();
}
void loop()
{
val = 30;
servo1.write(val); //サーボを動かす(0度)
servo3.write(val); //サーボを動かす(0度)

delay(500);

cds = analogRead(0);//アナログ0番ピンからcdsの抵抗値を読み込み
Console.println(cds) ;//cdsの抵抗値をシリアルモニターに表示 

if(cds > 500) {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  servo2.write(val); //サーボを動かす(0度)
  servo4.write(val); //サーボを動かす(0度)
  delay(10000);
  servo1.write(130); //サーボを動かす(0度)
  servo3.write(130); //サーボを動かす(0度)
  delay(500);
  }else {
  servo2.write(130); //サーボを動かす(0度)
  servo4.write(130); //サーボを動かす(0度)
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  
}

/*
delay(2000);
val = 30;
servo2.write(val); //サーボを動かす(90度)
delay(2000);
*/
}
