int speakerPin = 12;
int kankan[]={2,2,2,2,1,0,0,0,1,1,2,2,1,1,1,0,1,1,1,1,1,1,1,1,2,1,1,1,0,0,1,1,2,2,2,1,0,0,0,0};
//delayTimeは本当は190usec(5250Hz)程度になるはずだが、音程が合わないので適当に調整した。
int delayTime = 95;
 
void setup(){
  //スピーカーピンを出力モードにする
  pinMode(speakerPin, OUTPUT);
  //PWMを高速化する(今回は6番ピンを使った)
  TCCR0B = 0x01;   // PWM 6 & 5 @ 64 kHz
}

void loop(){
  //区間(1)：増大
  for(int i=0; i<6; i++){
    for(int j=0; j<40; j++){
      analogWrite(speakerPin, (18*i+12)*kankan[j]);
      delayMicroseconds(delayTime);
    }
  }
  //区間(2)：一定
  for(int i=0; i<10; i++){
    for(int j=0; j<40; j++){
      analogWrite(speakerPin, 120*kankan[j]);
      delayMicroseconds(delayTime);
    }
  }
  //区間(3)：減衰
  for(int i=0; i<8; i++){
    for(int j=0; j<40; j++){
      analogWrite(speakerPin, (120-10*i)*kankan[j]);
      delayMicroseconds(delayTime);
    }
  }
  //区間(4)：ゆるやかに減衰
  for(int i=0; i<40; i++){
    for(int j=0; j<40; j++){
      analogWrite(speakerPin, (40-i)*kankan[j]);
      delayMicroseconds(delayTime);
    }
  }
  // 休み
  delay(10000);
}
