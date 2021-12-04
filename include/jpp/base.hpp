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
        explicit base( jpp::invalid_t );
        explicit base( json_t * _object );
        base( json_t * _object, jpp::borrowed_t );
        base( const jpp::base & _base );
        base( jpp::base && _base );

    public:
        const jpp::base & operator = ( jpp::invalid_t );
        const jpp::base & operator = ( const jpp::base & _base );
        const jpp::base & operator = ( jpp::base && _base );

    public:
        jpp_bool_t invalid() const;

    public:
        e_type type() const;

    public:
        json_t * ptr() const;
        json_t * ret() const;
        json_t * pop();

    public:
        void reset();

    public:
        jpp_bool_t operator == ( invalid_t ) const;
        jpp_bool_t operator != ( invalid_t ) const;
        jpp_bool_t operator == ( const jpp::base & _base ) const;
        jpp_bool_t operator != ( const jpp::base & _base ) const;

    public:
        jpp_bool_t equal( const jpp::base & _base ) const;


    public:
        jpp_bool_t is_type_object() const;
        jpp_bool_t is_type_array() const;
        jpp_bool_t is_type_string() const;
        jpp_bool_t is_type_integer() const;
        jpp_bool_t is_type_real() const;
        jpp_bool_t is_type_true() const;
        jpp_bool_t is_type_false() const;
        jpp_bool_t is_type_null() const;

    protected:
        void reset_( json_t * _value );

    protected:
        json_t * m_object;
    };

    const char * get_jpp_type_string( const jpp::base & _o );
}