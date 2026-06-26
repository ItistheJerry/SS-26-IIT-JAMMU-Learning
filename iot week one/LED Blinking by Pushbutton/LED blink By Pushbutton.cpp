// C++ code
//

const int LED_1= 10;
const int LED_2= 11;
const int LED_3= 12;
  
void setup()
{
  pinMode(LED_1, OUTPUT);
}

void loop()
{
  digitalWrite(LED_1, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_1, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_2, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_2, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_3, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_3, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}