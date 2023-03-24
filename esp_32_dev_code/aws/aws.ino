#include "secrets.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <Servo.h>

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"
#define DOOR_SENSOR_PIN  19  // ESP32 pin GIOP19 connected to door sensor's pin
#define TRIG_PIN 23 // ESP32 pin GIOP23 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 22 // ESP32 pin GIOP22 connected to Ultrasonic Sensor's ECHO pin
#define SERVO_PIN 26 // ESP32 pin GIOP26 connected to servo motor
Servo servoMotor;
int doorState;
int prevDoorState = 0;
float duration_us, distance_cm;

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  // Create a message handler
  client.onMessage(messageHandler);

  Serial.print("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

void publishMessage()
{
  StaticJsonDocument<200> doc;
  doorState = digitalRead(DOOR_SENSOR_PIN); // read state

  if (doorState == HIGH) {
    prevDoorState = 1;
    // Serial.println("The door is open");
  } else {
    if (prevDoorState == 1) {
         // generate 10-microsecond pulse to TRIG pin
        digitalWrite(TRIG_PIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG_PIN, LOW);

        // measure duration of pulse from ECHO pin
        duration_us = pulseIn(ECHO_PIN, HIGH);

        // calculate the distance
        distance_cm = 0.017 * duration_us;

        // print the value to Serial Monitor
        Serial.print("distance: ");
        Serial.print(distance_cm);
        Serial.println(" cm");
        if (distance_cm < 15) {
              doc["time"] = millis();
              doc["data"] = "You have mail!";
              char jsonBuffer[512];
              serializeJson(doc, jsonBuffer); // print to client

              client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
              lockDoor();
              delay(3000); // waits 15ms to reach the position
              unlockDoor();
        }
    }
    prevDoorState = 0;
    // Serial.println("The door is closed");
  }
  // print the value to Serial Monitor
  // Serial.print("distance: ");
  // Serial.print(distance_cm);
  // Serial.println(" cm");
  // doc["time"] = millis();
  // doc["data"] = "You have mail!";
  // char jsonBuffer[512];
  // serializeJson(doc, jsonBuffer); // print to client

  // client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}
void lockDoor() {
  // rotates from 0 degrees to 180 degrees
  for (int pos = 90; pos >= 0; pos -= 1) {
    // in steps of 1 degree
    servoMotor.write(pos);
    delay(15); // waits 15ms to reach the position
  }
}

void unlockDoor() {
  // rotates from 0 degrees to 180 degrees
  for (int pos = 0; pos <= 90; pos += 1) {
    // in steps of 1 degree
    servoMotor.write(pos);
    delay(15); // waits 15ms to reach the position
  }
}

void messageHandler(String &topic, String &payload) {
  // Serial.println("incoming: " + topic + " - " + payload);
  // Serial.print("incoming: ");
  // Serial.println(topic);

  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  // Serial.print(message);
  if (topic == "esp32/sub") 
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    // Serial.print(payload);
    String Relay1 = doc["message"];
    int r1 = Relay1.toInt();
    servoMotor.write(r1);
    Serial.print("Motor at ");
    Serial.print(r1);
    Serial.print(" Degrees");

  }
}


void setup() {
  Serial.begin(9600);
  pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP); // set ESP32 pin to input pull-up mode
  pinMode(TRIG_PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO_PIN, INPUT);
  servoMotor.attach(SERVO_PIN);  // attaches the servo on ESP32 pin
  connectAWS();
}

void loop() {
  publishMessage();
  client.loop();
  delay(1000);
}