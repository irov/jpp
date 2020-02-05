#pragma once

#include "jpp/types.hpp"

namespace jpp
{
    enum class e_type
    {
        JPP_OBJECT,
        JPP_ARRAY,
        JPP_STRING,
        JPP_INTEGER,
        JPP_REAL,
        JPP_TRUE,
        JPP_FALSE,
        JPP_NULL
    };

    struct invalid_t
    {
    };

    struct borrowed_t
    {
    };

    namespace detail
    {
        const invalid_t invalid;
        const borrowed_t borrowed;
    }

    class base
    {
    public:
        base();
        ~base();

    public:
        explicit base( invalid_t );
        explicit base( json_t * _object );
        base( json_t * _object, borrowed_t );
        base( const base & _base );
        base( base && _base );

    public:
        const base & operator = ( invalid_t );
        const base & operator = ( const base & _base );

    public:
        jpp_bool_t invalid() const;

    public:
        e_type type() const;

    public:
        json_t * ptr() const;
        void reset();

    public:
        jpp_bool_t operator == ( invalid_t ) const;
        jpp_bool_t operator != ( invalid_t ) const;
        jpp_bool_t operator == ( const base & _base ) const;
        jpp_bool_t operator != ( const base & _base ) const;

    public:
        jpp_bool_t equal( const base & _base ) const;

    protected:
        json_t * m_object;
    };
}