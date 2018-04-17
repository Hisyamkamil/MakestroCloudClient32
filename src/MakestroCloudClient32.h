#include <PubSubClient.h>
#include "WiFi.h"
#include <ArduinoJson.h>
#include <Arduino.h>

#define MAKESTROCLOUD_HOST "cloud.makestro.com"
#define MAKESTROCLOUD_PORT 1883

//String topic;

class MakestroCloudClient32  {
public :
    MakestroCloudClient32();
    void connect(const char* username, const char* token, const char* project, const char* clientId);
    bool connected();
    void publish(String topic, String payload);
    void subscribe(String topic);
    void publishKeyValue(String topic, const char* key, char Valueval);
    void publishData(String topic, String payload);
    void loop();
    PubSubClient* data();

private:
    PubSubClient* PubSubPtr_ = nullptr;

};
