#pragma once

namespace jpp
{
    namespace mpl
    {
        // SFINAE has method c_str
        template <typename T>
        class has_c_str
        {
            typedef char one;
            struct two
            {
                char x[2];
            };

            template <typename C> static one test( decltype(&C::c_str) );
            template <typename C> static two test( ... );

        public:
            enum
            {
                value = sizeof( test<T>( 0 ) ) == sizeof( char )
            };
        };
    }
}