#pragma once

#include "jpp/types.hpp"
#include "jpp/base.hpp"

namespace jpp
{
    json_t * cast_value( const base & _value );
    json_t * cast_value( jpp_bool_t _value );
    json_t * cast_value( jpp_int32_t _value );
    json_t * cast_value( jpp_uint32_t _value );
    json_t * cast_value( jpp_uint32_t _value );
    json_t * cast_value( jpp_long_t _value );
    json_t * cast_value( jpp_float_t _value );
    json_t * cast_value( jpp_double_t _value );
    json_t * cast_value( jpp_long_double_t _value );
    json_t * cast_value( jpp_string_t _value );
}