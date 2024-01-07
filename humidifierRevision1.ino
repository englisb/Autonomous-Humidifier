#include <Wire.h>         //enables i2c with gpio pins
#include "DHT.h"          //humidity temerature sensor
#include <Adafruit_GFX.h> //OLED library
#include <Adafruit_SSD1306.h>
#include <SPI.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C
#define DHTPIN 2  
#define DHTTYPE DHT11

#define HUMID_MAX 60
#define HUMID_MIN 30
#define humidifier 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  display.begin();
  display.clearDisplay();
  Serial.begin(9600);
  dht.begin();
  digitalWrite(humidifier, LOW);
  pinMode(humidifier, OUTPUT);
}

void loop() {
  display.setCursor(0, 0);
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.setTextWrap(true);

  float h = dht.readHumidity();

  if (isnan(h)) {
    display.println(F("Unable to read humidity!"));
    Serial.print(F("Unable to read humidity!"));
  }
  
  else {
    display.println(F("Current humidity:"));
    Serial.print(F("Current humidity: "));
    Serial.println(h);
    display.print(h);

    if (digitalRead(humidifier) == LOW) {
      if (h < HUMID_MAX) {
        digitalWrite(humidifier, HIGH);
      }
    }
    else {
      if (h >= HUMID_MAX) {
        digitalWrite(humidifier, LOW);
      }
    }
  }
  
  display.display();
  delay(2000);
}
