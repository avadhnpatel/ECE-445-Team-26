# Roshun Worklog

[[_TOC_]]

# 2023-02-28 - Begin 3D printing design

Today, we went to the BIF to talk with the Illinois Makerlab about designing and printing our mailbox. The
outer assembly was designed along with dimensions being finalized

# 2023-03-02 - Continue 3D printing design process

Designed the inner panels with the cutouts for the ultrasonic sensors as well as added supports to elevate
the panels.

# 2023-03-07 - Continue 3D printing design process

Completed the door and hinge assembly which took much longer than anticipated. However, this finishes
the mailbox design and will begin printing after spring break as it will take several days to print.


# 2023-03-21 - Unit test all sensors and write barebones auto locking code

Today, Avadh and I breadboarded the ultrasonic sensors, magnetic contact sensors, and servo motor seperately
to an ESP32 devboard and printed their results in the serial monitor to ensure they worked as intended.
Next, we breadboared all required sensors to the devboard and attempted to make the servo motor move
to a desired location depending on the state of the ultasonic sensor and magenetic contact sensor. We
were successful.

# 2023-03-22 - Start AWS IOT Connection

Currently, I am trying to connect our ESP32 devboard to the AWS IOT Core. However, even though the code
and credentials seem to be correct, I am not seeing any data show up on the AWS console.

# 2023-03-23 - Fixed AWS no data issue

I finally figured out that the reason data was not going through to the console from the devboard. 
It seems as though our apartment WIFI network is blocking the MQTT protocol that is used by AWS
to send IOT data. I was able to get around this issue by using a mobile hotspot as the network for the 
ESP32.

# 2023-03-24 - AWS update

I have found another issue with AWS. For no apparent reason, even though I have got data to be sent from
AWS to the ESP 32 and vice versa, it seems as though the messages stop being recieved by AWS after about
5 to 10 seconds. I have not been able to find any reason for this and may begin looking into alternatives.

# 2023-03-25 - Apple Homekit functionality worked

Today I was looking at alternatives to AWS as progress was not being made in a fix to data not sending after
some time. I decided to try and use Apple Homekit to make our mailbox a smart home device as Homekit
still offered the same lock, unlock, and scheudling functionality that we needed. This was a straight
forwared process to code and I was able to control the mailbox from my phone!

# 2023-03-29 - Begin push notifications

I attempted to implement push notifications to my phone whenever the mailbox is locked or unlocked. The service
I am trying to use is Pushover which has an app that I downloaded onto my phone. I added the required code
to our project.


# 2023-03-30 - Issue with notifications

It seems as though even though I see the code is reaching the point to send a notifications as confirmed
by a print statement, no notification is being sent.

# 2023-04-03 - Changing implementation to Arduino IOT Cloud

After talking with my teammates, we decided that their was a better implementation of our application which 
could be done on the Arduino IOT Cloud which has a corresponding mobile app. The main reasoning for this
is that we can now control the mailbox from anywhere, regardless if we are on the same WIFI network as
the mailbox, which was a limitation of Apple Homekit. The good news is that much of the preivously coded
mailbox functionlaity can still be used and we just need to add some things on top of it.

# 2023-04-10 - Assembled and attached door assembly

Today was exciting as we began assembling the 3D printed components. Super glue was used to put them together
and the two covers were sucessfully able to be glued around the door hinges in order to make the door.
After this dried, the door was glued onto the front of the mailbox.

# 2023-04-11 - Placing sensors

In order to ensure mail is seen properly, the ultrasonic sensors needed to be placed precicely under
the cutouts in the false floor. This process was not easy and required a ton of trial and error.
However, I was able to finally duck tape down both ultrasonic sensors down in the right spot. I also
glued on the servo motor and then aligned the metal piece on the door which the lock will slot into.

![](https://github.com/avadhnpatel/ECE-445-Team-26/blob/main/notebooks/Roshun/Screenshot%202023-05-03%20at%205.39.06%20PM.png)

# 2023-04-12 - Put together whole mailbox

After ensuring that the mailbox was functioning as intended, the two halves of the mailbox body were 
glued together. This was left to dry for several hours to be safe.

![](https://github.com/avadhnpatel/ECE-445-Team-26/blob/main/notebooks/Roshun/Screenshot%202023-05-03%20at%205.43.17%20PM.png)

# 2023-04-13 - Routing wires and completing the project.

In order for the mailbox to look clean and properly assembled, the wires needed to be taped down and 
routed underneath the false floor. This process was made a little harder due to a lack of light inside
the mailbox and a lack of space. Once the battery was placed inside the mailbox, we officially completed
the project!






  
