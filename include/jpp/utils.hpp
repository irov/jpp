#pragma once

#include "jpp/base.hpp"
#include "jpp/array.hpp"
#include "jpp/object_iterator.hpp"

namespace jpp
{
    template<class T>
    void to_array( const jpp::array & _obj, T & _array )
    {
        for( const jpp::object & v : _obj )
        {
            _array.push_back( v );
        }
    }
}