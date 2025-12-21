/*
  Autor: Lemmer C.
  Date: 2025-12-21
  Title: Detect I2C Device
  Description: 
    Check for a single I2C-device connected to the ESP32-C6 µC.
    In this case, use of PIN 6 and 7 for SDA and SCL. For this µC,
    PIN 8 is not available because of the built in LED on the device.

    This LED will blink every ~2.5s to inform the user that the script
    is running.

    In the serial monitor, it will show on which addresse it found an I2C
    device. If non is found, it will display this and restart the loop.
*/

#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define LED_PIN 8 // Reserved for built in LED, DO NOT USE AS GPIO!
#define PIN_SDA 6
#define PIN_SCL 7

#define LED_COUNT 1

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setColor(uint8_t r, uint8_t g, uint8_t b) {
    strip.setPixelColor(0, strip.Color(r,g,b));
    strip.show();
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  Wire.begin(PIN_SDA, PIN_SCL); // Pin8 = SDA, Pin9 = SCL

  Serial.println("I2C scan...");

  // Init Onboard LED
  strip.begin();
  strip.setBrightness(50);
  strip.show();
}

void loop() {
  setColor(255,255,255); // White
  bool found_device = false;
  
  for(byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if(Wire.endTransmission() == 0) {
      Serial.print("Device found at address: 0x");
      Serial.println(addr, HEX);
      found_device = true;
      break;
    }
  }

  if(!found_device) {
    Serial.print("No device found!");
  }

  delay(2500);

  setColor(0,0,0); // LED-OFF

  delay(2500);
}
