#include "Arduino.h"
#include "RYLR896.h"

RYLR896::RYLR896(int baudRate){
    // Initialize Serial
    Serial.begin(baudRate);
}

bool RYLR896::Test(){
    Serial.println("AT");
    while(!Serial.available()){}
    String msg = Serial.readStringUntil('\r');
    // Consume last \n
    Serial.readStringUntil('\n');
    if (msg == "+OK") {
        return true;
    } else return false;
}
