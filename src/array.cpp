#include "jpp/array.hpp"

#include "jansson.h"

#include <assert.h>

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    array::array( const jpp::object & _obj )
        : base( _obj.ptr() )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    array::array( const jpp::object & _obj, jpp::borrowed_t )
        : base( _obj.ptr(), detail::borrowed )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    array::array( jpp::object && _obj )
        : base( _obj.ptr(), detail::borrowed )
    {
        _obj.reset();
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
        assert( m_object != nullptr );
        assert( json_is_array( m_object ) == true );

        size_t size = json_array_size( m_object );

        return (jpp::array::size_type)size;
    }
    //////////////////////////////////////////////////////////////////////////
    bool array::empty() const
    {
        assert( m_object != nullptr );
        assert( json_is_array( m_object ) == true );

        size_t size = json_array_size( m_object );

        return size == 0;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object array::operator [] ( jpp::array::size_type _index ) const
    {
        assert( m_object != nullptr );
        assert( json_is_array( m_object ) == true );

        json_t * j = json_array_get( m_object, _index );

        return jpp::object( j );
    }
    //////////////////////////////////////////////////////////////////////////
    void array::push_back_( json_t * _j )
    {
        assert( m_object != nullptr );
        assert( json_is_array( m_object ) == true );

        json_array_append( m_object, _j );
    }
    //////////////////////////////////////////////////////////////////////////
    void array::clear()
    {
        assert( m_object != nullptr );
        assert( json_is_array( m_object ) == true );

        json_array_clear( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    void array::remove( size_type _index )
    {
        assert( m_object != nullptr );
        assert( json_is_array( m_object ) == true );
        assert( json_array_size( m_object ) > _index );

        json_array_remove( m_object, _index );
    }
    //////////////////////////////////////////////////////////////////////////
    void array::remove_back()
    {
        assert( m_object != nullptr );
        assert( json_is_array( m_object ) == true );
        assert( json_array_size( m_object ) != 0 );

        size_t count = json_array_size( m_object );

        json_array_remove( m_object, count - 1 );
    }
    //////////////////////////////////////////////////////////////////////////
    void array::remove_front()
    {
        assert( m_object != nullptr );
        assert( json_is_array( m_object ) == true );
        assert( json_array_size( m_object ) != 0 );

        json_array_remove( m_object, 0 );
    }
    //////////////////////////////////////////////////////////////////////////
}
