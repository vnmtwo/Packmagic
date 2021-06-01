#include "hsv.h"
#include "configuration.h"
#include "utils.h"

HSV_t ten_output_hsv[DEVICES];
uint16_t ten_start_time[DEVICES];

long ten_frame_counter;
double ten_v;
uint8_t ten_phase;
uint16_t ten_pause_counter;
uint16_t ten_wakeup_start;

fptr ten_init(){
  ten_output_hsv[0].h = TEN_FIRSTLAMP_H;
  ten_output_hsv[0].s = TEN_FIRSTLAMP_S;
  ten_output_hsv[0].v = 0;
  
  randomSeed(5);
  for (int i=1; i< DEVICES; i++){
    ten_start_time[i]=random(0, TEN_MAX_RANDOM_T);
    
    ten_output_hsv[i].h = TEN_OTHERLAMP_H;
    ten_output_hsv[i].s = TEN_OTHERLAMP_S;
    ten_output_hsv[i].v = 0;
  }
  
  ten_frame_counter = 0;
  ten_phase = 0;
  return ten_do;
}

void ten_do(void){
  for (int i=0; i<DEVICES; i++){
    switch(ten_phase){
      case 0:
        if (i==0){
          ten_output_hsv[i].v+=TEN_FIRSTLAMP_V_SPEED;
          if (ten_output_hsv[i].v>=COLOR_VALUE_LIMIT){
            ten_output_hsv[i].v=COLOR_VALUE_LIMIT;
            ten_phase = 1;
            ten_pause_counter = ten_frame_counter + TEN_FIRSTLAMP_H_FLOAT_T;
          }
        }
        break;
      case 1:
        if (ten_frame_counter>ten_pause_counter){
          ten_phase = 2;
          ten_wakeup_start = ten_frame_counter;
          break;
        }
        if (i==0){
          ten_output_hsv[i].h = TEN_FIRSTLAMP_H + TEN_FIRSTLAMP_H_FLOAT_AMP*sin(ten_frame_counter/TEN_FIRSTLAMP_H_FLOAT_SIN_DIV);
        }
        break;
      case 2:
        if (i!=0){
          if (ten_frame_counter>(ten_wakeup_start+ten_start_time[i])){
            ten_output_hsv[i].v+=TEN_OTHERLAMP_V_SPEED;
            if (ten_output_hsv[i].v>COLOR_VALUE_LIMIT){
              ten_output_hsv[i].v=COLOR_VALUE_LIMIT;
            }
          }
        }
        break;
    }
    ColorConverter::HsvToRgb(ten_output_hsv[i].h, ten_output_hsv[i].s, ten_output_hsv[i].v, packetBuffer[i*3], packetBuffer[i*3+1], packetBuffer[i*3+2]);
  }
  ten_frame_counter++;
}
