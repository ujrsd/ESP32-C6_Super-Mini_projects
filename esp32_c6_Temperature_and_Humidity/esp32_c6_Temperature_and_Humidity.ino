/*
  Autor: Lemmer C.
  Date: 2025-12-21
  Title: Temperature and Humidity
  Description: 
    
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

byte checkForDevice() {
  Serial.println("Scan for an I2C device ...");
  for(byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if(Wire.endTransmission() == 0) {
      Serial.print("Device found at address: 0x");
      Serial.println(addr, HEX);
      return addr;
    }
  }
  return 255;
}

double calc_temp(uint8_t MSB_temp, uint8_t LSB_temp) {
  // From the datasheet:
  // T = (-45 + 175*(S_T)/(2^16-1))

  uint32_t value = ((uint16_t) MSB_temp << 8) | ((uint16_t) MSB_temp << 0);
  double res = -45 + (175.0 * value)/((1UL << 16)-1); // 2^16 = (1UL << 16)
  res = (int)(res*10)/10.0;

  return res;
}

double calc_humi(uint8_t MSB_humi, uint8_t LSB_humi) {
  // From the datasheet:
  // RH = (-6 + 125*(S_RH)/(2^16-1)) can reach < 0 and > 100

  uint32_t value = ((uint16_t) MSB_humi << 8) | ((uint16_t) LSB_humi << 0);
  double res = -6 + (125.0 * value)/((1UL << 16)-1); // 2^16 = (1UL << 16)
  res = (int)(res*10)/10.0;

  if(res < 0) {
    res = 0;
  }

  if(res > 100) {
    res = 100;
  }

  return res;
}

void printI2CData(const uint8_t* data, size_t length) {
  Serial.print("Raw bytes: ");
  for(int i = 0; i < length; i++) {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

template <typename T>
void printInformation(String name, T value , String physicalUnit) {
  Serial.print(name);
  Serial.print(": ");
  Serial.print(value);
  Serial.print(" ");
  Serial.println(physicalUnit);
}

void setLEDColorByHumidity(double humidity) {
  if(humidity > 80) {
    setColor(255, 0, 0); // Red
  } else if(humidity >= 75) {
    setColor(255, 50, 0); // Red-Orange
  } else if(humidity >= 70) {
    setColor(255, 150, 0); // Orange
  } else if(humidity >= 65) {
    setColor(255, 255, 0); // Yellow
  } else if(humidity >= 60) {
    setColor(144, 238, 0); // Light Green
  } else if(humidity >= 55) {
    setColor(0, 255, 0); // Green
  } else if(humidity >= 50) {
    setColor(0, 205, 50); // Green-Light blue
  } else if(humidity >= 45) {
    setColor(0, 155, 100); // light blue
  }
}

// Pseudo Code !!!
bool CRC_check(uint8_t MSB_byte, uint8_t LSB_byte, uint8_t CRC_checksum) {
  uint8_t byte_init = 0xFF;
  uint8_t padding = 0x00;

  // XOR Init value with MSB byte
  MSB_byte = MSB_byte ^ byte_init;

  // Value to divide
  uint32_t value = ((uint32_t)MSB_byte << 16) | ((uint32_t)LSB_byte << 8) | padding;
  Serial.print("value = 0x");
  Serial.println(value, HEX);
  Serial.print("value (bin) = ");
  Serial.println(value, BIN);

  Serial.print("value to divide = ");
  // Calculation for left over
  for(uint8_t i = 0; i < 16; i++) {
    uint8_t position = 23-i;
    Serial.print((value >> position) & 1);
  }
  Serial.println();

  uint8_t result = 0x00;

  // Check if CRC-result is the same as the given value
  Serial.print("Calculated checksum: 0x");
  Serial.print(result, HEX);
  Serial.print("  vs.  0x");
  Serial.print(CRC_checksum, HEX);
  Serial.println(" obtained Checksum");

  return result == CRC_checksum;
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  Wire.begin(PIN_SDA, PIN_SCL); // Pin8 = SDA, Pin9 = SCL

  // Init Onboard LED
  strip.begin();
  strip.setBrightness(50);
  strip.show();
  setColor(255,255,255); // White

  Serial.println("Setup completed!");
}

void loop() {
  byte SHT40_addr = checkForDevice();

  if(SHT40_addr != 255) {
    Wire.beginTransmission(SHT40_addr);
    Wire.write(0xFD); // High precision measurement
    Wire.endTransmission();
    delay(10);

    uint8_t count = Wire.requestFrom(SHT40_addr, (uint8_t)6);

    if (count == 6) {
      uint8_t data[count] = {0};

      for (int i = 0; i < count; i++) {
        data[i] = Wire.read();
      }

      uint8_t MSB_temp = data[0];
      uint8_t LSB_temp = data[1];
      uint8_t CRC_temp = data[2];
      uint8_t MSB_humi = data[3];
      uint8_t LSB_humi = data[4];
      uint8_t CRC_humi = data[5];

      printI2CData(data, count);

      //CRC_check(MSB_temp, LSB_temp, CRC_temp);
      double temperature = calc_temp(MSB_temp, LSB_temp);
      printInformation("Temperature", temperature, "°C");

      double humidity = calc_humi(MSB_humi, LSB_humi);
      printInformation("Humidity", humidity, "%RH");
      setLEDColorByHumidity(humidity);

    } else {
      Serial.print("I2C read error, bytes received: ");
      Serial.println(count);
    }

    delay(2000);

  } else {
    setColor(255,0,0);
    delay(250);
    setColor(0,0,0);
    delay(250);
  }
}
