#include <Adafruit_NeoPixel.h>

#define PIN 6
#define max_bright 0.075
#define fader 0.003

Adafruit_NeoPixel strip = Adafruit_NeoPixel(18, PIN, NEO_GRB + NEO_KHZ800);

bool button = false;
int last = 1;

float bright = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  int sensorVal = digitalRead(2);
  if (last != sensorVal && sensorVal == 1)
  {
    button = !button;
  }

  if(button)
  {
    bright += fader;
    if(bright>max_bright) bright = max_bright;
  } else
  {
    bright -= fader;
    if(bright<0) bright = 0.0;
  }

  for(int i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(255.0 * bright, 140.0 * bright, 0));
  }

  

  last = sensorVal;
  Serial.println(button);
  
  strip.show();
  delay(50);  
}



