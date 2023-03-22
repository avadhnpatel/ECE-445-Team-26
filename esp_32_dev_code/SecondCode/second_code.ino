#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
 
#define AWS_IOT_SUBSCRIBE_TOPIC1 "esp32/lamp1"
#define AWS_IOT_SUBSCRIBE_TOPIC2 "esp32/lamp2"
#define AWS_IOT_SUBSCRIBE_TOPIC3 "esp32/lamp3"
#define AWS_IOT_SUBSCRIBE_TOPIC4 "esp32/lamp4"
 
#define lamp1 19
#define lamp2 21
#define lamp3 22
#define lamp4 23
 
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);
 
void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);
 
/*##################### Lamp 1 #####################*/
  if ( strstr(topic, "esp32/lamp1") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay1 = doc["status"];
    int r1 = Relay1.toInt();
    if(r1==1)
    {
      digitalWrite(lamp1, LOW);
      Serial.print("Lamp1 is ON");
    }
    else if(r1==0)
    {
      digitalWrite(lamp1, HIGH);
      Serial.print("Lamp1 is OFF");
    }
  }
 
/*##################### Lamp 2 #####################*/
  if ( strstr(topic, "esp32/lamp2") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay2 = doc["status"];
    int r2 = Relay2.toInt();
    if(r2==1)
    {
      digitalWrite(lamp2, LOW);
      Serial.print("Lamp2 is ON");
    }
    else if(r2==0)
    {
      digitalWrite(lamp2, HIGH);
      Serial.print("Lamp2 is OFF");
    }
  }
 
/*##################### Lamp 3 #####################*/
  if ( strstr(topic, "esp32/lamp3") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay3 = doc["status"];
    int r3 = Relay3.toInt();
    if(r3==1)
    {
      digitalWrite(lamp3, LOW);
      Serial.print("Lamp3 is ON");
    }
    else if(r3==0)
    {
      digitalWrite(lamp3, HIGH);
      Serial.print("Lamp3 is OFF");
    }
  }
 
/*##################### Lamp 4 #####################*/
  if ( strstr(topic, "esp32/lamp4") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay4 = doc["status"];
    int r4 = Relay4.toInt();
    if(r4==1)
    {
      digitalWrite(lamp4, LOW);
      Serial.print("Lamp4 is ON");
    }
    else if(r4==0)
    {
      digitalWrite(lamp4, HIGH);
      Serial.print("Lamp4 is OFF");
    }
  }
  Serial.println();
}
 
 
void setup()
{
  Serial.begin(115200);
  
  pinMode (lamp1, OUTPUT);
  pinMode (lamp2, OUTPUT);
  pinMode (lamp3, OUTPUT);
  pinMode (lamp4, OUTPUT);
 
  digitalWrite(lamp1, HIGH);
  digitalWrite(lamp2, HIGH);
  digitalWrite(lamp3, HIGH);
  digitalWrite(lamp4, HIGH);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println("Connecting to Wi-Fi");
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
 
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC1);
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC2);
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC3);
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC4);
 
  Serial.println("AWS IoT Connected!");
}
 
 
void loop()
{
  client.loop();
  delay(1000);
}