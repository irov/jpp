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
    typedef void (*jpp_error_t)(jpp_int32_t _line, jpp_int32_t _column, jpp_int32_t _position, const char * _source, const char * _text, void * _ud);

    jpp::object make_string( const char * value );
    jpp::object make_stringn( const char * value, jpp_size_t len );
    jpp::object make_integer( jpp_int64_t value );
    jpp::object make_real( jpp_double_t value );
    jpp::object make_true();
    jpp::object make_false();
    jpp::object make_boolean( jpp_bool_t _value );
    jpp::object make_null();
    jpp::object make_object();
    jpp::array make_array();

    template<class ... Args>
    jpp::array make_tuple( Args && ... _args )
    {
        jpp::array a = jpp::make_array();

        (a.push_back( _args ), ...);

        return a;
    }

    void set_object_seed( jpp_size_t _seed );
    void set_alloc_funcs( jpp_malloc_t _malloc, jpp_free_t _free );

    enum ejson_load_mode
    {
        JPP_REJECT_DUPLICATES = 1 << (0),
        JPP_DISABLE_EOF_CHECK = 1 << (1),
        JPP_DECODE_ANY = 1 << (2),
        JPP_DECODE_INT_AS_REAL = 1 << (3),
        JPP_ALLOW_NUL = 1 << (4),
    };

    jpp::object load( const void * _buffer, jpp_size_t _size, uint32_t _mode, jpp_error_t _err, void * _ud );
    jpp::object load( jpp_load_callback_t _callback, uint32_t _mode, jpp_error_t _err, void * _ud );
    jpp_bool_t dump( const jpp::object & _obj, jpp_dump_callback_t _callback, void * _ud );
    jpp_bool_t dump_compact( const jpp::object & _obj, jpp_dump_callback_t _callback, void * _ud );

    enum class merge_mode_e
    {
        update,
        update_with_array,
        existing,
        missing
    };

    jpp::object copy( const jpp::object & _obj );
    jpp::array copy( const jpp::array & _array );
    jpp_bool_t merge( const jpp::object & _obj, const jpp::object & _merge, jpp_bool_t _copy, jpp_bool_t _recursive, merge_mode_e _mode );
    jpp_bool_t once( const jpp::object & _obj );
}