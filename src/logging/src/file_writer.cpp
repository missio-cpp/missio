//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/file_writer.hpp>
#include <missio/logging/detail/timestamp.hpp>
#include <missio/format/adapters/boost.hpp>
#include <missio/format/format.hpp>

// BOOST headers
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

// STL headers
#include <memory>


namespace missio
{
namespace logging
{

file_writer::file_writer(file_options const& options) :
    writer_base(options),
    filename_(options.filename_),
    max_file_size_(options.max_file_size_),
    max_file_index_(options.max_file_index_)
{
    rotate_all_files();
    initialize_file(true);
}

file_writer::~file_writer() throw()
{
}

void file_writer::write_impl(message const& message)
{
    if(!file_.is_open())
        initialize_file(true);

    if(file_.is_open())
        format(file_, message);
}

void file_writer::flush_impl()
{
    if(file_.is_open())
    {
        file_.flush();
        backup_file();
    }
}

void file_writer::backup_file()
{
    std::streampos const pos = file_.tellp();

    if(max_file_size_ > 0 && pos > 0)
    {
        if(static_cast<std::size_t>(pos) >= max_file_size_)
        {
            rotate_all_files();
            initialize_file(false);
        }
    }
}

void file_writer::rotate_all_files()
{
    file_.close();

    if(boost::filesystem::exists(filename_))
    {
        if(boost::filesystem::file_size(filename_) >= max_file_size_)
        {
            if(max_file_index_ > 0)
            {
                for(std::size_t index = max_file_index_; index > 0; --index)
                {
                    boost::filesystem::path const old_filename = build_filename(index - 1);
                    boost::filesystem::path const new_filename = build_filename(index);

                    if(boost::filesystem::exists(old_filename))
                        boost::filesystem::rename(old_filename, new_filename);
                }

                boost::filesystem::rename(filename_, build_filename(0));
            }
            else
            {
                boost::filesystem::remove(filename_);
            }
        }
    }
}

void file_writer::create_file_directory()
{
    boost::filesystem::create_directories(boost::filesystem::absolute(filename_).parent_path());
}

void file_writer::initialize_file(bool is_new_session)
{
    create_file_directory();

    file_.open(filename_.c_str(), std::ios::out);

    if(is_new_session && file_.is_open())
    {
        file_.seekp(0, std::ios::end);

        if(file_.tellp() > 0)
            format::write(file_, '\n', '\n');

        format::write(file_, format::repeat('=', 40), ' ');
        format::write(file_, detail::timestamp().value(), ' ');
        format::write(file_, format::repeat('=', 40), '\n');

        file_.flush();
    }
}

std::string file_writer::build_filename(std::size_t index) const
{
    std::string filename;

    format::write(filename, filename_, '.', index);

    return filename;
}

file_options::file_options(severity severity) :
    basic_options(severity),
    filename_("missio.log"),
    max_file_size_(0),
    max_file_index_(0)
{
}

file_options& file_options::filename(std::string const& filename)
{
    filename_ = filename;
    return self();
}

file_options& file_options::max_file_size(std::size_t max_file_size)
{
    max_file_size_ = max_file_size;
    return self();
}

file_options& file_options::max_file_index(std::size_t max_file_index)
{
    max_file_index_ = max_file_index;
    return self();
}

}   // namespace logging
}   // namespace missio
