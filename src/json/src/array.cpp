//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/array.hpp>
#include <missio/json/exception.hpp>

// STL headers
#include <utility>


namespace missio
{
namespace json
{

array::array(std::initializer_list<value> values) :
    values_(values.begin(), values.end())
{
}

array& array::operator=(std::initializer_list<value> values)
{
    values_.assign(values);
    return *this;
}

bool array::empty() const
{
    return values_.empty();
}

void array::clear()
{
    values_.clear();
}

std::size_t array::size() const
{
    return values_.size();
}

void array::resize(std::size_t size)
{
    values_.resize(size);
}

std::size_t array::capacity() const
{
    return values_.capacity();
}

void array::reserve(std::size_t size)
{
    values_.reserve(size);
}

void array::grow(std::size_t size)
{
    values_.resize(std::max(size, values_.size()));
}

void array::shrink(std::size_t size)
{
    values_.resize(std::min(size, values_.size()));
}

array::iterator array::begin()
{
    return values_.begin();
}

array::const_iterator array::begin() const
{
    return values_.begin();
}

array::iterator array::end()
{
    return values_.end();
}

array::const_iterator array::end() const
{
    return values_.end();
}

value& array::front()
{
    return values_.front();
}

value const& array::front() const
{
    return values_.front();
}

value& array::back()
{
    return values_.back();
}

value const& array::back() const
{
    return values_.back();
}

void array::push_back(value&& value)
{
    values_.push_back(std::forward<value_type>(value));
}

void array::push_back(value const& value)
{
    values_.push_back(value);
}

void array::pop_back()
{
    values_.pop_back();
}

void array::erase(iterator pos)
{
    values_.erase(pos);
}

void array::erase(iterator first, iterator last)
{
    values_.erase(first, last);
}

void array::insert(iterator pos, value&& value)
{
    values_.insert(pos, std::forward<value_type>(value));
}

void array::insert(iterator pos, value const& value)
{
    values_.insert(pos, value);
}

void array::insert(iterator pos, std::initializer_list<value> values)
{
    values_.insert(pos, values);
}

value& array::operator[](std::size_t index)
{
    grow(index + 1);
    return values_[index];
}

value const& array::operator[](std::size_t index) const
{
    if(index >= values_.size())
        throw exception("index out of range");

    return values_[index];
}

bool operator==(array const& lhs, array const& rhs)
{
    return lhs.values_ == rhs.values_;
}

bool operator<(array const& lhs, array const& rhs)
{
    return lhs.values_ < rhs.values_;
}

}   // namespace json
}   // namespace missio
