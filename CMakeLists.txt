cmake_minimum_required(VERSION 3.4...3.18)
project(interface_cpp)

find_package(Python3 COMPONENTS Interpreter Development)

set(VENV ${CMAKE_CURRENT_LIST_DIR}/venv)
set(BIN_DIR ${VENV}/bin)
set(PYTHON ${BIN_DIR}/python)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

execute_process (COMMAND "${Python3_EXECUTABLE}" -m venv "${VENV}")

# Trick to use python from the new venv
## update the environment with VIRTUAL_ENV variable (mimic the activate script)
set (ENV{VIRTUAL_ENV} "${VENV}")
## change the context of the search
set (Python3_FIND_VIRTUALENV FIRST)
## unset Python3_EXECUTABLE because it is also an input variable (see documentation, Artifacts Specification section)
unset (Python3_EXECUTABLE)
## Launch a new search
find_package(Python3 COMPONENTS Interpreter Development)

# TODO maybe: pip install --upgrade pip
execute_process (COMMAND "${Python3_EXECUTABLE}" -m pip install -r "${CMAKE_CURRENT_LIST_DIR}/requirements.txt")

# build and install the python abstract interface
execute_process(
    COMMAND "${Python3_EXECUTABLE}" -m build "${CMAKE_CURRENT_LIST_DIR}/pyinterface"
    --wheel --no-isolation -o "${CMAKE_BINARY_DIR}/dist"
)
execute_process (COMMAND "${Python3_EXECUTABLE}" -m pip install "${CMAKE_BINARY_DIR}/dist/pyinterface-0.1.0-py3-none-any.whl")

# build and install the first python example
execute_process(
    COMMAND "${Python3_EXECUTABLE}" -m build "${CMAKE_CURRENT_LIST_DIR}/pyderived"
    --wheel --no-isolation -o "${CMAKE_BINARY_DIR}/dist"
)
execute_process (COMMAND "${Python3_EXECUTABLE}" -m pip install "${CMAKE_BINARY_DIR}/dist/pyderived-0.1.0-py3-none-any.whl")

# add_custom_command(
#     OUTPUT ${VENV}
#     COMMAND ${Python3_EXECUTABLE} -m venv ${VENV}
#     COMMAND ${BIN_DIR}/pip install -r ${REQUIREMENTS}
#     COMMAND ${BIN_DIR}/pip freeze > ${VENV}/environment.txt
#     DEPENDS ${REQUIREMENTS}
# )
# 
# add_custom_target(venv DEPENDS ${PYTHON})

find_package(pybind11 CONFIG)

# Create an shared lib to link against other executables / libs
add_library(interfaceCPPcpp SHARED src/base.cpp src/base.h src/interface.cpp)
target_link_libraries(interfaceCPPcpp PUBLIC pybind11::module)
target_compile_definitions(
    interfaceCPPcpp
    PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO}
)

# create an target for python
pybind11_add_module(interfaceCPP src/base.cpp src/base.h src/interface.cpp)
set_target_properties( interfaceCPP
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${VENV}/lib/python3.10/site-packages/interfaceCPP"
)
target_compile_definitions(
    interfaceCPP
    PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO}
)

#add the example library
pybind11_add_module(derivedExample src/derived.cpp src/derived.h)
target_link_libraries(derivedExample PUBLIC interfaceCPPcpp)
# define (VERSION_INFO) here.
target_compile_definitions(
    derivedExample
    PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO}
)

#TODO create an executable and to use the example library


# Make substitution based on "@" marked strings
# set(INTERFACE_INSTALL_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
# install(FILES interfaceCPP DESTINATION ${INTERFACE_INSTALL_PATH})
# Configure 'sys.path' in pybase.py, so it may find interfaceCPP.
# configure_file("scripts/pyinterface/pybase.py" "scripts/pyinterface/pybase.py" @ONLY)
