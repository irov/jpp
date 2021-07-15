#pragma once

#include "jpp/config.hpp"

#include <cstddef>
#include <cstdint>

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
    typedef char * jpp_mutable_string_t;

    typedef size_t jpp_size_t;
}