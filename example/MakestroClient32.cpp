#include <MakestroCloudClient32.h>
#include "WiFi.h"

const char* username = "your username";
const char* key = "your token";
const char* project = "your project";
const char* clientId = "your device id";


void setup(){
    MakestroCloudClient32(username, key, project, clientId);
}

void loop(){
    publishKeyValue("sensor", "123456" );
}