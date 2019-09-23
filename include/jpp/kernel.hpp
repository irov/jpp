#pragma once

#include "jpp/object.hpp"

namespace jpp
{
    typedef jpp_size_t( *jpp_load_callback_t )(void * _buffer, jpp_size_t _buflen, void * _ud);
    typedef void * (*jpp_malloc_t)(jpp_size_t);
    typedef void (*jpp_free_t)(void *);
    typedef void (*jpp_error_t)(jpp_int32_t _line, jpp_int32_t _column, jpp_int32_t _position, jpp_string_t _source, jpp_string_t _text, void * _ud);

    object load( jpp_load_callback_t _callback, jpp_malloc_t _malloc, jpp_free_t _free, jpp_error_t _err, void * _ud );
}