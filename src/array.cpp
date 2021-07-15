#include "jpp/array.hpp"

#include "jpp/assert.hpp"

#include "jansson.h"

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    array::array( const jpp::object & _obj )
        : base( _obj.ptr() )
    {
        JPP_ASSERT( m_object == nullptr || json_is_array( m_object ) == true );
    }
    //////////////////////////////////////////////////////////////////////////
    array::array( const jpp::object & _obj, jpp::borrowed_t )
        : base( _obj.ptr(), detail::borrowed )
    {
        JPP_ASSERT( m_object == nullptr || json_is_array( m_object ) == true );
    }
    //////////////////////////////////////////////////////////////////////////
    array::array( jpp::object && _obj )
        : base( _obj.ptr(), detail::borrowed )
    {
        _obj.reset();

        JPP_ASSERT( m_object == nullptr || json_is_array( m_object ) == true );
    }
    //////////////////////////////////////////////////////////////////////////
    const jpp::array & array::none()
    {
        static jpp::array a( detail::invalid );

        return a;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::array::size_type array::size() const
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_array( m_object ) == true );

        size_t size = json_array_size( m_object );

        return (jpp::array::size_type)size;
    }
    //////////////////////////////////////////////////////////////////////////
    bool array::empty() const
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_array( m_object ) == true );

        size_t size = json_array_size( m_object );

        return size == 0;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object array::operator [] ( jpp::array::size_type _index ) const
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_array( m_object ) == true );

        json_t * j = json_array_get( m_object, _index );

        return jpp::object( j );
    }
    //////////////////////////////////////////////////////////////////////////
    void array::push_back_( json_t * _j )
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_array( m_object ) == true );

        json_array_append( m_object, _j );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object array::front() const
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_array( m_object ) == true );
        JPP_ASSERT( json_array_size( m_object ) != 0 );

        json_t * j = json_array_get( m_object, 0 );

        return jpp::object( j );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object array::back() const
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_array( m_object ) == true );
        JPP_ASSERT( json_array_size( m_object ) != 0 );

        size_t s = json_array_size( m_object );

        json_t * j = json_array_get( m_object, s - 1 );

        return jpp::object( j );
    }
    //////////////////////////////////////////////////////////////////////////
    void array::clear()
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_array( m_object ) == true );

        json_array_clear( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    void array::remove( size_type _index )
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_array( m_object ) == true );
        JPP_ASSERT( json_array_size( m_object ) > _index );

        json_array_remove( m_object, _index );
    }
    //////////////////////////////////////////////////////////////////////////
    void array::remove_back()
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_array( m_object ) == true );
        JPP_ASSERT( json_array_size( m_object ) != 0 );

        size_t count = json_array_size( m_object );

        json_array_remove( m_object, count - 1 );
    }
    //////////////////////////////////////////////////////////////////////////
    void array::remove_front()
    {
        JPP_ASSERT( m_object != nullptr );
        JPP_ASSERT( json_is_array( m_object ) == true );
        JPP_ASSERT( json_array_size( m_object ) != 0 );

        json_array_remove( m_object, 0 );
    }
    //////////////////////////////////////////////////////////////////////////
}
