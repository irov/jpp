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
    jpp_bool_t object::operator == ( const jpp::object & _value ) const
    {
        jpp_bool_t successful = (m_object == _value.ptr());

        return successful;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t object::operator == ( const char * _value ) const
    {
        const char * value;
        jpp::cast_object_internal()(m_object, &value);

        if( strcmp( value, _value ) != 0 )
        {
            return false;
        }

        return true;
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
    jpp_bool_t object::exist( const char * _key, jpp::object * _obj ) const
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
    object object::operator [] ( int32_t _index ) const
    {
        assert( m_object != nullptr );
        assert( json_is_array( m_object ) == true );

        json_t * j = json_array_get( m_object, _index );

        return object( j );
    }
    //////////////////////////////////////////////////////////////////////////
    object object::operator [] ( uint32_t _index ) const
    {
        assert( m_object != nullptr );
        assert( json_is_array( m_object ) == true );

        json_t * j = json_array_get( m_object, _index );

        return object( j );
    }
    //////////////////////////////////////////////////////////////////////////
    object object::operator [] ( const char * _key ) const
    {
        assert( m_object != nullptr );
        assert( json_is_object( m_object ) == true );

        json_t * j = json_object_get( m_object, _key );

        return object( j );
    }
    //////////////////////////////////////////////////////////////////////////
    object object::get( const char * _key ) const
    {
        assert( m_object != nullptr );
        assert( json_is_object( m_object ) == true );

        json_t * j = json_object_get( m_object, _key );

        return object( j );
    }
    //////////////////////////////////////////////////////////////////////////
}
