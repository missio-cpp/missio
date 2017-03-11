//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_impl_common_hpp
#define _missio_unicode_impl_common_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <cstdint>


namespace missio
{
namespace unicode
{
namespace impl
{

std::uint32_t const code_point_max = 0x10FFFF;
std::uint32_t const replacement_char = 0xFFFD;

inline bool is_code_point_valid(std::uint32_t cp)
{
    return cp <= code_point_max && cp != 0xFFFE && cp != 0xFFFF;
}

}   // namespace impl
}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_impl_common_hpp
