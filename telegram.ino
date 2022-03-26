#include "CTBot.h"

CTBot myBot;
String ssid = ""; // your wifi ssid 
String pass = ""; // your wifi password
String token = ""; // fill this with your bot token
const int id = ; // id your telegram account

void setup() {
    Serial.begin(9600);
    myBot.wifiConnect(ssid, pass);
    myBot.setTelegramToken(token);
