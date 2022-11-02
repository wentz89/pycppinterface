/*
 * Copyright (C) 2022  Alexander Wentz
*/
 
#include "derived.h"

namespace py = pybind11;

DerivedCpp::DerivedCpp(std::string moduleName) : Base(moduleName)
{
    // use naming convention so that its always from modulName.moduleName import moduleName
    py::scoped_interpreter guard{}; // auto release when this variable goes out of scope
    py::object derivedClass = py::module_::import("pyderived.pyderived").attr("pyderived");
    mObject = derivedClass("example");

}

uint8_t DerivedCpp::Run(std::vector<uint8_t> &args)
{
    py::scoped_interpreter guard{}; // auto release when this variable goes out of scope
    return mObject.attr("Run")(args).cast<uint8_t>();
}


uint8_t DerivedCpp::Stop(std::vector<uint8_t> &args)
{
    py::scoped_interpreter guard{}; // auto release when this variable goes out of scope
    return mObject.attr("Stop")(args).cast<uint8_t>();
}
