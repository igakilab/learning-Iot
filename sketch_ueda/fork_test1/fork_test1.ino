#include <Console.h>
#include <Bridge.h>

#define AEN 10
#define APHASE 9
#define BEN 6
#define BPHASE 11
#define MODE 2

int URPWM = 3; // PWM Output 0－25000US，Every 50US represent 1cm
int URTRIG=5; // PWM trigger pin
uint8_t EnPwmCmd[4]={0x44,0x02,0xbb,0x01};    // distance measure command

void setup() {
  Bridge.begin();
  Console.begin();
  Serial.begin(9600); 

  pinMode(13, OUTPUT);
  
  pinMode(BEN, OUTPUT);
  pinMode(BPHASE, OUTPUT);
  pinMode(AEN, OUTPUT);
  pinMode(APHASE, OUTPUT);
  pinMode(MODE, OUTPUT);
  digitalWrite(MODE, HIGH);
  PWM_Mode_Setup();
}

void loop() {
    PWM_Mode();
    delay(20);
    
    digitalWrite(APHASE, HIGH);
    delay(2000);
    analogWrite(AEN, 20);
    delay(100000);
    analogWrite(AEN, 0);
    delay(5000);
    digitalWrite(APHASE, LOW);
    delay(2000);
    analogWrite(AEN, 21);
    delay(100000);
    analogWrite(AEN, 0);
    delay(5000);
}


void PWM_Mode_Setup() {
   
  pinMode(URTRIG,OUTPUT);                     // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG,HIGH);                  // Set to HIGH
   
  pinMode(URPWM, INPUT);                      // Sending Enable PWM mode command
   
  for(int i=0;i<4;i++)
  {
      Serial.write(EnPwmCmd[i]);
  } 
}

void PWM_Mode() {                              // a low pull on pin COMP/TRIG  triggering a sensor reading
  
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);               // reading Pin PWM will output pulses
  
  unsigned long DistanceMeasured=pulseIn(URPWM,LOW);
  digitalWrite(13, HIGH);
  Console.println(DistanceMeasured);
  if(DistanceMeasured > 0){
    digitalWrite(13, LOW);
  }
}
