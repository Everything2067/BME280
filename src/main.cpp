/*
  BME280 by Everything2067.
  Displays a BME280 sensor's readings.
  The sensor interfaces via both I2C and SPI.
  You can change the protocol (I2C and SPI), sensor address (I2C only), sea level pressure, delay, and baud rate.
*/

// I2C Settings
  #define I2C_MODE
  #define SENSOR_ADDRESS 0x76

// SPI Settings
  // #define SPI_MODE
  // #define BME280_CIPO
  // #define BME280_COPI
  // #define BME280_SCK
  // #define BME280_CS

// Defining values, you can set them as per your needs.
  #define DELAY 1000
  #define SEALEVELPRESSURE_HPA 1013.25

// Uncomment and change this to set baud rate.
  // #define BAUD_RATE
  #ifndef BAUD_RATE
    #ifdef ARDUINO_BOARD
      #define BAUD_RATE 9600
    #endif
    #ifdef ESP_BOARD
      #define BAUD_RATE 115200
    #endif
  #endif


// Including required libraries.
  #ifdef I2C_MODE
    #include <Wire.h>
  #endif
  #ifdef SPI_MODE
    #include <SPI_Pins.h>
  #endif
  #include <Adafruit_Sensor.h>
  #include <Adafruit_BME280.h>

#ifdef I2C_MODE
  Adafruit_BME280 BME;
#endif
#ifdef SPI_MODE
  Adafruit_BME280 BME(CS_PIN, COPI_PIN, CIPO_PIN, SCK_PIN);
#endif

void setup() {
    Serial.begin(BAUD_RATE);
    #ifdef I2C_MODE
      BME.begin(SENSOR_ADDRESS);
    #endif
    #ifdef SPI_MODE
      BME.begin();
    #endif
}

void loop() {
  // Temperature
  Serial.print("Temperature: ");
  Serial.print(BME.readTemperature());
  Serial.println(" °C");

  // Pressure
  Serial.print("Pressure: ");
  Serial.print(BME.readPressure() / 100.0F);
  Serial.println(" hPa");

  // Altitude
  Serial.print("Approx. Altitude: ");
  Serial.print(BME.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  // Humidity
  Serial.print("Humidity: ");
  Serial.print(BME.readHumidity());
  Serial.println(" %");

  Serial.println();
  delay(DELAY);
}