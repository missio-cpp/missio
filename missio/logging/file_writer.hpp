//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_file_writer_hpp
#define _missio_logging_file_writer_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/logging/writer_options.hpp>
#include <missio/logging/writer_base.hpp>
#include <missio/logging/message.hpp>

// STL headers
#include <fstream>
#include <string>


namespace missio
{
namespace logging
{

class file_options;

class file_writer : public writer_base
{
public:
    explicit file_writer(file_options const& options);
    virtual ~file_writer() throw();

protected:
    virtual void write_impl(message const& message);
    virtual void flush_impl();

private:
    void backup_file();
    void rotate_all_files();
    void create_file_directory();
    void initialize_file(bool is_new_session);
    std::string build_filename(std::size_t index) const;

private:
    std::ofstream file_;
    std::string filename_;
    std::size_t max_file_size_;
    std::size_t max_file_index_;
};

class file_options : public basic_options<file_writer, file_options>
{
friend class file_writer;

public:
    explicit file_options(severity severity);

    file_options(file_options const&) = default;
    file_options& operator=(file_options const&) = delete;

    file_options& filename(std::string const& filename);
    file_options& max_file_size(std::size_t max_file_size);
    file_options& max_file_index(std::size_t max_file_index);

private:
    std::string filename_;
    std::size_t max_file_size_;
    std::size_t max_file_index_;
};

}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_file_writer_hpp
