#include "RYLR896.h"

RYLR896* lora;

void setup(){
  lora = new RYLR896(&Serial, 115200);
}

void loop(){
    lora->Reset();
    delay(1000);
}
