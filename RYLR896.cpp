#include "Arduino.h"
#include "RYLR896.h"

RYLR896::RYLR896(HardwareSerial* loraSerial, int baudRate){
    // Initialize Serial
    this->loraSerial = loraSerial;
    this->loraSerial->begin(baudRate);
}

bool RYLR896::Test(){
    String repsonse = this->WriteToLoRa("AT");
    if (repsonse == "+OK") {
        return true;
    } else return false;
}

String RYLR896::WriteToLoRa(String message){

    // Send message to serial
    this->loraSerial->println(message);

    // Block until we get a response
    while(!this->loraSerial->available()){}

    // RYLR896 responses terminate with \r\n
    // In order to read them properly without relying to the readString's timeout,
    // we are going to read up until the first \r character and then we are going
    // to consume the final \n character.

    // Read response from serial until \r
    String response = this->loraSerial->readStringUntil('\r');
    // Consume last \n
    this->loraSerial->readStringUntil('\n');

    return response;

}
