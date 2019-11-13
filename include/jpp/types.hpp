#pragma once

#include <stddef.h>
#include <stdint.h>

struct json_t;

namespace jpp
{
    typedef bool jpp_bool_t;
    typedef int32_t jpp_int32_t;
    typedef uint32_t jpp_uint32_t;
    typedef long jpp_long_t;
    typedef float jpp_float_t;
    typedef double jpp_double_t;
    typedef long double jpp_long_double_t;
    typedef const char * jpp_string_t;

    typedef size_t jpp_size_t;
}