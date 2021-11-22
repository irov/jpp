#pragma once

#include "jpp/config.hpp"

#include <cstddef>
#include <cstdint>

struct json_t;

namespace jpp
{
    typedef bool jpp_bool_t;
    typedef int8_t jpp_int8_t;
    typedef uint8_t jpp_uint8_t;
    typedef int16_t jpp_int16_t;
    typedef uint16_t jpp_uint16_t;
    typedef int32_t jpp_int32_t;
    typedef uint32_t jpp_uint32_t;
    typedef int64_t jpp_int64_t;
    typedef uint64_t jpp_uint64_t;
    typedef float jpp_float_t;
    typedef double jpp_double_t;

    typedef size_t jpp_size_t;
}