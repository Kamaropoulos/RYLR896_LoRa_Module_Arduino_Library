#include "RYLR896.h"

RYLR896* lora;

void setup(){
  lora = new RYLR896(&Serial, 115200);
  lora->SetRFParamsLessThan3KM();
}

void loop(){
  String msg = lora->Receive();
  lora->Send(msg);
}
