#ifndef RYLR896_h
#define RYLR896_h

#include "Arduino.h"

class RYLR896{
    public:
        RYLR896(HardwareSerial* loraSerial, int baudRate);
        bool Test();

    private:
        HardwareSerial* loraSerial;
        String WriteToLoRa(String message);

};

#endif