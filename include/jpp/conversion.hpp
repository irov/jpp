#pragma once

#include "jpp/types.hpp"

namespace jpp
{
    class object;
    class array;

    class conversion
    {
    public:
        conversion( const object & _obj );
        conversion( json_t * _obj );
        ~conversion();

    public:
        operator jpp::array() const;
        operator jpp::object() const;

    protected:
        json_t * m_obj;
    };
}