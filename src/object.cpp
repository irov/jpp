#include "jpp/object.hpp"

#include "jansson.h"

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    object::operator bool() const
    {
        return json_is_true( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator int32_t() const
    {
        json_int_t integer = json_integer_value( m_object );

        return (int32_t)integer;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator uint32_t() const
    {
        json_int_t integer = json_integer_value( m_object );

        return (uint32_t)integer;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator float() const
    {
        double number = json_number_value( m_object );

        return (float)number;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator double() const
    {
        double number = json_number_value( m_object );

        return number;
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator const char * () const
    {
        return json_string_value( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    size_t object::size() const
    {
        size_t size = json_object_size( m_object );

        return size;
    }
    //////////////////////////////////////////////////////////////////////////
    object object::operator [] ( const char * _name ) const
    {
        json_t * j = json_object_get( m_object, _name );

        return object( j );
    }
}
