#include "jpp/kernel.hpp"

#include "jansson.h"

#include <cstring>

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    const char * get_version()
    {
        const char * version = ::jansson_version_str();

        return version;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object make_invalid()
    {
        return jpp::object( jpp::detail::invalid );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object make_string( const char * _value )
    {
        json_t * j = ::json_string( _value );

        return jpp::object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object make_stringn( const char * _value, jpp_size_t _len )
    {
        json_t * j = ::json_stringn( _value, _len );

        return jpp::object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object make_integer( jpp_int64_t _value )
    {
        json_t * j = ::json_integer( _value );

        return jpp::object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object make_real( jpp_double_t _value )
    {
        json_t * j = ::json_real( _value );

        return jpp::object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object make_true()
    {
        json_t * j = ::json_true();

        return jpp::object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object make_false()
    {
        json_t * j = ::json_false();

        return jpp::object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object make_boolean( jpp_bool_t _value )
    {
        json_t * j = json_boolean( _value );

        return jpp::object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object make_null()
    {
        json_t * j = ::json_null();

        return jpp::object( j, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    const char * get_string_and_size( const jpp::object & _obj, jpp_size_t * const _size )
    {
        json_t * j = _obj.ptr();

        if( json_is_string( j ) == false )
        {
            return nullptr;
        }

        const char * value = ::json_string_value( j );
        size_t size = ::json_string_length( j );

        *_size = (jpp_size_t)size;

        return value;
    }
    //////////////////////////////////////////////////////////////////////////
    void set_object_seed( jpp_size_t _seed )
    {
        ::json_object_seed( _seed );
    }
    //////////////////////////////////////////////////////////////////////////
    void set_alloc_funcs( jpp_malloc_t _malloc, jpp_realloc_t _realloc, jpp_free_t _free )
    {
        ::json_set_alloc_funcs2( _malloc, _realloc, _free );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object make_object()
    {
        json_t * j = ::json_object();

        jpp::object o( j, detail::borrowed );

        return o;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::array make_array()
    {
        json_t * j = ::json_array();

        jpp::array a( j, detail::borrowed );

        return a;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object load( const void * _buffer, jpp_size_t _size, jpp_uint32_t _mode, jpp_error_t _error, void * _ud )
    {
        json_error_t er;
        json_t * jroot = ::json_loadb( (const char *)_buffer, _size, _mode, &er );

        if( jroot == nullptr )
        {
            if( _error != nullptr )
            {
                jpp::load_error_code_e error_code = ::json_error_code( &er ) == json_error_numeric_overflow
                    ? jpp::load_error_code_e::numeric_overflow
                    : jpp::load_error_code_e::invalid;

                (*_error)(er.line, er.column, er.position, er.source, er.text, error_code, _ud);
            }

            return jpp::object( detail::invalid );
        }

        return jpp::object( jroot, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object load( jpp_load_callback_t _callback, jpp_uint32_t _mode, jpp_error_t _error, void * _ud )
    {
        json_error_t er;
        json_t * jroot = ::json_load_callback( _callback, _ud, _mode, &er );

        if( jroot == nullptr )
        {
            if( _error != nullptr )
            {
                jpp::load_error_code_e error_code = ::json_error_code( &er ) == json_error_numeric_overflow
                    ? jpp::load_error_code_e::numeric_overflow
                    : jpp::load_error_code_e::invalid;

                (*_error)(er.line, er.column, er.position, er.source, er.text, error_code, _ud);
            }

            return jpp::object( detail::invalid );
        }

        return jpp::object( jroot, detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    namespace Detail
    {
        //////////////////////////////////////////////////////////////////////////
        struct dump_state
        {
            jpp_dump_callback_t callback;
            void * user_data;
            jpp_size_t indent;
            jpp_size_t pending_spaces;
            jpp_bool_t line_start;
        };
        //////////////////////////////////////////////////////////////////////////
        static int __dump_emit( dump_state * _state, const char * _buffer, jpp_size_t _size )
        {
            if( _size == 0 )
            {
                return 0;
            }

            return (*_state->callback)( _buffer, _size, _state->user_data );
        }
        //////////////////////////////////////////////////////////////////////////
        static int __dump_emit_spaces( dump_state * _state, jpp_size_t _count )
        {
            static const char spaces[] = "                                                                ";

            while( _count != 0 )
            {
                jpp_size_t chunk_size = _count < sizeof( spaces ) - 1 ? _count : sizeof( spaces ) - 1;

                if( __dump_emit( _state, spaces, chunk_size ) != 0 )
                {
                    return -1;
                }

                _count -= chunk_size;
            }

            return 0;
        }
        //////////////////////////////////////////////////////////////////////////
        static int __dump_callback( const char * _buffer, jpp_size_t _size, void * _ud )
        {
            dump_state * state = static_cast<dump_state *>(_ud);
            jpp_size_t position = 0;

            while( position != _size )
            {
                if( state->line_start == true )
                {
                    while( position != _size && _buffer[position] == ' ' )
                    {
                        state->pending_spaces += 1;
                        position += 1;
                    }

                    if( position == _size )
                    {
                        return 0;
                    }

                    for( jpp_size_t index = 0; index != state->pending_spaces; ++index )
                    {
                        if( __dump_emit_spaces( state, state->indent ) != 0 )
                        {
                            return -1;
                        }
                    }

                    state->pending_spaces = 0;
                    state->line_start = false;
                }

                const void * newline_memory = std::memchr( _buffer + position, '\n', _size - position );

                if( newline_memory == nullptr )
                {
                    return __dump_emit( state, _buffer + position, _size - position );
                }

                const char * newline = static_cast<const char *>(newline_memory);
                jpp_size_t line_size = (jpp_size_t)(newline - (_buffer + position)) + 1;

                if( __dump_emit( state, _buffer + position, line_size ) != 0 )
                {
                    return -1;
                }

                position += line_size;
                state->line_start = true;
            }

            return 0;
        }
        //////////////////////////////////////////////////////////////////////////
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t dump( const jpp::object & _obj, jpp_size_t _indent, jpp_dump_callback_t _callback, void * _ud )
    {
        Detail::dump_state state;
        state.callback = _callback;
        state.user_data = _ud;
        state.indent = _indent;
        state.pending_spaces = 0;
        state.line_start = true;

        int writebytes = ::json_dump_callback( _obj.ptr(), &Detail::__dump_callback, &state, JSON_INDENT( 1 ) | JSON_ENCODE_ANY );

        if( writebytes == -1 )
        {
            return false;
        }

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t dump_compact( const jpp::object & _obj, jpp_dump_callback_t _callback, void * _ud )
    {
        int writebytes = ::json_dump_callback( _obj.ptr(), _callback, _ud, JSON_COMPACT | JSON_ENCODE_ANY );

        if( writebytes == -1 )
        {
            return false;
        }

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    static int __json_object_update( json_t * _object, json_t * _other, jpp_bool_t _recursive )
    {
        const char * key;
        json_t * value;

        json_object_foreach( _other, key, value )
        {
            json_t * j = ::json_object_get( _object, key );

            if( json_is_object( j ) && json_is_object( value ) && _recursive == true )
            {
                if( __json_object_update( j, value, _recursive ) == -1 )
                {
                    return -1;
                }
            }
            else
            {
                if( ::json_object_set_nocheck( _object, key, value ) == -1 )
                {
                    return -1;
                }
            }
        }

        return 0;
    }
    //////////////////////////////////////////////////////////////////////////
    static int __json_object_update_with_array( json_t * _object, json_t * _other, jpp_bool_t _recursive )
    {
        const char * key;
        json_t * value;

        json_object_foreach( _other, key, value )
        {
            json_t * j = ::json_object_get( _object, key );

            if( json_is_object( j ) && json_is_object( value ) && _recursive == true )
            {
                if( __json_object_update_with_array( j, value, _recursive ) == -1 )
                {
                    return -1;
                }
            }
            else if( json_is_array( j ) && json_is_array( value ) )
            {
                if( ::json_array_extend( j, value ) == -1 )
                {
                    return -1;
                }
            }
            else
            {
                if( ::json_object_set_nocheck( _object, key, value ) == -1 )
                {
                    return -1;
                }
            }
        }

        return 0;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::object copy( const jpp::object & _obj )
    {
        json_t * j = _obj.ptr();

        if( j == nullptr )
        {
            return jpp::make_object();
        }

        json_t * jcopy = ::json_deep_copy( j );

        return jpp::object( jcopy, jpp::detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp::array copy( const jpp::array & _array )
    {
        json_t * j = _array.ptr();

        if( j == nullptr )
        {
            return jpp::make_array();
        }

        json_t * jcopy = ::json_deep_copy( j );

        return jpp::array( jcopy, jpp::detail::borrowed );
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t merge( const jpp::object & _obj, const jpp::object & _merge, jpp_bool_t _copy, jpp_bool_t _recursive, merge_mode_e _mode )
    {
        json_t * jb = _obj.ptr();
        json_t * jm = _merge.ptr();

        if( _copy == true )
        {
            jm = ::json_deep_copy( jm );
        }

        jpp_bool_t successful = true;

        switch( _mode )
        {
        case merge_mode_e::update:
            {
                if( !json_is_object( jb ) || !json_is_object( jm ) )
                {
                    successful = false;
                    break;
                }

                if( __json_object_update( jb, jm, _recursive ) == -1 )
                {
                    successful = false;
                }
            }break;
        case merge_mode_e::update_with_array:
            {
                if( !json_is_object( jb ) || !json_is_object( jm ) )
                {
                    successful = false;
                    break;
                }

                if( __json_object_update_with_array( jb, jm, _recursive ) == -1 )
                {
                    successful = false;
                }
            }break;
        case merge_mode_e::existing:
            {
                if( ::json_object_update_existing( jb, jm ) == -1 )
                {
                    successful = false;
                }
            }break;
        case merge_mode_e::missing:
            {
                if( ::json_object_update_missing( jb, jm ) == -1 )
                {
                    successful = false;
                }
            }break;
        default:
            successful = false;
            break;
        }

        if( _copy == true )
        {
            ::json_decref( jm );
        }

        return successful;
    }
    //////////////////////////////////////////////////////////////////////////
    static jpp_bool_t __json_array_once( json_t * j );
    static jpp_bool_t __json_object_once( json_t * j );
    //////////////////////////////////////////////////////////////////////////
    static jpp_bool_t __json_array_once( json_t * j )
    {
        if( j->refcount != 1 )
        {
            return false;
        }

        size_t index;
        json_t * value;

        json_array_foreach( j, index, value )
        {
            if( json_is_object( value ) == true )
            {
                if( __json_object_once( value ) == false )
                {
                    return false;
                }
            }
            else if( json_is_array( value ) )
            {
                if( __json_array_once( value ) == false )
                {
                    return false;
                }
            }
            else if( json_is_string( value ) )
            {
                if( value->refcount != 1 )
                {
                    return false;
                }
            }
        }

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    static jpp_bool_t __json_object_once( json_t * j )
    {
        if( j->refcount == (size_t)-1 )
        {
            return true;
        }

        if( j->refcount != 1 )
        {
            return false;
        }

        const char * key;
        json_t * value;

        json_object_foreach( j, key, value )
        {
            if( json_is_object( value ) == true )
            {
                if( __json_object_once( value ) == false )
                {
                    return false;
                }
            }
            else if( json_is_array( value ) )
            {
                if( __json_array_once( value ) == false )
                {
                    return false;
                }
            }
            else if( json_is_string( value ) )
            {
                if( value->refcount != 1 )
                {
                    return false;
                }
            }
        }

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    jpp_bool_t once( const jpp::object & _obj )
    {
        json_t * j = _obj.ptr();

        jpp_bool_t result = __json_object_once( j );

        return result;
    }
    //////////////////////////////////////////////////////////////////////////
}
