//***********************************************************
// サーボモーターを動かすプログラム
//***********************************************************
#include <Servo.h>  //サーボモーター用ライブラリを読み込み
#include <Console.h>   //ueda追記
#include <Bridge.h>    //ueda追記

Servo servo1; //サーボ用のオブジェクト1を作成
Servo servo2; //サーボ用のオブジェクト2を作成
int close; //閉まる
int open; //開く
int cds_1; //cds_1セルの値(信号機)
int flag = 0;

void setup()
{
 servo1.attach(9); //デジタル9番ピンをサーボの角度命令出力ピンとして設定
 servo2.attach(10); //デジタル10番ピンをサーボの角度命令出力ピンとして設定
 
 Bridge.begin();
}
void loop()
{
close = 90;
open = 20;

cds_1 = analogRead(0);//アナログ1番ピンからcds_2の抵抗値を読み込み
Console.print("Traffic light      ");
Console.println(cds_1);

  if(cds_1 > 700){
  servo1.write(close); //サーボを動かす(0度)
  delay(100);
  servo2.write(close); //サーボを動かす(0度)
  delay(100);//10秒駅に停車
  flag = 1;
  
  }
  if(cds_1 <= 720){
    if(flag == 1){
       delay(2500);//電車の通過待ち
       flag = 0;
    }
  servo1.write(open); //サーボを動かす(0度)
  delay(100);
  servo2.write(open); //サーボを動かす(0度)
  delay(100);
  }
}
