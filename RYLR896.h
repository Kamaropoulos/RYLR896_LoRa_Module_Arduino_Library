#ifndef RYLR896_h
#define RYLR896_h

#include "Arduino.h"

class RYLR896{
    public:
        RYLR896(int baudRate);
        bool Test();
};

#endif