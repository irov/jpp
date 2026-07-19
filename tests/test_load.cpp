#include "jpp/jpp.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <utility>

static size_t musage = 0;

static void my_jpp_free( void* _free );

//////////////////////////////////////////////////////////////////////////
static size_t my_jpp_load_callback( void* _buffer, jpp::jpp_size_t _size, void* _ud )
{
    FILE* f = (FILE*)_ud;

    size_t r = fread( _buffer, 1, _size, f );

    return r;
}
//////////////////////////////////////////////////////////////////////////
static void* my_jpp_malloc( jpp::jpp_size_t _size )
{
    if( _size == 0 )
    {
        _size = 1;
    }

    void* ptr = malloc( _size + sizeof( size_t ) );

    if( ptr == nullptr )
    {
        return nullptr;
    }

    *(size_t*)ptr = _size;

    musage += _size;

    return (size_t*)ptr + 1;
}
//////////////////////////////////////////////////////////////////////////
static void* my_jpp_realloc( void* _ptr, jpp::jpp_size_t _size )
{
    if( _ptr == nullptr )
    {
        return my_jpp_malloc( _size );
    }

    if( _size == 0 )
    {
        my_jpp_free( _ptr );

        return nullptr;
    }

    size_t* ptr = (size_t*)_ptr - 1;

    size_t old_size = *ptr;

    size_t* new_ptr = (size_t*)realloc( ptr, _size + sizeof( size_t ) );

    if( new_ptr == nullptr )
    {
        return nullptr;
    }

    ptr = new_ptr;

    *ptr = _size;

    musage -= old_size;
    musage += _size;

    return ptr + 1;
}
//////////////////////////////////////////////////////////////////////////
static void my_jpp_free( void* _free )
{
    if( _free == nullptr )
    {
        return;
    }

    size_t* ptr = (size_t*)_free - 1;

    size_t size = *ptr;

    musage -= size;

    free( ptr );
}
//////////////////////////////////////////////////////////////////////////
static void my_jpp_error( int32_t _line, int32_t _column, int32_t _position, const char * _source, const char * _text, void* _ud )
{
    JPP_UNUSED( _ud );

    printf( "error: %s\nline: %d\n column: %d\nposition: %d\nsource: %s\n"
        , _text
        , _line
        , _column
        , _position
        , _source
    );
}
//////////////////////////////////////////////////////////////////////////
void jpp_printf( const jpp::object& _obj, uint32_t _ident = 0 )
{
    jpp::e_type type = _obj.type();

    switch( type )
    {
    case jpp::e_type::JPP_OBJECT:
        {
            printf( "{\n" );
            for( auto && [key, value] : _obj )
            {
                printf( "%*c%s = ", _ident + 2, ' ', key );
                jpp_printf( value, _ident + 2 );
            }
            printf( "%*c}\n", _ident, ' ' );
        }break;
    case jpp::e_type::JPP_ARRAY:
        {
            printf( "[\n" );
            for( const jpp::object& value : jpp::array( _obj ) )
            {
                printf( "%*c", _ident + 2, ' ' );
                jpp_printf( value, _ident + 2 );
            }
            printf( "%*c]\n", _ident, ' ' );
        }break;
    case jpp::e_type::JPP_STRING:
        {
            const char* value = _obj;
            printf( "%s\n", value );
        }break;
    case jpp::e_type::JPP_INTEGER:
        {
            int value = _obj;
            printf( "%d\n", value );
        }break;
    case jpp::e_type::JPP_REAL:
        {
            float value = _obj;
            printf( "%f\n", value );
        }break;
    case jpp::e_type::JPP_TRUE:
        {
            printf( "true\n" );
        }break;
    case jpp::e_type::JPP_FALSE:
        {
            printf( "false\n" );
        }break;
    case jpp::e_type::JPP_NULL:
        {
            printf( "null\n" );
        }break;
    }
}
//////////////////////////////////////////////////////////////////////////
jpp::jpp_bool_t jpp_test( const char * _filepath )
{
    jpp::set_alloc_funcs( &my_jpp_malloc, &my_jpp_realloc, &my_jpp_free );

    FILE* f = fopen( _filepath, "rb" );

    if( f == nullptr )
    {
        return false;
    }

    jpp::object root = jpp::load( &my_jpp_load_callback, jpp::JPP_LOAD_MODE_NONE, &my_jpp_error, f );

    fclose( f );

    if( root.invalid() == true )
    {
        return false;
    }

    jpp_printf( root );

    return true;
}
//////////////////////////////////////////////////////////////////////////
static jpp::jpp_bool_t jpp_test_move_assignment()
{
    size_t begin_musage = musage;

    {
        jpp::object a = jpp::make_object();
        jpp::object b = jpp::make_object();

        a = std::move( b );
    }

    return musage == begin_musage;
}
//////////////////////////////////////////////////////////////////////////
static jpp::jpp_bool_t jpp_test_copy_invalid_array()
{
    size_t begin_musage = musage;

    {
        jpp::array a;
        jpp::array copy = jpp::copy( a );

        if( copy.is_type_array() == false )
        {
            return false;
        }
    }

    return musage == begin_musage;
}
//////////////////////////////////////////////////////////////////////////
static jpp::jpp_bool_t jpp_test_merge_copy_fail_cleanup()
{
    size_t begin_musage = musage;

    {
        jpp::object invalid = jpp::make_invalid();
        jpp::object merge = jpp::make_object();

        if( jpp::merge( invalid, merge, true, false, jpp::merge_mode_e::update ) == true )
        {
            return false;
        }
    }

    return musage == begin_musage;
}
//////////////////////////////////////////////////////////////////////////
static jpp::jpp_bool_t jpp_test_compare_non_string()
{
    jpp::object value = jpp::make_integer( 1 );

    const char * text = "1";

    return (value == text) == false;
}
//////////////////////////////////////////////////////////////////////////
static int jpp_test_dump_callback( const char * _buffer, jpp::jpp_size_t _size, void * _ud )
{
    std::string * value = static_cast<std::string *>(_ud);

    value->append( _buffer, _size );

    return 0;
}
//////////////////////////////////////////////////////////////////////////
static void jpp_test_error_ex_callback( jpp::jpp_int32_t _line, jpp::jpp_int32_t _column, jpp::jpp_int32_t _position, const char * _source, const char * _text, jpp::load_error_code_e _code, void * _ud )
{
    (void)_line;
    (void)_column;
    (void)_position;
    (void)_source;
    (void)_text;

    jpp::load_error_code_e * code = static_cast<jpp::load_error_code_e *>(_ud);
    *code = _code;
}
//////////////////////////////////////////////////////////////////////////
static jpp::jpp_bool_t jpp_test_load_error_code()
{
    const char value[] = "9223372036854775808";
    jpp::load_error_code_e code = jpp::load_error_code_e::invalid;
    jpp::object result = jpp::load_ex( value, sizeof( value ) - 1, jpp::JPP_LOAD_MODE_DECODE_ANY, &jpp_test_error_ex_callback, &code );

    return result.invalid() == true && code == jpp::load_error_code_e::numeric_overflow;
}
//////////////////////////////////////////////////////////////////////////
static jpp::jpp_bool_t jpp_test_dump_modes()
{
    jpp::object root = jpp::make_object();
    jpp::array items = jpp::make_array();
    items.push_back( 1 );
    items.push_back( 2 );
    root.set( "items", items );

    std::string compact;
    if( jpp::dump_compact( root, &jpp_test_dump_callback, &compact ) == false || compact != "{\"items\":[1,2]}" )
    {
        return false;
    }

    std::string indent_zero;
    if( jpp::dump_indent( root, 0, &jpp_test_dump_callback, &indent_zero ) == false || indent_zero != "{\n\"items\": [\n1,\n2\n]\n}" )
    {
        return false;
    }

    std::string indent_one;
    if( jpp::dump_indent( root, 1, &jpp_test_dump_callback, &indent_one ) == false || indent_one != "{\n \"items\": [\n  1,\n  2\n ]\n}" )
    {
        return false;
    }

    std::string indent_two;
    if( jpp::dump_indent( root, 2, &jpp_test_dump_callback, &indent_two ) == false || indent_two != "{\n  \"items\": [\n    1,\n    2\n  ]\n}" )
    {
        return false;
    }

    std::string indent_large;
    if( jpp::dump_indent( root, 40, &jpp_test_dump_callback, &indent_large ) == false )
    {
        return false;
    }

    if( indent_large.find( "\n" + std::string( 40, ' ' ) + "\"items\"" ) == std::string::npos || indent_large.find( "\n" + std::string( 80, ' ' ) + "1" ) == std::string::npos )
    {
        return false;
    }

    jpp::object scalar = jpp::make_integer( 42 );
    std::string scalar_compact;
    if( jpp::dump_compact( scalar, &jpp_test_dump_callback, &scalar_compact ) == false || scalar_compact != "42" )
    {
        return false;
    }

    std::string scalar_pretty;
    if( jpp::dump_indent( scalar, 8, &jpp_test_dump_callback, &scalar_pretty ) == false || scalar_pretty != "42" )
    {
        return false;
    }

    const char sized_key[] = {'a', '\0', 'b'};
    jpp::object sized_key_object = jpp::make_object();
    if( sized_key_object.setn( sized_key, sizeof( sized_key ), 7 ) == false )
    {
        return false;
    }

    std::string sized_key_json;
    if( jpp::dump_compact( sized_key_object, &jpp_test_dump_callback, &sized_key_json ) == false || sized_key_json != "{\"a\\u0000b\":7}" )
    {
        return false;
    }

    return true;
}
//////////////////////////////////////////////////////////////////////////
struct jpp_test_load_error_t
{
    int32_t line;
    int32_t column;
    std::string message;
};
//////////////////////////////////////////////////////////////////////////
static void jpp_test_load_error( int32_t _line, int32_t _column, int32_t _position, const char * _source, const char * _text, void * _ud )
{
    JPP_UNUSED( _position );
    JPP_UNUSED( _source );

    jpp_test_load_error_t * error = static_cast<jpp_test_load_error_t *>(_ud);
    error->line = _line;
    error->column = _column;
    error->message.assign( _text );
}
//////////////////////////////////////////////////////////////////////////
static jpp::jpp_bool_t jpp_test_strict_load()
{
    const char scalar_json[] = "-9223372036854775808";
    jpp::object scalar = jpp::load( scalar_json, sizeof( scalar_json ) - 1, jpp::JPP_LOAD_MODE_DECODE_ANY, nullptr, nullptr );

    if( scalar.invalid() == true || scalar.is_type_integer() == false || (int64_t)scalar != INT64_MIN )
    {
        fprintf( stderr, "strict scalar root failed\n" );
        return false;
    }

    const char trailing_json[] = "42 trailing";
    jpp::object trailing = jpp::load( trailing_json, sizeof( trailing_json ) - 1, jpp::JPP_LOAD_MODE_DECODE_ANY, nullptr, nullptr );

    if( trailing.invalid() == false )
    {
        fprintf( stderr, "strict trailing data failed\n" );
        return false;
    }

    const char malformed_json[] = "[\n  1,\n]";
    jpp_test_load_error_t parse_error = {0, 0, {}};
    jpp::object malformed = jpp::load( malformed_json, sizeof( malformed_json ) - 1, jpp::JPP_LOAD_MODE_DECODE_ANY, &jpp_test_load_error, &parse_error );

    if( malformed.invalid() == false || parse_error.line <= 0 || parse_error.column <= 0 || parse_error.message.empty() == true )
    {
        fprintf( stderr, "strict malformed diagnostics failed: line=%d column=%d message='%s'\n", parse_error.line, parse_error.column, parse_error.message.c_str() );
        return false;
    }

    const char invalid_utf8_json[] = {'\"', (char)0xFF, '\"'};
    jpp::object invalid_utf8 = jpp::load( invalid_utf8_json, sizeof( invalid_utf8_json ), jpp::JPP_LOAD_MODE_DECODE_ANY, nullptr, nullptr );

    if( invalid_utf8.invalid() == false )
    {
        fprintf( stderr, "strict invalid UTF-8 failed\n" );
        return false;
    }

    const char sized_key_json[] = "{\"a\\u0000b\":7}";
    jpp_test_load_error_t sized_key_error = {0, 0, {}};
    jpp::object sized_key_object = jpp::load( sized_key_json, sizeof( sized_key_json ) - 1, jpp::JPP_LOAD_MODE_DECODE_ANY | jpp::JPP_LOAD_MODE_ALLOW_NUL, &jpp_test_load_error, &sized_key_error );

    if( sized_key_object.invalid() == true || sized_key_object.size() != 1 )
    {
        fprintf( stderr, "strict sized key load failed: line=%d column=%d message='%s'\n", sized_key_error.line, sized_key_error.column, sized_key_error.message.c_str() );
        return false;
    }

    jpp::object_iterator iterator = jpp::begin( sized_key_object );
    jpp::object_iterator_pair pair = *iterator;
    const char expected_key[] = {'a', '\0', 'b'};

    if( iterator.key_size() != sizeof( expected_key ) || std::memcmp( pair.key, expected_key, sizeof( expected_key ) ) != 0 || (int32_t)pair.value != 7 )
    {
        fprintf( stderr, "strict sized key contents failed: size=%zu\n", iterator.key_size() );
        return false;
    }

    return true;
}
//////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    char full_example_file_path[256];
    if( argc > 1 )
    {
        snprintf( full_example_file_path, sizeof( full_example_file_path ), "%s/%s"
            , argv[1]
            , "example.json"
        );
    }
    else
    {
        snprintf( full_example_file_path, sizeof( full_example_file_path ), "%s"
            , "example.json"
        );
    }

    if( jpp_test( full_example_file_path ) == false )
    {
        fprintf( stderr, "jpp_test failed\n" );
        return EXIT_FAILURE;
    }
    
    if( musage != 0 )
    {
        fprintf( stderr, "allocator leak after jpp_test: %zu bytes\n", musage );
        return EXIT_FAILURE;
    }

    if( jpp_test_move_assignment() == false )
    {
        fprintf( stderr, "jpp_test_move_assignment failed\n" );
        return EXIT_FAILURE;
    }

    if( jpp_test_copy_invalid_array() == false )
    {
        fprintf( stderr, "jpp_test_copy_invalid_array failed\n" );
        return EXIT_FAILURE;
    }

    if( jpp_test_merge_copy_fail_cleanup() == false )
    {
        fprintf( stderr, "jpp_test_merge_copy_fail_cleanup failed\n" );
        return EXIT_FAILURE;
    }

    if( jpp_test_compare_non_string() == false )
    {
        fprintf( stderr, "jpp_test_compare_non_string failed\n" );
        return EXIT_FAILURE;
    }

    if( jpp_test_dump_modes() == false )
    {
        fprintf( stderr, "jpp_test_dump_modes failed\n" );
        return EXIT_FAILURE;
    }

    if( jpp_test_load_error_code() == false )
    {
        fprintf( stderr, "jpp_test_load_error_code failed\n" );
        return EXIT_FAILURE;
    }

    if( jpp_test_strict_load() == false )
    {
        fprintf( stderr, "jpp_test_strict_load failed\n" );
        return EXIT_FAILURE;
    }

    if( musage != 0 )
    {
        fprintf( stderr, "allocator leak after JSON tests: %zu bytes\n", musage );
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
