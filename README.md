# dubhacks15
Dubhacks 2015 fall at University of Washington

## Inspiration
To replay a complete ultimate frisbee game at phone, and provide info for coach to analyze.

## What it does
Take accelerometer and gyroscope data and visualize it in processing with a 3D image. Send the trajectory of a single throw to a web App.

## How I built it
Powering an accelerometer and gyroscope unit MPU6050 to sense the frisbee's curve, record the raw data in an Arduino Uno through I2C bus. Both boards are powered by an LiPo battery in 3.3V. The Arduino then process the raw data, transform the raw six-axis data into quaternion, and then transform it into Euler angles for Processing IDE to display. We planned to transmit the data through serial bus to an wifi module called ESP8266, and send out the data as an web client to a Microsoft Azure IoT Hub. Then we planned to build an iOS web app to demo, but we didn't finish to that part.

## Challenges I ran into
Couldn't build a server-client relationship from ESP8266 to Azure; Originally planned to remove the Arduino Uno and solely use the ESP8266 as a micro-controller, however we can not make the interrupt triggered successfully from the IMU sensor to the ESP8266 board; Hard to finish processing code in a wireless communication; Hard to plot the data in python; Noisy signal coming from IMU sensor, and hard to build a good filter for it; Hard to program ESP8266 with FTDI cable.

## Accomplishments that I'm proud of
Successfully program and connect ESP8266 in a server-client module. Successfully run the processing program and Arduino program concurrently. Successfully visualize the movement of the frisbee on a 3D module as shown in the thumbnail image. Fully understand the structure and schematics of ESP8266. Have further experience on internet of things development, especially on the server transmission side.

## What I learned
Interrupts in micro-controller and IMU sensor. The algorithm to transform six-axis value to a Euler angle. The basic way to setup a server to receive and transmit.

## What's next for SmartFrisbee
Solely use ESP8266 to record data. Focus on the use case of the project and have a clear spec about the constraints on transmission speed, power, storage on board and charging. Build up a server to storage the data transmitted. Analyze the data for useful information. Build a clean user interface for the frisbee trajectory on a web app.
