#include <Servo.h>

int val;
int pote = A0;

const int servePin = 3;
int serDelay = 1000;

// Object creation:
Servo myServo;

void setup()
{
  Serial.begin(9600);
  myServo.attach(servePin);
  
  pinMode(pote, INPUT);
}

void loop()
{
  val = analogRead(pote);
  Serial.println("Direct Potentiometer reading is: ");
  Serial.println(val);
  
  // PWM Conversion
  val = (180./1023.)*val;
  Serial.println("PWM Potentiometer Reading is: ");
  Serial.println(val);
  
  myServo.write(val);
  delay(1000);
}
