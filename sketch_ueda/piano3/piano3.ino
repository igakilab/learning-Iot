#define BEAT 200   // 音の長さを指定

void setup() {
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
}
void loop() {

     for(int i = 0; i < 10; i++){
     digitalWrite(11,698,HIGH);
     digitalWrite(12,740,HIGH);
     delay(300); 
     }
}
