#pragma once

#include "jpp/types.hpp"

namespace jpp
{
    class base;
    class object;
    class array;

    struct cast_object_internal
    {
        void operator()( json_t * _j, jpp::base * _value ) const;
        void operator()( json_t * _j, jpp::object * _value ) const;
        void operator()( json_t * _j, jpp::array * _value ) const;
        void operator()( json_t * _j, jpp_bool_t * _value ) const;
        void operator()( json_t * _j, jpp_int32_t * _value ) const;
        void operator()( json_t * _j, jpp_uint32_t * _value ) const;
        void operator()( json_t * _j, jpp_long_t * _value ) const;
        void operator()( json_t * _j, jpp_float_t * _value ) const;
        void operator()( json_t * _j, jpp_double_t * _value ) const;
        void operator()( json_t * _j, jpp_long_double_t * _value ) const;
        void operator()( json_t * _j, const char ** _value ) const;

        template<size_t I>
        void operator()( json_t * _j, char * _value[I] ) const
        {
            this->operator ()( _j, (const char *)_value );
        }

        template<class T>
        void operator()( json_t * _j, T * _value ) const;

        json_t * operator()( const jpp::base & _value ) const;
        json_t * operator()( const jpp::object & _value ) const;
        json_t * operator()( const jpp::array & _value ) const;
        json_t * operator()( jpp_bool_t _value ) const;
        json_t * operator()( jpp_int32_t _value ) const;
        json_t * operator()( jpp_uint32_t _value ) const;
        json_t * operator()( jpp_long_t _value ) const;
        json_t * operator()( jpp_float_t _value ) const;
        json_t * operator()( jpp_double_t _value ) const;
        json_t * operator()( jpp_long_double_t _value ) const;
        json_t * operator()( char * _value ) const;
        json_t * operator()( const char * _value ) const;

        template<class T>
        json_t * operator()( const T & _value ) const;
    };
}