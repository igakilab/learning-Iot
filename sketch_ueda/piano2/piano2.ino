#define BEAT 200   // 音の長さを指定

#define PINNO 12   // 圧電スピーカを接続したピン番号

void setup() {
}
void loop() {

     tone(PINNO,784,BEAT) ;  // ファ
     delay(250) ;
     tone(PINNO,698,BEAT) ;  // ファ#
     delay(250) ;
     tone(PINNO,784,BEAT) ;  // ファ#
     delay(250) ;
     
     delay(300) ;           // ３秒後に繰り返す
}
