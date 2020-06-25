#pragma once

#include "jpp/base.hpp"

#include <utility>

namespace jpp
{
    class object;

    template<class T>
    struct cast_object
    {
        void operator()( const jpp::object & _obj, T & _value ) const;
    };

    class object
        : public base
    {
    public:
        using base::base;
        using base::operator=;
        using base::operator==;

    public:
        operator jpp_bool_t() const;
        operator jpp_int32_t() const;
        operator jpp_uint32_t() const;
        operator jpp_long_t() const;
        operator jpp_float_t() const;
        operator jpp_double_t() const;
        operator jpp_long_double_t() const;
        operator jpp_string_t () const;

    public:
        static const object & none();

    public:
        template<class T>
        operator T () const
        {
            T value;
            jpp::cast_object<T>()(*this, value);
            return std::move( value );
        }

    protected:
        operator json_t * () const = delete;

    public:
        object get( jpp_string_t _key ) const;
        jpp_bool_t get( jpp_string_t _key, jpp_bool_t _default ) const;
        jpp_int32_t get( jpp_string_t _key, jpp_int32_t _default ) const;
        jpp_uint32_t get( jpp_string_t _key, jpp_uint32_t _default ) const;
        jpp_long_t get( jpp_string_t _key, jpp_long_t _default ) const;
        jpp_float_t get( jpp_string_t _key, jpp_float_t _default ) const;
        jpp_double_t get( jpp_string_t _key, jpp_double_t _default ) const;
        jpp_long_double_t get( jpp_string_t _key, jpp_long_double_t _default ) const;
        jpp_string_t get( jpp_string_t _key, jpp_string_t _default ) const;

    public:
        template<class T>
        T get( jpp_string_t _key, const T & _default ) const
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
            jpp::cast_object<T>()(object( j ), value);

            return std::move( value );
        }

    public:
        template<class T>
        typename std::remove_reference<T>::type get( jpp_string_t _key, T && _default ) const
        {
            typedef typename std::remove_reference<T>::type RRT;

            if( m_object == nullptr )
            {
                return std::forward<RRT &&>( _default );
            }

            json_t * j = this->get_( _key );

            if( j == nullptr )
            {
                return std::forward<RRT &&>( _default );
            }

            RRT value;
            jpp::cast_object<RRT>()(object( j ), value);

            return std::move( value );
        }

    public:
        void set( jpp_string_t _key, const object & _obj );
        void set( jpp_string_t _key, object && _obj );
        void set( jpp_string_t _key, jpp_bool_t _value );
        void set( jpp_string_t _key, jpp_int32_t _value );
        void set( jpp_string_t _key, jpp_uint32_t _value );
        void set( jpp_string_t _key, jpp_long_t _value );
        void set( jpp_string_t _key, jpp_float_t _value );
        void set( jpp_string_t _key, jpp_double_t _value );
        void set( jpp_string_t _key, jpp_long_double_t _value );
        void set( jpp_string_t _key, jpp_string_t _value );

    public:
        jpp_bool_t operator == ( jpp_bool_t _value ) const;
        jpp_bool_t operator == ( jpp_int32_t _value ) const;
        jpp_bool_t operator == ( jpp_uint32_t _value ) const;
        jpp_bool_t operator == ( jpp_long_t _value ) const;
        jpp_bool_t operator == ( jpp_float_t _value ) const;
        jpp_bool_t operator == ( jpp_double_t _value ) const;
        jpp_bool_t operator == ( jpp_long_double_t _value ) const;
        jpp_bool_t operator == ( jpp_string_t _value ) const;

    public:
        size_t size() const;

    public:
        jpp_bool_t exist( jpp_string_t _key, jpp::object * _obj ) const;

    public:
        jpp_bool_t includes( const jpp::object & _obj ) const;

    public:
        object operator [] ( jpp_string_t _key ) const;
        object operator [] ( jpp_mutable_string_t _key ) const;

    public:
        template<class T>
        object operator [] ( const T & _key ) const
        {
            jpp_string_t str_key = _key.c_str();

            object j = this->operator []( str_key );

            return std::move( j );
        }
    };
}