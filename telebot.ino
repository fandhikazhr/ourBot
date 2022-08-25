#include "CTBot.h"
#include <WiFiUdp.h>
#include <NTPClient.h>

CTBot myBot;
CTBotReplyKeyboard myKbd;   // reply keyboard object helper
bool isKeyboardActive;      // store if the reply keyboard is shown

String ssid = ""; // fill with yours ssid
String pass = ""; // fill with yours password of ssid
String token = ""; // filll with yours token bot

// NTP Client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

String weekDays[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
String months[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};

void setup() {
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("Starting TelegramBot...");

  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);

  // set the telegram bot token
  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection FAILED");

  myKbd.addButton("Time");

  myKbd.addButton("Contact request", CTBotKeyboardButtonContact);

  myKbd.addButton("Location request", CTBotKeyboardButtonLocation);

  myKbd.addRow();

  // (it will be used to hide the reply keyboard)
  myKbd.addButton("Hide replyKeyboard");

  myKbd.enableResize();
  isKeyboardActive = false;

  // Initial NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(0);
}

void loop() {
  // a variable to store telegram message data
  TBMessage msg;
  timeClient.update();
  
  // Get Time
  time_t epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  
  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {
    // check what kind of message I received
    if (msg.messageType == CTBotMessageText) {
      // received a text message
      if (msg.text == "/start"){
        myBot.sendMessage(msg.sender.id, "Welcome @" + msg.sender.username);
      }
  }
  
  // wait 500 milliseconds
  delay(500);
}
