/*
author Hisyam Kamil
23/32018

*/


#include "MakestroCloudClient32.h"

WiFiClient client;
// PubSubClient mqtt_client(client);

MakestroCloudClient32::MakestroCloudClient32(){
    PubSubPtr_ = new PubSubClient(client);
    PubSubPtr_->setServer(MAKESTROCLOUD_HOST, MAKESTROCLOUD_PORT);
}

void MakestroCloudClient32::connect(const char* username, const char* token, const char* project, const char* clientId){
    // Loop until we're reconnected
    while(!PubSubPtr_->connected()){
        if (PubSubPtr_->connect(clientId, username, token)) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(PubSubPtr_->state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
    
}

bool MakestroCloudClient32::connected(){
    return PubSubPtr_->connected();
}

void MakestroCloudClient32::publish(String topic, String payload){
    PubSubPtr_->publish(topic.c_str(), payload.c_str());
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

void MakestroCloudClient32::subscribe(String topic){
    if(PubSubPtr_->subscribe(topic.c_str(), 0)){
        Serial.print("Success subscribe to topic: ");
        Serial.println(topic);
    } else {
        Serial.print("Failed subscribe to topic: ");
        Serial.println(topic);
    }
}

void MakestroCloudClient32::loop(){
    PubSubPtr_->loop();
}

PubSubClient* MakestroCloudClient32::data(){
    return PubSubPtr_;
}


