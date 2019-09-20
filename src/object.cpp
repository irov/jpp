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
        const char * string = json_string_value( m_object );

        return string;
    }
    //////////////////////////////////////////////////////////////////////////
    size_t object::size() const
    {
        size_t size = json_object_size( m_object );

        return size;
    }
    //////////////////////////////////////////////////////////////////////////
    object object::operator [] ( const char * _key ) const
    {
        json_t * j = json_object_get( m_object, _key );

        return object( j );
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * object::get( const char * _key ) const
    {
        json_t * j = json_object_get( m_object, _key );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    bool object::get( const char * _key, bool _default ) const
    {
        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        return json_is_true( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    int32_t object::get( const char * _key, int32_t _default ) const
    {
        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        json_int_t integer = json_integer_value( j );

        return (int32_t)integer;
    }
    //////////////////////////////////////////////////////////////////////////
    uint32_t object::get( const char * _key, uint32_t _default ) const
    {
        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        json_int_t integer = json_integer_value( j );

        return (uint32_t)integer;
    }
    //////////////////////////////////////////////////////////////////////////
    float object::get( const char * _key, float _default ) const
    {
        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        double number = json_number_value( j );

        return (float)number;
    }
    //////////////////////////////////////////////////////////////////////////
    double object::get( const char * _key, double _default ) const
    {
        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        double number = json_number_value( j );

        return number;
    }
    //////////////////////////////////////////////////////////////////////////
    const char * object::get( const char * _key, const char * _default ) const
    {
        json_t * j = this->get( _key );

        if( j == nullptr )
        {
            return _default;
        }

        const char * string = json_string_value( j );

        return string;
    }
    //////////////////////////////////////////////////////////////////////////
}
