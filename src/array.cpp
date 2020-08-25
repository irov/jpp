#include "jpp/array.hpp"

#include "jansson.h"

#include <assert.h>

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    array::array( const object & _obj )
        : base( _obj.ptr() )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    array::array( const object & _obj, borrowed_t )
        : base( _obj.ptr(), detail::borrowed )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    array::array( object && _obj )
        : base( _obj.ptr(), detail::borrowed )
    {
        _obj.reset();
    }
    //////////////////////////////////////////////////////////////////////////
    const array & array::none()
    {
        static array a( detail::invalid );

        return a;
    }
    //////////////////////////////////////////////////////////////////////////
    array::size_type array::size() const
    {
        assert( m_object != nullptr );
        assert( json_is_array( m_object ) == true );

        return json_array_size( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    object array::operator [] ( array::size_type _index ) const
    {
        assert( m_object != nullptr );
        assert( json_is_array( m_object ) == true );

        json_t * j = json_array_get( m_object, _index );

        return object( j );
    }
    //////////////////////////////////////////////////////////////////////////
    void array::push_back( const base & _obj )
    {
        assert( m_object != nullptr );
        assert( json_is_array( m_object ) == true );

        json_t * j = _obj.ptr();

        json_array_append( m_object, j );
    }
}
