#include <Console.h>
#include <Bridge.h>

const int LED = 13;
const int PIR = 2;
unsigned long start_t = 0;
unsigned long end_t;

void setup() { 
  Bridge.begin();
  Console.begin();
  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);
}
 
void loop() {
  int aa = digitalRead(PIR) ;
  Console.println(aa) ;
  if (digitalRead(PIR) == HIGH) {
    digitalWrite(LED, HIGH);
    start_t = millis();
  } 
  else {
    end_t = millis();
    if(end_t - start_t >= 5000){
      digitalWrite(LED, LOW);
    }
  }
 
  delay(200);
}
