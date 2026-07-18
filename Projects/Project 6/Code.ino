// LED's
#define rled 13
#define gled 12

// Moisture Delay
#define mPin A0
int val;
int mdelay = 1000;

void setup(){
  Serial.begin(9600);
  Serial.println("The Moisture Sensor is Initializing......");
  delay(10000);
  Serial.println(".................||...............");
  delay(10000);
  
  // LED's
  pinMode(rled, OUTPUT);
  pinMode(gled, OUTPUT);
  
  // Moisture
  pinMode(mPin, INPUT);
  
}

void loop(){
  val = analogRead(mPin);
  Serial.println("Analog Sensor Value is: ");
  Serial.println(val);
  delay(1000);
  
  val = (100./1023.)*val;
  Serial.println("Moisture Percent is: ");
  Serial.println(val);
  delay(1000);
  
}
