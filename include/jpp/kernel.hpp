#pragma once

#include "jpp/object.hpp"

#include <functional>

namespace jpp
{
    typedef size_t( *jpp_load_callback_t )(void* _buffer, size_t _buflen, void* _data);
    typedef void* (*jpp_malloc_t)(size_t);
    typedef void (*jpp_free_t)(void*);

    object load( jpp_load_callback_t _callback, jpp_malloc_t _malloc, jpp_free_t _free, void * _ud );
}