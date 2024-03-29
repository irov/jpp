#pragma once

#include "jpp/types.hpp"
#include "jpp/cast.hpp"

namespace jpp
{
	class extract
	{
	public:
        explicit extract( json_t * _j )
            : m_j( _j )
        {
        }

        ~extract()
        {
        }

	public:
		template<class T>
		operator T ()
		{
            T value;
            jpp::cast_object_internal()(m_j, &value);

            return value;
		}

	protected:
		json_t * m_j;
	};
}