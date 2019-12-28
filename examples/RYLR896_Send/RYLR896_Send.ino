#include "RYLR896.h"

RYLR896* lora;

void setup(){
  lora = new RYLR896(&Serial, 115200);
  lora->SetRFParamsLessThan3KM();
  lora->SetAddress(4);
}

void loop(){
  lora->Send("HELLO");
}
