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
