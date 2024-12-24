//AIO_KEY and Wi-Fi password is hidden in this code

int val=0;

#include "DHT.h"
#define DHTPIN 8     
#define DHTTYPE DHT11   // DHT 11


DHT dht(DHTPIN, DHTTYPE);




#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "Redmi Note 13 5G"
#define WLAN_PASS       "*********"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "ray_dipta"
//#define AIO_KEY         "********************************"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiClientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

Adafruit_MQTT_Publish loc = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/location");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {

Serial.begin(115200);

  Serial.println(F("DHTxx test!"));
  dht.begin();

 
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());


  MQTT_connect();

  
  

}

//uint32_t x=0;

void loop() {

  MQTT_connect();

      val = analogRead(A0);
    Serial.print("Value from MQ-2 sensor is "); 
    Serial.println(val); 


      float t = dht.readTemperature();

  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;  }


  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));



    if(t>35.0 ||val>70)
  {
      Serial.print(F("\n Publishing location because something is wrong"));
  
  Serial.print("...");
  if (!loc.publish("Beleghata")) {
    Serial.println(F("Location data is published"));
  } else {
    Serial.println(F("Location data is not published"));
  }
  }



     
  
delay(5000);

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */

}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() 
{
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
