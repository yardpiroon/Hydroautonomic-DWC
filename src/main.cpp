#include <Arduino.h>
#include "hydroautonomic.h"
#include <ArduinoJson.h>
#include <SPI.h>
#include <RBwifi.h>
#include <MQTT.h>
#include "creds.h"

#define ROLE "RED_OAK001"

#define RED_OAK


AutomaticGrowing redOak;
MQTTClient client(512);

void messageReceived(String &topic, String &payload);
void connect_mqtt();
void pubilsh();

void setup() {
  
  connectToWifi(SECRET_SSID, SECRET_PASS);
  IPAddress server(MQTT_IP_0, MQTT_IP_1, MQTT_IP_2, MQTT_IP_3);
  client.begin(server, MQTT_PORT, wifiClient);
  client.onMessage(messageReceived);
  connect_mqtt();

  redOak.setup();
  redOak.bucket_init(2,5,6);
  redOak.plant_init(6);
  
}

void loop() {
  redOak.loop();
}


void messageReceived(String &topic, String &payload)
{
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, payload);

  if (topic == "airpump")
  {
    redOak.air_pump = bool(payload);
  }else if (topic == "water_in")
  {
    redOak.water_pump_in = bool(payload);
    redOak.water_pump_out = false;
  }
  else if (topic == "water_out")
  {
    redOak.water_pump_out = bool(payload);
    redOak.water_pump_in = false;
  }
  
  
}

void connect_mqtt()
{
  reconnectToWifi(SECRET_SSID, SECRET_PASS);

  client.setKeepAlive(1);
  char buffer[40];
  sprintf(buffer, CLIENT_ID_PREFIX "_04%ld", random(10000));

  while (!client.connect(buffer, MQTT_USERNAME, MQTT_PASSWORD))
  {
    delay(1000);
  }
  client.publish("STATUS_TOPIC", "online", true, 1);
  client.loop();

}
