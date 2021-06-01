#include "hsv.h"
#include "configuration.h"
#include "utils.h"

HSV_t countdown_output_hsv[DEVICES];

long countdown_frame_counter;
double countdown_v;

fptr countdown_init(){
  for (int i=0; i< DEVICES; i++){ 
    countdown_output_hsv[i].h = COUNTDOWN_COLOR_H;
    countdown_output_hsv[i].s = COUNTDOWN_COLOR_S;
    countdown_output_hsv[i].v = 0;
  }
  
  countdown_frame_counter = 0;
  return countdown_do;
}

void countdown_do(void){
  if (countdown_frame_counter<PI*COUNTDOWN_SINE_DIV*COUNTDOWN_COUNT){
    for (int i=0; i<DEVICES; i++){
      countdown_output_hsv[i].v = COUNTDOWN_LOW_V+(1-COUNTDOWN_LOW_V)*abs(sin(countdown_frame_counter/COUNTDOWN_SINE_DIV));
      ColorConverter::HsvToRgb(countdown_output_hsv[i].h, countdown_output_hsv[i].s, countdown_output_hsv[i].v, packetBuffer[i*3], packetBuffer[i*3+1], packetBuffer[i*3+2]);
    }
  }
  countdown_frame_counter++;
}
