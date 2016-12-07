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
  server.listenOnLocalhost();
  server.begin();

}

void loop() { 

  YunClient client = server.accept();

  if (client) {

    process(client);
    client.println("accses");

    client.stop();
  }
  delay(20);
}

void process(YunClient client) {

  String command = client.readStringUntil('/');
  client.println(command);
  if(command == "FORWARD") {
    client.println("Forward");
    client.println("<html>");
    client.println("<head>");
    client.println("<title>train information</title>");
    client.println("</head>");
    client.println("<body>");
    client.println("<font size=\"25\">");
    client.println("<div align=\"center\">"); 
    client.println("電車の発着情報<br>");
    client.println("<br><br>");
    client.println("</div>");
    client.println("</body>");
    client.println("<html>");
  }
  if (command == "BACK") {
    client.println("Back");
  }
  if (command == "STOP") {
    client.println("Stop");
  }
  if (command == "LEFT"){
    client.println("Left");
  }
  if (command == "RIGHT"){
    client.println("Right");
  }
  if (command == "RESULT"){
    client.println("command");
  }
}
