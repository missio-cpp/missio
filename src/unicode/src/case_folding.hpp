//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_impl_case_folding_hpp
#define _missio_unicode_impl_case_folding_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Implementation headers
#include "locale_helper.hpp"

// STL headers
#include <algorithm>


namespace missio
{
namespace unicode
{
namespace impl
{

struct code_point_case_folding
{
    char32_t code_point;
    char32_t fold_case[3];

    bool operator<(char32_t other_code_point) const
    {
        return code_point < other_code_point;
    }
};

code_point_case_folding const case_folding[]
{
#include "case_folding.inc"
};

constexpr bool is_turkic_language_special_case_folding(char32_t code_point)
{
    return code_point == 0x0049   // LATIN CAPITAL LETTER I
        || code_point == 0x0130;  // LATIN CAPITAL LETTER I WITH DOT ABOVE
}

template <typename OutputIterator>
void fold_code_point_case(char32_t code_point, OutputIterator dest, locale_helper const& locale_helper)
{
    auto result = std::lower_bound(std::begin(case_folding), std::end(case_folding), code_point);

    if(result != std::end(case_folding) && code_point == result->code_point)
    {
        if(is_turkic_language_special_case_folding(code_point))
        {
            if(locale_helper.is_turkic_language())
            {
                ++result;
            }
        }

        for(char32_t fold_case_code_point : result->fold_case)
        {
            if(fold_case_code_point)
            {
                *dest++ = fold_case_code_point;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        *dest++ = code_point;
    }
}

}   // namespace impl
}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_impl_case_folding_hpp
