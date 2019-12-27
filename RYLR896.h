#ifndef RYLR896_h
#define RYLR896_h

#include "Arduino.h"

class RYLR896{
    public:
        RYLR896(HardwareSerial* loraSerial, int baudRate);
        bool Test();
        bool Reset();
        bool SleepMode();
        bool NormalMode();
        // int GetMode();

    private:
        HardwareSerial* loraSerial;
        void WriteToLoRa(String message);
        String ReadFromLoRa();
};

#endif