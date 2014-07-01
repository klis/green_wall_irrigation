#include "DHT.h"

#define SEPARATOR ";"

#define ERROR_CODE_OK "0"
#define ERROR_CODE_DHT_SENSOR "1"

// define pin and sensor type for DHT
#define DHTPIN 7
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// define pin for float switch
byte floatSwitchPin = 6;

void setup() { 
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);
  readTemperatureAndHumidity();
  readFloatSwitchValue();
  
  Serial.println();
}

String readTemperatureAndHumidity() {
  // read humidity
  float humidity = dht.readHumidity();

  // read temperature as Celsius
  float temperature = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    return ERROR_CODE_DHT_SENSOR;
  }
  
  Serial.print(humidity);
  Serial.print(SEPARATOR);
  Serial.print(temperature);
  Serial.print(SEPARATOR);

  return ERROR_CODE_OK;
}

void readFloatSwitchValue() { 
  if(digitalRead(floatSwitchPin) == HIGH) {
    Serial.print("0");
    Serial.print(SEPARATOR);
  } else {
    Serial.print("1");
    Serial.print(SEPARATOR);
  }  
}
