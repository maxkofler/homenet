#ifndef __HNDRIVER_H__
#define __HNDRIVER_H__

class HNDriver;

#include "hnvalue.h"
#include "log.h"

#include <string>
#include <vector>

class HNDriver{
public:
    HNDriver(std::string name, size_t id);
    ~HNDriver();

    /**
     * @brief   Adds a hnvalue_t to the driver
     * @param   newValue                    The new value to add (gets copied)
     */
    bool                                    addValue(hnvalue_t* newValue);

    std::vector<hnvalue_t*>                 getValues(){return this->_values;}
    std::string                             name(){return this->_name;}
    size_t                                  id(){return this->_id;}

private:
    std::vector<hnvalue_t*>                 _values;

    std::string                             _name;
    size_t                                  _id;
};

#endif
