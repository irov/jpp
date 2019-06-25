#include "jpp/jpp.hpp"

#include <stdlib.h>

static size_t my_jpp_load_callback( void* _buffer, size_t _size, void* _data )
{
    FILE* f = (FILE*)_data;

    size_t r = fread( _buffer, 1, _size, f );

    return r;

}

int main(int argc, char* argv[])
{
    FILE* f = fopen( "example.json", "rb" );

    jpp::object root = jpp::load( &my_jpp_load_callback, malloc, free, f );

    jpp::object root_glossary = root["glossary"];

    for( auto [key, value] : root_glossary )
    {
        printf( "key %s\n", key );
    }

    return EXIT_SUCCESS;
}