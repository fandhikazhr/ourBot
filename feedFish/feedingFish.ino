#include "CTBot.h"
#include <Servo.h>

Servo myServo;
CTBot myBot;
String ssid = "YOUR'S WIFI SSID";
String pass = "YOUR'S WIFI PASSWORD";
String token = "YOUR'S BOT TOKEN";
const int id = ; //YOUR'S TELEGRAM ID

void setup(){
  Serial.begin(9600);
  myServo.attach(0); // signal pin on NodeMCU ESP8266 at D3
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
}


void loop(){
  TBMessage msg;
  if(myBot.getNewMessage(msg)){
    Serial.println("Message : + msg.text");
    String message = msg.txt;
    if(message = "Beri Makan"){
      myServo.write(0);
    }
    delay(100); // delay 1 second
    myServo.write(90); // back to first position
    myBot.sendMessage(id, "YOUR FISH HAVE BEEN FED !!!");
    myBot.sendMessage(id, "YUMMY :)");
  }
}
