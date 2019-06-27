#include "jpp/kernel.hpp"

#include "jansson.h"

namespace jpp
{
    object load( jpp_load_callback_t _callback, jpp_malloc_t _malloc, jpp_free_t _free, jpp_error_t _error, void* _ud )
    {
        json_set_alloc_funcs( _malloc, _free );

        json_error_t er;
        json_t* jroot = json_load_callback( _callback, _ud, 0, &er );

        if( jroot == nullptr )
        {
            (*_error)(er.line, er.column, er.position, er.source, er.text, _ud);

            return object( detail::invalid );
        }

        return object( jroot, detail::borrowed );
    }
}