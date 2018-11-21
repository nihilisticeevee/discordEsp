#include <ESP8266WiFi.h> 
#include "espBotClass.h"

const char* ssid     = "ssid";
const char* password = "wepKey";
espBotClass espBot;

void setup()
{
  //starts serial
  Serial.begin(115200);
  //start display
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
 
  //start wifi connection
  WiFi.begin(ssid, password);
 
  int timeoutcount = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    timeoutcount++;
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

//test function
 espBot.setTokenId("botToken", "channelId");
 espBot.getLastMessage();
 //espBot.post("data", "false", "false", "timeStamp");
}
 
void loop() 
{
 // espBot.equals()
espBot.getLastMessage();
espBot.printLastMsgTime();
delay(30000);
}
