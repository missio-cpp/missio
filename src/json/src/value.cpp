//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/value.hpp>

// STL headers
#include <utility>


namespace missio
{
namespace json
{

value::value()
{
}

value::~value()
{
}

value::value(value&& other) :
    variant_(std::move(other.variant_))
{
}

value& value::operator=(value&& other)
{
    assign(std::forward<value>(other));
    return *this;
}

value::value(value const& other) :
    variant_(other.variant_)
{
}

value& value::operator=(value const& other)
{
    assign(other);
    return *this;
}

void value::assign(value&& other)
{
    if(&other != this)
        variant_ = std::move(other.variant_);
}

void value::assign(value const& other)
{
    if(&other != this)
        variant_ = other.variant_;
}

int value::which() const
{
    return variant_.which();
}

value::variant_type const& value::variant() const
{
    return variant_;
}

value& value::operator[](std::size_t index)
{
    return get<array>()[index];
}

value const& value::operator[](std::size_t index) const
{
    return get<array>()[index];
}

value& value::operator[](string const& key)
{
    return get<object>()[key];
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
