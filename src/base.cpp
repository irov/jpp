#include "jpp/base.hpp"

#include "jansson.h"

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    base::base()
        : m_object( nullptr )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    base::~base()
    {
        json_decref( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    base::base( invalid_t )
        : base( nullptr )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    base::base( json_t * _object )
        : m_object( _object )
    {
        json_incref( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    base::base( json_t * _object, jpp::borrowed_t )
        : m_object( _object )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    base::base( const jpp::base & _base )
        : base( _base.ptr() )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    base::base( jpp::base && _base )
        : base( _base.ptr(), detail::borrowed )
    {
        _base.reset();
    }
    //////////////////////////////////////////////////////////////////////////
    const jpp::base & base::operator = ( jpp::invalid_t )
    {
        if( m_object != nullptr )
        {
            json_decref( m_object );
        }

        m_object = nullptr;

        return *this;
    }
    //////////////////////////////////////////////////////////////////////////
    const jpp::base & base::operator = ( const jpp::base & _base )
    {
        json_t * j = _base.ptr();

        this->reset_( j );

        return *this;
    }
    //////////////////////////////////////////////////////////////////////////
    const jpp::base & base::operator = ( jpp::base && _base )
    {
        m_object = _base.ptr();

        _base.reset();

        return *this;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t base::invalid() const
    {
        return m_object == nullptr;
    }
    //////////////////////////////////////////////////////////////////////////
    e_type base::type() const
    {
        return e_type( json_typeof( m_object ) );
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * base::ptr() const
    {
        return m_object;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * base::ret() const
    {
        if( m_object == nullptr )
        {
            return nullptr;
        }

        json_incref( m_object );

        return m_object;
    }
    //////////////////////////////////////////////////////////////////////////
    json_t * base::pop()
    {
        json_t * j = m_object;

        m_object = nullptr;

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
    void base::reset()
    {
        m_object = nullptr;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t base::operator == ( jpp::invalid_t ) const
    {
        return this->invalid();
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t base::operator != ( jpp::invalid_t ) const
    {
        return !this->operator ==( detail::invalid );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t base::operator == ( const jpp::base & _base ) const
    {
        return m_object == _base.ptr();
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t base::operator != ( const jpp::base & _base ) const
    {
        return !this->operator ==( _base );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t base::equal( const jpp::base & _base ) const
    {
        json_t * jbase = _base.ptr();
        json_t * jthis = this->ptr();

        if( json_equal( jbase, jthis ) == 0 )
        {
            return false;
        }

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t base::is_type_object() const
    {
        return json_is_object( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t base::is_type_array() const
    {
        return json_is_array( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t base::is_type_string() const
    {
        return json_is_string( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t base::is_type_integer() const
    {
        return json_is_integer( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t base::is_type_real() const
    {
        return json_is_real( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t base::is_type_true() const
    {
        return json_is_true( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t base::is_type_false() const
    {
        return json_is_false( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t base::is_type_null() const
    {
        return json_is_null( m_object );
    }
    //////////////////////////////////////////////////////////////////////////
    void base::reset_( json_t * _value )
    {
        if( m_object != nullptr )
        {
            json_decref( m_object );
        }

        m_object = _value;

        if( m_object != nullptr )
        {
            json_incref( m_object );
        }
    }
    //////////////////////////////////////////////////////////////////////////
    const char * get_jpp_type_string( const jpp::base & _o )
    {
        e_type t = _o.type();

        switch( t )
        {
        case e_type::JPP_OBJECT:
            return "JPP_OBJECT";
        case e_type::JPP_ARRAY:
            return "JPP_ARRAY";
        case e_type::JPP_STRING:
            return "JPP_STRING";
        case e_type::JPP_INTEGER:
            return "JPP_INTEGER";
        case e_type::JPP_REAL:
            return "JPP_REAL";
        case e_type::JPP_TRUE:
            return "JPP_TRUE";
        case e_type::JPP_FALSE:
            return "JPP_FALSE";
        case e_type::JPP_NULL:
            return "JPP_NULL";
        default:
            break;
        }

        return "UNKNOWN";
    }
    //////////////////////////////////////////////////////////////////////////
}
