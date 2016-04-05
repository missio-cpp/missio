//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2016 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_impl_convert_hpp
#define _missio_unicode_impl_convert_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Implementation headers
#include "utf16_iterator.hpp"
#include "utf8_iterator.hpp"
#include "case_folding.hpp"


namespace missio
{
namespace unicode
{
namespace impl
{

template <typename OctetIterator, typename OutputIterator>
void utf8_to_utf16(OctetIterator first, OctetIterator last, OutputIterator dest)
{
    while(first != last)
    {
        utf16::write(utf8::next(first, last), dest);
    }
}

template <typename OctetIterator, typename OutputIterator>
void utf8_to_utf32(OctetIterator first, OctetIterator last, OutputIterator dest)
{
    while(first != last)
    {
        *dest++ = utf8::next(first, last);
    }
}

template <typename UTF16Iterator, typename OutputIterator>
void utf16_to_utf8(UTF16Iterator first, UTF16Iterator last, OutputIterator dest)
{
    while(first != last)
    {
        utf8::write(utf16::next(first, last), dest);
    }
}

template <typename UTF16Iterator, typename OutputIterator>
void utf16_to_utf32(UTF16Iterator first, UTF16Iterator last, OutputIterator dest)
{
    while(first != last)
    {
        *dest++ = utf16::next(first, last);
    }
}

template <typename UTF32Iterator, typename OutputIterator>
void utf32_to_utf8(UTF32Iterator first, UTF32Iterator last, OutputIterator dest)
{
    while(first != last)
    {
        utf8::write(*first++, dest);
    }
}

template <typename UTF32Iterator, typename OutputIterator>
void utf32_to_utf16(UTF32Iterator first, UTF32Iterator last, OutputIterator dest)
{
    while(first != last)
    {
        utf16::write(*first++, dest);
    }
}

template <typename OctetIterator, typename OutputIterator>
void fold_case_utf8(OctetIterator first, OctetIterator last, OutputIterator dest)
{
    auto output_iterator = utf8::make_output_iterator(dest);

    while(first != last)
    {
        fold_code_point_case(utf8::next(first, last), output_iterator);
    }
}

template <typename UTF16Iterator, typename OutputIterator>
void fold_case_utf16(UTF16Iterator first, UTF16Iterator last, OutputIterator dest)
{
    auto output_iterator = utf16::make_output_iterator(dest);

    while(first != last)
    {
        fold_code_point_case(utf16::next(first, last), output_iterator);
    }
}

template <typename UTF32Iterator, typename OutputIterator>
void fold_case_utf32(UTF32Iterator first, UTF32Iterator last, OutputIterator dest)
{
    while(first != last)
    {
        fold_code_point_case(*first++, dest);
    }
}

}   // namespace impl
}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_impl_convert_hpp
