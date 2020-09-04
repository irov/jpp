#include "jpp/cast.hpp"

#include "jansson.h"

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_value( const base & _value )
    {
        json_t * j = _value.ptr();

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_value( jpp_bool_t _value )
    {
        json_t * j = json_boolean( _value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_value( jpp_int32_t _value )
    {
        json_t * j = json_integer( _value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_value( jpp_uint32_t _value )
    {
        json_t * j = json_integer( _value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_value( jpp_long_t _value )
    {
        json_t * j = json_real( _value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_value( jpp_float_t _value )
    {
        json_t * j = json_real( (double)_value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_value( jpp_double_t _value )
    {
        json_t * j = json_real( _value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_value( jpp_long_double_t _value )
    {
        json_t * j = json_real( (double)_value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_value( jpp_string_t _value )
    {
        json_t * j = json_string( _value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
}
