//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2013 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/object.hpp>
#include <missio/json/value.hpp>

// BOOST headers
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/algorithm.hpp>

// STL headers
#include <iterator>
#include <utility>


namespace missio
{
namespace json
{

object::object()
{
}

object::~object()
{
}

object::object(object&& other) :
    values_(std::move(other.values_))
{
}

object& object::operator=(object&& other)
{
    if(&other != this)
        values_ = std::move(other.values_);
    return *this;
}

object::object(object const& other) :
    values_(other.values_)
{
}

object& object::operator=(object const& other)
{
    if(&other != this)
        values_ = other.values_;
    return *this;
}

bool object::empty() const
{
    return values_.empty();
}

std::size_t object::size() const
{
    return values_.size();
}

object::iterator object::begin()
{
    return values_.begin();
}

object::const_iterator object::begin() const
{
    return values_.begin();
}

object::iterator object::end()
{
    return values_.end();
}

object::const_iterator object::end() const
{
    return values_.end();
}

object::iterator object::find(string const& key)
{
    return boost::find_if(values_, [&key](value_type const& value){ return value.first == key; });
}

object::const_iterator object::find(string const& key) const
{
    return boost::find_if(values_, [&key](value_type const& value){ return value.first == key; });
}

bool object::contains(string const& key) const
{
    return find(key) != values_.end();
}

void object::clear()
{
    values_.clear();
}

void object::erase(iterator position)
{
    values_.erase(position);
}

void object::erase(iterator first, iterator last)
{
    values_.erase(first, last);
}

void object::erase(string const& key)
{
    boost::remove_erase_if(values_, [&key](value_type const& value){ return value.first == key; });
}

bool object::insert(iterator position, value_type const& value)
{
    if(!contains(value.first))
    {
        values_.insert(position, value);
        return true;
    }

    return false;
}

bool object::insert(string const& key, value const& value)
{
    if(!contains(key))
    {
        values_.emplace_back(key, value);
        return true;
    }

    return false;
}

value& object::operator[](string const& key)
{
    iterator position(find(key));

    if(position == values_.end())
    {
        values_.emplace_back(key, value());
        position = std::prev(values_.end());
    }

    return position->second;
}

value const& object::operator[](string const& key) const
{
    const_iterator position(find(key));

    if(position == values_.end())
        throw exception("value not found");

    return position->second;
}

bool operator==(object const& lhs, object const& rhs)
{
    return lhs.values_ == rhs.values_;
}

bool operator<(object const& lhs, object const& rhs)
{
    return lhs.values_ < rhs.values_;
}

}   // namespace json
}   // namespace missio
