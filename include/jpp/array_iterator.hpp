#pragma once

#include "jpp/types.hpp"
#include "jpp/array.hpp"

namespace jpp
{
    class array_iterator
    {
    public:
        array_iterator( const array_iterator& _r );
        ~array_iterator();

    public:
        array_iterator( json_t* _obj, size_t _iter );

    public:
        bool operator == ( const array_iterator& _it ) const;
        bool operator != ( const array_iterator& _it ) const;

    public:
        array_iterator& operator ++ ();
        array_iterator operator ++ ( int );

        object operator -> () const;
        object operator * () const;

    protected:        
        json_t* m_object;
        size_t m_iter;
    };
}

namespace std
{
    jpp::array_iterator begin( const jpp::array& _array );
    jpp::array_iterator end( const jpp::array& _array );
}