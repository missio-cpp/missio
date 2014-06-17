//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2013 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_null_hpp
#define _missio_json_null_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <iostream>


namespace missio
{
namespace json
{

struct null
{
};

null const null_value;

inline bool operator==(null const&, null const&)
{
    return true;
}

inline bool operator<=(null const&, null const&)
{
    return true;
}

inline bool operator>=(null const&, null const&)
{
    return true;
}

inline bool operator!=(null const&, null const&)
{
    return false;
}

inline bool operator<(null const&, null const&)
{
    return false;
}

inline bool operator>(null const&, null const&)
{
    return false;
}

inline std::ostream& operator<<(std::ostream& os, null const&)
{
    os << "null";
    return os;
}

inline std::wostream& operator<<(std::wostream& os, null const&)
{
    os << L"null";
    return os;
}

}   // namespace json
}   // namespace missio

#endif  // _missio_json_null_hpp
