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

  // reply keyboard customization
  // add a button that send a message with "Simple button" text
  myKbd.addButton("Time");
  // add another button that send the user contact
  myKbd.addButton("Contact request", CTBotKeyboardButtonContact);
  // add another button that send the user position (location)
  myKbd.addButton("Location request", CTBotKeyboardButtonLocation);
  // add a new empty button row
  myKbd.addRow();
  // add a button that send a message with "Hide replyKeyboard" text
  // (it will be used to hide the reply keyboard)
  myKbd.addButton("Hide replyKeyboard");
  // resize the keyboard to fit only the needed space
  myKbd.enableResize();
  isKeyboardActive = false;

  // Initial NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(0);
}
