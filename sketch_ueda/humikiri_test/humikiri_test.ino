#include <Console.h>
#include <Bridge.h>

#define AEN 10
#define APHASE 9
#define BEN 6
#define BPHASE 5
#define MODE 2
int flag_L ;
int flag_R = 0;
void setup() {
                  
  Bridge.begin();
  Console.begin();

  pinMode(BEN, OUTPUT);
  pinMode(BPHASE, OUTPUT);
  pinMode(AEN, OUTPUT);
  pinMode(APHASE, OUTPUT);
  pinMode(MODE, OUTPUT);
  digitalWrite(MODE, HIGH);

 // while (!Console);
}
 
void loop() {
  int val_L;//左側のフォトインタラプタの値
  int val_R;//右側のフォトインタラプタの値
  val_L = analogRead(0) ; //アナログ0番ピンからセンサ値を読み込み
  Console.println(val_L) ; // シリアルモニターへ表示
  Console.println("L") ; // シリアルモニターへ表示
  val_R = analogRead(1) ; //アナログ1番ピンからセンサ値を読み込み
  Console.println(val_R) ; // シリアルモニターへ表示
  Console.println("R") ; // シリアルモニターへ表示
  delay(100);

//センサLが侵入を検知した場合  
   if(val_L > 5){
    digitalWrite(APHASE, HIGH);
    digitalWrite(BPHASE, HIGH);
    analogWrite(AEN, 10);
    analogWrite(BEN, 10);
    delay(2500);
    analogWrite(AEN, 0);
    analogWrite(BEN, 0);
    while(val_R < 5){
      val_R = analogRead(1) ; //アナログ1番ピンからセンサ値を読み込み
    }
    digitalWrite(APHASE, LOW);
    digitalWrite(BPHASE, LOW);
    analogWrite(AEN, 10);
    analogWrite(BEN, 10);
    delay(2500);
    analogWrite(AEN, 0);
    analogWrite(BEN, 0);
   }
//センサRが侵入を検知した場合  
   if(val_R > 5){
    digitalWrite(APHASE, HIGH);
    digitalWrite(BPHASE, HIGH);
    analogWrite(AEN, 10);
    analogWrite(BEN, 10);
    delay(2500);
    analogWrite(AEN, 0);
    analogWrite(BEN, 0);
    while(val_L < 5){
      val_L = analogRead(0) ; //アナログ0番ピンからセンサ値を読み込み
    }
    digitalWrite(APHASE, LOW);
    digitalWrite(BPHASE, LOW);
    analogWrite(AEN, 10);
    analogWrite(BEN, 10);
    delay(2500);
    analogWrite(AEN, 0);
    analogWrite(BEN, 0);
   }
  /*
  if(val_L > 5 && train == 0) {
    digitalWrite(APHASE, HIGH);
    digitalWrite(BPHASE, HIGH);
    analogWrite(AEN, 10);
    analogWrite(BEN, 10);
    delay(2500);
    analogWrite(AEN, 0);
    analogWrite(BEN, 0);
    train = 1;
  }
  if(val_R > 5 && train == 1) {
    digitalWrite(APHASE, LOW);
    digitalWrite(BPHASE, LOW);
    analogWrite(AEN, 10);
    analogWrite(BEN, 10);
    delay(2500);
    analogWrite(AEN, 0);
    analogWrite(BEN, 0);
    train = 0;
  }
*/
  
}

