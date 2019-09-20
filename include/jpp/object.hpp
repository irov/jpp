#pragma once

#include "jpp/base.hpp"

namespace jpp
{
    class object
        : public base
    {
    public:
        using base::base;
        using base::operator=;

    public:
        operator bool() const;
        operator int32_t() const;
        operator uint32_t() const;
        operator float() const;
        operator double() const;
        operator const char * () const;

    public:
        template<class T>
        operator T () const
        {
            T value;
            jpp::cast_object<T>()(*this, value);
            return value;
        }

    public:
        json_t * get( const char * _key ) const;
        bool get( const char * _key, bool _default ) const;
        int32_t get( const char * _key, int32_t _default ) const;
        uint32_t get( const char * _key, uint32_t _default ) const;
        float get( const char * _key, float _default ) const;
        double get( const char * _key, double _default ) const;
        const char * get( const char * _key, const char * _default ) const;

    public:
        template<class T>
        T get( const char * _key, const T & _default ) const
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
        object operator [] ( const char * _key ) const;
    };

    template<class T>
    struct cast_object
    {
        void operator()( const jpp::object & _obj, T & _value ) const;
    };
}