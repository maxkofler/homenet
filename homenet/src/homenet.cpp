#include "homenet.h"

HomeNet::~HomeNet(){
    FUN();
    

	delete this->_historyDaemon;
    delete this->_config;
    delete this->_python;
    delete this->_drivers;
    delete this->_networking;
    delete this->_history;
}
