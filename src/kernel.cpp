#include "jpp/kernel.hpp"

#include "jansson.h"

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    void set_object_seed( size_t _seed )
    {
        json_object_seed( _seed );
    }
    //////////////////////////////////////////////////////////////////////////
    void set_alloc_funcs( jpp_malloc_t _malloc, jpp_free_t _free )
    {
        json_set_alloc_funcs( _malloc, _free );
    }
    //////////////////////////////////////////////////////////////////////////
    object load( const void * _buffer, size_t _size, jpp_error_t _error, void * _ud )
    {
        json_error_t er;
        json_t * jroot = json_loadb( (const char *)_buffer, _size, 0, &er );

        if( jroot == nullptr )
        {
            if( _error != nullptr )
            {
                (*_error)(er.line, er.column, er.position, er.source, er.text, _ud);
            }

            return object( detail::invalid );
        }

        return object( jroot, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    object load( jpp_load_callback_t _callback, jpp_error_t _error, void * _ud )
    {
        json_error_t er;
        json_t * jroot = json_load_callback( _callback, _ud, 0, &er );

        if( jroot == nullptr )
        {
            if( _error != nullptr )
            {
                (*_error)(er.line, er.column, er.position, er.source, er.text, _ud);
            }

            return object( detail::invalid );
        }

        return object( jroot, detail::borrowed );
    }
}