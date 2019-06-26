#include "jpp/kernel.hpp"

#include "jansson.h"

namespace jpp
{
    object load( jpp_load_callback_t _callback, jpp_malloc_t _malloc, jpp_free_t _free, void* _ud )
    {
        json_set_alloc_funcs( _malloc, _free );

        json_error_t error;
        json_t* jroot = json_load_callback( _callback, _ud, 0, &error );

        if( jroot == nullptr )
        {
            return object( detail::invalid );
        }

        return object( jroot, detail::borrowed );
    }
}