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
}
