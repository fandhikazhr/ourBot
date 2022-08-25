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
      if (msg.text.equalsIgnoreCase("show keyboard")) {
        // the user is asking to show the reply keyboard --> show it
        myBot.sendMessage(msg.sender.id, "Reply Keyboard enable. You can know what time, your contact, your location or hide the keyboard", myKbd);
        isKeyboardActive = true;
      }
      // check if the reply keyboard is active 
      else if (isKeyboardActive) {
        // is active -> manage the text messages sent by pressing the reply keyboard buttons
        if (msg.text.equalsIgnoreCase("Hide replyKeyboard")) {
          // sent the "hide keyboard" message --> hide the reply keyboard
          myBot.removeReplyKeyboard(msg.sender.id, "Reply keyboard removed");
          isKeyboardActive = false;
        } else {
          String whattime = timeClient.getFormattedTime();
          int day = ptm->tm_mday;
          String weekDay = weekDays[timeClient.getDay()];
          int currentMonth = ptm->tm_mon+1;
          String month = months[currentMonth-1];
          int currentYear = ptm->tm_year+1900;
          // print every others messages received
          myBot.sendMessage(msg.sender.id, "Time : " + whattime + "\nDate : " + weekDay + ", " + day + "/" + month + "/" + currentYear);
        }
      }
  }
  
  // wait 500 milliseconds
  delay(500);
}
