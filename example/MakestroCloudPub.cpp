#include <MakestroCloudClient32.h>
#include "WiFi.h"

#define use_ESPectro32 1

#if use_ESPectro32
    #include <ESPectro32_Board.h>
#endif

const char* SSID = "Your SSID";
const char* Password = "Your SSID Password";
const char* username = "Your User Name";
const char* token = "Your Token";
const char* project = "Your Project Name";
const char* deviceId = "Your Device ID";
const char* topic = "Your Topic";

MakestroCloudClient32 makestro;

void setup(){
    Serial.begin(115200);
    #if use_ESPectro32
        ESPectro32.begin();
    #endif
    
    // If too long to connect, uncomment line below, then reupload
    // WiFi.disconnect();
    delay(100);
    WiFi.begin(SSID, Password);
   
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    delay(3000);   

    // MQTT Initializing..
    makestro.connect(username, token, project, deviceId);
    delay(1000);
}

void loop(){
    int phototr = ESPectro32.readPhotoTransistorValue();
    Serial.println(phototr);
    makestro.publishKeyValue(topic, "sensor", phototr);
    Serial.println("publish to cloud");
    delay(1000);
}