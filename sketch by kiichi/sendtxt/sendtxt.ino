//***********************************************************
// サーボモーターを動かすプログラム
//***********************************************************
#include <Servo.h>  //サーボモーター用ライブラリを読み込み
#include <Console.h>   //ueda追記
#include <Bridge.h>    //ueda追記
#include <YunServer.h>
#include <YunClient.h>
#include <FileIO.h>

YunServer server;

Servo servo1; //サーボ用のオブジェクト1を作成
Servo servo2; //サーボ用のオブジェクト2を作成
int val; //サーボの角度を格納するための変数

int cds_1; //cds_1セルの値(駅)
int cds_2; //cds_2セルの値(信号機)
int cnt=0; //10秒停止用カウンタ
int flag_1=0; //10秒カウント中
int flag_2=0; //10秒経ったかを確認

void setup()
{
 servo1.attach(9); //デジタル9番ピンをサーボの角度命令出力ピンとして設定
 servo2.attach(10); //デジタル10番ピンをサーボの角度命令出力ピンとして設定
 pinMode(3, OUTPUT);
 pinMode(5, OUTPUT);
 digitalWrite(3, LOW);
 digitalWrite(5, LOW);
 Bridge.begin();
 Console.begin();
 FileSystem.begin();
 server.listenOnLocalhost();
 server.begin();
}
void loop(){
YunClient client = server.accept();

client.println("Information");
client.println("");

val = 30;
servo1.write(val); //サーボを動かす(0度)

delay(100);
cds_1 = analogRead(0);//アナログ1番ピンからcds_1の抵抗値を読み込み
if(cds_1 > 500) {
  //client.println("Train              Stop");
  delay(100);
  analogWrite(3, 0);
  analogWrite(5, 20);
  
  servo2.write(val); //サーボを動かす(0度)
  //servo4.write(val); //サーボを動かす(0度)
    if(flag_1 == 0){
    flag_1 = 1;
    }
    if(flag_1 == 1){
      cnt += 1;
  } 
  delay(100);//10秒駅に停車
  
  if(cnt == 18){
    cnt = 0;
    flag_1 = 0;
    flag_2 = 1;
  }
  
  if(flag_2 == 1){
  servo1.write(130); //サーボを動かす(0度)
  //servo3.write(130); //サーボを動かす(0度)
  delay(300);
  flag_2 = 0;
  }
}

if(cds_1 <= 500 && flag_1 == 0){
//client.println("Train              Absent");
delay(100);  
servo2.write(130); //サーボを動かす(0度)
analogWrite(3, 20);
analogWrite(5, 0);
}

cds_2 = analogRead(1);//アナログ1番ピンからcds_2の抵抗値を読み込み
if(cds_2 > 700) {
  Traffictxt(0);
  delay(100);
  Railroadtxt(0);
  delay(100);//0.3秒 
}else{
  Traffictxt(1);
  delay(100);
  Railroadtxt(1);
  delay(100);//0.3秒
}
if(flag_1 == 1){
    Stationtxt(0);
    delay(100);
  }else{
    Stationtxt(1);
    delay(100);
  }
client.println("");
delay(100);//0.3秒
client.stop();
}

void Stationtxt(int a){
  File stationfile = FileSystem.open("/mnt/sd/arduino/www/station.txt", FILE_WRITE);
  if(a == 0){
    stationfile.println("停車中");
  }else{
    stationfile.println("不在");
  }
  stationfile.close();
}

void Traffictxt(int a){
  File trafficfile = FileSystem.open("/mnt/sd/arduino/www/traffic.txt", FILE_WRITE);
  if(a == 0){
    trafficfile.println("閉じる");
  }else{
    trafficfile.println("開く");
  }
  trafficfile.close();
}

void Railroadtxt(int a){
  File railroadfile = FileSystem.open("/mnt/sd/arduino/www/railroad.txt", FILE_WRITE);
  if(a == 0){
    railroadfile.println("赤色");
  }else{
    railroadfile.println("緑色");
  }
  railroadfile.close();
}
