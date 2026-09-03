#include <Arduino.h>
#include <ESP32Servo.h>
#include <my_cpp_functions/blinkLed.h>
 
Servo myservo;  // create servo object to control a servo
Servo myservo2;
// 16 servo objects can be created on the ESP32
 
int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 33;
int servo2Pin = 34;
 
void setup() {
	Serial.begin(115200);
	// Allow allocation of all timers
	//ESP32PWM::allocateTimer(0);
	//ESP32PWM::allocateTimer(1);
	//ESP32PWM::allocateTimer(2);
	//ESP32PWM::allocateTimer(3);
	//myservo.setPeriodHertz(50);    // standard 50 hz servo
	//myservo.attach(servoPin, 1000, 2000); // attaches the servo on pin 33 to the servo object
	//myservo2.setPeriodHertz(50);
	//myservo2.attach(servoPin, 1000, 2000);
	// using default min/max of 1000us and 2000us
	// different servos may require different min/max settings
	// for an accurate 0 to 180 sweep
	blink_led(3, 100, "white");
}
 
void loop() {
 
	//myservo.write(0);
	//myservo2.write(0);
	delay(500);
}