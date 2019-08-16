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
        object operator [] ( const char * _name ) const;
    };
}