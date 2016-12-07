#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

YunServer server;

void setup() {
  Bridge.begin();
  Console.begin();
  server.listenOnLocalhost();
  server.begin();
}

void loop() { 

  YunClient client = server.accept();

  if (client) {
    process(client);
    delay(200);
    client.stop();
  }
  delay(20);
}

void process(YunClient client) {

  client.println("Information");
  client.println("");
  client.println("");
  client.print("Train                ");
  client.println("Stop");
  client.println("");
  client.print("Traffic light        ");
  client.println("Stop");
  client.println("");
  client.print("Railroad crossing    ");
  client.println("close");
  client.println("");
}
