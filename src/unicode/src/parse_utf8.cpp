//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Implementation headers
#include "parse_utf8.hpp"


namespace missio
{
namespace unicode
{
namespace impl
{

utf8_octet_sequence const utf8_octet_sequences[8] =
{
    // two octets sequences
    { 0xC2, 0xDF, { { 0x80, 0xBF } } },

    // three octets sequences
    { 0xE0, 0xE0, { { 0xA0, 0xBF }, { 0x80, 0xBF } } },
    { 0xE1, 0xEC, { { 0x80, 0xBF }, { 0x80, 0xBF } } },
    { 0xED, 0xED, { { 0x80, 0x9F }, { 0x80, 0xBF } } },
    { 0xEE, 0xEF, { { 0x80, 0xBF }, { 0x80, 0xBD } } },

    // four octets sequences
    { 0xF0, 0xF0, { { 0x90, 0xBF }, { 0x80, 0xBF }, { 0x80, 0xBF } } },
    { 0xF1, 0xF3, { { 0x80, 0xBF }, { 0x80, 0xBF }, { 0x80, 0xBF } } },
    { 0xF4, 0xF4, { { 0x80, 0x8F }, { 0x80, 0xBF }, { 0x80, 0xBF } } }
};

}   // namespace impl
}   // namespace unicode
}   // namespace missio