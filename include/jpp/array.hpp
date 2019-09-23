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
}