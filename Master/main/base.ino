#include "hsv.h"
#include "configuration.h"

HSV_t base_color = {BASE_COLOR_H, BASE_COLOR_S, BASE_COLOR_V};

void base_init(){
  for (int i=0; i< DEVICES; i++){
    ColorConverter::HsvToRgb(base_color.h, base_color.s, base_color.v, packetBuffer[i*3+1], packetBuffer[i*3], packetBuffer[i*3+2]);
  }
}

void base_do(){
  for (int i=0; i< DEVICES; i++){
    ColorConverter::HsvToRgb(base_color.h, base_color.s, base_color.v, packetBuffer[i*3+1], packetBuffer[i*3], packetBuffer[i*3+2]);
  }
}
