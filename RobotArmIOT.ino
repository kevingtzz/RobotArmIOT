//Name: getThingWorx
//Author: David Velasquez, Juan Gonzalo Quiroz, Daniel Lopez, Kevin Gutierrez
//Date: 13/11/2017
//Description: This program gets Thingworx Server variables using REST GET request through ThingworxWiFi101 library

#include <Servo.h>

//Potentiometer pin declaration.
int spinP = 0;  
int arm1P = 1;
int arm2P = 2;
int arm3P = 3;
int gripP = 5;
 
//Potentiometer var declaration.
int spinV;  
int arm1V;
int arm2V;
int arm3V;
int gripV;

//Servo objects.
Servo spin, arm1, arm2, arm3, grip; 

void setup() {


  spin.attach(5);   //D0
  arm1.attach(4);   //D1
  arm2.attach(3);  //D2
  arm3.attach(2);   //D3
  grip.attach(1);   //D4

  spinV = analogRead(spinP);
  delay(1);
  arm1V = analogRead(arm1P);
  delay(1);
  arm2V = analogRead(arm2P);
  delay(1);
  arm3V = analogRead(arm3P);
  delay(1);
  gripV = analogRead(gripP);
  delay(1);

  grip.write(25);

  Serial.begin(2400);
}

void loop() {

  
      spinV = analogRead(spinP);
      delay(1);
      spinV = map(spinV,0,1023,0,180);
      spin.write(spinV);
      //Serial.println("spin: " + spinV);
     
      arm1V = analogRead(arm1P);
      delay(1);
      arm1V = map(arm1V,0,1023,0,180);
      arm1.write(arm1V);
      //Serial.println("arm1: " + arm1V);

      arm2V = analogRead(arm2P);
      delay(1);
      arm2V = map(arm2V,0,1023,0,180);
      arm2.write(arm2V);
      //Serial.println("arm2: " + arm2V);

      arm3V = analogRead(arm3P);
      delay(1);
      arm3V = map(arm3V,0,1023,0,180);
      arm3.write(arm3V);
      //Serial.println("arm3: " + arm3V);

      gripV = analogRead(gripP);
      delay(1);
      gripV = map(gripV,0,1023,0,180);
      grip.write(gripV);
      Serial.println(gripV);
}
