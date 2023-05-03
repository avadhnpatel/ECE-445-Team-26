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

# 2023-04-03 - Started Arduino IOT Cloud

I have found an alternative to AWS and Apple Homekit called Arduino IOT Cloud. I have created an account, configured our ESP32 Development Board to the server, and connected it. I have been able to create a button in a dashboard that moves the servo from 0 to 90 degrees and back to 0 degrees. This dashboard is available on the arduino iot cloud webstie and the Arduino IoT Cloud iOS App.

# 2023-04-06 - Continued with Arduino IOT Cloud

We have decided that we are going to do everything through Arduino IOT Cloud. I have added status boxes that show the status of mail, the lock, and the door on the app. There is also a switch that has been added that controls the mailbox locking mechanism. All of these statuses update within a second of any action being made on the mailbox.

# 2023-04-06 - Added Scheduling Arduino IOT Cloud

I have found a scheduler component that can be added to our dashboard. The schedule can be set for a speicifc date and time. It will be set for a duration that is specified by the user. We know when the schedule is active in the code so we will leave the mailbox unlocked while it is active. I have also added a status for the scheduler that will show whether or not the schedule is active.

# 2023-04-08 - IFTTT Notifications

I have configured IFTTT (which is a service that allows push notifications) with the ESP32 Development board and now it sends notifications to any phone that has IFTTT downloaded with my credentials logged in. I send notifications any time the door is open/closed, mail is put in the mailbox, the scheduler turns on/off, or if the mailbox is locked. 

# 2023-04-20 - Added updates based on mail being taken out of mailbox

After getting some feedback from Vishal, I have added a feature to include notifications and status updates any time that mail is taken out of the mailbox. 




