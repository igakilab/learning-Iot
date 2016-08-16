void setup() {
                  
  Serial.begin(9600);
}
 
void loop() {
  int val_L;//進行方向左側のフォトインタラプタの値
  val_L = analogRead(1) ; //アナログ0番ピンからセンサ値を読み込み
  Serial.println(val_L) ; // シリアルモニターへ表示
  delay(100);
}
 
