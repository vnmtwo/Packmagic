#include "hsv.h"
#include "configuration.h"
#include "utils.h"

HSV_t rhytm_output_hsv[DEVICES];

long rhytm_frame_counter;
double rhytm_v;

fptr rhytm_init(){
  for (int i=0; i< DEVICES; i++){ 
    rhytm_output_hsv[i].h = RHYTM_COLOR_H;
    rhytm_output_hsv[i].s = RHYTM_COLOR_S;
    rhytm_output_hsv[i].v = 0;
  }
  
  rhytm_frame_counter = 0;
  return rhytm_do;
}

void rhytm_do(void){
  for (int i=0; i<DEVICES; i++){
    rhytm_output_hsv[i].v = COLOR_VALUE_LIMIT*0.5*(1+sin(rhytm_frame_counter/RHYTM_SIN_DIV));
    ColorConverter::HsvToRgb(rhytm_output_hsv[i].h, rhytm_output_hsv[i].s, rhytm_output_hsv[i].v, packetBuffer[i*3+1], packetBuffer[i*3], packetBuffer[i*3+2]);
  }
  rhytm_frame_counter++;
}
