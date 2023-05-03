# Avadh Worklog

# 2023-03-02 - Parts Updates

We have bought the SERVO MOTOR HS-311 and 3 Ultrasonic Distance Sensors - HC-SR04 from the ECE Supply Center. We also have picked up the two magentic contact sensors we ordered from the ECEB 2072.

# 2023-03-07 - Parts Updates

The ESP32 Development board has been delivered. We have tested it on our breadboard and it is able to print to the serial monitor and turn on the led that is built in.

# 2023-03-21 - Unit Testing

Roshun and I have unit tested our motor/sensors on the breadboard. For the Servo Motor we used the following diagram to connect it to the development board: ![](https://esp32io.com/images/tutorial/esp32-servo-motor-wiring-diagram.jpg)
For the Magnetic Contact Sensor we used the following diagram to connect it to the development board: ![](https://esp32io.com/images/tutorial/esp32-door-sensor-wiring-diagram.jpg)
For the Ultrasonic Sensors we used the following diagram to connect them to the development board: ![](https://esp32io.com/images/tutorial/esp32-ultrasonic-sensor-wiring-diagram.jpg)

We connected all three components together and wrote the logic in order to move the servo (lock the mailbox) if the contact sensors go from being open to closed and the ultrasonic distance is less than 17 cm (there is mail in the mailbox).

Some issues:

- The motor pulley is scraping on the motor mount. This is an issue of tolerances, as the
motor mount I am using is 6mm wide and the Motor shaft has a tolerance of 6.2mm +-
0.5mm. In theory, we should have 0.2mm of space, but the margin of error was not in our
favor.

- The threads on the ends of the trucks are not deep enough. We need bearing spacers to
push the wheel out.

  
  
