#pragma once

#include "jpp/types.hpp"
#include "jpp/cast.hpp"

namespace jpp
{
	class extract_safe
	{
	public:
		explicit extract_safe( json_t * _j )
            : m_j( _j )
		{
        }

		~extract_safe()
		{
        }

	public:
		template<class T>
		operator T ()
		{
			if( m_j == nullptr )
			{
                return T();
			}

            T value;
            jpp::cast_object_internal()(m_j, &value);

            return value;
		}

	protected:
		json_t * m_j;
	};
}