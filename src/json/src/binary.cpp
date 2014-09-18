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
#include <algorithm>
#include <utility>


namespace missio
{
namespace json
{

template <typename Container>
static void assign_to_container(Container& container, void const* data, std::size_t size)
{
    container.assign(static_cast<typename Container::const_pointer>(data), static_cast<typename Container::const_pointer>(data) + size);
}

template <typename Container>
static void append_to_container(Container& container, void const* data, std::size_t size)
{
    container.insert(container.end(), static_cast<typename Container::const_pointer>(data), static_cast<typename Container::const_pointer>(data) + size);
}

binary binary::from_base64_string(string const& str)
{
    return binary(detail::base64::decode(str));
}

string binary::to_base64_string(binary const& value)
{
    return string(detail::base64::encode(value.data_));
}

binary::binary(void const* data, std::size_t size)
{
    assign_to_container(data_, data, size);
}

binary::binary(std::vector<value_type>&& data) :
    data_(std::forward<std::vector<value_type>>(data))
{
}

binary& binary::operator=(std::vector<value_type>&& data)
{
    data_ = std::forward<std::vector<value_type>>(data);
    return *this;
}

binary::binary(std::initializer_list<value_type> data) :
    data_(data)
{
}

binary& binary::operator=(std::initializer_list<value_type> data)
{
    assign(data);
    return *this;
}

void binary::assign(void const* data, std::size_t size)
{
    assign_to_container(data_, data, size);
}

void binary::append(void const* data, std::size_t size)
{
    append_to_container(data_, data, size);
}

void binary::assign(std::initializer_list<value_type> data)
{
    data_.assign(data);
}

void binary::append(std::initializer_list<value_type> data)
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

binary::size_type binary::size() const
{
    return data_.size();
}

binary::const_pointer binary::data() const
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
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

bool operator==(binary const& lhs, binary const& rhs)
{
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator!=(binary const& lhs, binary const& rhs)
{
    return !operator==(lhs, rhs);
}

}   // namespace json
}   // namespace missio
