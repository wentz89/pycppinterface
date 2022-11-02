/*
 * Copyright (C) 2022  Alexander Wentz
 */

#include <vector>
#include <string>
#include <cstdint>

class Base
{
public:
    Base() = delete;
    Base(std::string name);
    virtual ~Base();
    virtual uint8_t Run( std::vector<uint8_t> &args );
    virtual uint8_t Stop( std::vector<uint8_t> &args );
private:
    std::string m_name;
};
