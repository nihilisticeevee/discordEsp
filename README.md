# discordEsp
esp8266 based discordbot 

Very beta!

just add your wifi ssid, and wep key to:
const char* ssid     = "ssid";
const char* password = "wepKey";

and add your bot token and channel id to:
espBot.setTokenId("botToken", "channelId");

As of now it can only get the latest message and post a message.
