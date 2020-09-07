#pragma once

#include "jpp/base.hpp"
#include "jpp/cast.hpp"

#include <utility>

namespace jpp
{
    class object
        : public base
    {
    public:
        using base::base;
        using base::operator=;
        using base::operator==;

    public:
        static const object & none();

    public:
        template<class T>
        operator T () const
        {
            T value;
            jpp::cast_object_internal()(m_object, &value);

            return std::move( value );
        }

    protected:
        operator json_t * () const = delete;

    public:
        object get( const char * _key ) const;

    public:
        const char * get( const char * _key, const char * _default ) const
        {
            const char * value = this->get<const char *>( _key, _default );

            return value;
        }

        template<class T>
        T get( const char * _key, T _default ) const
        {
            if( m_object == nullptr )
            {
                return _default;
            }

            json_t * j = this->get_( _key );

            if( j == nullptr )
            {
                return _default;
            }

            T value;
            jpp::cast_object_internal()(j, &value);

            return std::move( value );
        }

    public:
        template<class T>
        void set( const char * _key, T _value )
        {
            json_t * j = cast_object_internal()(_value);

            this->set_( _key, j );
        }

    public:
        jpp_bool_t operator == ( const jpp::object & _value ) const;
        jpp_bool_t operator == ( const char * _value ) const;

        template<class T>
        jpp_bool_t operator == ( T _value ) const
        {
            T value;
            jpp::cast_object_internal()(m_object, &value);

            jpp_bool_t successful = (value == _value);

            return successful;
        }

    public:
        size_t size() const;

    public:
        jpp_bool_t exist( const char * _key, jpp::object * _obj ) const;

    public:
        jpp_bool_t includes( const jpp::object & _obj ) const;

    public:
        object operator [] ( int32_t _index ) const;
        object operator [] ( uint32_t _index ) const;
        object operator [] ( const char * _key ) const;

    public:
        template<class T>
        object operator [] ( const T & _key ) const
        {
            const char * str_key = _key.c_str();

            object j = this->operator []( str_key );

            return std::move( j );
        }
    };
}