/*
  This is temperature and humidity displaying project on lcd screen.

  Hardawares used-  
    Temperature and humidity sensor DHT11
    Arduino
    1602 LCD Module 
*/

/*
      CONNECTION
  For lcd 
    1. SCL - A0
    2. SDA - A1
    3. VCC - 5V
    4. GND - GND
  For DHT11 Sensor
    1. DATA - D2
    2. VCC - 5V
    3. GND - GND
    4. Connect a 10K resistor between data and vcc pin of DHT11 sensor.(Mandatory)
*/

#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 column and 2 rows
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  dht.begin();     // initialize the sensor
  lcd.init();      // initialize the lcd
  lcd.backlight(); // open the backlight 
}

void loop()
{
  delay(2000); // wait a few seconds between measurements

  float humi  = dht.readHumidity();    // read humidity
  float tempC = dht.readTemperature(); // read temperature

  lcd.clear();
  // check if any reads failed
  if (isnan(humi) || isnan(tempC)) {
    lcd.setCursor(0, 0);
    lcd.print("Failed");
  } else {
    lcd.setCursor(0, 0);  // start to print at the first row
    lcd.print("Temp: ");
    lcd.print(tempC);     // print the temperature
    lcd.print((char)223); // print ° character
    lcd.print("C");

    lcd.setCursor(0, 1);  // start to print at the second row
    lcd.print("Humi: ");
    lcd.print(humi);      // print the humidity
    lcd.print("%");
  }
}
