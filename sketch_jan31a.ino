#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>0

#define DHTPIN D2

#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);


float humidityData;
float temperatureData;


const char* ssid = "lenovo k8 note";// ENTER USER NAME
const char* password = "nandu123";// ENTER PASSWORD
//WiFiClient client;
char server[] = "api.thingspeak.com";   //eg: 192.168.0.222 r let it be as it is


WiFiClient client;    


void setup()
{
 Serial.begin(9600);
  delay(10);
  dht.begin();
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
//  server.begin();
  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(1000);
  Serial.println("connecting...");
 }
void loop()
{ 
  humidityData = dht.readHumidity();
  temperatureData = dht.readTemperature(); 
  Sending_To_thingspeak(); 
  delay(3000); // interval
 }

 void Sending_To_thingspeak()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 80)) {
    
    // Make a HTTP request:
    
    client.print("GET /update?api_key=63AI2N88NEKHC4W7&field1=0");     //YOUR URL
    
    Serial.print("humidity:");
    Serial.println(humidityData);
    client.print(humidityData);
    client.print("&field2=");
    Serial.print("temperature:");
    client.print(temperatureData);
    Serial.println(temperatureData);
    client.println(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }
