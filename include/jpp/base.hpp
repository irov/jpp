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
        base( invalid_t );
        explicit base( json_t* _object );
        base( json_t* _object, borrowed_t );
        base( const base& _base );
        base( base&& _base );

    public:
        const base& operator = ( const base& _base );

    public:
        bool invalid() const;

    public:
        e_type type() const;

    public:
        json_t* ptr() const;
        void reset();

    public:
        bool operator == ( invalid_t ) const;
        bool operator == ( const base& _base ) const;
        bool operator != ( const base& _base ) const;

    protected:
        json_t* m_object;
    };
}