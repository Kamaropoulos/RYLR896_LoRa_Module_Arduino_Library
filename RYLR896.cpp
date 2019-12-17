#include "Arduino.h"
#include "RYLR896.h"

RYLR896::RYLR896(HardwareSerial* loraSerial, int baudRate){
    // Initialize Serial
    this->loraSerial = loraSerial;
    this->loraSerial->begin(baudRate);
}

bool RYLR896::Test(){
    this->loraSerial->println("AT");
    while(!this->loraSerial->available()){}
    String msg = this->loraSerial->readStringUntil('\r');
    // Consume last \n
    this->loraSerial->readStringUntil('\n');
    if (msg == "+OK") {
        return true;
    } else return false;
}
