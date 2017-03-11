//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_convert_hpp
#define _missio_unicode_convert_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Common headers
#include <missio/common/export.hpp>

// STL headers
#include <string>
#include <locale>


namespace missio
{
namespace unicode
{

// Unicode Normalization Forms
enum class normalization
{
  nfd,  // Normalization Form D (canonical decomposition)
  nfc,  // Normalization Form C (canonical decomposition followed by canonical composition)
  nfkd, // Normalization Form KD (compatibility decomposition)
  nfkc  // Normalization Form KC (compatibility decomposition followed by canonical composition)
};

// Convert UTF-16 / UTF-32 string to UTF-8 string
MISSIO_EXPORT std::string to_utf8(std::u16string const& str);
MISSIO_EXPORT std::string to_utf8(std::u32string const& str);

// Convert UTF-8 / UTF-32 string to UTF-16 string
MISSIO_EXPORT std::u16string to_utf16(std::string const& str);
MISSIO_EXPORT std::u16string to_utf16(std::u32string const& str);

// Convert UTF-8 / UTF-16 string to UTF-32 string
MISSIO_EXPORT std::u32string to_utf32(std::string const& str);
MISSIO_EXPORT std::u32string to_utf32(std::u16string const& str);

// Normalize UTF-8 / UTF-16 / UTF-32 string
MISSIO_EXPORT std::string normalize(std::string const& str, normalization norm = normalization::nfc, std::locale const& loc = std::locale());
MISSIO_EXPORT std::u16string normalize(std::u16string const& str, normalization norm = normalization::nfc, std::locale const& loc = std::locale());
MISSIO_EXPORT std::u32string normalize(std::u32string const& str, normalization norm = normalization::nfc, std::locale const& loc = std::locale());

// Convert UTF-8 string to upper / lower / title case
MISSIO_EXPORT std::string to_upper(std::string const& str, std::locale const& loc = std::locale());
MISSIO_EXPORT std::string to_lower(std::string const& str, std::locale const& loc = std::locale());
MISSIO_EXPORT std::string to_title(std::string const& str, std::locale const& loc = std::locale());

// Convert UTF-16 string to upper / lower / title case
MISSIO_EXPORT std::u16string to_upper(std::u16string const& str, std::locale const& loc = std::locale());
MISSIO_EXPORT std::u16string to_lower(std::u16string const& str, std::locale const& loc = std::locale());
MISSIO_EXPORT std::u16string to_title(std::u16string const& str, std::locale const& loc = std::locale());

// Convert UTF-32 string to upper / lower / title case
MISSIO_EXPORT std::u32string to_upper(std::u32string const& str, std::locale const& loc = std::locale());
MISSIO_EXPORT std::u32string to_lower(std::u32string const& str, std::locale const& loc = std::locale());
MISSIO_EXPORT std::u32string to_title(std::u32string const& str, std::locale const& loc = std::locale());

// Fold case of UTF-8 / UTF-16 / UTF-32 string
MISSIO_EXPORT std::string fold_case(std::string const& str, std::locale const& loc = std::locale());
MISSIO_EXPORT std::u16string fold_case(std::u16string const& str, std::locale const& loc = std::locale());
MISSIO_EXPORT std::u32string fold_case(std::u32string const& str, std::locale const& loc = std::locale());

}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_convert_hpp
