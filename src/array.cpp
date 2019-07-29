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
    array::size_type array::size() const
    {
        return json_array_size( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    object array::operator [] ( array::size_type _index ) const
    {
        return object( json_array_get( m_object, _index ) );
    }
}
