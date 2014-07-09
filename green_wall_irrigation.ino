#include "DHT.h"

#define SEPARATOR "|"

#define ERROR_CODE_OK "0"
#define ERROR_CODE_DHT_SENSOR "1"

// define pin and sensor type for DHT
#define DHTPIN 7
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// define pin for float switch
byte floatSwitchPin = 6;

byte led = 13; // used for testing, this will be water pump when it's connected

int receivedDataFromSerial = 0;

void setup() { 
  Serial.begin(9600);
  dht.begin();
  
  pinMode(led, OUTPUT); // used for testing, this will be water pump when it's connected
}

void loop() {
  
  while (Serial.available() > 0) {
    receivedDataFromSerial = Serial.parseInt();
    
    switch (receivedDataFromSerial) {
      case 1:
          readTemperatureAndHumidity();
        break;
      case 2:
          readFloatSwitchValue();
        break;
      case 3:
         // read pump state
        readWaterPumpValue();
        break;
      case 4:
        // open pump
        digitalWrite(led, HIGH);
        break;
      case 5:
        // close pump
        digitalWrite(led, LOW);
        break;
      default: 
        // if nothing else matches, do the default
        // default is optional
        Serial.println("Error!");
    }
    Serial.println();
    delay(1000);
  }
  
  // send data  
  delay(2000);
  readTemperatureAndHumidity();
  readFloatSwitchValue();
  readWaterPumpValue();
  
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
  
  Serial.print(temperature);
  Serial.print(SEPARATOR);
  Serial.print(humidity);
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

void readWaterPumpValue() {
  if(digitalRead(led) == HIGH) {
    Serial.print("1");
    Serial.print(SEPARATOR);
  } else {
    Serial.print("0");
    Serial.print(SEPARATOR);
  }
}
