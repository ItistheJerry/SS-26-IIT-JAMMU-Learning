#include <Servo.h>
#include <stdio.h>

const int servoPin = 5;
int serDelay = 1000;

// Creating Object
Servo myservo;



void setup(){
  Serial.begin(9600);
  myservo.attach(servoPin);
}

void loop(){
  myservo.write(0);
  delay(serDelay);
  
  myservo.write(20);
  delay(serDelay);
  
  myservo.write(40);
  delay(serDelay);
  
  myservo.write(60);
  delay(serDelay);
  
  myservo.write(80);
  delay(serDelay);
  
  myservo.write(100);
  delay(serDelay);
  
  myservo.write(120);
  delay(serDelay); 
  
  myservo.write(140);
  delay(serDelay);
  
  myservo.write(160);
  delay(serDelay);
  
  myservo.write(180);
  delay(serDelay);
  
  myservo.write(0);
  delay(serDelay);
}
