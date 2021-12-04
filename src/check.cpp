#include "jpp/check.hpp"

#include "jpp/base.hpp"
#include "jpp/object.hpp"
#include "jpp/array.hpp"
#include "jpp/assert.hpp"

#include "jansson.h"

namespace jpp
{
    //////////////////////////////////////////////////////////////////////////
    bool check_object_internal::operator()( json_t * _j, jpp::base * ) const
    {
        JPP_UNUSED( _j );

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool check_object_internal::operator()( json_t * _j, jpp::object * ) const
    {
        return json_is_object( _j ) == true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool check_object_internal::operator()( json_t * _j, jpp::array * ) const
    {
        return json_is_array( _j ) == true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool check_object_internal::operator()( json_t * _j, jpp_bool_t * ) const
    {
        return json_is_boolean( _j ) == true || (json_is_number( _j ) == true && (json_integer_value( _j ) == 1 || json_integer_value( _j ) == 0));
    }
    //////////////////////////////////////////////////////////////////////////
    bool check_object_internal::operator()( json_t * _j, jpp_int8_t * ) const
    {
        return json_is_number( _j ) == true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool check_object_internal::operator()( json_t * _j, jpp_uint8_t * ) const
    {
        return json_is_number( _j ) == true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool check_object_internal::operator()( json_t * _j, jpp_int16_t * ) const
    {
        return json_is_number( _j ) == true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool check_object_internal::operator()( json_t * _j, jpp_uint16_t * ) const
    {
        return json_is_number( _j ) == true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool check_object_internal::operator()( json_t * _j, jpp_int32_t * ) const
    {
        return json_is_number( _j ) == true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool check_object_internal::operator()( json_t * _j, jpp_uint32_t * ) const
    {
        return json_is_number( _j ) == true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool check_object_internal::operator()( json_t * _j, jpp_int64_t * ) const
    {
        return json_is_number( _j ) == true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool check_object_internal::operator()( json_t * _j, jpp_uint64_t * ) const
    {
        return json_is_number( _j ) == true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool check_object_internal::operator()( json_t * _j, jpp_float_t * ) const
    {
        return json_is_number( _j ) == true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool check_object_internal::operator()( json_t * _j, jpp_double_t * ) const
    {
        return json_is_number( _j ) == true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool check_object_internal::operator()( json_t * _j, const char ** ) const
    {
        return json_is_string( _j ) == true;
    }
    //////////////////////////////////////////////////////////////////////////
}
