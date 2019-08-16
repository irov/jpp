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
    base::base( json_t * _object, borrowed_t )
        : m_object( _object )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    base::base( const base & _base )
        : base( _base.ptr() )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    base::base( base && _base )
        : base( _base.ptr(), detail::borrowed )
    {
        _base.reset();
    }
    //////////////////////////////////////////////////////////////////////////
    const base & base::operator = ( invalid_t )
    {
        if( m_object != nullptr )
        {
            json_decref( m_object );
        }

        m_object = nullptr;

        return *this;
    }
    //////////////////////////////////////////////////////////////////////////
    const base & base::operator = ( const base & _base )
    {
        if( m_object != nullptr )
        {
            json_decref( m_object );
        }

        m_object = _base.ptr();

        if( m_object != nullptr )
        {
            json_incref( m_object );
        }

        return *this;
    }
    //////////////////////////////////////////////////////////////////////////
    bool base::invalid() const
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
    void base::reset()
    {
        m_object = nullptr;
    }
    //////////////////////////////////////////////////////////////////////////
    bool base::operator == ( invalid_t ) const
    {
        return this->invalid();
    }
    //////////////////////////////////////////////////////////////////////////
    bool base::operator == ( const base & _base ) const
    {
        return m_object == _base.ptr();
    }
    //////////////////////////////////////////////////////////////////////////
    bool base::operator != ( const base & _base ) const
    {
        return !this->operator ==( _base );
    }
}
