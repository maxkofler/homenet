#include "hnnetworking.h"

bool HNNetworking::processValueRequest(std::string message, QTcpSocket* sender){
    FUN();

    LOGD("The value request is: \"" + message + "\"");

    char mode = message[0];
    if (message.length() >= 2)
        message = message.substr(1, message.length()-1);

    switch(mode){
    case 'q':   //Value query
                {
                size_t valueIndex = stoi(message);
                LOGI("Requesting value #" + std::to_string(valueIndex));
                if (!this->_drivers->ok()){
                    LOGE("HNDrivers instance is not ok!");
                    break;
                }
                std::vector<hnvalue_t*>* valuesVector = this->_drivers->getValues();
                if (valueIndex < valuesVector->size()){
                    std::string response = valuesVector->at(valueIndex)->toTransmissionString() + "\n";
                    sender->write(response.c_str());
                    sender->flush();
                    sender->waitForBytesWritten(response.length());
                }else{
                    std::string retMsg = "<E><ValueID out of bounds!>";
                    sender->write(retMsg.c_str());
                    sender->flush();
                    sender->waitForBytesWritten(retMsg.length());
                }
                break;
                }

    case 'a':   //Query of all values
            {
                std::vector<hnvalue_t*>* valuesVector = this->_drivers->getValues();

                std::string retMsg = "";
                for (hnvalue_t* curValue : *valuesVector){
                    retMsg += curValue->toTransmissionString() + "\n";
                }

                sender->write(retMsg.c_str());
                sender->flush();
                sender->waitForBytesWritten(retMsg.length());
                break;
            }


    case 'h':   //Value history
                LOGI("Requesting history of value #" + message);
                break;

    default:
            {
                std::string retMsg = "<E><Not a valid value request!>";
                sender->write(retMsg.c_str());
                sender->flush();
                sender->waitForBytesWritten(retMsg.length());
            }
    }

    return true;
}