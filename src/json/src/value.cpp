//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/value.hpp>


namespace missio
{
namespace json
{

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
    return get<array>()[index];
}

value& value::operator[](string const& key)
{
    return to_object()[key];
}

value const& value::operator[](string const& key) const
{
    return get<object>()[key];
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
