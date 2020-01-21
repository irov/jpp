#include "jpp/kernel.hpp"

#include "jansson.h"

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    object make_string( const char * value )
    {
        return jpp::object( json_string( value ), detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    object make_stringn( const char * value, size_t len )
    {
        return jpp::object( json_stringn( value, len ), detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    object make_integer( jpp_long_t value )
    {
        return jpp::object( json_integer( value ), detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    object make_real( jpp_double_t value )
    {
        return jpp::object( json_real( value ), detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    object make_true()
    {
        return jpp::object( json_true(), detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    object make_false()
    {
        return jpp::object( json_false(), detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    object make_boolean( jpp_bool_t _value )
    {
        return jpp::object( json_boolean( _value ), detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    object make_null()
    {
        return jpp::object( json_null(), detail::borrowed );
    }
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
    static int __json_object_update( json_t * object, json_t * other )
    {
        const char * key;
        json_t * value;

        json_object_foreach( other, key, value )
        {
            json_t * j = json_object_get( object, key );

            if( json_is_object( j ) && json_is_object( value ) )
            {
                if( __json_object_update( j, value ) == -1 )
                {
                    return -1;
                }
            }
            else
            {
                if( json_object_set_nocheck( object, key, value ) == -1 )
                {
                    return -1;
                }
            }
        }

        return 0;
    }
    //////////////////////////////////////////////////////////////////////////
    static int __json_object_update_with_array( json_t * object, json_t * other )
    {
        const char * key;
        json_t * value;

        json_object_foreach( other, key, value )
        {
            json_t * j = json_object_get( object, key );

            if( json_is_object( j ) && json_is_object( value ) )
            {
                if( __json_object_update_with_array( j, value ) == -1 )
                {
                    return -1;
                }
            }
            else if( json_is_array( j ) && json_is_array( value ) )
            {
                if( json_array_extend( j, value ) == -1 )
                {
                    return -1;
                }
            }
            else
            {
                if( json_object_set_nocheck( object, key, value ) == -1 )
                {
                    return -1;
                }
            }
        }

        return 0;
    }
    //////////////////////////////////////////////////////////////////////////
    bool merge( const object & _obj, const object & _merge, merge_mode_e _mode )
    {
        json_t * jb = _obj.ptr();
        json_t * jm = _merge.ptr();

        switch( _mode )
        {
        case merge_mode_e::update:
            {
                if( !json_is_object( jb ) || !json_is_object( jm ) )
                {
                    return false;
                }

                if( __json_object_update( jb, jm ) == -1 )
                {
                    return false;
                }
            }break;
        case merge_mode_e::update_with_array:
            {
                if( !json_is_object( jb ) || !json_is_object( jm ) )
                {
                    return false;
                }

                if( __json_object_update_with_array( jb, jm ) == -1 )
                {
                    return false;
                }
            }break;
        case merge_mode_e::existing:
            {
                if( json_object_update_existing( jb, jm ) == -1 )
                {
                    return false;
                }
            }break;
        case merge_mode_e::missing:
            {
                if( json_object_update_missing( jb, jm ) == -1 )
                {
                    return false;
                }
            }break;
        default:
            return false;
            break;
        }

        return true;
    }
}