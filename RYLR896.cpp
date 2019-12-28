#include "Arduino.h"
#include "RYLR896.h"

RYLR896::RYLR896(HardwareSerial* loraSerial, int baudRate){
    // Initialize Serial
    this->loraSerial = loraSerial;
    this->loraSerial->begin(baudRate);
    this->SetIPR(baudRate);
}

bool RYLR896::SetIPR(int IPR){
    this->WriteToLoRa("AT+IPR="+String(IPR));
    String response = ReadFromLoRa();
    if (response == "+OK") {
        return true;
    } else return false;
}

bool RYLR896::Test(){
    this->WriteToLoRa("AT");
    String response = ReadFromLoRa();
    if (response == "+OK") {
        return true;
    } else return false;
}

bool RYLR896::Reset(){
    this->WriteToLoRa("AT+RESET");
    String response1 = ReadFromLoRa(); // +RESET
    this->loraSerial->readStringUntil(0); // Consume '0' when module resets
    if (response1 == "+RESET") {
        String response2 = ReadFromLoRa(); // ! and +READY
        if (response2 == "+READY"){
            return true;
        } else return false;
        return true;
    } else return false;
}

bool RYLR896::Send(String message){
    this->WriteToLoRa("AT+SEND=0,"+String(message.length())+","+message);
    String response = ReadFromLoRa();
    if (response == "+OK") {
        return true;
    } else return false;
}

bool RYLR896::Send(String message, word address){
    this->WriteToLoRa("AT+SEND="+String(address)+","+String(message.length())+","+message);
    String response = ReadFromLoRa();
    if (response == "+OK") {
        return true;
    } else return false;
}

String RYLR896::Receive(){
    String loraData = ReadFromLoRa();
    if (loraData.startsWith("+RCV=")){
        loraData = loraData.substring(loraData.indexOf("=")+1, loraData.length());
        word fromAddress = (word)loraData.substring(0, loraData.indexOf(",")).toInt();
        loraData = loraData.substring(loraData.indexOf(",")+1, loraData.length());
        int length = loraData.substring(0, loraData.indexOf(",")).toInt();
        loraData = loraData.substring(loraData.indexOf(",")+1, loraData.length());
        String message = loraData.substring(0, loraData.indexOf(","));
        loraData = loraData.substring(loraData.indexOf(",")+1, loraData.length());
        // TODO: Parse RSSI and SNR
        // TODO: Return structure including all parsed data
        return message;
    }
}

// TODO: Getting mode as well as changing mode seems a bit buggy for now,
//       leaving this here for a later time.

// int RYLR896::GetMode(){
//     this->WriteToLoRa("AT+MODE?");
//     String response = ReadFromLoRa();
//     if (response.substring(0, 5) == "+MODE="){
//         return (response[6] == '0') ? 0 : 1;
//     } else return -1;
// }

bool RYLR896::SleepMode(){
    this->WriteToLoRa("AT+MODE=1");
    String response = ReadFromLoRa();
    if (response == "+OK") {
        return true;
    } else return false;
}

bool RYLR896::NormalMode(){
    this->WriteToLoRa("AT+MODE=0");
    String response = ReadFromLoRa();
    if (response == "+OK") {
        return true;
    } else return false;
}

bool RYLR896::SetRFParams(int spreadingFactor, int bandwidth, int codingRate, int programmedPreamble){
    this->WriteToLoRa("AT+PARAMETER="+String(spreadingFactor)+","+String(bandwidth)+","+String(codingRate)+","+String(programmedPreamble));
    String response = ReadFromLoRa();
    if (response == "+OK") {
        return true;
    } else return false;
}

bool RYLR896::SetRFParamsLessThan3KM(){
    return this->SetRFParams(10,7,1,7);
}

bool RYLR896::SetRFParamsMoreThan3KM(){
    return this->SetRFParams(12,3,1,7);
}

bool RYLR896::SetAddress(word address){
    this->WriteToLoRa("AT+ADDRESS="+String(address));
    String response = ReadFromLoRa();
    if (response == "+OK") {
        return true;
    } else return false;
}

word RYLR896::GetAddress(){
    this->WriteToLoRa("AT+ADDRESS?");
    String response = ReadFromLoRa();
    if (response.startsWith("+ADDRESS=")) {
        return (word)response.substring(response.indexOf("=")+1, response.length()).toInt();
    }
}

bool RYLR896::SetNetworkID(uint8_t networkID){
    this->WriteToLoRa("AT+NETWORKID="+String(networkID));
    String response = ReadFromLoRa();
    if (response == "+OK") {
        return true;
    } else return false;
}

String RYLR896::ReadFromLoRa(){
    // Block until we get a response
    while(!this->loraSerial->available()){}

    // RYLR896 responses terminate with \r\n
    // In order to read them properly without relying to the readString's timeout,
    // we are going to read up until the first \r character and then we are going
    // to consume the final \n character.

    // Read response from serial until \r
    String response = this->loraSerial->readStringUntil('\r');
    // Consume last \n or 234
    char c = this->loraSerial->read();

    return response;
}

void RYLR896::WriteToLoRa(String message){
    // Send message to serial
    this->loraSerial->println(message);
}
