#include "hsv.h"
#include "configuration.h"
#include "utils.h"

HSV_t x_program_color = {BASE_COLOR_H, 0, 0};

fptr x_program_init(){
  for (int i=0; i< DEVICES; i++){
    ColorConverter::HsvToRgb(x_program_color.h, x_program_color.s, x_program_color.v, packetBuffer[i*3], packetBuffer[i*3+1], packetBuffer[i*3+2]);
  }
  return x_program_do;
}

void x_program_do(){
  for (int i=0; i< DEVICES; i++){
    ColorConverter::HsvToRgb(x_program_color.h, x_program_color.s, x_program_color.v, packetBuffer[i*3], packetBuffer[i*3+1], packetBuffer[i*3+2]);
  }
}
