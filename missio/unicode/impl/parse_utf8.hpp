//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_impl_parse_utf8_hpp
#define _missio_unicode_impl_parse_utf8_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>

// STL headers
#include <cstdint>


namespace missio
{
namespace unicode
{
namespace impl
{

template <typename Iterator>
struct utf8_grammar : boost::spirit::qi::grammar<Iterator, std::uint32_t()>
{
    utf8_grammar() : utf8_grammar::base_type(code_point_)
    {
        using namespace boost::spirit::qi;

        octet_          =   byte_ >> eps(_r1 <= _val && _val <= _r2);

        two_octets_     =   octet_(0xC2, 0xDF)   [ _val  = (_1 & 0x1F) << 6  ]
                        >   octet_(0x80, 0xBF)   [ _val +=  _1 & 0x3F        ];

        three_octets_   =   octet_(0xE0, 0xE0)   [ _val  = (_1 & 0x0F) << 12 ]
                        >   octet_(0xA0, 0xBF)   [ _val += (_1 & 0x3F) << 6  ]
                        >   octet_(0x80, 0xBF)   [ _val +=  _1 & 0x3F        ]

                        |   octet_(0xE1, 0xEC)   [ _val  = (_1 & 0x0F) << 12 ]
                        >   octet_(0x80, 0xBF)   [ _val += (_1 & 0x3F) << 6  ]
                        >   octet_(0x80, 0xBF)   [ _val +=  _1 & 0x3F        ]

                        |   octet_(0xED, 0xED)   [ _val  = (_1 & 0x0F) << 12 ]
                        >   octet_(0x80, 0x9F)   [ _val += (_1 & 0x3F) << 6  ]
                        >   octet_(0x80, 0xBF)   [ _val +=  _1 & 0x3F        ]

                        |   octet_(0xEE, 0xEF)   [ _val  = (_1 & 0x0F) << 12 ]
                        >   octet_(0x80, 0xBF)   [ _val += (_1 & 0x3F) << 6  ]
                        >   octet_(0x80, 0xBF)   [ _val +=  _1 & 0x3F        ];

        four_octets_    =   octet_(0xF0, 0xF0)   [ _val  = (_1 & 0x07) << 18 ]
                        >   octet_(0x90, 0xBF)   [ _val += (_1 & 0x3F) << 12 ]
                        >   octet_(0x80, 0xBF)   [ _val += (_1 & 0x3F) << 6  ]
                        >   octet_(0x80, 0xBF)   [ _val +=  _1 & 0x3F        ]

                        |   octet_(0xF1, 0xF3)   [ _val  = (_1 & 0x07) << 18 ]
                        >   octet_(0x80, 0xBF)   [ _val += (_1 & 0x3F) << 12 ]
                        >   octet_(0x80, 0xBF)   [ _val += (_1 & 0x3F) << 6  ]
                        >   octet_(0x80, 0xBF)   [ _val +=  _1 & 0x3F        ]

                        |   octet_(0xF4, 0xF4)   [ _val  = (_1 & 0x07) << 18 ]
                        >   octet_(0x80, 0x8F)   [ _val += (_1 & 0x3F) << 12 ]
                        >   octet_(0x80, 0xBF)   [ _val += (_1 & 0x3F) << 6  ]
                        >   octet_(0x80, 0xBF)   [ _val +=  _1 & 0x3F        ];

        code_point_     =   byte_ >> eps(_val < 0x80u) | two_octets_ | three_octets_ | four_octets_;

        on_error<fail>(code_point_, boost::phoenix::nothing);
    }

    boost::spirit::qi::rule<Iterator, std::uint8_t(std::uint8_t, std::uint8_t)> octet_;

    boost::spirit::qi::rule<Iterator, std::uint32_t()> two_octets_;
    boost::spirit::qi::rule<Iterator, std::uint32_t()> three_octets_;
    boost::spirit::qi::rule<Iterator, std::uint32_t()> four_octets_;

    boost::spirit::qi::rule<Iterator, std::uint32_t()> code_point_;
};

template <typename OctetIterator>
bool parse_utf8(OctetIterator& pos, OctetIterator end, std::uint32_t& cp)
{
    static utf8_grammar<OctetIterator> const grammar;
    return boost::spirit::qi::parse(pos, end, grammar, cp);
}

}   // namespace impl
}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_impl_parse_utf8_hpp
