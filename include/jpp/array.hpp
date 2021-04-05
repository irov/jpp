#pragma once

#include "jpp/base.hpp"
#include "jpp/object.hpp"
#include "jpp/cast.hpp"

namespace jpp
{
    class array
        : public base
    {
    public:
        using base::base;

    public:
        typedef jpp_size_t size_type;

    public:
        array( const object & _obj );
        array( const object & _obj, borrowed_t );
        array( object && _obj );

    public:
        static const array & none();

    public:
        size_type size() const;
        bool empty() const;

    public:
        object operator [] ( size_type _index ) const;

    protected:
        void push_back_( json_t * _j );

    public:
        template<class T>
        void push_back( T _value )
        {
            json_t * j = cast_object_internal()(_value);

            this->push_back_( j );
        }

    public:
        void clear();
        void remove( size_type _index );
        void remove_back();
        void remove_front();
    };
}