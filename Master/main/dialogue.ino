#include "hsv.h"
#include "configuration.h"
#include "utils.h"

HSV_t dialogue_output_hsv[DEVICES];

long dialogue_frame_counter;
double dialogue_v;
uint8_t dialogue_phase;
uint16_t dialogue_pause_counter; 
uint8_t dialogue_group;
bool dialogue_change_group;

fptr dialogue_init(){
  for (int i=0; i< DEVICES; i++){ 
    dialogue_output_hsv[i].h = DIALOGUE_COLOR_H;
    dialogue_output_hsv[i].s = DIALOGUE_COLOR_S;
    dialogue_output_hsv[i].v = 0;
  }
  dialogue_phase = 0;
  dialogue_frame_counter = 0;
  dialogue_group=0;
  dialogue_change_group = false;
  
  return dialogue_do;
}

void dialogue_do(void){
  switch (dialogue_phase){
    case 0:
      for (int i=0; i<DEVICES; i++){
        if (i%2==dialogue_group){
          dialogue_output_hsv[i].v+= DIALOGUE_V_SPEED;
          if (dialogue_output_hsv[i].v>=DIALOGUE_MAX_V){
            dialogue_output_hsv[i].v = DIALOGUE_MAX_V;
            dialogue_phase = 1;
            dialogue_pause_counter = dialogue_frame_counter+DIALOGUE_PAUSE;
          }
        }
        ColorConverter::HsvToRgb(dialogue_output_hsv[i].h, dialogue_output_hsv[i].s, dialogue_output_hsv[i].v, packetBuffer[i*3+1], packetBuffer[i*3], packetBuffer[i*3+2]);
      }
      break;
    case 1:
      if (dialogue_frame_counter>dialogue_pause_counter){
        dialogue_phase = 2;
      }
      break;
    case 2:
      for (int i=0; i<DEVICES; i++){
        if (i%2==dialogue_group){
          dialogue_output_hsv[i].v-= DIALOGUE_V_SPEED;
          if (dialogue_output_hsv[i].v<=0.0){
            dialogue_output_hsv[i].v = 0.0;
            dialogue_phase = 3;
            dialogue_pause_counter = dialogue_frame_counter+DIALOGUE_PAUSE;
          }
        }
        ColorConverter::HsvToRgb(dialogue_output_hsv[i].h, dialogue_output_hsv[i].s, dialogue_output_hsv[i].v, packetBuffer[i*3+1], packetBuffer[i*3], packetBuffer[i*3+2]);
      }
      break;
     case 3: 
       if (dialogue_frame_counter>dialogue_pause_counter){
        dialogue_change_group = true;
        dialogue_phase = 0;
      }
      break;             
  }

  if (dialogue_change_group){
    dialogue_group = dialogue_group==0?1:0;
    dialogue_change_group = false;
  }
  dialogue_frame_counter++;
}
