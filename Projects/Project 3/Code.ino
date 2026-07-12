// We read potentiometer Reading
// if pot = 0 - 50 | RED
// if pot = 50 - 100 | BLUE
// if pot = 100 - 150 | GREEN
// if pot = 150 - 200 | MAGENTA
// if pot = 200 - 250 | YELLOW
// if pot = 250+      | CYAN

#define red 13
#define green 11
#define blue 12
int val;
int pote = A0;

void setup(){
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  
  pinMode(pote, INPUT);
}

void loop(){
  val = analogRead(pote);
  Serial.println("Potentiometer Reading is: ");
  Serial.println(val);
  
  // Convert to PWM Values
  val = (255./1023.)*val;
  Serial.println("PWM Reading is: ");
  Serial.println(val);
  
  // Condition for printing;
  if(val >= 0 && val <= 50)
  {
  	digitalWrite(red, HIGH);
  	digitalWrite(green, LOW);
  	digitalWrite(blue, LOW);
    delay(1000);
  }
  else if(val >= 50 && val <= 100)
  {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
    delay(1000);
  }
  else if(val >= 100 && val <= 150)
  {
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, HIGH);
    delay(1000);
  }
  else if(val >= 150 && val <= 200)
  {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, HIGH);
    delay(1000);
  }
  else if(val >= 200 && val <= 250)
  {
    digitalWrite(red,HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
    delay(1000);
  }
  else
  {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(blue, HIGH);
    delay(1000);
  }
}

    
    
    
    
    
    
    
    
    
    
    
    
    
  
