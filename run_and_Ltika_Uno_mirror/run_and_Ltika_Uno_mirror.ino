
#define AEN 10
#define APHASE 9
#define BEN 6
#define BPHASE 5
#define MODE 2
  
void setup() {
 
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(BEN, OUTPUT);
  pinMode(BPHASE, OUTPUT);
  pinMode(AEN, OUTPUT);
  pinMode(APHASE, OUTPUT);
  pinMode(MODE, OUTPUT);
  digitalWrite(MODE, HIGH);


}


void loop() { 

 
  motor_stop();
  Ltika();
  delay(50);
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
     
      digitalWrite(13, LOW);

   }else{

      digitalWrite(APHASE, HIGH);
      digitalWrite(BPHASE, HIGH);
      analogWrite(AEN, 30);
      analogWrite(BEN, 30);
      digitalWrite(13, HIGH);     
   }
}

