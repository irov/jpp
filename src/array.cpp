#include "jpp/array.hpp"

#include "jansson.h"

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    array::array( const object & _obj )
        : base( _obj.ptr() )
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
        return json_array_size( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    object array::operator [] ( array::size_type _index ) const
    {
        json_t * j = json_array_get( m_object, _index );

        return object( j );
    }
}
