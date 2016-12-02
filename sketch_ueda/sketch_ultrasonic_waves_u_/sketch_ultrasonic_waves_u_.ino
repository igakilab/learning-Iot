#include <Console.h>
#include <Bridge.h>

#define AEN 10
#define APHASE 9
#define BEN 6
#define BPHASE 11
#define MODE 2

int URPWM = 3; // PWM Output 0－25000US，Every 50US represent 1cm
int URTRIG=5; // PWM trigger pin
  
unsigned int Distance=0;
uint8_t EnPwmCmd[4]={0x44,0x02,0xbb,0x01};    // distance measure command
  
void setup()
{  
  Bridge.begin();
  Console.begin();
  // Serial initialization
  Serial.begin(9600);                         // Sets the baud rate to 9600
  pinMode(13, OUTPUT);
  pinMode(BEN, OUTPUT);
  pinMode(BPHASE, OUTPUT);
  pinMode(AEN, OUTPUT);
  pinMode(APHASE, OUTPUT);
  pinMode(MODE, OUTPUT);
  digitalWrite(MODE, HIGH);
  PWM_Mode_Setup();
}
  
void loop()
{
  PWM_Mode();
  //delay(20);
}                      //PWM mode setup function
  
void PWM_Mode_Setup()
{ 
  pinMode(URTRIG,OUTPUT);                     // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG,HIGH);                  // Set to HIGH
   
  pinMode(URPWM, INPUT);                      // Sending Enable PWM mode command
   
  for(int i=0;i<4;i++)
  {
    Serial.write(EnPwmCmd[i]);
  } 
}
  
void PWM_Mode()
{                              // a low pull on pin COMP/TRIG  triggering a sensor reading
    digitalWrite(URTRIG, LOW);
    digitalWrite(URTRIG, HIGH);               // reading Pin PWM will output pulses
      
    unsigned long DistanceMeasured=pulseIn(URPWM,LOW);
    Console.println(DistanceMeasured);     
    while(DistanceMeasured<=1000)
    {              // the reading is invalid.
      digitalWrite(13, HIGH);
      digitalWrite(APHASE, LOW);
      delay(20);
      analogWrite(AEN, 21);
      delay(1000);
      digitalWrite(URTRIG, LOW);
      digitalWrite(URTRIG, HIGH);   
      DistanceMeasured=pulseIn(URPWM,LOW);
    }

      Distance=DistanceMeasured/50;           // every 50us low level stands for 1cm
      Console.print("Distance=");
      Console.print(Distance);
      Serial.println("cm");
      digitalWrite(13, LOW);
      digitalWrite(APHASE, HIGH);
      delay(2000);
      analogWrite(AEN, 21);
      delay(1000);
 
}
