//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/binary.hpp>
#include <missio/json/detail/base64.hpp>

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

binary::binary(std::initializer_list<std::uint8_t> data) :
    data_(data.begin(), data.end())
{
}

binary::binary(std::uint8_t const* data, std::size_t size) :
    data_(data, data + size)
{
}

void binary::assign(std::uint8_t const* data, std::size_t size)
{
    data_.assign(data, data + size);
}

void binary::append(std::uint8_t const* data, std::size_t size)
{
    data_.insert(data_.end(), data, data + size);
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
