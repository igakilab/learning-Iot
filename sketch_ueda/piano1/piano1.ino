#define BEAT 200   // 音の長さを指定

#define PINNO 12   // 圧電スピーカを接続したピン番号

void setup() {
}
void loop() {

     //tone(PINNO,698,BEAT) ;  // ファ
     //delay(BEAT) ;
     tone(PINNO,698,BEAT) ;  // ファ
     delay(500) ;
     //tone(PINNO,740,BEAT) ;  // ファ#
     //delay(200) ;
     
     //delay(500) ;           // ３秒後に繰り返す
}
