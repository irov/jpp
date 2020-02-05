#include "jpp/array_iterator.hpp"

#include "jansson.h"

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    array_iterator::array_iterator( const array_iterator & _it )
        : m_object( _it.m_object )
        , m_iter( _it.m_iter )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    array_iterator::array_iterator( json_t * _obj, jpp_size_t _iter )
        : m_object( _obj )
        , m_iter( _iter )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    array_iterator::~array_iterator()
    {
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t array_iterator::operator == ( const array_iterator & _it ) const
    {
        return m_iter == _it.m_iter;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t array_iterator::operator != ( const array_iterator & _it ) const
    {
        return !this->operator ==( _it );
    }
    //////////////////////////////////////////////////////////////////////////
    array_iterator & array_iterator::operator ++ ()
    {
        ++m_iter;

        return *this;
    }
    //////////////////////////////////////////////////////////////////////////
    array_iterator array_iterator::operator ++ ( int )
    {
        array_iterator tmp = *this;
        ++ * this;

        return tmp;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::conversion array_iterator::operator -> () const
    {
        return jpp::conversion( json_array_get( m_object, m_iter ) );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::conversion array_iterator::operator * () const
    {
        return jpp::conversion( json_array_get( m_object, m_iter ) );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::array_iterator begin( const jpp::array & _array )
    {
        return jpp::array_iterator( _array.ptr(), 0 );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::array_iterator end( const jpp::array & _array )
    {
        return jpp::array_iterator( _array.ptr(), _array.size() );
    }
}