#include "jpp/object.hpp"

#include "jansson.h"

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    const object & object::none()
    {
        static object o( detail::invalid );

        return o;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator jpp_bool_t() const
    {
        bool result = json_is_true( m_object );

        return (jpp_bool_t)result;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator jpp_int32_t() const
    {
        json_int_t integer = json_integer_value( m_object );

        return (jpp_int32_t)integer;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator jpp_uint32_t() const
    {
        json_int_t integer = json_integer_value( m_object );

        return (jpp_uint32_t)integer;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator jpp_float_t() const
    {
        jpp_double_t number = json_number_value( m_object );

        return (jpp_float_t)number;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator jpp_double_t() const
    {
        double number = json_number_value( m_object );

        return (jpp_double_t)number;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator jpp_string_t () const
    {
        jpp_string_t string = json_string_value( m_object );

        return string;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_size_t object::size() const
    {
        size_t size = json_object_size( m_object );

        return (jpp_size_t)size;
    }
    //////////////////////////////////////////////////////////////////////////
    bool object::exist( jpp_string_t _key, jpp::object * _obj ) const
    {
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
    object object::operator [] ( jpp_string_t _key ) const
    {
        json_t * j = json_object_get( m_object, _key );

        return object( j );
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * object::get( jpp_string_t _key ) const
    {
        json_t * j = json_object_get( m_object, _key );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t object::get( jpp_string_t _key, jpp_bool_t _default ) const
    {
        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        bool result = json_is_true( j );

        return result;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_int32_t object::get( jpp_string_t _key, jpp_int32_t _default ) const
    {
        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        json_int_t integer = json_integer_value( j );

        return (jpp_int32_t)integer;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_uint32_t object::get( jpp_string_t _key, jpp_uint32_t _default ) const
    {
        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        json_int_t integer = json_integer_value( j );

        return (jpp_uint32_t)integer;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_float_t object::get( jpp_string_t _key, jpp_float_t _default ) const
    {
        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        double number = json_number_value( j );

        return (jpp_float_t)number;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_double_t object::get( jpp_string_t _key, jpp_double_t _default ) const
    {
        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        double number = json_number_value( j );

        return (jpp_double_t)number;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_string_t object::get( jpp_string_t _key, jpp_string_t _default ) const
    {
        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        const char * string = json_string_value( j );

        return (jpp_string_t)string;
    }
    //////////////////////////////////////////////////////////////////////////
}
