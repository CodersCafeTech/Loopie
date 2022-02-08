#include <Adafruit_NeoPixel.h>

// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
#define PIN 4
#define NUM_PIX 22
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIX, PIN, NEO_GRB + NEO_KHZ800);
unsigned int i;
void setup() 
{ 
  strip.begin();
  strip.show(); 
  Serial.begin(9600);
}

void loop() 
{
  for(i=0;i<5;i++)
  {
    rgbFade(0, 0, 255, 5); 
    rgbFade(0, 0, 255, 5); 
    rgbFade(0, 255, 0, 5); 
    rgbFade(0, 255, 0, 5); 
    rgbFade(255, 0, 0, 5); 
    rgbFade(255, 0, 0, 5); 
    
  }
  for(i=0;i<5;i++)
  {
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
    colorWipe(strip.Color(0, 255, 0), 50); // Green
    colorWipe(strip.Color(255, 0, 0), 50); // Red*/
  }
  for(i=0;i<5;i++)
  {
    rainbow(20);
  }
  for(i=0;i<5;i++){
    rainbowCycle(20);
  }
}

void rgbFade(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) 
{
  strip.setBrightness(255);
  for(uint8_t b=0; b<255; b++) 
  {
     for(uint8_t i=0; i<strip.numPixels(); i++) 
     {
        strip.setPixelColor(i, red * b/255, green * b/255, blue * b/255);
     }
     strip.show();
     delay(wait);
  }
delay(500);

  for(uint8_t b=255; b > 0; b--) 
  {
     for(uint8_t i = 0; i < strip.numPixels(); i++) 
     {
        strip.setPixelColor(i, red * b/255, green * b/255, blue * b/255);
     }
     strip.show();
     delay(wait);
  }
   strip.setBrightness(0);
   strip.show();
  delay(200);
}

// //заполнение ленты пиксель за пикселем
void colorWipe(uint32_t c, uint8_t wait) 
{
  strip.setBrightness(255);
  for(uint16_t i=0; i<strip.numPixels(); i++) 
  {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

//радуга
void rainbow(uint8_t wait) 
{
  uint16_t i, j;
  
strip.setBrightness(255);
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) 
{
  uint16_t i, j;

strip.setBrightness(255);
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) 
{
strip.setBrightness(255);
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) 
{
  strip.setBrightness(255);
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
