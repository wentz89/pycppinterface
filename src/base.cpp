#include <stdio.h>

#include "base.h"


Base::Base(std::string pyModuleName) : m_name(pyModuleName)
{ }

Base::~Base()
{
    printf("DELETE: %s\n", m_name.c_str());
}

uint8_t Base::Run( std::vector<uint8_t> &args )
{
    printf("RUN: %s\n", m_name.c_str());
    return 0u;
}

uint8_t Base::Stop( std::vector<uint8_t> &args )
{
    printf("STOP: %s\n", m_name.c_str());
    return 255u;
}