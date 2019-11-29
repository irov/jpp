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
    object make_object()
    {
        json_t * j = json_object();
        object o( j, detail::borrowed );

        return o;
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
    //////////////////////////////////////////////////////////////////////////
    bool dump( const object & _obj, jpp_dump_callback_t _callback, void * _ud )
    {
        int writebytes = json_dump_callback( _obj.ptr(), _callback, _ud, JSON_INDENT( 2 ) );

        if( writebytes == -1 )
        {
            return false;
        }

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    void merge( const object & _obj, const object & _merge, merge_mode_e _mode )
    {
        json_t * jb = _obj.ptr();
        json_t * jm = _merge.ptr();

        switch( _mode )
        {
        case merge_mode_e::update:
            {
                json_object_update( jb, jm );
            }break;
        case merge_mode_e::existing:
            {
                json_object_update_existing( jb, jm );
            }break;
        case merge_mode_e::missing:
            {
                json_object_update_missing( jb, jm );
            }break;
        default:
            break;
        }
    }
}