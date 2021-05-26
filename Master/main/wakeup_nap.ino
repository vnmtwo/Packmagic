#include "hsv.h"
#include "configuration.h"
#include "utils.h"

HSV_t wakeup_nap_output_hsv[DEVICES];
uint16_t wakeup_nap_start_time[DEVICES];

long wakeup_nap_frame_counter;
double wakeup_nap_v;
double wakeup_nap_att = WAKEUP_NAP_SIN_ATT_START;

fptr wakeup_nap_init(){
  randomSeed(5);
  for (int i=0; i< DEVICES; i++){
    wakeup_nap_start_time[i]=random(0, WAKEUP_NAP_MAX_RANDOM_T);
    
    wakeup_nap_output_hsv[i].h = WAKEUP_BLUE_LIGHT_H;
    wakeup_nap_output_hsv[i].s = 1;
    wakeup_nap_output_hsv[i].v = 0;
  }
  
  wakeup_nap_frame_counter = 0;
  wakeup_nap_att = WAKEUP_NAP_SIN_ATT_START;
  
  return wakeup_nap_do;
}

void wakeup_nap_do(void){
  for (int i=0; i<DEVICES; i++){
    if (wakeup_nap_start_time[i]<wakeup_nap_frame_counter){
      if (wakeup_nap_output_hsv[i].v<COLOR_VALUE_LIMIT){
        wakeup_nap_v = wakeup_nap_output_hsv[i].v+WAKEUP_NAP_V_SPEED;
        wakeup_nap_output_hsv[i].v = min(COLOR_VALUE_LIMIT, wakeup_nap_v);
      }
      else{
        if (wakeup_nap_output_hsv[i].h>WAKEUP_NAP_WARM_HUE){
          wakeup_nap_v = wakeup_nap_output_hsv[i].h - WAKEUP_NAP_H_SPEED;
          wakeup_nap_output_hsv[i].h = max(WAKEUP_NAP_WARM_HUE, wakeup_nap_v);
        }
      }
    }
    double m = (1-wakeup_nap_att)+sin(wakeup_nap_frame_counter/WAKEUP_NAP_SIN_DIV)*wakeup_nap_att;
    if (wakeup_nap_att>0){
      wakeup_nap_att=max(0.0, wakeup_nap_att-WAKEUP_NAP_SIN_ATT_SPEED);
    }
    
    ColorConverter::HsvToRgb(wakeup_nap_output_hsv[i].h, wakeup_nap_output_hsv[i].s, wakeup_nap_output_hsv[i].v*m, packetBuffer[i*3+1], packetBuffer[i*3], packetBuffer[i*3+2]);    
//    ColorConverter::HsvToRgb(wakeup_nap_output_hsv[i].h, wakeup_nap_output_hsv[i].s, min(1.0, max(0.0, wakeup_nap_output_hsv[i].v+m)), packetBuffer[i*3+1], packetBuffer[i*3], packetBuffer[i*3+2]);
  }
  wakeup_nap_frame_counter++;
}
