#pragma once

#include "jpp/object.hpp"

#include <functional>

namespace jpp
{
    typedef size_t( *jpp_load_callback_t )(void* _buffer, size_t _buflen, void* _ud);
    typedef void* (*jpp_malloc_t)(size_t);
    typedef void (*jpp_free_t)(void*);
    typedef void (*jpp_error_t)(int line, int column, int position, const char* source, const char* text, void* _ud);

    object load( jpp_load_callback_t _callback, jpp_malloc_t _malloc, jpp_free_t _free, jpp_error_t _err, void * _ud );
}