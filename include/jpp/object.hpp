#pragma once

#include "jpp/base.hpp"
#include "jpp/cast.hpp"

#include <utility>

namespace jpp
{
    class object;

    template<class T>
    struct cast_object_extern
    {
        void operator()( const jpp::object & _obj, T * const _value ) const;
    };

    class object
        : public base
    {
    public:
        using base::base;
        using base::operator=;
        using base::operator==;

    public:
        typedef jpp_size_t size_type;

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
        size_type size() const;
        bool empty() const;

    public:
        jpp_bool_t exist( const char * _key, jpp::object * const _obj ) const;

    public:
        jpp_bool_t includes( const jpp::object & _obj ) const;

    public:
        object operator [] ( int32_t _index ) const;
        object operator [] ( uint32_t _index ) const;
        object operator [] ( const char * _key ) const;

        template<jpp_size_t I>
        object operator [] ( const char( &_key )[I] ) const
        {
            object o = this->operator []( _key );

            return o;
        }

        template<class T>
        object operator [] ( const T & _key ) const
        {
            const char * key_str = _key.c_str();

            object o = this->operator []( key_str );

            return o;
        }
    };
    //////////////////////////////////////////////////////////////////////////
    template<class T>
    void cast_object_internal::operator()( json_t * _j, T * const _value ) const
    {
        jpp::cast_object_extern<T>()(object( _j ), _value);
    }
    //////////////////////////////////////////////////////////////////////////
}
