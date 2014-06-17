//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
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
    return string(detail::base64::encode(value.data()));
}

binary::binary()
{
}

binary::binary(std::vector<unsigned char>&& data) :
    data_(std::move(data))
{
}

binary::binary(std::vector<unsigned char> const& data) :
    data_(data)
{
}

binary::binary(unsigned char const* data, std::size_t size) :
    data_(data, data + size)
{
}

binary::binary(binary&& other) :
    data_(std::move(other.data_))
{
}

binary& binary::operator=(binary&& other)
{
    if(&other != this)
        data_ = std::move(other.data_);
    return *this;
}

binary::binary(binary const& other) :
    data_(other.data_)
{
}

binary& binary::operator=(binary const& other)
{
    if(&other != this)
        data_ = other.data_;
    return *this;
}

void binary::assign(std::vector<unsigned char> const& data)
{
    data_.assign(data.begin(), data.end());
}

void binary::append(std::vector<unsigned char> const& data)
{
    data_.insert(data_.end(), data.begin(), data.end());
}

void binary::assign(unsigned char const* data, std::size_t size)
{
    data_.assign(data, data + size);
}

void binary::append(unsigned char const* data, std::size_t size)
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

std::vector<unsigned char> const& binary::data() const
{
    return data_;
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
