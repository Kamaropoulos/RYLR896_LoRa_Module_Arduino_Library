#ifndef RYLR896_h
#define RYLR896_h

#include "Arduino.h"

class RYLR896{
    public:
        RYLR896(HardwareSerial* loraSerial, int baudRate);
        bool Test();
        bool Reset();
        bool Send(String message);
        bool Send(String message, word address);
        String Receive();
        bool SleepMode();
        bool NormalMode();
        // int GetMode();
        bool SetRFParams(int spreadingFactor, int bandwidth, int codingRate, int programmedPreamble);
        bool SetRFParamsLessThan3KM();
        bool SetRFParamsMoreThan3KM();
        bool SetAddress(word address);
        word GetAddress();
        bool SetNetworkID(uint8_t networkID);
        bool SetAESPassword(String password);
        String GetVersion();
    private:
        HardwareSerial* loraSerial;
        void WriteToLoRa(String message);
        String ReadFromLoRa();
        bool SetIPR(int IPR);
};

#endif