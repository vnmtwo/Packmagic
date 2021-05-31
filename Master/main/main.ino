#include "ColorConverterLib.h"
#include "hsv.h"
#include "utils.h"
#include "configuration.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

uint8_t packetBuffer[DEVICES*3];

IPAddress remoteIP(255, 255, 255, 255);
WiFiUDP Udp;

uint8_t current_program = 0;
bool program_changed = false;
fptr loop_function;

void select_program(){
  switch(current_program){
    case 0:
      loop_function = base_init();
      break;
    case 1:
      loop_function = wakeup_init();
      break;
    case 2:
      loop_function = wakeup_nap_init();
      break;
    case 3:
      loop_function = applause_init();
      break;
    case 4:
      loop_function = rhytm_init();
      break;
    case 5:
      loop_function = crazy_time_init();
      break;
    case 6:
      loop_function = countdown_init();
      break;
    case 7:
      loop_function = dialogue_init();
      break;
    case 8:
      loop_function = lamp_init();
      break;
    case 9:
      loop_function = ten_init();
      break;
    case 10:
      loop_function = x_program_init();
      break;
    case 11:
      loop_function = l_program_init();
      break;
  }

}

long last_push = 0;

void handleInterrupt01() {
  if (millis()>last_push+BUTTON_TIMEOUT){  
    last_push = millis();
    current_program=0;
    program_changed = true;
  }
}

ICACHE_RAM_ATTR void handleInterrupt02() {
  if (millis()>last_push+BUTTON_TIMEOUT){  
    last_push = millis();
    current_program=1;
    program_changed = true;
  }
}

ICACHE_RAM_ATTR void handleInterrupt03() {
  if (millis()>last_push+BUTTON_TIMEOUT){  
    last_push = millis();
    current_program=2;
    program_changed = true;
  }
}

ICACHE_RAM_ATTR void handleInterrupt04() {
  if (millis()>last_push+BUTTON_TIMEOUT){  
    last_push = millis();
    current_program=3;
    program_changed = true;
  }
}

ICACHE_RAM_ATTR void handleInterrupt05() {
  if (millis()>last_push+BUTTON_TIMEOUT){  
    last_push = millis();
    current_program=4;
    program_changed = true;
  }
}
ICACHE_RAM_ATTR void handleInterrupt06() {
  if (millis()>last_push+BUTTON_TIMEOUT){  
    last_push = millis();
    current_program=5;
    program_changed = true;
  }
}
ICACHE_RAM_ATTR void handleInterrupt07() {
  if (millis()>last_push+BUTTON_TIMEOUT){  
    last_push = millis();
    current_program=6;
    program_changed = true;
  }
}
ICACHE_RAM_ATTR void handleInterrupt08() {
  if (millis()>last_push+BUTTON_TIMEOUT){  
    last_push = millis();
    current_program=7;
    program_changed = true;
  }
}
ICACHE_RAM_ATTR void handleInterrupt09() {
  if (millis()>last_push+BUTTON_TIMEOUT){  
    last_push = millis();
    current_program=8;
    program_changed = true;
  }
}
ICACHE_RAM_ATTR void handleInterrupt10() {
  if (millis()>last_push+BUTTON_TIMEOUT){  
    last_push = millis();
    current_program=9;
    program_changed = true;
  }
}

ICACHE_RAM_ATTR void handleInterruptX() {
  if (millis()>last_push+BUTTON_TIMEOUT){  
    last_push = millis();
    current_program=10;
    program_changed = true;
  }
}

void handleInterruptL() {
  if (millis()>last_push+BUTTON_TIMEOUT){  
    last_push = millis();
    current_program=11;
    program_changed = true;
  }
}

void setup_buttons(){
  pinMode(BUTTON_PROGRAM01_PIN, INPUT_PULLDOWN_16);
  pinMode(BUTTON_PROGRAM02_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PROGRAM03_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PROGRAM04_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PROGRAM05_PIN, INPUT_PULLUP);

  pinMode(BUTTON_PROGRAM06_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PROGRAM07_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PROGRAM08_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PROGRAM09_PIN, INPUT);
  pinMode(BUTTON_PROGRAM10_PIN, INPUT_PULLUP);

  pinMode(BUTTON_X_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PROGRAM02_PIN), handleInterrupt02, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PROGRAM03_PIN), handleInterrupt02, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PROGRAM04_PIN), handleInterrupt04, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PROGRAM05_PIN), handleInterrupt05, RISING);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PROGRAM06_PIN), handleInterrupt06, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PROGRAM07_PIN), handleInterrupt07, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PROGRAM08_PIN), handleInterrupt08, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PROGRAM09_PIN), handleInterrupt09, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PROGRAM10_PIN), handleInterrupt10, RISING);

  attachInterrupt(digitalPinToInterrupt(BUTTON_X_PIN), handleInterruptX, RISING);
}
void setup() { 
  setup_buttons();   
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  select_program();
}

bool last_button01_state = true;

void check_button01(){
  bool t = digitalRead(BUTTON_PROGRAM01_PIN);
  if (!t && last_button01_state)
    handleInterrupt01();
   last_button01_state = t;
}

bool last_button02_state = false;

void check_buttonL(){
  int t = analogRead(A0);
  if (t<127 && last_button02_state)
    handleInterruptL();
  last_button02_state=(t>127);
}


unsigned long ts =0;
void loop() {
  if (millis()-ts>30){
    ts = millis();

    check_button01();
    check_buttonL();
    
    if (program_changed){
      select_program();
      program_changed = false;
    }
    
    loop_function();
    
    Udp.beginPacket(remoteIP,REMOTE_PORT);
    Udp.write(packetBuffer, sizeof(packetBuffer));
    Udp.endPacket();
  }
}
