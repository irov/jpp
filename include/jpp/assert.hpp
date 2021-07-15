#pragma once

#include "jpp/config.hpp"

#ifndef JPP_ASSERT
#   if !defined(JPP_DISABLE_ASSERT) && defined(_DEBUG)
#       include <assert.h>
#       define JPP_ASSERT(X) assert(X)
#   else
#       define JPP_ASSERT(X)
#   endif
#endif