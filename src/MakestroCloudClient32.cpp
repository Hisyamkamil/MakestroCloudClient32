/*
author Hisyam Kamil
23/32018

*/


#include "MakestroCloudClient32.h"

WiFiClient client;
PubSubClient mqtt_client(client);

MakestroCloudClient32::MakestroCloudClient32(){
    mqtt_client.setServer(MAKESTROCLOUD_HOST, MAKESTROCLOUD_PORT);    
}


void MakestroCloudClient32::connect(const char* username, const char* token, const char* project, const char* clientId){
      // Loop until we're reconnected
    while (!mqtt_client.connected()) {
        Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqtt_client.connect(clientId, username, token)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic", "hello world");
      // ... and resubscribe
      //client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void MakestroCloudClient32::publish(String topic, String payload){    
    mqtt_client.publish(topic.c_str(), payload.c_str());
}

void MakestroCloudClient32::publishKeyValue(String topic, const char* key, char Valueval) {
    const int bufferSize = JSON_OBJECT_SIZE(20);
    StaticJsonBuffer<bufferSize> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root[key] = Valueval;

    String jsonString;
    root.printTo(jsonString);
    publishData(topic, jsonString);
    }

void MakestroCloudClient32::publishData(String topic, String payload){
    publish(topic, payload);
    
}