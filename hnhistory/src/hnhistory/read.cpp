#include "hnhistory.h"

#include <filesystem>

bool HNHistory::read(hnvalue_t value){
    FUN();

    LOGF("Opening history of value \"" + ((HNDriver*)value.driver)->name() + "." + value.name + "\"");

    std::string vHistoryDir = this->_historyDir + "/" + ((HNDriver*)(value.driver))->name();

    //Check if all directories for the value history exist
    if (!std::filesystem::exists(vHistoryDir)){
        std::filesystem::create_directories(vHistoryDir);
    }

    if (this->_historyFile.is_open()){
        LOGI("History file was already open, closing...");
        this->_historyFile.close();
    }

    this->_historyFile.open(vHistoryDir + "/" + value.name + ".hnhist", std::ios::in);

    if (!this->_historyFile.is_open()){
        LOGE("Error in opening history file!");
        return false;
    }

    this->_parser.clear();
    bool ret = this->_parser.parseStream(this->_historyFile);
    return ret;
}
