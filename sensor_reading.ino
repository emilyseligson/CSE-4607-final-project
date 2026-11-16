#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Define I2C pins for ESP32-C3
#define I2C_SDA 8
#define I2C_SCL 9

// Sea level pressure in hPa for altitude calculation
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; 

void setup() {
  Serial.begin(115200);
  // Wait briefly for USB CDC serial connection on ESP32-C3
  delay(1000); 
  Serial.println("\n--- BME280 Sensor Test ---");

  // Initialize I2C with explicit ESP32-C3 pins
  Wire.begin(I2C_SDA, I2C_SCL);

  // Initialize BME280
  // Note: Most generic breakout boards use 0x76; official Adafruit boards use 0x77.
  if (!bme.begin(0x76, &Wire)) {
    Serial.println("Could not find a valid BME280 sensor at 0x76, trying 0x77...");
    if (!bme.begin(0x77, &Wire)) {
      Serial.println("Could not find a valid BME280 sensor! Check wiring.");
      while (1) delay(10);
    }
  }

  Serial.println("BME280 successfully initialized!\n");
}

void loop() {
  // Read and print Temperature
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  // Read and print Pressure (converted from Pascals to hPa)
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  // Read and print Approximate Altitude
  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  // Read and print Humidity
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println("--------------------------");
  delay(2000); // Wait 2 seconds between readings
}