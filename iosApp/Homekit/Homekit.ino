/*
 * switch.ino
 *
 *  Created on: 2020-05-15
 *      Author: Mixiaoxiao (Wang Bin)
 *
 * HAP section 8.38 Switch
 * An accessory contains a switch.
 *
 * This example shows how to:
 * 1. define a switch accessory and its characteristics (in my_accessory.c).
 * 2. get the switch-event sent from iOS Home APP.
 * 3. report the switch value to HomeKit.
 *
 * You should:
 * 1. read and use the Example01_TemperatureSensor with detailed comments
 *    to know the basic concept and usage of this library before other examples。
 * 2. erase the full flash or call homekit_storage_reset() in setup()
 *    to remove the previous HomeKit pairing storage and
 *    enable the pairing with the new accessory of this new HomeKit example.
 */

#include <Arduino.h>
// #include <HTTPClient.h>
// #include <ESP_Mail_Client.h>
#include <arduino_homekit_server.h>
#include "twilio.hpp"
#include "wifi_info.h"
#include <Servo.h>
#define DOOR_SENSOR_PIN  19  // ESP32 pin GIOP19 connected to door sensor's pin
#define SERVO_PIN 26 // ESP32 pin GIOP26 connected to servo motor
#define TRIG_PIN 23 // ESP32 pin GIOP23 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 22 // ESP32 pin GIOP22 connected to Ultrasonic Sensor's ECHO pin
// #define SMTP_server "smtp.gmail.com"
// #define SMTP_Port 465
// #define sender_email "upcomingsportsgames@gmail.com"
// #define sender_password "msisnbmofbyuboce"
// #define Recipient_email "9085009632@txt.att.net"
// SMTPSession smtp;

// Values from Twilio (find them on the dashboard)
static const char *account_sid = "AC79f5c4e075b511c9db23ae9ea3881384";
static const char *auth_token = "58f117518b242f6d85f929c1d9ccfc0a";
// Phone number should start with "+<countrycode>"
static const char *from_number = "+18449941245";

// You choose!
// Phone number should start with "+<countrycode>"
static const char *to_number = "+13312296253";
static const char *setup_message = "Setup Message from ESP32";
static const char *door_open_message = "Your mailbox has been opened";
static const char *door_closed_message = "Your mailbox has been closed";
static const char *mail_message = "You have mail!";


Twilio *twilio;
Servo servoMotor;
int doorState;
int prevDoorState = 0;
float duration_us, distance_cm;
// HTTPClient http;


// access your HomeKit characteristics defined in my_accessory.c
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_switch_on;

#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

void unlockDoor() {
  // rotates from 0 degrees to 180 degrees
  for (int pos = 10; pos <= 90; pos += 1) {
    // in steps of 1 degree
    servoMotor.write(pos);
    delay(15); // waits 15ms to reach the position
  }
}

void lockDoor() {
  // rotates from 0 degrees to 180 degrees
  for (int pos = 90; pos >= 10; pos -= 1) {
    // in steps of 1 degree
    servoMotor.write(pos);
    delay(15); // waits 15ms to reach the position
  }
}
void setup() {
	Serial.begin(115200);
  pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP); // set ESP32 pin to input pull-up mode

  // configure the trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO_PIN, INPUT);
  servoMotor.attach(SERVO_PIN);  // attaches the servo on ESP32 pin
  servoMotor.write(90);
  // Blynk.begin(auth, ssid, password);
	wifi_connect(); // in wifi_info.h
  twilio = new Twilio(account_sid, auth_token);
  delay(1000);
  String response;
  bool success = twilio->send_message(to_number, from_number, setup_message, response);
  if (success) {
    Serial.println("Setup!");
  } else {
    Serial.println(response);
  }
  // smtp.debug(1);  
  // ESP_Mail_Session session;
  // session.server.host_name = SMTP_server ;
  // session.server.port = SMTP_Port;
  // session.login.email = sender_email;
  // session.login.password = sender_password;
  // session.login.user_domain = "";

  // SMTP_Message message;

  // message.sender.name = "ESP32";
  // message.sender.email = sender_email;
  // message.subject = "ESP32 Testing Email";
  // message.addRecipient("Microcontrollerslab",Recipient_email);

    
  // String textMsg = "Hello Microcontrollerslab! This is a simple text sent from ESP board";
  // message.text.content = textMsg.c_str();
  // message.text.charSet = "us-ascii";
  // message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;	//homekit_storage_reset(); // to remove the previous HomeKit pairing storage when you first run this new HomeKit example

  // if (!smtp.connect(&session))
  //   return;


  // if (!MailClient.sendMail(&smtp, &message))
  //   Serial.println("Error sending Email, " + smtp.errorReason());
  
	my_homekit_setup();

}


