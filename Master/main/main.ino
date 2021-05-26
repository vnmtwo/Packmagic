#include "ColorConverterLib.h"
#include "hsv.h"
#include "configuration.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

uint8_t packetBuffer[DEVICES*3];

IPAddress remoteIP(255, 255, 255, 255);
WiFiUDP Udp;

void (*loop_function)(void);
void wakeup_do(void);

void select_program(){
  wakeup_init();
  loop_function = wakeup_do;
}

void setup() {
  Serial.begin(115200);
    
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  select_program();
}

unsigned long ts =0;
void loop() {
  if (millis()-ts>30){
    ts = millis();

    loop_function();
    
    Udp.beginPacket(remoteIP,REMOTE_PORT);
    Udp.write(packetBuffer, sizeof(packetBuffer));
    Udp.endPacket();
  }
}
