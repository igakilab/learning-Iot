#include <Bridge.h>
#include <Console.h>

void setup() {                
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  Bridge.begin();
  Console.begin();
}
 
void loop() {
  
  delay(100);

  int val_L;//進行方向左側のフォトインタラプタの値
  int val_R;//進行方向右側のフォトインタラプタの値
  val_L = analogRead(0) ; //アナログ0番ピンからセンサ値を読み込み
   Console.println(val_L) ; // シリアルモニターへ表示
   Console.println("L") ; // シリアルモニターへ表示
  val_R = analogRead(1) ; //アナログ1番ピンからセンサ値を読み込み
   Console.println(val_R) ; // シリアルモニターへ表示
   Console.println("R") ; // シリアルモニターへ表示

   delay(400);

  if(val_L >1 && val_R >1){
    digitalWrite(13, HIGH);
  }else{
    digitalWrite(13, LOW);
  }
}
