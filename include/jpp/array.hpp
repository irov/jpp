#pragma once

#include "jpp/base.hpp"
#include "jpp/object.hpp"

namespace jpp
{
    class array
        : public base
    {
        using base::base;

    public:
        typedef size_t size_type;

    public:
        array( const object & _obj );
        array( object && _obj );

    public:
        size_type size() const;
        object operator [] ( size_type _index ) const;
    };

    template<class T>
    void to_array( const jpp::array & _obj, T & _array )
    {
        for( const jpp::object & v : _obj )
        {
            _array.push_back( v );
        }
    }
}