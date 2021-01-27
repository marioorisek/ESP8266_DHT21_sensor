#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <SPI.h>
#include "DHT.h"

#include "cfg.h"
#include "wifi_cfg.h"

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C
DHT dht(DHT_SENSOR_PIN, DHT_TYPE);

float temperature = 0.0;
float humidity = 0;

void drawScreen(byte screenId) {
      u8g2.clearBuffer(); // clear the internal memory
      u8g2.setFont(FONT_LARGE);

  switch (screenId) {
    case 0:  // splash screen
      Serial.println("Splash screen displayed.");
      u8g2.setCursor(0,26);
      u8g2.print("Hello");
      break;

    case 1: // temperature
      Serial.println("Temperature screen displayed.");
      u8g2.setCursor(0,26);
      u8g2.print(temperature, 1);
      u8g2.print(" C");
      break;

    case 2: // humidity
      Serial.println("Humidity screen displayed.");
      u8g2.setCursor(0,26);
      u8g2.print(humidity, 0);
      u8g2.print(" %");
      break;
  }
  u8g2.sendBuffer();
  delay(SCREEN_DELAY);

}

void measure() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temperature,1);
  Serial.print(" deg. C | Humidity: ");
  Serial.print(humidity, 0);
  Serial.println(" %");

}

void setup() {
  Serial.begin(115200);
  u8g2.begin();
  dht.begin();
  delay(1000);

  Serial.println();
  Serial.println("Sensor init..");

  drawScreen(0);
  }

void loop() {
  measure();
  drawScreen(1);
  drawScreen(2);

}
