#pragma once

#include "jpp/config.hpp"

#ifndef JPP_STRCMP
#   include <string.h>
#   define JPP_STRCMP(a, b) ::strcmp((a), (b))
#endif