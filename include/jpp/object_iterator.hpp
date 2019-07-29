#pragma once

#include "jpp/types.hpp"
#include "jpp/object.hpp"

namespace jpp
{
    struct object_iterator_end_t
    {
    };

    struct object_iterator_pair
    {
        const char * key;
        object value;
    };

    class object_iterator
    {
    public:
        object_iterator( const object_iterator & _r );
        ~object_iterator();

    public:
        object_iterator( json_t * _obj );
        object_iterator( json_t * _obj, object_iterator_end_t );

    public:
        bool operator == ( const object_iterator & _it ) const;
        bool operator != ( const object_iterator & _it ) const;

    public:
        object_iterator & operator ++ ();
        object_iterator operator ++ ( int );

        object_iterator_pair operator -> () const;
        object_iterator_pair operator * () const;

    protected:
        json_t * m_object;
        void * m_iter;
    };
    //////////////////////////////////////////////////////////////////////////
    jpp::object_iterator begin( const jpp::object & _object );
    jpp::object_iterator end( const jpp::object & _object );
}
