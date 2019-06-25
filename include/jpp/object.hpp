#pragma once

#include "jpp/types.hpp"

namespace jpp
{
    struct borrowed_t
    {
    };

    class object
    {
    public:
        object();
        ~object();

    public:
        object(nullptr_t);
        explicit object(json_t* _object);
        object( json_t* _object, borrowed_t );
        object(const object & _object);
        object(object && _object);
        
    public:
        json_t* ptr() const;
        void reset();

    public:
        operator bool() const;
        operator int32_t() const;
        operator uint32_t() const;
        operator float() const;
        operator double() const;
        operator const char *() const;

    public:
        object operator [] ( const char* _name ) const;

    protected:
        json_t* m_object;
    };
}