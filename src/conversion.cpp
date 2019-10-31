#include "jpp/conversion.hpp"

#include "jpp/object.hpp"
#include "jpp/array.hpp"

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    conversion::conversion( json_t * _obj )
        : m_obj( _obj )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    conversion::~conversion()
    {
    }
    //////////////////////////////////////////////////////////////////////////
    conversion::operator jpp::array() const
    {
        return jpp::array( m_obj );
    }
    //////////////////////////////////////////////////////////////////////////
    conversion::operator jpp::object() const
    {
        return jpp::object( m_obj );
    }
    //////////////////////////////////////////////////////////////////////////
}