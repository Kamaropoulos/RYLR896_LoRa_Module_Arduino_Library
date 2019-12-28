#include "RYLR896.h"

RYLR896* lora;

void setup(){
  lora = new RYLR896(&Serial, 115200);
  word initialAddress = lora->GetAddress();
  lora->SetAddress(5);
  lora->GetAddress();
  lora->SetAddress(initialAddress);
}

void loop(){
  
}
