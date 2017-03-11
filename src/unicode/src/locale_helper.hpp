//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_impl_locale_helper_hpp
#define _missio_unicode_impl_locale_helper_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <locale>


namespace missio
{
namespace unicode
{
namespace impl
{

class locale_helper
{
public:
    explicit locale_helper(std::locale const& loc);

    locale_helper(locale_helper&&) = default;
    locale_helper(locale_helper const&) = default;

    locale_helper& operator=(locale_helper&&) = delete;
    locale_helper& operator=(locale_helper const&) = delete;

    bool is_turkic_language() const;

private:
    std::locale const& locale_;
    mutable bool is_turkic_language_;
    mutable bool is_turkic_language_flag_;
};

}   // namespace impl
}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_impl_locale_helper_hpp
