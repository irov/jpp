#pragma once

#include "jpp/base.hpp"

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

    public:
        operator jpp_bool_t() const;
        operator jpp_int32_t() const;
        operator jpp_uint32_t() const;
        operator jpp_float_t() const;
        operator jpp_double_t() const;
        operator jpp_string_t () const;

    public:
        template<class T>
        operator T () const
        {
            T value;
            jpp::cast_object<T>()(*this, value);
            return value;
        }

    public:
        json_t * get( jpp_string_t _key ) const;
        jpp_bool_t get( jpp_string_t _key, jpp_bool_t _default ) const;
        jpp_int32_t get( jpp_string_t _key, jpp_int32_t _default ) const;
        jpp_uint32_t get( jpp_string_t _key, jpp_uint32_t _default ) const;
        jpp_float_t get( jpp_string_t _key, jpp_float_t _default ) const;
        jpp_double_t get( jpp_string_t _key, jpp_double_t _default ) const;
        jpp_string_t get( jpp_string_t _key, jpp_string_t _default ) const;

    public:
        template<class T>
        T get( jpp_string_t _key, const T & _default ) const
        {
            json_t * j = this->get( _key );

            if( j == nullptr )
            {
                return _default;
            }

            T value;
            jpp::cast_object<T>()(object( j ), value);
            return value;
        }

    public:
        size_t size() const;

    public:
        bool exist( jpp_string_t _key ) const;

        object operator [] ( jpp_string_t _key ) const;
    };    
}