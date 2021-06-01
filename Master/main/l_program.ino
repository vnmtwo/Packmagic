#include "hsv.h"
#include "configuration.h"
#include "utils.h"

HSV_t l_program_color = {L_PROGRAM_COLOR_H, L_PROGRAM_COLOR_S, L_PROGRAM_COLOR_V};

fptr l_program_init(){
  for (int i=0; i< DEVICES; i++){
    ColorConverter::HsvToRgb(l_program_color.h, l_program_color.s, l_program_color.v, packetBuffer[i*3], packetBuffer[i*3+1], packetBuffer[i*3+2]);
  }
  return l_program_do;
}

void l_program_do(){
  for (int i=0; i< DEVICES; i++){
    ColorConverter::HsvToRgb(l_program_color.h, l_program_color.s, l_program_color.v, packetBuffer[i*3], packetBuffer[i*3+1], packetBuffer[i*3+2]);
  }
}
