#include "jpp/cast.hpp"

#include "jpp/base.hpp"
#include "jpp/object.hpp"
#include "jpp/array.hpp"

#include "jansson.h"

#include <assert.h>

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    void cast_object_internal::operator()( json_t * _j, jpp::base * _value ) const
    {
        *_value = jpp::base( _j );
    }
    //////////////////////////////////////////////////////////////////////////
    void cast_object_internal::operator()( json_t * _j, jpp::object * _value ) const
    {
        assert( json_is_object( _j ) == true );

        *_value = jpp::object( _j );
    }
    //////////////////////////////////////////////////////////////////////////
    void cast_object_internal::operator()( json_t * _j, jpp::array * _value ) const
    {
        assert( json_is_array( _j ) == true );

        *_value = jpp::array( _j );
    }
    //////////////////////////////////////////////////////////////////////////
    void cast_object_internal::operator()( json_t * _j, jpp_bool_t * _value ) const
    {
        assert( json_is_boolean( _j ) == true );

        jpp_bool_t value = json_is_true( _j );

        *_value = value;
    }
    //////////////////////////////////////////////////////////////////////////
    void cast_object_internal::operator()( json_t * _j, jpp_int32_t * _value ) const
    {
        assert( json_is_number( _j ) == true );

        if( json_is_integer( _j ) == true )
        {
            json_int_t integer = json_integer_value( _j );

            *_value = (jpp_int32_t)integer;
        }
        else
        {
            double real = json_real_value( _j );

            *_value = (jpp_int32_t)real;
        }
    }
    //////////////////////////////////////////////////////////////////////////
    void cast_object_internal::operator()( json_t * _j, jpp_uint32_t * _value ) const
    {
        assert( json_is_number( _j ) == true );

        if( json_is_integer( _j ) == true )
        {
            json_int_t integer = json_integer_value( _j );

            *_value = (jpp_uint32_t)integer;
        }
        else
        {
            double real = json_real_value( _j );

            *_value = (jpp_uint32_t)real;
        }
    }
    //////////////////////////////////////////////////////////////////////////
    void cast_object_internal::operator()( json_t * _j, jpp_long_t * _value ) const
    {
        assert( json_is_number( _j ) == true );

        if( json_is_integer( _j ) == true )
        {
            json_int_t integer = json_integer_value( _j );

            *_value = (jpp_long_t)integer;
        }
        else
        {
            double real = json_real_value( _j );

            *_value = (jpp_long_t)real;
        }
    }
    //////////////////////////////////////////////////////////////////////////
    void cast_object_internal::operator()( json_t * _j, jpp_float_t * _value ) const
    {
        assert( json_is_number( _j ) == true );

        if( json_is_real( _j ) == true )
        {
            double real = json_real_value( _j );

            *_value = (jpp_float_t)real;
        }
        else
        {
            json_int_t integer = json_integer_value( _j );

            *_value = (jpp_float_t)integer;
        }
    }
    //////////////////////////////////////////////////////////////////////////
    void cast_object_internal::operator()( json_t * _j, jpp_double_t * _value ) const
    {
        assert( json_is_number( _j ) == true );

        if( json_is_real( _j ) == true )
        {
            double real = json_real_value( _j );

            *_value = (jpp_double_t)real;
        }
        else
        {
            json_int_t integer = json_integer_value( _j );

            *_value = (jpp_double_t)integer;
        }
    }
    //////////////////////////////////////////////////////////////////////////
    void cast_object_internal::operator()( json_t * _j, jpp_long_double_t * _value ) const
    {
        assert( json_is_number( _j ) == true );

        if( json_is_real( _j ) == true )
        {
            double real = json_real_value( _j );

            *_value = (jpp_long_double_t)real;
        }
        else
        {
            json_int_t integer = json_integer_value( _j );

            *_value = (jpp_long_double_t)integer;
        }
    }
    //////////////////////////////////////////////////////////////////////////
    void cast_object_internal::operator()( json_t * _j, const char ** _value ) const
    {
        assert( json_is_string( _j ) == true );

        const char * string = json_string_value( _j );

        *_value = string;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_object_internal::operator()( const base & _value ) const
    {
        json_t * j = _value.ret();

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_object_internal::operator()( const jpp::object & _value ) const
    {
        json_t * j = _value.ret();

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_object_internal::operator()( const jpp::array & _value ) const
    {
        json_t * j = _value.ret();

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_object_internal::operator()( jpp_bool_t _value ) const
    {
        json_t * j = json_boolean( _value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_object_internal::operator()( jpp_int32_t _value ) const
    {
        json_t * j = json_integer( (json_int_t)_value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_object_internal::operator()( jpp_uint32_t _value ) const
    {
        json_t * j = json_integer( (json_int_t)_value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_object_internal::operator()( jpp_long_t _value ) const
    {
        json_t * j = json_integer( (json_int_t)_value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_object_internal::operator()( jpp_float_t _value ) const
    {
        json_t * j = json_real( (double)_value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_object_internal::operator()( jpp_double_t _value ) const
    {
        json_t * j = json_real( _value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_object_internal::operator()( jpp_long_double_t _value ) const
    {
        json_t * j = json_real( (double)_value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_object_internal::operator()( char * _value ) const
    {
        json_t * j = json_string( _value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * cast_object_internal::operator()( const char * _value ) const
    {
        json_t * j = json_string( _value );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
}
