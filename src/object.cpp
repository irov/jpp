#include "jpp/object.hpp"

#include "jansson.h"

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    object::operator bool() const
    {
        return json_is_true(m_object);
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator int32_t() const
    {
        return (int32_t)json_integer_value(m_object);
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator uint32_t() const
    {
        return (uint32_t)json_integer_value(m_object);
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator float() const
    {
        return (float)json_real_value(m_object);
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator double() const
    {
        return (double)json_real_value(m_object);
    }
    //////////////////////////////////////////////////////////////////////////
    object::operator const char* () const
    {
        return json_string_value(m_object);
    }
    //////////////////////////////////////////////////////////////////////////
    object object::operator [] ( const char* _name ) const
    {
        json_t * j = json_object_get( m_object, _name );

        return object( j );
    }
}
