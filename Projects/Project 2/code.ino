#define red 13
#define green 12
#define blue 11

void setup(){
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop(){
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
  delay(1000);
  
  digitalWrite(green, HIGH);
  digitalWrite(blue, LOW);
  digitalWrite(red, LOW);
  delay(1000);
  
  digitalWrite(blue, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  delay(1000);
  
}
