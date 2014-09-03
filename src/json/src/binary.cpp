//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/binary.hpp>

// Implementation headers
#include "base64.hpp"

// STL headers
#include <utility>


namespace missio
{
namespace json
{

binary binary::from_base64_string(string const& str)
{
    return binary(detail::base64::decode(str));
}

string binary::to_base64_string(binary const& value)
{
    return string(detail::base64::encode(value.data_));
}

binary::binary(std::vector<std::uint8_t>&& data) :
    data_(std::forward<std::vector<std::uint8_t>>(data))
{
}

binary::binary(std::initializer_list<std::uint8_t> data) :
    data_(data)
{
}

binary& binary::operator=(std::initializer_list<std::uint8_t> data)
{
    data_.assign(data);
    return *this;
}

void binary::assign(std::initializer_list<std::uint8_t> data)
{
    data_.assign(data);
}

void binary::append(std::initializer_list<std::uint8_t> data)
{
    data_.insert(data_.end(), data);
}

void binary::clear()
{
    data_.clear();
}

bool binary::empty() const
{
    return data_.empty();
}

std::size_t binary::size() const
{
    return data_.size();
}

std::uint8_t const* binary::data() const
{
    return data_.data();
}

binary::const_iterator binary::begin() const
{
    return data_.begin();
}

binary::const_iterator binary::end() const
{
    return data_.end();
}

bool operator<(binary const& lhs, binary const& rhs)
{
    return lhs.data_ < rhs.data_;
}

bool operator==(binary const& lhs, binary const& rhs)
{
    return lhs.data_ == rhs.data_;
}

}   // namespace json
}   // namespace missio
