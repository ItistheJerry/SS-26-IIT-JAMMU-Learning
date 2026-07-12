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
  val = (255./1023.)*val;
  Serial.println("PWM Potentiometer Reading is: ");
  Serial.println(val);
  
  // Conditional Process:
  if(val >= 0 && val <= 100){
    myServo.write(0);
    delay(serDelay);
  }
  else if(val >= 100 && val <= 200){
    myServo.write(90);
    delay(serDelay);
  }
  else{
    myServo.write(180);
    delay(serDelay);
  }
}
