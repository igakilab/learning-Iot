#include <Console.h>
#include <FileIO.h>

void setup() {
  // put your setup code here, to run once:
  Bridge.begin();
  Console.begin();
  while(!Console);
  
  Console.println("program start");
   
}

int cnt = 0;

void loop() {
  if( cnt == 0 ){
    testFileWrite();
    cnt++;
  }else{
    testFileRead();
  }
  delay(1000);

  Console.println();
}

void testFileWrite(){
  Console.println("WRITING");
  if( !FileSystem.begin() ){
    Console.println("ERR begin failed");
  }else{
    Console.println("begin success");
  }
  File f = FileSystem.open("/mnt/sd/ryokun.txt", FILE_WRITE);

  if( f ){
    Console.println("sd opened");
    f.println("imadeshow!!!w");
    f.close();
  }else{
    Console.println("ERR open failed");
  }
}


void testFileRead(){
  Console.println("READING");
  File f = FileSystem.open("/mnt/sd/ryokun.txt", FILE_READw);

  if( f ){
    Console.println("sd opened");
    Console.write(f.read());
    f.close();
  }else{
    Console.println("ERR open failed");
  }
}

