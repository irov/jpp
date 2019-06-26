#include "jpp/jpp.hpp"

#include <stdlib.h>

static size_t musage = 0;

static void * my_jpp_malloc( size_t _size )
{
    void * ptr = malloc( _size + sizeof( size_t ) );

    *(size_t*)ptr = _size;

    musage += _size;

    return (size_t*)ptr + 1;
}

static void my_jpp_free( void* _free )
{
    size_t* ptr = (size_t*)_free - 1;

    size_t size = *ptr;

    musage -= size;

    free( ptr );
}

static size_t my_jpp_load_callback( void* _buffer, size_t _size, void* _data )
{
    FILE* f = (FILE*)_data;

    size_t r = fread( _buffer, 1, _size, f );

    return r;
}

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

bool jpp_test( const char * _filepath )
{
    FILE* f = fopen( _filepath, "rb" );

    if( f == nullptr )
    {
        return false;
    }

    jpp::object root = jpp::load( &my_jpp_load_callback, my_jpp_malloc, my_jpp_free, f );

    fclose( f );

    if( root.invalid() == true )
    {
        return false;
    }

    jpp_printf( root );

    return true;
}

int main(int argc, char* argv[])
{
    char full_example_file_path[256];
    if( argc > 1 )
    {
        sprintf( full_example_file_path, "%s/%s"
            , argv[1]
            , "example.json"
        );
    }
    else
    {
        sprintf( full_example_file_path, "%s"
            , "example.json"
        );
    }

    if( jpp_test( full_example_file_path ) == false )
    {
        return EXIT_FAILURE;
    }
    
    if( musage != 0 )
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}