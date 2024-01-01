#include "jpp/object.hpp"

#include "jpp/stdstr.hpp"
#include "jpp/assert.hpp"

#include "jansson.h"

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    const jpp::object & object::none()
    {
        static jpp::object o( detail::invalid );

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

        if( JPP_STRCMP( value, _value ) != 0 )
        {
            return false;
        }

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object object::get_or_create( const char * _key, const std::function<jpp::object()> & _creator )
    {
        jpp::object o;
        if( this->exist( _key, &o ) == true )
        {
            return o;
        }

        jpp::object new_o = _creator();

        this->set( _key, new_o );

        return new_o;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object::size_type object::size() const
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_object( m_object ) == true );

        size_t size = json_object_size( m_object );

        return (jpp::object::size_type)size;
    }
    //////////////////////////////////////////////////////////////////////////
    bool object::empty() const
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_object( m_object ) == true );

        size_t size = json_object_size( m_object );

        return size == 0;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t object::exist( const char * _key, jpp::object * const _obj ) const
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_object( m_object ) == true );

        json_t * j = json_object_get( m_object, _key );

        if( j == nullptr || jpp::is_null( j ) == true )
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

        JPP_ASSERT( json_is_object( m_object ) == true );
        JPP_ASSERT( json_is_object( jb ) == true );

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
    jpp::extract object::operator [] ( const char * _key ) const
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_object( m_object ) == true );

        json_t * j = json_object_get( m_object, _key );

        return jpp::extract( j );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::extract_safe object::get( const char * _key ) const
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_object( m_object ) == true );

        json_t * j = json_object_get( m_object, _key );

        return jpp::extract_safe( j );
    }
    //////////////////////////////////////////////////////////////////////////
    const char * object::get( const char * _key, const char * _default ) const
    {
        const char * value = this->get<const char *>( _key, _default );

        return value;
    }
    //////////////////////////////////////////////////////////////////////////
    void object::set_( const char * _key, json_t * _value )
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_object( m_object ) == true );

        json_object_set_new( m_object, _key, _value );
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * object::get_( const char * _key ) const
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_object( m_object ) == true );

        json_t * j = json_object_get( m_object, _key );

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
}
