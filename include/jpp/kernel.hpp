#pragma once

#include "jpp/object.hpp"
#include "jpp/array.hpp"

#include <tuple>

namespace jpp
{
    typedef jpp_size_t( *jpp_load_callback_t )(void * _buffer, jpp_size_t _size, void * _ud);
    typedef int (*jpp_dump_callback_t)(const char * _buffer, jpp_size_t _size, void * _ud);
    typedef void * (*jpp_malloc_t)(jpp_size_t);
    typedef void (*jpp_free_t)(void *);
    typedef void (*jpp_error_t)(jpp_int32_t _line, jpp_int32_t _column, jpp_int32_t _position, jpp_string_t _source, jpp_string_t _text, void * _ud);

    object make_string( const char * value );
    object make_stringn( const char * value, size_t len );
    object make_integer( jpp_long_t value );
    object make_real( jpp_double_t value );
    object make_true();
    object make_false();
    object make_boolean( jpp_bool_t _value );
    object make_null();
    object make_object();
    array make_array();

    template<class ... Args>
    array make_tuple( Args && ... _args )
    {
        array a = make_array();

        (a.push_back( _args ), ...);

        return a;
    }

    void set_object_seed( size_t _seed );
    void set_alloc_funcs( jpp_malloc_t _malloc, jpp_free_t _free );

    object load( const void * _buffer, size_t _size, jpp_error_t _err, void * _ud );
    object load( jpp_load_callback_t _callback, jpp_error_t _err, void * _ud );
    jpp_bool_t dump( const jpp::object & _obj, jpp_dump_callback_t _callback, void * _ud );
    jpp_bool_t dump_compact( const jpp::object & _obj, jpp_dump_callback_t _callback, void * _ud );

    enum class merge_mode_e
    {
        update,
        update_with_array,
        existing,
        missing
    };

    object copy( const jpp::object & _obj );
    jpp_bool_t merge( const jpp::object & _obj, const jpp::object & _merge, jpp_bool_t _copy, jpp_bool_t _recursive, merge_mode_e _mode );
    jpp_bool_t once( const jpp::object & _obj );
}