// Includes
#include <Adafruit_NeoPixel.h> // Manage onboard RGB LED
#include <Wire.h> // Data connection for sensor
#include <SensirionI2cSht4x.h> // Functions to read from sensor

// Constants
  // Pins
#define LED_PIN 8
#define PIN_SDA 6
#define PIN_SCL 7

  // LED
#define LED_COUNT 1

// Inits
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
SensirionI2cSht4x sensor;

// Help functions
void setColor(uint8_t r, uint8_t g, uint8_t b) {
    strip.setPixelColor(0, strip.Color(r,g,b));
    strip.show();
}

void setup() {
  // Init onboard LED
  strip.begin();
  strip.setBrightness(50);
  strip.show();

  Serial.begin(115200); // Set baud rate for USB connection
    delay(100);

  // Check if USB-connection to a computer exists
    // blink blue if connection exists, orange if not
  if(Serial) {
    setColor(0,0, 255);
    delay(200);
  } else {
    setColor(255, 150, 0);
    delay(200);
  }

  // Init SH40 sensor
  Wire.begin()
  sensor.begin(Wire, SHT40)
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
