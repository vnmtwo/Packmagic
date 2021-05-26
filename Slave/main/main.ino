#define DEVICE_ID 0
#define PIN 2
#define NUMPIXELS 25
#define STASSID "vnmhome"
#define STAPSK  "vnm159wifi"

void ICACHE_RAM_ATTR espShow(uint8_t pin, uint8_t *pixels, uint32_t numBytes, boolean is800KHz);

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

unsigned int localPort = 8888;
#define UDP_PACKET_SIZE 60
uint8_t packetBuffer[UDP_PACKET_SIZE];
WiFiUDP Udp;

//GRB
uint8_t black[3] = {0,0,0};
uint8_t blue[3] = {0,0,128};

void led_begin(void) {
  if(PIN >= 0) {
    pinMode(PIN, OUTPUT);
    digitalWrite(PIN, LOW);
  }
}
void setup() {
  led_begin();
  espShow(PIN, &(black[0]),NUMPIXELS*3, true);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    espShow(PIN, &(blue[0]),NUMPIXELS*3, true);
    delay(500);
    espShow(PIN, &(black[0]),NUMPIXELS*3, true);
  }

  Udp.begin(localPort);
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize==UDP_PACKET_SIZE) {
    Udp.read(packetBuffer, UDP_PACKET_SIZE);
    espShow(PIN, &(packetBuffer[DEVICE_ID*3]),NUMPIXELS*3, true);
  }
}
