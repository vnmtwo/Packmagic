#include "hsv.h"
#include "configuration.h"
#include "utils.h"

HSV_t wakeup_output_hsv[DEVICES];
uint16_t wakeup_start_time[DEVICES];

long wakeup_frame_counter;
double wakeup_v;

fptr wakeup_init(){
  randomSeed(5);
  for (int i=0; i< DEVICES; i++){
    wakeup_start_time[i]=random(0, WAKEUP_MAX_RANDOM_T);
    
    wakeup_output_hsv[i].h = WAKEUP_BLUE_LIGHT_H;
    wakeup_output_hsv[i].s = 1;
    wakeup_output_hsv[i].v = 0;
  }
  
  wakeup_frame_counter = 0;
  return wakeup_do;
}

void wakeup_do(void){
  for (int i=0; i<DEVICES; i++){
    if (wakeup_start_time[i]<wakeup_frame_counter){
      if (wakeup_output_hsv[i].v<COLOR_VALUE_LIMIT){
        wakeup_v = wakeup_output_hsv[i].v+WAKEUP_V_SPEED;
        wakeup_output_hsv[i].v = min(COLOR_VALUE_LIMIT, wakeup_v);
      }
      else{
        if (wakeup_output_hsv[i].h>WAKEUP_WARM_HUE){
          wakeup_v = wakeup_output_hsv[i].h - WAKEUP_H_SPEED;
          wakeup_output_hsv[i].h = max(WAKEUP_WARM_HUE, wakeup_v);
        }
      }
    }
    ColorConverter::HsvToRgb(wakeup_output_hsv[i].h, wakeup_output_hsv[i].s, wakeup_output_hsv[i].v, packetBuffer[i*3], packetBuffer[i*3+1], packetBuffer[i*3+2]);
  }
  wakeup_frame_counter++;
}
