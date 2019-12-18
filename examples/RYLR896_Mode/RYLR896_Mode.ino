#include "RYLR896.h"

RYLR896* lora;

void setup(){
  lora = new RYLR896(&Serial, 115200);
  lora->Test();
}

void loop(){
    lora->SleepMode();
    delay(500);
    lora->NormalMode();
    delay(500);
}
