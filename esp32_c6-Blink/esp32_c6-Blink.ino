/*
  Autor: Lemmer C.
  Date: 2025-12-24
  Title: Temperature and Humidity
  Description: Simple Blink code to get introduced with the ESP32-C6 device.
    Introduction to use a library, create a function and write into the console.
    Use of delay() so that changes don't happen instantly.
*/

#include <Adafruit_NeoPixel.h>

#define LED_PIN 8
#define LED_COUNT 1

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setColor(uint8_t r, uint8_t g, uint8_t b) {
  strip.setPixelColor(0, strip.Color(r,g,b));
  strip.show();
  delay(500);
}

void setup() {
  Serial.println("Starting setup ...");

  strip.begin();
  strip.setBrightness(50);
  strip.show();

  Serial.println("... setup done!");
}

void loop() {
  Serial.println("Start loop: ");

  setColor(255, 0, 0); // Red
  setColor(255, 50, 0); // Red-Orange
  setColor(255, 150, 0); // Orange
  setColor(255, 255, 0); // Yellow
  setColor(144, 238, 0); // Light Green
  setColor(0, 255, 0); // Green

  setColor(0, 0, 0); // Off
  delay(3000);
}