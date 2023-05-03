# Neehar Worklog

[[_TOC_]]

# 2-8-2023 - Initial CAD & Soldering Assignment

My group has placed me in charge of designing and soldering the PCB. I am a little worried as I do not have too much experience with PCB design. I paid very close attention in the CAD assignment becoming familiar with KiCad and the shortcuts required. The main important things are to choose the right parts, connect the signals correctly, select the footprints, and finally efficiently place parts and route wires/vias. I am gonna begin soldering the PCB for the mini encabulator today. I have some experience with soldering so I believe I can apply those skills today and on our actual PCB.


# 3-7-2023 - Parts Ordering

We have began ordering parts now and understanding which signals will be required for the parts. We have received an ESP32 development board and will begin breadboarding and slowly integrating the ultrasonic sensors, magnetic contact switch, and servo motor. We have found the link below and hope to utilize this resource as it gives examples using all these parts.

[link](esp32io.com)


# 3-8-2023 - No Development Boards Allowed

I have began planning and designing the schematic for the PCB. I was planning on including female headers to connect all the sensors and female headers to connect the ESP32 development board. However, we just found out we cannot use development boards which will significantly complicate my design of the PCB. The past couple weeks we have been planning on using a development board and this will be a major setback with the first round PCBway orders being today. We will have to figure out another approach by the next round.


# 2021-02-18 - Battery Update

Received the pair of 6s4p batteries, along with battery building supplies such as a Smart BMS, nickel strips, fishpaper, 10 gauge wire, and more. Upon closer inspection, splitting the 6s4p pack into a 12s2p pack is difficult, as there is no leverage to remove the existing H-shaped nickel strips.

The pair of 6s4p packs take up a lot less space than I expected. It would be easier to make a 12s4p pack out of them instead, which will provide us the same power as I required from earlier at nearly 500 Whr. Additionally, I have gotten in contact with a coworker who has a battery spot welder I can use.

Once I have planned out the build and assembled the materials, we should be good to go to complete the battery.

# 2021-02-24 - Investigation acquiring RPM data from VESCs

I have done some investigating of the VESC hardware and software and discovered that you can query them for RPM telemetry data. This removes the need for us to develop RPM sensing
around the motorized wheels.

To accomplish this however, we may need to talk to each VESC individually. Having a dual VESC is convenient, but this may interfere with our ability to query data from them properly. Some dual VESCs have dual MCUs, other more recent designs have single MCUs as shown earlier in this journal.

# 2021-03-01 - Parts update

From further discussions about the issue of communicating to both VESCs individually or to a ‘master’ VESC to both, we have decided to go with a pair of single VESCs. For example, we could attach a CANBUS cable between the pair of VESCs in order to allow them to communicate with each other, or simply split two PPM signals to pass throttle information individually, among various other choices. In other words, the VESCs can work in tandem with one another or can be independent from each other.

I have assembled a significant portion of the board at this point, as seen here in this picture below:

![](parts_update.png)

Some issues:

- The motor pulley is scraping on the motor mount. This is an issue of tolerances, as the
motor mount I am using is 6mm wide and the Motor shaft has a tolerance of 6.2mm +-
0.5mm. In theory, we should have 0.2mm of space, but the margin of error was not in our
favor.
  ![](motor_pulley_scraping.png)
- The threads on the ends of the trucks are not deep enough. We need bearing spacers to
push the wheel out.
  ![](bearing_spacer.png)
  
  
