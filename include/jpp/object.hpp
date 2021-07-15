#pragma once

#include "jpp/base.hpp"
#include "jpp/cast.hpp"
#include "jpp/internal.hpp"
#include "jpp/mpl.hpp"

#include <utility>
#include <type_traits>

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    class object;
    //////////////////////////////////////////////////////////////////////////
    template<class T>
    struct cast_object_extern
    {
        void operator()( const jpp::object & _obj, T * const _value ) const;
    };
    //////////////////////////////////////////////////////////////////////////
    template<class T>
    struct extract_object_extern
    {
        jpp::object operator()( const T & _value ) const;
    };
    //////////////////////////////////////////////////////////////////////////
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
        static const jpp::object & none();

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
        jpp::object update( const char * _key, const jpp::object & _default );

    public:
        jpp::object get( const char * _key ) const;

    public:
        const char * get( const char * _key, const char * _default ) const;

        template<class T>
        T get( const char * _key, const T & _default ) const
        {
            if( m_object == nullptr )
            {
                return _default;
            }

            json_t * j = this->get_( _key );

            if( j == nullptr || jpp::is_null( j ) == true )
            {
                return _default;
            }

            T value;
            jpp::cast_object_internal()(j, &value);

            return std::move( value );
        }

    public:
        template<class T>
        void set( const char * _key, const T & _value )
        {
            json_t * j = jpp::cast_object_internal()(_value);

            this->set_( _key, j );
        }

        template<class K, class T, typename std::enable_if<jpp::mpl::has_c_str<K>::value, T>::type * = nullptr>
        void set( const K & _key, const T & _value )
        {
            const char * key_str = _key.c_str();

            json_t * j = jpp::cast_object_internal()(_value);

            this->set_( key_str, j );
        }

    public:
        template<class T>
        const object & operator = ( const T & _value )
        {
            json_t * j = jpp::cast_object_internal()(_value);

            this->reset_( j );

            return *this;
        }

    public:
        jpp_bool_t operator == ( const jpp::object & _value ) const;
        jpp_bool_t operator == ( const char * _value ) const;

        template<class T>
        jpp_bool_t operator == ( const T & _value ) const
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
        jpp::object operator [] ( const char * _key ) const;

        template<class K, typename std::enable_if<jpp::mpl::has_c_str<K>::value, K>::type * = nullptr>
        jpp::object operator [] ( const K & _key ) const
        {
            const char * key_str = _key.c_str();

            jpp::object o = this->operator []( key_str );

            return o;
        }

    protected:
        void set_( const char * _key, json_t * _value );
        json_t * get_( const char * _key ) const;
    };
    //////////////////////////////////////////////////////////////////////////
    template<class T>
    void cast_object_internal::operator()( json_t * _j, T * const _value ) const
    {
        jpp::cast_object_extern<T>()(jpp::object( _j ), _value);
    }
    //////////////////////////////////////////////////////////////////////////
    template<class T>
    json_t * cast_object_internal::operator()( const T & _value ) const
    {
        jpp::object o = jpp::extract_object_extern<T>()(_value);

        json_t * j = o.pop();

        return j;
    }
    //////////////////////////////////////////////////////////////////////////
}