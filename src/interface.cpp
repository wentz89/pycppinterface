/*
 * Copyright (C) 2022  Alexander Wentz
*/

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "base.h"

namespace py = pybind11;

class PyBase : public Base
{
    using Base::Base;

    ~PyBase()
    { }

    /* Trampoline (need one for each virtual function) */
    uint8_t Run( std::vector<uint8_t> &args) override
    {
        PYBIND11_OVERRIDE_PURE(
            uint8_t, // return type
            Base,    // Parent Class
            Run,     // Name of the C++ Function (must match Python name)
            args     // arguments
        );
    }

    uint8_t Stop( std::vector<uint8_t> &args) override
    {
        PYBIND11_OVERRIDE_PURE(
            uint8_t, // return type
            Base,    // Parent Class
            Stop,     // Name of the C++ Function (must match Python name)
            args     // arguments
        );
    }

};

PYBIND11_MODULE(interfaceCPP, module) {
    module.doc() = "PyBase interface to Base"; // optional module docstring

    py::class_<Base, PyBase>(module, "Base")
        .def(py::init<std::string>())
        .def("Run", &Base::Run)
        .def("Stop", &Base::Stop);

    //module.def("add", &add, "A function that adds two numbers", py::arg("i"), py::arg("j"));
}
