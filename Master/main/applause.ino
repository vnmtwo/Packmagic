#include "hsv.h"
#include "configuration.h"
#include "utils.h"

HSV_t applause_output_hsv[DEVICES];
float applause_sine_phase[DEVICES];

long applause_frame_counter;
double applause_v;

fptr applause_init(){
  randomSeed(5);
  for (int i=0; i< DEVICES; i++){
    applause_sine_phase[i]=random(0, 628)/100.0f;
    
    applause_output_hsv[i].h = APLLAUSE_COLOR_H;
    applause_output_hsv[i].s = APLLAUSE_COLOR_S;
    applause_output_hsv[i].v = 0;
  }
  
  applause_frame_counter = 0;
  return applause_do;
}

void applause_do(void){
  for (int i=0; i<DEVICES; i++){
    applause_output_hsv[i].v = COLOR_VALUE_LIMIT*0.5*(1+sin(applause_frame_counter/APLLAUSE_SIN_DIV+applause_sine_phase[i]));
    ColorConverter::HsvToRgb(applause_output_hsv[i].h, applause_output_hsv[i].s, applause_output_hsv[i].v, packetBuffer[i*3+1], packetBuffer[i*3], packetBuffer[i*3+2]);
  }
  applause_frame_counter++;
}
