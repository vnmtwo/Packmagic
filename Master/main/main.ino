#include "ColorConverterLib.h"
#include "hsv.h"
#include "utils.h"
#include "configuration.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

uint8_t packetBuffer[DEVICES*3];

IPAddress remoteIP(255, 255, 255, 255);
WiFiUDP Udp;

uint8_t current_program = 0;
bool program_changed = false;
fptr loop_function;

void select_program(){
  switch(current_program){
    case 0:
      loop_function = base_init();
      break;
    case 1:
      loop_function = wakeup_init();
      break;
    case 2:
      loop_function = wakeup_nap_init();
      break;
  }

}

ICACHE_RAM_ATTR void handleInterrupt() {
  current_program+=1;
  current_program = current_program%3;
  program_changed = true;
}

void setup_buttons(){
  pinMode(BUTTON_PROGRAM00_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PROGRAM00_PIN), handleInterrupt, RISING);
}
void setup() {
  Serial.begin(115200);
  setup_buttons();   
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
    if (program_changed){
      Serial.print("program changed "); Serial.println(current_program, DEC);
      select_program();
      program_changed = false;
    }
    loop_function();
    
    Udp.beginPacket(remoteIP,REMOTE_PORT);
    Udp.write(packetBuffer, sizeof(packetBuffer));
    Udp.endPacket();
  }
}
