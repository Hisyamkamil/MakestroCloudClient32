#include <MakestroCloudClient32.h>
#include "WiFi.h"

#define use_ESPectro32 1

#if use_ESPectro32
    #include <ESPectro32_Board.h>
#endif

const int ledPin = 15;

const char* SSID = "Your SSID";
const char* Password = "Your SSID Password";
const char* username = "Your User Name";
const char* token = "Your Token";
const char* project = "Your Project Name";
const char* deviceId = "Your Device ID";
const char* subsTopic = "Your Topic";

MakestroCloudClient32 makestro;

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.println("Message arrived");
    char msg = (char)payload[9];
    
    if (msg == '1') {
        digitalWrite(ledPin, LOW);
    } else {
        digitalWrite(ledPin, HIGH);
    }
}

void setup(){
    Serial.begin(115200);
    #if use_ESPectro32
        ESPectro32.begin();
    #endif

    // If too long to connect, uncomment line below, then reupload
    // WiFi.disconnect();
    delay(100);
    pinMode(ledPin, OUTPUT);
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

    // MQTT initializing..
    makestro.connect(username, token, project, deviceId);
    makestro.subscribe(subsTopic);
    makestro.data()->setCallback(callback);
    delay(1000);
}

void loop(){
    
    if(!makestro.connected()){
        makestro.connect(username, token, project, deviceId);
        makestro.subscribe(subsTopic);
    }
    makestro.loop();
}
