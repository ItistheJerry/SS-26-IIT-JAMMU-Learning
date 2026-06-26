// C++ code
//
int LED[] = {9, 10, 11};
void setup()
{
  for (int i = 0; i < 3; i++){
  pinMode(LED[i], OUTPUT);
  }
}

void loop()
{
  for (int i = 0; i < 3; i++){
    int currentLED = LED[i];
    // FADE IN: increase brightness from 0 to 255
      for (int brightness = 0; brightness <= 255; brightness += 5) {
       analogWrite(currentLED, brightness);
      delay(10);
    }
    // FADE OUT: decrease brightness from 255 to 0
      for (int brightness = 255; brightness >=0; brightness -= 5) {
       analogWrite(currentLED, brightness);
      delay(10);
    }
    // Give a tiny pause before moving to the next LED
      delay(100);
  } 
}