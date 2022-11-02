/*
 * Copyright (C) 2022  Alexander Wentz
*/

#include <string>
#include <vector>

#include "base.h"
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>  // python interpreter
#include <pybind11/stl.h>    // type conversion

class DerivedCpp : public Base
{
public:
    DerivedCpp() = delete;
    ~DerivedCpp() = default;

    DerivedCpp(std::string moduleName); // : Base(moduleName)
    uint8_t Run(std::vector<uint8_t> &args);
    uint8_t Stop(std::vector<uint8_t> &args);
private:
    pybind11::object mObject;
};
