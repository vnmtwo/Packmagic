#define DEVICE_ID 4
#define PIN 5 //D1
#define NUMPIXELS 25
#define STASSID "packmagic"
#define STAPSK  "volnavolna"

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>

unsigned int localPort = 8888;
#define UDP_PACKET_SIZE 60
uint8_t packetBuffer[UDP_PACKET_SIZE];
WiFiUDP Udp;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint8_t black[3] = {0,0,0};
uint8_t blue[3] = {0,0,128};

void showColor(uint8_t *pColor){
  for (int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i, *(pColor), *(pColor+1), *(pColor+2));
  }
  pixels.show();
}
void setup() {
  pixels.begin();
  pixels.clear();
  pixels.show();
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    showColor(&blue[0]);
    delay(500);
    showColor(&black[0]);
    delay(500);
  }
  
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  
  Udp.begin(localPort);
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize==UDP_PACKET_SIZE) {
    Udp.read(packetBuffer, UDP_PACKET_SIZE);
    showColor(&(packetBuffer[DEVICE_ID*3]));
  }
}
