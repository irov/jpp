#include "jpp/object_iterator.hpp"

#include "jansson.h"

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    object_iterator::object_iterator( const object_iterator& _it )
    {
        m_object = _it.m_object;
        m_iter = _it.m_iter;
    }
    //////////////////////////////////////////////////////////////////////////
    object_iterator::object_iterator( json_t* _obj )
        : m_object( _obj )
        , m_iter( json_object_iter( _obj ) )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    object_iterator::object_iterator( json_t* _obj, object_iterator_end_t )
        : m_object( _obj )
        , m_iter( nullptr )
    {

    }
    //////////////////////////////////////////////////////////////////////////
    object_iterator::~object_iterator()
    {
    }
    //////////////////////////////////////////////////////////////////////////
    bool object_iterator::operator == ( const object_iterator& _it ) const
    {
        return m_iter == _it.m_iter;
    }
    //////////////////////////////////////////////////////////////////////////
    bool object_iterator::operator != ( const object_iterator& _it ) const
    {
        return !this->operator ==( _it );
    }
    //////////////////////////////////////////////////////////////////////////
    object_iterator& object_iterator::operator ++ ()
    {
        m_iter = json_object_iter_next( m_object, m_iter );

        return *this;
    }
    //////////////////////////////////////////////////////////////////////////
    object_iterator object_iterator::operator ++ ( int )
    {
        object_iterator tmp = *this;
        ++* this;

        return tmp;
    }
    //////////////////////////////////////////////////////////////////////////
    object_iterator_pair object_iterator::operator -> () const
    {
        return {json_object_iter_key( m_iter ), object( json_object_iter_value( m_iter ) )};
    }
    //////////////////////////////////////////////////////////////////////////
    object_iterator_pair object_iterator::operator * () const
    {
        return {json_object_iter_key( m_iter ), object( json_object_iter_value( m_iter ) )};
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object_iterator begin( const jpp::object& _object )
    {
        return jpp::object_iterator( _object.ptr() );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object_iterator end( const jpp::object& _object )
    {
        return jpp::object_iterator( _object.ptr(), jpp::object_iterator_end_t() );
    }
}