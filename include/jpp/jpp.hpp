#pragma once

#include <cstddef>

struct json_t;

namespace jpp
{
    class object
    {
    public:
        object();
        ~object();

    public:
        object(nullptr_t);
        explicit object(json_t* _object);
        object(const object & _object);
        object(object && _object);
        
    public:
        json_t* get() const;
        void reset();

    protected:
        json_t* m_object;
    };
}