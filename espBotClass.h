#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

WiFiClientSecure client;


class espBotClass
{
  public:
  void setTokenId(String token, String id);
  void getHeaders();
  void getLastMessage();
  void post(String content, String tts, bool embed, String timeStamp);
  void printLastMsgTime();
  bool equals(String time1, String time2);

  private:
  const char* host = "discordapp.com";
  const int httpsPort = 443; //ssl port
  String botToken;
  String channelId;
  String temp;

  String lastMsg = "not set!";
  String lastTimeStamp = "not set!";
  String msg = "not set!";
  String timeStamp = "not set!";
};
void espBotClass::setTokenId(String token, String id)
{
  botToken = token;
  channelId = id;
}
void espBotClass::getHeaders()
{
      while (client.connected()) 
      {
        String line = client.readStringUntil('\n');
        if (line == "\r")   
          {
          //Serial.println("headers received");
          break;
           }
      }
}

void espBotClass::getLastMessage()
{
    // Use WiFiClientSecure class to create TLS connection
    client.setNoDelay(1);
    if (!client.connect(host, httpsPort)) 
    {
      Serial.println("connection failed");
      return;
    }
    
    // Send get request to client
    client.println("GET /api/channels/" + channelId + "/messages HTTP/1.1");
    client.println("Host: " + String(host));
    client.println("Authorization: Bot " + botToken);
    client.println("User-Agent: DiscordBot (https://github.com/nihilisticeevee/esp8266-discordbot, v0.1)");
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.println();

    getHeaders();

     // if there are incoming bytes available
    // from the server, read them and print them:
  for (int x = 0; x <= 20; x++)
    {
      String line = client.readStringUntil(',');  // read data till ','
      if (line.substring(2, 9) == "content")
      {
        lastMsg = msg;
        temp = line.substring(13, (line.length()-1));
        msg = temp;
      }  
      if (line.substring(2, 11) == "timestamp")
      {
        lastTimeStamp = timeStamp;
        temp = line.substring(15, (line.length()-1));
        timeStamp = temp;
      } 

    }
  client.stop();   
}

void espBotClass::post(String content, String tts, bool embed, String timeStamp)
{
  if (!client.connect(host, httpsPort)) 
    {
      Serial.println("connection failed");
      return;
    }

  if (WiFi.status() == WL_CONNECTED) 
  {
    // Send get request to client
    String postData = "{\r\n  \"content\": " + String("\"") + content + String("\"") +",\r\n  \"tts\": " + String("\"") + tts + String("\"")  + "\r\n}";
    client.println("POST /api/channels/" + channelId + "/messages HTTP/1.1");
    client.println("Host: " + String(host));
    client.println("Authorization: Bot " + botToken);
    client.println("User-Agent: DiscordBot (https://github.com/nihilisticeevee/esp8266-discordbot, v0.1)");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.print(postData.length());
    client.println("\r\n"); 
    client.println(postData);  
    //print to serial
    //Serial.println("------------------------------------------------------");
    //Serial.println("POST /api/channels/" + channelId + "/messages HTTP/1.1");
    //Serial.println("Host: " + String(host));
    //Serial.println("Authorization: Bot " + botToken);
    //Serial.println("User-Agent: DiscordBot (https://github.com/nihilisticeevee/esp8266-discordbot, v0.1)");
    //Serial.println("Content-Type: application/json");
    //Serial.print("Content-Length: ");
    //Serial.print(postData.length());   
    //Serial.println("\r\n"); 
    //Serial.println(postData);  
  }
  else
  {
    Serial.println("not connected to server");
  }

client.stop();   
}

bool espBotClass::equals(String time1, String time2)
{
  if (time1 == time2) return true;
  else return false;
}
void espBotClass::printLastMsgTime()
{
  Serial.print("lastMsg: ");
  Serial.println(lastMsg);
  Serial.print("Last time: ");
  Serial.println(lastTimeStamp);

  Serial.print("Msg: ");
  Serial.println(msg);
  Serial.print("time: ");
  Serial.println(timeStamp);
  Serial.print("Is equal? ");
  Serial.println(equals(lastTimeStamp, timeStamp));



}

