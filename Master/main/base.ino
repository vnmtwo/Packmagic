#include "hsv.h"
#include "configuration.h"
#include "utils.h"

HSV_t base_color = {BASE_COLOR_H, BASE_COLOR_S, BASE_COLOR_V};

fptr base_init(){
  for (int i=0; i< DEVICES; i++){
    ColorConverter::HsvToRgb(base_color.h, base_color.s, base_color.v, packetBuffer[i*3+1], packetBuffer[i*3], packetBuffer[i*3+2]);
  }
  return base_do;
}

void base_do(){
  for (int i=0; i< DEVICES; i++){
    ColorConverter::HsvToRgb(base_color.h, base_color.s, base_color.v, packetBuffer[i*3+1], packetBuffer[i*3], packetBuffer[i*3+2]);
  }
}
