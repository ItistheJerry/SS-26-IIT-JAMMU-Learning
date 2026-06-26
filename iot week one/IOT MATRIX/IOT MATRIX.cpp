// C++ code
//
int rowPins[4] = {2, 3, 4, 5};
int colPins[4] = {6, 7, 8, 9};
// designing the letter 'A' ()

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}