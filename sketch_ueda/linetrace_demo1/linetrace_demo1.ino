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
  Serial.begin(9600);

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
  int L = 30;//モータの回転速度
   val_L = analogRead(0) ; //アナログ0番ピンからセンサ値を読み込み
   Serial.println(val_L) ; // シリアルモニターへ表示
   Serial.println("L") ; // シリアルモニターへ表示
   val_R = analogRead(1) ; //アナログ1番ピンからセンサ値を読み込み
   Serial.println(val_R) ; // シリアルモニターへ表示
   Serial.println("R") ; // シリアルモニターへ表示
   
  if (val_L > L-5 && val_R > L-5) {
     
      digitalWrite(APHASE, HIGH);
      digitalWrite(BPHASE, HIGH);
      analogWrite(AEN, 40);
      analogWrite(BEN, 40);
      digitalWrite(13, HIGH);
   }else if(val_L > L && val_R < L){
      digitalWrite(APHASE, HIGH);
      digitalWrite(BPHASE, HIGH);
      analogWrite(AEN, 0);
      analogWrite(BEN, 50);
      digitalWrite(13, HIGH);
   }else if(val_L < L && val_R > L){
      digitalWrite(APHASE, HIGH);
      digitalWrite(BPHASE, HIGH);
      analogWrite(AEN, 50);
      analogWrite(BEN, 0);
      digitalWrite(13, HIGH);
   
   }else{
      digitalWrite(13, LOW);
   }
}

