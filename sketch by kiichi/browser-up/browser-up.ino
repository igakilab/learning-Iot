#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

#define AEN 10
#define APHASE 9
#define BEN 6
#define BPHASE 5
#define MODE 2

YunServer server;

void setup() {
Bridge.begin();
Console.begin();

pinMode(BEN, OUTPUT);
pinMode(BPHASE, OUTPUT);
pinMode(AEN, OUTPUT);
pinMode(APHASE, OUTPUT);
pinMode(MODE, OUTPUT);
digitalWrite(MODE, HIGH);

  server.listenOnLocalhost();
  server.begin();

}

void loop() { 

  YunClient client = server.accept();

  if (client) {

    process(client);
    Console.println("accses");

    client.stop();
  }
  delay(20);
}

void process(YunClient client) {

  String command = client.readStringUntil('/');
  Console.println(command);
  if (command == "FORWARD") {
    Console.println("Forward");
    digitalWrite(APHASE, HIGH);
    digitalWrite(BPHASE, HIGH);
    analogWrite(AEN, 40);
    analogWrite(BEN, 40);
  }
  if (command == "BACK") {
    Console.println("Back");
    digitalWrite(BPHASE, LOW);
    analogWrite(BEN, 35);
    digitalWrite(APHASE, LOW);
    analogWrite(AEN, 35);
  }
  if (command == "STOP") {
    Console.println("Stop");
    motor_stop();
  }
  if (command == "LEFT"){
    Console.println("Left");
    digitalWrite(BPHASE, HIGH);
    analogWrite(BEN, 50);
    digitalWrite(APHASE, LOW);
    analogWrite(AEN, 50);
  }
  if (command == "RIGHT"){
    Console.println("Right");
    digitalWrite(APHASE, HIGH);
    analogWrite(AEN, 50);
    digitalWrite(BPHASE, LOW); 
    analogWrite(BEN, 50);
  }
  if (command == "RESULT"){
    client.print("command");
  }
}

void motor_stop(){
  analogWrite(AEN,0);
  analogWrite(APHASE,0);
  analogWrite(BEN,0);
  analogWrite(BPHASE,0);
}
