#pragma once

#include "jpp/base.hpp"
#include "jpp/check.hpp"
#include "jpp/cast.hpp"
#include "jpp/internal.hpp"
#include "jpp/mpl.hpp"
#include "jpp/extract.hpp"
#include "jpp/extract_safe.hpp"

#include <utility>
#include <type_traits>
#include <functional>

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    class object;
    //////////////////////////////////////////////////////////////////////////
    template<class T>
    struct check_object_extern
    {
        bool operator()( const jpp::object & _obj, T * const ) const;
    };
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
        using base::operator!=;

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

            return value;
        }

    protected:
        operator json_t * () const = delete;

    public:
        template<class T>
        jpp::object update( const char * _key, const T & _default )
        {
            json_t * j = this->get_( _key );

            if( j != nullptr && jpp::is_null( j ) == false )
            {
                return jpp::object( j );
            }

            json_t * j_default = jpp::cast_object_internal()(_default);

            this->set_( _key, j_default );

            return jpp::object( j_default );
        }

    public:
        jpp::extract_safe get( const char * _key ) const;

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

            return value;
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

            this->set( key_str, _value );
        }

    public:
        template<class T>
        jpp::object emplace( const char * _key, const T & _value )
        {
            json_t * j = jpp::cast_object_internal()(_value);

            this->set_( _key, j );

            return jpp::object( j );
        }

        template<class K, class T, typename std::enable_if<jpp::mpl::has_c_str<K>::value, T>::type * = nullptr>
        jpp::object emplace( const K & _key, const T & _value )
        {
            const char * key_str = _key.c_str();

            return this->emplace( key_str, _value );
        }

    public:
        jpp::object get_or_create( const char * _key, const std::function<jpp::object()> & _creator );

    public:
        template<class K>
        jpp::object get_or_create( const K & _key, const std::function<jpp::object()> & _creator ) = delete;

        template<class K, typename std::enable_if<jpp::mpl::has_c_str<K>::value, K>::type * = nullptr>
        jpp::object get_or_create( const K & _key, const std::function<jpp::object()> & _creator )
        {
            const char * key_str = _key.c_str();

            return this->get_or_create( key_str, _creator );
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
        jpp::extract operator [] ( const char * _key ) const;

        template<class K, typename std::enable_if<jpp::mpl::has_c_str<K>::value, K>::type * = nullptr>
        jpp::extract operator [] ( const K & _key ) const
        {
            const char * key_str = _key.c_str();

            jpp::extract o = this->operator []( key_str );

            return o;
        }

    protected:
        void set_( const char * _key, json_t * _value );
        json_t * get_( const char * _key ) const;
    };
    //////////////////////////////////////////////////////////////////////////
    template<class T>
    bool check_object_internal::operator()( json_t * _j, T * const _value ) const
    {
        bool result = jpp::check_object_extern<T>()(jpp::object( _j ), _value);

        return result;
    }
    //////////////////////////////////////////////////////////////////////////
    template<class T>
    void cast_object_internal::operator()( json_t * _j, T * const _value ) const
    {
        if( _j == nullptr )
        {
            return;
        }

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