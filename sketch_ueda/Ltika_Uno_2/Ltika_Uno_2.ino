#define LED 6

void setup() {
                  
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.begin(9600);
}
 
void loop() {
  int val_L;//進行方向左側のフォトインタラプタの値
  val_L = analogRead(5) ; //アナログ0番ピンからセンサ値を読み込み
  Serial.println(val_L) ; // シリアルモニターへ表示
  delay(100);
 digitalWrite(LED, HIGH);
  if(val_L >20 ){
    digitalWrite(LED, LOW);
  }
}
