/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-door-sensor
 */

#include <Servo.h>
#define DOOR_SENSOR_PIN  19  // ESP32 pin GIOP19 connected to door sensor's pin
#define SERVO_PIN 26 // ESP32 pin GIOP26 connected to servo motor
#define TRIG_PIN 23 // ESP32 pin GIOP23 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 22 // ESP32 pin GIOP22 connected to Ultrasonic Sensor's ECHO pin
Servo servoMotor;
int doorState;
int prevDoorState = 0;
float duration_us, distance_cm;

void setup() {
  Serial.begin(9600);                     // initialize serial
  pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP); // set ESP32 pin to input pull-up mode

  // configure the trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO_PIN, INPUT);
  servoMotor.attach(SERVO_PIN);  // attaches the servo on ESP32 pin
  servoMotor.write(90);
}

void unlockDoor() {
  // rotates from 0 degrees to 180 degrees
  for (int pos = 0; pos <= 90; pos += 1) {
    // in steps of 1 degree
    servoMotor.write(pos);
    delay(15); // waits 15ms to reach the position
  }
}

void lockDoor() {
  // rotates from 0 degrees to 180 degrees
  for (int pos = 90; pos >= 0; pos -= 1) {
    // in steps of 1 degree
    servoMotor.write(pos);
    delay(15); // waits 15ms to reach the position
  }
}

void loop() {
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
              Serial.print("You have Mail!");
              lockDoor();
              delay(3000); // waits 15ms to reach the position
              unlockDoor();
        }
    }
    prevDoorState = 0;
    // Serial.println("The door is closed");
  }
 
}



