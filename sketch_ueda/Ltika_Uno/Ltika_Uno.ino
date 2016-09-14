void setup() {
                  
  Serial.begin(9600);
}
 
void loop() {
  int val_L;//進行方向左側のフォトインタラプタの値
  int val_R;//進行方向左側のフォトインタラプタの値
  val_L = analogRead(0) ; //アナログ0番ピンからセンサ値を読み込み
  Serial.println(val_L) ; // シリアルモニターへ表示
  Serial.println("L") ; // シリアルモニターへ表示
  val_R = analogRead(1) ; //アナログ0番ピンからセンサ値を読み込み
  Serial.println(val_R) ; // シリアルモニターへ表示
  Serial.println("R") ; // シリアルモニターへ表示
  delay(100);
}
 
