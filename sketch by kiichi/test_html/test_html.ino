#include <Bridge.h>
#include <Console.h>
#include <YunServer.h>
#include <YunClient.h>
#include <FileIO.h>

#define MSG_LEN 4

#define AEN 10
#define APHASE 9
#define BEN 6
#define BPHASE 5
#define MODE 2

YunServer server;

void setup() {
  Bridge.begin();
  Console.begin();
  FileSystem.begin();
  //while( !Console );
  //Console.println("PROGRAM START");
  
  server.listenOnLocalhost();
  server.begin();

  
}

String messages[MSG_LEN] = {"いつやるの", "いまでしょ", "こんにちは", "上田です"};
int cnt = 0;     //カウンター
int wait = 250;  //スキップする回数
int pos = 0;     //messagesの位置

void loop() {

  YunClient client = server.accept();

  if (client) {

    process(client);
    Console.println("accses");

    client.stop();
  }

  if( cnt % wait == 0 ){
    File myfile = FileSystem.open("/mnt/sd/arduino/www/news.txt", FILE_WRITE);
    myfile.println(messages[pos]);
    Console.print("FILE UPDATED: ");
    Console.println(messages[pos]);
    pos = (pos + 1) % MSG_LEN;
    cnt = 0;
  }

  cnt++;
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
