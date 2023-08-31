/*******************************************************************
    A telegram bot for your ESP8266 that responds
    with whatever message you send it.

    Parts:
    D1 Mini ESP8266 * - http://s.click.aliexpress.com/e/uzFUnIe
    (or any ESP8266 board)

      = Affilate

    If you find what I do useful and would like to support me,
    please consider becoming a sponsor on Github
    https://github.com/sponsors/witnessmenow/


    Written by Brian Lough
    YouTube: https://www.youtube.com/brianlough
    Tindie: https://www.tindie.com/stores/brianlough/
    Twitter: https://twitter.com/witnessmenow
 *******************************************************************/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Servo.h>
#include <UniversalTelegramBot.h>
// Wifi network station credentials
#define WIFI_SSID "Nitikan UH6"
#define WIFI_PASSWORD "imamsuharyati462"
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "5646319472:AAFGmtTomNJXMLWz0O2yS1GrWt389clVZKs"

const unsigned long BOT_MTBS = 1000; // mean time between scan messages
Servo myServo;
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

void handleNewMessages(int numNewMessages)
{
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if (text == "/beri_makan")
    {
      bot.sendChatAction(chat_id, "typing");
      delay(4000);
      bot.sendMessage(chat_id, "Sedang Memberi Makan Ikan");
      myServo.write(0);
      delay(2500);
      myServo.write(90);
      bot.sendMessage(chat_id, "Ikan Sudah Diberi Makan !!!"); 
    }

    if (text == "/start")
    {
      String welcome = "Silahkan Beri Makan Ikan, " + from_name + ".\n";
      welcome += "/beri_makan : untuk menyalakan alat pemberi makan ikan\n";
      bot.sendMessage(chat_id, welcome);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  myServo.attach(0); // signal of servo to D3 PIN
  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}

void loop()
{
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}
