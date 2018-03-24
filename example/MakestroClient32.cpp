#include <MakestroCloudClient32.h>
#include "WiFi.h"

#define use_ESPectro32 1

#if use_ESPectro32
    #include <ESPectro32_board.h>
#endif

const char* SSID = "Your SSID";
const char* Password = "Your SSID Password";
const char* username = "Your User Name";
const char* token = "Your Token";
const char* project = "Your Project Name";
const char* clientId = "Your Device ID";
const char* topic = "Your Topic";
//WiFiClient client;

MakestroCloudClient32 makestro;

void setup(){
    Serial.begin(115200);
    #if use_ESPectro32
        ESPectro32.begin();
    #endif
    
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
    makestro.connect(username, token, project, clientId);
    delay(1000);
        
}

void loop(){
    int phototr = ESPectro32.readPhotoTransistorValue();
    Serial.println(phototr);
    makestro.publishKeyValue(topic, "sensor", phototr);
    Serial.println("publish to cloud");
    delay(1000);
}
