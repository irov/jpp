#pragma once

#include "jpp/types.hpp"

namespace jpp
{
    class base;
    class object;
    class array;

    struct check_object_internal
    {
        bool operator()( json_t * _j, jpp::base * _value ) const;
        bool operator()( json_t * _j, jpp::object * _value ) const;
        bool operator()( json_t * _j, jpp::array * _value ) const;
        bool operator()( json_t * _j, jpp_bool_t * _value ) const;
        bool operator()( json_t * _j, jpp_int8_t * _value ) const;
        bool operator()( json_t * _j, jpp_uint8_t * _value ) const;
        bool operator()( json_t * _j, jpp_int16_t * _value ) const;
        bool operator()( json_t * _j, jpp_uint16_t * _value ) const;
        bool operator()( json_t * _j, jpp_int32_t * _value ) const;
        bool operator()( json_t * _j, jpp_uint32_t * _value ) const;
        bool operator()( json_t * _j, jpp_int64_t * _value ) const;
        bool operator()( json_t * _j, jpp_uint64_t * _value ) const;
        bool operator()( json_t * _j, jpp_float_t * _value ) const;
        bool operator()( json_t * _j, jpp_double_t * _value ) const;
        bool operator()( json_t * _j, const char ** _value ) const;

        template<size_t I>
        bool operator()( json_t * _j, char * _value[I] ) const
        {
            bool result = this->operator ()( _j, (const char *)_value );

            return result;
        }

        template<class T>
        bool operator()( json_t * _j, T * _value ) const;
    };
}