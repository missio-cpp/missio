//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/value.hpp>


namespace missio
{
namespace json
{

bool value::is_null() const
{
    return is<null>();
}

bool value::is_number() const
{
    return is<integer>();
}

bool value::is_boolean() const
{
    return is<boolean>();
}

bool value::is_string() const
{
    return is<string>();
}

bool value::is_object() const
{
    return is<object>();
}

bool value::is_array() const
{
    return is<array>();
}

object& value::to_object()
{
    detail::convert<object>::call(variant_);
    return boost::get<object>(variant_);
}

array& value::to_array()
{
    detail::convert<array>::call(variant_);
    return boost::get<array>(variant_);
}

object const& value::get_object() const
{
    return detail::get_type<object>::call(variant_); 
}

array const& value::get_array() const
{
    return detail::get_type<array>::call(variant_); 
}

value::variant_type const& value::variant() const
{
    return variant_;
}

value& value::operator[](std::size_t index)
{
    return to_array()[index];
}

value const& value::operator[](std::size_t index) const
{
    return get_array()[index];
}

value& value::operator[](string const& key)
{
    return to_object()[key];
}

value const& value::operator[](string const& key) const
{
    return get_object()[key];
}

bool operator==(value const& lhs, value const& rhs)
{
    return lhs.variant_ == rhs.variant_;
}

bool operator<(value const& lhs, value const& rhs)
{
    return lhs.variant_ < rhs.variant_;
}

}   // namespace json
}   // namespace missio
