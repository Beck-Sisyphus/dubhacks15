// Dubhacks 2015, Beck Pang and Wenlu Cheng
// Smart Frisbee, test 1
// On board ESP8266, with MPU6050 sensor

#include <ESP8266WiFi.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

const char* ssid = "Beck's iPhone";
const char* password = "robomasters";

// Set the GPIO5, as an interrupt pin for G_INT at MPU 6050
const int PIN_INT = 5;

// Create an instance of the server
// default IP as 172.20.10.3
WiFiServer server(80);

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;

		// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
		// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
		// not so easy to parse, and slow(er) over UART.
		#define OUTPUT_READABLE_ACCELGYRO

		// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
		// binary, one right after the other. This is very fast (as fast as possible
		// without compression or data loss), and easy to parse, but impossible to read
		// for a human.
		//#define OUTPUT_BINARY_ACCELGYRO

void setup() {
	pinMode(PIN_INT, INPUT);
	attachInterrupt(digitalPinToInterrupt(PIN_INT), readIMUValue, CHANGE);
    // join I2C bus 
    Wire.begin();
    Serial.begin(115200);
    delay(10);

    WiFi.begin(ssid, password);
  
	while (WiFi.status() != WL_CONNECTED) {
	    delay(500);
	    // Serial.print(".");
	}
	// Serial.println("");
	// Serial.println("WiFi connected");
  
	// Start the server
	server.begin();
	Serial.println(WiFi.localIP());

	// initialize device
	accelgyro.initialize();

    // use the code below to change accel/gyro offset values
    // -76	-2359	1688	0	0	0
    accelgyro.setXGyroOffset(220);
    accelgyro.setYGyroOffset(76);
    accelgyro.setZGyroOffset(-85);
}

void loop() {

	// Check if a client has connected
	WiFiClient client = server.available();
	if (!client) {
		return;
	}
  
	// Wait until the client sends some data
	Serial.println("new client");
	while(!client.available()){
		delay(1);
	}
  
	// Read the first line of the request
	String req = client.readStringUntil('\r');
	Serial.println(req);
	client.flush();
  
	// Match the request
	int val;
	// Prepare the response
	String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\ndx dy dz gx gy gz\r\n";

	if (req.indexOf("/gpio/0") != -1)
		val = 0;
	else if (req.indexOf("/gpio/1") != -1)
		val = 1;
	else if (req.indexOf("/api/read") != -1) {
		s += ax;
		s += " ";
		s += ay;
		s += " ";
		s += az;
		s += " ";
		s += gx;
		s += " ";
		s += gy;
		s += " ";
		s += gz;
	} else {
		Serial.println("invalid request");
		client.stop();
		return;
	}

	// Set GPIO2 according to the request
	digitalWrite(2, val);
  
	client.flush();

	s += "</html>\n";

	// Send the response to the client
	client.print(s);
	delay(1);
}

void readIMUValue() {
	// read raw accel/gyro measurements from device
	accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
}
