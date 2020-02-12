#include "jpp/object.hpp"

#include "jansson.h"

#include <string.h>
#include <assert.h>

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    const object & object::none()
    {
        static object o( detail::invalid );

        return o;
    }
    //////////////////////////////////////////////////////////////////////////
    const object & object::operator = ( const object & _obj )
    {
        if( m_object != nullptr )
        {
            json_decref( m_object );
        }

        m_object = _obj.ptr();

        if( m_object != nullptr )
        {
            json_incref( m_object );
        }

        return *this;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator jpp_bool_t() const
    {
        assert( m_object != nullptr );
        assert( json_is_boolean( m_object ) == true );

        jpp_bool_t result = json_is_true( m_object );

        return (jpp_bool_t)result;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator jpp_int32_t() const
    {
        assert( m_object != nullptr );
        assert( json_is_number( m_object ) == true );

        json_int_t integer = json_integer_value( m_object );

        return (jpp_int32_t)integer;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator jpp_uint32_t() const
    {
        assert( m_object != nullptr );
        assert( json_is_number( m_object ) == true );

        json_int_t integer = json_integer_value( m_object );

        return (jpp_uint32_t)integer;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator jpp_long_t() const
    {
        assert( m_object != nullptr );
        assert( json_is_number( m_object ) == true );

        json_int_t integer = json_integer_value( m_object );

        return (jpp_long_t)integer;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator jpp_float_t() const
    {
        assert( m_object != nullptr );
        assert( json_is_number( m_object ) == true );

        jpp_double_t number = json_number_value( m_object );

        return (jpp_float_t)number;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator jpp_double_t() const
    {
        assert( m_object != nullptr );
        assert( json_is_number( m_object ) == true );

        double number = json_number_value( m_object );

        return (jpp_double_t)number;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator jpp_long_double_t() const
    {
        assert( m_object != nullptr );
        assert( json_is_number( m_object ) == true );

        double number = json_number_value( m_object );

        return (jpp_long_double_t)number;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator jpp_string_t () const
    {
        assert( m_object != nullptr );
        assert( json_is_string( m_object ) == true );

        jpp_string_t string = json_string_value( m_object );

        return string;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_size_t object::size() const
    {
        assert( m_object != nullptr );
        assert( json_is_object( m_object ) == true );

        size_t size = json_object_size( m_object );

        return (jpp_size_t)size;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t object::exist( jpp_string_t _key, jpp::object * _obj ) const
    {
        assert( m_object != nullptr );
        assert( json_is_object( m_object ) == true );

        json_t * j = json_object_get( m_object, _key );

        if( j == nullptr )
        {
            return false;
        }

        if( _obj != nullptr )
        {
            *_obj = jpp::object( j );
        }

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t object::includes( const jpp::object & _obj ) const
    {
        json_t * jb = _obj.ptr();

        assert( json_is_object( m_object ) == true );
        assert( json_is_object( jb ) == true );

        const char * key;
        json_t * value;

        json_object_foreach( jb, key, value )
        {
            json_t * j = json_object_get( m_object, key );

            if( j == nullptr )
            {
                return false;
            }

            if( json_equal( j, value ) == 0 )
            {
                return false;
            }
        }

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    object object::operator [] ( jpp_string_t _key ) const
    {
        assert( m_object != nullptr );
        assert( json_is_object( m_object ) == true );

        json_t * j = json_object_get( m_object, _key );

        return object( j );
    }
    //////////////////////////////////////////////////////////////////////////
    object object::operator [] ( jpp_mutable_string_t _key ) const
    {
        assert( m_object != nullptr );
        assert( json_is_object( m_object ) == true );

        json_t * j = json_object_get( m_object, _key );

        return object( j );
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * object::get( jpp_string_t _key ) const
    {
        assert( m_object != nullptr );
        assert( json_is_object( m_object ) == true );

        json_t * j = json_object_get( m_object, _key );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t object::get( jpp_string_t _key, jpp_bool_t _default ) const
    {
        if( m_object == nullptr )
        {
            return _default;
        }

        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        assert( json_is_boolean( j ) == true );

        jpp_bool_t value = json_is_true( j );

        return value;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_int32_t object::get( jpp_string_t _key, jpp_int32_t _default ) const
    {
        if( m_object == nullptr )
        {
            return _default;
        }

        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        assert( json_is_number( j ) == true );

        json_int_t integer = json_integer_value( j );

        return (jpp_int32_t)integer;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_uint32_t object::get( jpp_string_t _key, jpp_uint32_t _default ) const
    {
        if( m_object == nullptr )
        {
            return _default;
        }

        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        assert( json_is_number( j ) == true );

        json_int_t integer = json_integer_value( j );

        return (jpp_uint32_t)integer;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_long_t object::get( jpp_string_t _key, jpp_long_t _default ) const
    {
        if( m_object == nullptr )
        {
            return _default;
        }

        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        assert( json_is_number( j ) == true );

        json_int_t integer = json_integer_value( j );

        return (jpp_long_t)integer;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_float_t object::get( jpp_string_t _key, jpp_float_t _default ) const
    {
        if( m_object == nullptr )
        {
            return _default;
        }

        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        assert( json_is_number( j ) == true );

        double number = json_number_value( j );

        return (jpp_float_t)number;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_double_t object::get( jpp_string_t _key, jpp_double_t _default ) const
    {
        if( m_object == nullptr )
        {
            return _default;
        }

        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        assert( json_is_number( j ) == true );

        double number = json_number_value( j );

        return (jpp_double_t)number;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_long_double_t object::get( jpp_string_t _key, jpp_long_double_t _default ) const
    {
        if( m_object == nullptr )
        {
            return _default;
        }

        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        assert( json_is_number( j ) == true );

        double number = json_number_value( j );

        return (jpp_long_double_t)number;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_string_t object::get( jpp_string_t _key, jpp_string_t _default ) const
    {
        if( m_object == nullptr )
        {
            return _default;
        }

        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        assert( json_is_string( j ) == true );

        const char * string = json_string_value( j );

        return (jpp_string_t)string;
    }
    //////////////////////////////////////////////////////////////////////////
    object object::set( jpp_string_t _key, const object & _value ) const
    {
        assert( json_is_object( m_object ) == true );

        json_t * j = _value.ptr();

        json_object_set( m_object, _key, j );

        return _value;
    }
    //////////////////////////////////////////////////////////////////////////
    object object::set( jpp_string_t _key, jpp_bool_t _value ) const
    {
        assert( json_is_object( m_object ) == true );

        json_t * j = json_boolean( _value );

        json_object_set( m_object, _key, j );

        return object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    object object::set( jpp_string_t _key, jpp_int32_t _value ) const
    {
        assert( json_is_object( m_object ) == true );

        json_t * j = json_integer( _value );

        json_object_set( m_object, _key, j );

        return object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    object object::set( jpp_string_t _key, jpp_uint32_t _value ) const
    {
        assert( json_is_object( m_object ) == true );

        json_t * j = json_integer( _value );

        json_object_set( m_object, _key, j );

        return object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    object object::set( jpp_string_t _key, jpp_long_t _value ) const
    {
        assert( json_is_object( m_object ) == true );

        json_t * j = json_integer( _value );

        json_object_set( m_object, _key, j );

        return object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    object object::set( jpp_string_t _key, jpp_float_t _value ) const
    {
        assert( json_is_object( m_object ) == true );

        json_t * j = json_real( _value );

        json_object_set( m_object, _key, j );

        return object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    object object::set( jpp_string_t _key, jpp_double_t _value ) const
    {
        assert( json_is_object( m_object ) == true );

        json_t * j = json_real( _value );

        json_object_set( m_object, _key, j );

        return object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    object object::set( jpp_string_t _key, jpp_long_double_t _value ) const
    {
        assert( json_is_object( m_object ) == true );

        json_t * j = json_real( (double)_value );

        json_object_set( m_object, _key, j );

        return object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    object object::set( jpp_string_t _key, jpp_string_t _value ) const
    {
        assert( json_is_object( m_object ) == true );

        json_t * j = json_string( _value );

        json_object_set( m_object, _key, j );

        return object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t object::operator == ( jpp_bool_t _value ) const
    {
        jpp_bool_t value = json_is_true( m_object );

        jpp_bool_t successful = value == _value;

        return successful;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t object::operator == ( jpp_int32_t _value ) const
    {
        json_int_t integer = json_integer_value( m_object );

        jpp_bool_t successful = (jpp_int32_t)integer == _value;

        return successful;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t object::operator == ( jpp_uint32_t _value ) const
    {
        json_int_t integer = json_integer_value( m_object );

        jpp_bool_t successful = (jpp_uint32_t)integer == _value;

        return successful;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t object::operator == ( jpp_long_t _value ) const
    {
        json_int_t integer = json_integer_value( m_object );

        jpp_bool_t successful = (jpp_long_t)integer == _value;

        return successful;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t object::operator == ( jpp_float_t _value ) const
    {
        double number = json_number_value( m_object );

        jpp_bool_t successful = (jpp_float_t)number == _value;

        return successful;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t object::operator == ( jpp_double_t _value ) const
    {
        double number = json_number_value( m_object );

        jpp_bool_t successful = number == _value;

        return successful;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t object::operator == ( jpp_long_double_t _value ) const
    {
        double number = json_number_value( m_object );

        jpp_bool_t successful = (jpp_long_double_t)number == _value;

        return successful;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t object::operator == ( jpp_string_t _value ) const
    {
        const char * string = json_string_value( m_object );

        if( strcmp( string, _value ) != 0 )
        {
            return false;
        }

        return true;
    }
}
