#include "hsv.h"
#include "configuration.h"
#include "utils.h"

HSV_t crazy_time_output_hsv[DEVICES];

long crazy_time_frame_counter;
double crazy_time_v;

fptr crazy_time_init(){
  randomSeed(6);
  for (int i=0; i< DEVICES; i++){ 
    crazy_time_output_hsv[i].h = random(0,100)/100.0;
    crazy_time_output_hsv[i].s = CRAZY_TIME_COLOR_S;
    crazy_time_output_hsv[i].v = COLOR_VALUE_LIMIT;
  }
  
  crazy_time_frame_counter = 0;
  return crazy_time_do;
}

void crazy_time_do(void){
  for (int i=0; i<DEVICES; i++){
    crazy_time_output_hsv[i].h += CRAZY_TIME_SPEED;
    ColorConverter::HsvToRgb(crazy_time_output_hsv[i].h, crazy_time_output_hsv[i].s, crazy_time_output_hsv[i].v, packetBuffer[i*3], packetBuffer[i*3+1], packetBuffer[i*3+2]);
  }
  crazy_time_frame_counter++;
}
