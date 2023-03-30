/*
    This example code was authored and/or compiled by the Watson Combat Robotics League for use on the Build-The-Bot Platform.
    This code is open source as per the MIT license found on the WCRL Github Page (https://github.com/wcrl/Build-the-Bot/blob/eadc81d94e1f041c1e13751ea7d3190f495dc393/LICENSE)
    Last Revised: 2022-10-18
*/

#include <Dabble.h>
/*
   This code utilizes the Dabble Library for bluetooth control of the robot.
   However, a modification must be made to the library to allow for hardware serial instead of software serial.
   1. Download the Dabble library via the Arduino IDE
   1. Open the Dabble.cpp file and change "Serial<#>.begin" to "Serial.begin"
   2. In the same .cpp file change "DabbleSerial=&Serial<#>" to "DabbleSerial=&Serial"
   3. NOTE: When Dabble bluetooth connection active code cannot upload to arduino unit
*/

#include <Servo.h>   //Runs the PWM for the ESC
Servo ESC;          // Create servo object to control the ESC

#include <SparkFun_TB6612.h> // Motor Driver Library provided by Sparkfun

//Front Left Wheel is Motor A on the PCB
#define L_Front_Wheel_in1 A5  //A4
#define L_Front_Wheel_in2 A4  //A5
#define L_Front_Wheel_PWM 11  //D11

//Front Right Wheel is Motor B on the PCB
#define R_Front_Wheel_in1 4   //D4
#define R_Front_Wheel_in2 8   //D8
#define R_Front_Wheel_PWM 10  //D10

//Back Left Wheel is Motor C on the PCB
#define L_Back_Wheel_in1   //
#define L_Back_Wheel_in2   //
#define L_Bacl_Wheel_PWM   //

//Back Right Wheel is Motor D on the PCB
#define R_Back_Wheel_in1    //
#define R_Back_Wheel_in2    //
#define R_Back_Wheel_PWM    //

//Blade is Motor _ on the PCB
#define blade_in1   //
#define blade_in2   //
#define blade_PWM   //


const int motor_offset = -1;
#define STBY 2
//Front Wheels
Motor L_Front_Wheel(L_Front_Wheel_in1, L_Front_Wheel_in2, L_Front_Wheel_PWM, motor_offset, STBY);
Motor R_Front_Wheel(R_Front_Wheel_in1, R_Front_Wheel_in2, R_Front_Wheel_PWM, motor_offset, STBY);
//Back Wheels
Motor L_Back_Wheel(L_Back_Wheel_in1, L_Back_Wheel_in2, L_Back_Wheel_PWM, motor_offset, STBY);
Motor R_Back_Wheel(R_Back_Wheel_in1, R_Back_Wheel_in2, R_Back_Wheel_PWM, motor_offset, STBY);
//Weapon
Motor blade(blade_in1, blade_in2, blade_PWM, moto_offset, STBY);

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

//Blade start speed 
int blade_speed = 35;

void setup() {

  Serial.begin(250000);       // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600, 0, 1);   //(Baudrate, rx,tx) Enter baudrate of your bluetooth. Connect bluetooth on Bluetooth port present on evive (in Dabble Library Example).
  ESC.attach(5, 1000, 2000);  // Initializes the ESC  ---- Pin 5 = ESC A; Pin 6 = ESC B 
  ESC.write(0);               // Sets the speed to 0
}

void loop() {
  Dabble.processInput();      //this function is used to refresh data obtained from smartphone. Hence calling this function is mandatory in order to get data properly from your mobile.

  //Motion Control
  if (GamePad.isUpPressed())  //Move forward
  {
    // L_Front_Wheel.drive(255);
    // R_Front_Wheel.drive(-255);
    // L_Back_Wheel.drive(255);
    // R_Back_Wheel.drive(-255)
    L_Front_Wheel.drive(255);
    R_Front_Wheel.drive(255);
    L_Back_Wheel.drive(255);
    R_Back_Wheel.drive(255);
  }
  else if (GamePad.isDownPressed()) //Move backward
  {
    // L_Front_Wheel.drive(-255);
    // R_Front_Wheel.drive(255);
    L_Front_Wheel.drive(-255);
    R_Front_Wheel.drive(-255);
    L_Back_Wheel.drive(-255);
    R_Back_Wheel.drive(-255);
  }
  else if (GamePad.isLeftPressed()) { //Move left
    // L_Front_Wheel.drive(-255);
    // R_Front_Wheel.drive(-255);
    L_Front_Wheel.drive(-255);
    R_Front_Wheel.drive(255);
    L_Back_Wheel.drive(-255);
    R_Back_Wheel.drive(255);

  }
  else if (GamePad.isRightPressed()) { //Move right
    L_Front_Wheel.drive(255);
    R_Front_Wheel.drive(-255);
    L_Back_Wheel.drive(255);
    R_Back_Wheel.drive(-255);
  }
  else {  //Idle
    L_Front_Wheel.drive(0);
    R_Front_Wheel.drive(0);
    L_Back_Wheel.drive(0);
    R_Back_Wheel.drive(0);
  }

  //Competition Attachment (Weapon) Control
  if (GamePad.isTrianglePressed())  //Start up the Competition attachment
  {
    ESC.write(blade_speed); // speed of weapon
    Serial.print("Triangle");
  }


  if (GamePad.isCirclePressed())  //Increase the speed of the competition attachment
  {
    blade_speed = blade_speed + 10;
    ESC.write(blade_speed);
    Serial.print("Circle");
    
    

  }
  if (GamePad.isCrossPressed()) //Shut off the competition attachment
  {
    ESC.write(0);
    Serial.print("Cross");
  }

  if (GamePad.isStartPressed()) //Idle
  {
    Serial.print("Start");
    delay(100);
  }

  delay(100);

}