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
        array( const object & _obj, borrowed_t );
        array( object && _obj );

    public:
        static const array & none();

    public:
        size_type size() const;
        object operator [] ( size_type _index ) const;

    public:
        void push_back( const base & _obj );
    };
}