#define AEN 10
#define APHASE 9
#define BEN 6
#define BPHASE 5
#define MODE 2

void setup() {
                  
  Serial.begin(9600);

  pinMode(BEN, OUTPUT);
  pinMode(BPHASE, OUTPUT);
  pinMode(AEN, OUTPUT);
  pinMode(APHASE, OUTPUT);
  pinMode(MODE, OUTPUT);
  digitalWrite(MODE, HIGH);
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

  digitalWrite(APHASE, HIGH);
  digitalWrite(BPHASE, HIGH);
  analogWrite(AEN, 60);
  analogWrite(BEN, 60);
  
}
 
