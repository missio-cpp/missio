//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2016 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_impl_utf16_iterator_hpp
#define _missio_unicode_impl_utf16_iterator_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Implementation headers
#include "utf16.hpp"

// STL headers
#include <iterator>


namespace missio
{
namespace unicode
{
namespace impl
{
namespace utf16
{ 

template <typename BaseOutputIterator>
class output_iterator : public std::iterator<std::output_iterator_tag, void, void, void, void>
{
public:
    explicit output_iterator(BaseOutputIterator base) :
        base_(base)
    {
    }

    output_iterator(output_iterator const&) = default;
    output_iterator& operator=(output_iterator const&) = default;

    output_iterator& operator=(std::uint32_t cp)
    {
        write(cp, base_);
        return *this;
    }

    output_iterator& operator*()
    {
        return *this;
    }

    output_iterator& operator++()
    {
        return *this;
    }

    output_iterator operator++(int)
    {
        return *this;
    }

private:
    BaseOutputIterator base_;
};

template <typename BaseOutputIterator>
auto make_output_iterator(BaseOutputIterator iterator)
{
    return output_iterator<BaseOutputIterator>(iterator);
}

}   // namespace utf16
}   // namespace impl
}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_impl_utf16_iterator_hpp
