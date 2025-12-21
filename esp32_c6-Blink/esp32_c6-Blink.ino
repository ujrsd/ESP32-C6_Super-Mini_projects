#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define LED_PIN 8
#define LED_COUNT 1

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setColor(uint8_t r, uint8_t g, uint8_t b) {
    strip.setPixelColor(0, strip.Color(r,g,b));
    strip.show();
    delay(500);
}

void setup() {
  Serial.begin(115200);
  Wire.begin(8,9); // Pin8 = SDA, Pin9 = SCL
  Serial.println("I2C scan...");


  strip.begin();
  strip.setBrightness(50);
  strip.show();
}

void loop() {
  setColor(255, 0, 0); // Red
  setColor(255, 50, 0); // Red-Orange
  setColor(255, 150, 0); // Orange
  setColor(255, 255, 0); // Yellow
  setColor(144, 238, 0); // Light Green
  setColor(0, 255, 0); // Green

  setColor(0, 0, 0); // Off
  delay(3000);
}
