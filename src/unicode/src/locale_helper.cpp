//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Implementation headers
#include "locale_helper.hpp"

// STL headers
#include <algorithm>
#include <string>


namespace
{

#if defined(_WIN32)
// Windows locale language names
const char LANGUAGE_TR[] { 't', 'u', 'r', 'k', 'i', 's', 'h' };
const char LANGUAGE_AZ[] { 'a', 'z', 'e', 'r', 'i' };
#else
// ISO 639-1 language codes
const char LANGUAGE_TR[] { 't', 'r' };
const char LANGUAGE_AZ[] { 'a', 'z' };
#endif

constexpr char to_ascii_lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
}

void normalize_locale_name(std::string& locale_name)
{
    locale_name.resize(std::min(locale_name.find_first_of("-_@. "), locale_name.length()));
    std::transform(locale_name.begin(), locale_name.end(), locale_name.begin(), to_ascii_lower);
}

template <std::size_t N>
bool is_language_locale(std::string const& locale_name, char const (&language)[N])
{
    return std::equal(locale_name.begin(), locale_name.end(), std::begin(language), std::end(language));
}

bool is_turkic_language_locale(std::locale const& loc)
{
  std::string locale_name(loc.name());

  normalize_locale_name(locale_name);

  return is_language_locale(locale_name, LANGUAGE_TR)
      || is_language_locale(locale_name, LANGUAGE_AZ);
}

}   // namespace

namespace missio
{
namespace unicode
{
namespace impl
{

locale_helper::locale_helper(std::locale const& loc):
    locale_(loc),
    is_turkic_language_(false),
    is_turkic_language_flag_(false)
{
}

bool locale_helper::is_turkic_language() const
{
    if(!is_turkic_language_flag_)
    {
        is_turkic_language_ = is_turkic_language_locale(locale_);
        is_turkic_language_flag_ = true;
    }

    return is_turkic_language_;
}

}   // namespace impl
}   // namespace unicode
}   // namespace missio
