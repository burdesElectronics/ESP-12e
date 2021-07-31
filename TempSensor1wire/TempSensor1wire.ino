#include <OneWire.h>
#include <DallasTemperature.h>

// temperature sensor connected to GPIO 16
#define ONE_WIRE_BUS 16

// Setup a oneWire instance-
OneWire oneWire(ONE_WIRE_BUS);


DallasTemperature TempSensor(&oneWire);

void setup(void)
{
  //serial communication
  Serial.begin(9600);
  // Initialize
  TempSensor.begin();
}

void loop(void){ 
  // Initialize DS18B20 sensor manufactured by Dallas semiconductor Corp
  TempSensor.requestTemperatures(); 
  
  Serial.print("Deg C: ");
  // First IC on the wire is 0
  Serial.print(TempSensor.getTempCByIndex(0)); 
  delay(500); //500 milli sec
}