void loop() {  

  doorState = digitalRead(DOOR_SENSOR_PIN); // read state

  if (doorState == HIGH) {
    if (prevDoorState == 0){
      String responseDoorOpen;
      bool successDoorOpened = twilio->send_message(to_number, from_number, door_open_message, responseDoorOpen);
      if (successDoorOpened) {
        Serial.println("Setup!");
      } else {
        Serial.println(responseDoorOpen);
      }
    }
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
              Serial.print("You have Mail!");
              lockDoor();
              bool on = true;
              cha_switch_on.value.bool_value = on;
              homekit_characteristic_notify(&cha_switch_on, cha_switch_on.value);
              
              delay(3000); // waits 15ms to reach the position
              String responseMail;
              bool successDoorClosed = twilio->send_message(to_number, from_number, mail_message, responseMail);
              if (successDoorClosed) {
                Serial.println("Setup!");
              } else {
                Serial.println(responseMail);
              }
        }
        String responseDoorClosed;
        bool successDoorClosed = twilio->send_message(to_number, from_number, door_closed_message, responseDoorClosed);
        if (successDoorClosed) {
          Serial.println("Setup!");
        } else {
          Serial.println(responseDoorClosed);
        }
    }
    prevDoorState = 0;
    // Serial.println("The door is closed");
  }


  // static uint32_t last_toggle_millis = 0;
  // const uint32_t t = millis();

  // if (t - last_toggle_millis > 5000) {  // toggle every 5 seconds
  //   last_toggle_millis = t;

  //   // toggle the switch state
  //   bool on = !cha_switch_on.value.bool_value;
  //   cha_switch_on.value.bool_value = on;
  //   homekit_characteristic_notify(&cha_switch_on, cha_switch_on.value);

  //   LOG_D("Switch: %s", on ? "ON" : "OFF");

	my_homekit_loop();
  // http.end();
	delay(10);
}

//==============================
// HomeKit setup and loop
//==============================


static uint32_t next_heap_millis = 0;



#define PIN_SWITCH 2

//Called when the switch value is changed by iOS Home APP
void cha_switch_on_setter(const homekit_value_t value) {
	bool on = value.bool_value;
  cha_switch_on.value.bool_value = on;	//sync the 
  if (!on){
    unlockDoor();
    // prevDoorState = 0;

  } else {
    lockDoor();
    
  }
  LOG_D("Switch: %s", on ? "ON" : "OFF");
  digitalWrite(PIN_SWITCH, on ? LOW : HIGH);

  
}

void my_homekit_setup() {
	pinMode(PIN_SWITCH, OUTPUT);
	digitalWrite(PIN_SWITCH, HIGH);

	//Add the .setter function to get the switch-event sent from iOS Home APP.
	//The .setter should be added before arduino_homekit_setup.
	//HomeKit sever uses the .setter_ex internally, see homekit_accessories_init function.
	//Maybe this is a legacy design issue in the original esp-homekit library,
	//and I have no reason to modify this "feature".
	cha_switch_on.setter = cha_switch_on_setter;
	arduino_homekit_setup(&config);

	//report the switch value to HomeKit if it is changed (e.g. by a physical button)
	//bool switch_is_on = true/false;
	//cha_switch_on.value.bool_value = switch_is_on;
	//homekit_characteristic_notify(&cha_switch_on, cha_switch_on.value);
}

void my_homekit_loop() {
	arduino_homekit_loop();
	const uint32_t t = millis();
	if (t > next_heap_millis) {
		// show heap info every 5 seconds
		next_heap_millis = t + 5 * 1000;
		// LOG_D("Free heap: %d, HomeKit clients: %d",
		// 		ESP.getFreeHeap(), arduino_homekit_connected_clients_count());

	}
}
