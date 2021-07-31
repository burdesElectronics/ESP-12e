String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
 
String html_1 = R"=====(
<!DOCTYPE html>
<html>
 <head>
  <meta name='viewport' content='width=device-width, initial-scale=1.0'/>
  <meta charset='utf-8'>
  <style>
    body {font-size:100%;} 
    #main {display: table; margin: auto;  padding: 0 10px 0 10px; } 
    h2 {text-align:center; } 
    p { text-align:center; }
  </style>
  <script>
   function refresh(refTime) 
   {
      setTimeout("location.reload(true);", refTime);
   } 
   window.onload = refresh(5000);
  </script>
  <title>Temperature Monitoring Unit</title>
 </head>
 
 <body>
   <div id='main'>
     <h2>Temperature Monitoring Unit</h2>
     <div id='Deg C'> 
       <p>Deg C = %degree%</p>
     </div>
   </div> 
 </body>
</html>
)====="; 
 
#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// temperature sensor connected to GPIO 4
#define ONE_WIRE_BUS 4

// Setup a oneWire instance-
OneWire oneWire(ONE_WIRE_BUS);


DallasTemperature TempSensor(&oneWire);
// change these values to match your network
char ssid[] = "ssid_name";       //  your network SSID (name)
char pass[] = "said_key";          //  your network password
 
WiFiServer server(80);
 
String tmpString = "";
unsigned int degree = 0; 
 
void setup() 
{
    Serial.begin(9600);
    TempSensor.begin();
    // Connect WiFi network
    Serial.print(F("Connecting to "));  Serial.println(ssid);
    WiFi.begin(ssid, pass);
 
    while (WiFi.status() != WL_CONNECTED) 
    {
        Serial.print(".");
        delay(500);
    }
 
    Serial.println("");
    Serial.println(F("[CONNECTED]"));
    Serial.print("[IP ");              
    Serial.print(WiFi.localIP()); 
    Serial.println("]");
 
    // start a server
    server.begin();
    Serial.println("Server Initiated");
 
}
 
 
void loop() 
{
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)  {  return;  }
     // Initialize DS18B20 sensor manufactured by Dallas semiconductor Corp
    TempSensor.requestTemperatures(); 
    degree = TempSensor.getTempCByIndex(0); 
 
    tmpString = html_1;
    tmpString.replace("%degree%", String(degree) );
 
    client.flush();
    client.print( header );
    client.print( tmpString );   
 
    Serial.print("Deg C = "); Serial.println(degree); 
    delay(5);
}
