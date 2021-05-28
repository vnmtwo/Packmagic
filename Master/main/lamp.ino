#include "hsv.h"
#include "configuration.h"
#include "utils.h"

HSV_t lamp_output_hsv[DEVICES];

fptr lamp_init(){
  for (int i=0; i< DEVICES; i++){
    lamp_output_hsv[i].h = LAMP_COLOR_H;
    lamp_output_hsv[i].s = LAMP_COLOR_S;
    lamp_output_hsv[i].v = LAMP_COLOR_V;
  }
  
  return lamp_do;
}

void lamp_do(void){
  for (int i=0; i<DEVICES; i++){
    ColorConverter::HsvToRgb(lamp_output_hsv[i].h, lamp_output_hsv[i].s, lamp_output_hsv[i].v, packetBuffer[i*3+1], packetBuffer[i*3], packetBuffer[i*3+2]);
  }
}
