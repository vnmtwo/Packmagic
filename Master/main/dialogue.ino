#include "hsv.h"
#include "configuration.h"
#include "utils.h"

HSV_t dialogue_output_hsv[DEVICES];

long dialogue_frame_counter;
double dialogue_v;
uint8_t dialogue_phase;
uint16_t dialogue_pause_counter; 

fptr dialogue_init(){
  for (int i=0; i< DEVICES; i++){ 
    dialogue_hsv[i].h = DIALOGUE_COLOR_H;
    dialogue_hsv[i].s = DIALOGUE_COLOR_S;
    dialogue_hsv[i].v = 0;
  }
  dialogue_phase = 0;
  dialogue_frame_counter = 0;
  return dialogue_do;
}

void dialogue_do(void){
  for (int i=0; i<DEVICES; i++){
    switch (dialogue_phase){
      0:
        if (i&2==0){
          dialogue_hsv[i].v+= DIALOGUE_V_SPEED;
          if (dialogue_hsv[i].v>=DIALOGUE_MAX_V){
            dialogue_hsv[i].v = DIALOGUE_MAX_V;
            dialogue_phase = 1;
            dualogue_pause_counter = 0;
          }
        }
        break;
      1:
        if (dialogue_pause_counter>DIALOGUE_PAUSE){
          dialogue_phase = 2;
        }
        break;
      2:
        if (i%2==0){
          dialogue_hsv[i].v+= DIALOGUE_V_SPEED;
        }
      
    }
    dialogue_hsv[i].v = dialogue_LOW_V+(1-dialogue_LOW_V)*abs(sin(dialogue_frame_counter/dialogue_SINE_DIV));
    ColorConverter::HsvToRgb(dialogue_hsv[i].h, dialogue_hsv[i].s, dialogue_hsv[i].v, packetBuffer[i*3+1], packetBuffer[i*3], packetBuffer[i*3+2]);
  }

  dialogue_frame_counter++;
}
