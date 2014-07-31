//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

#include <missio/format/format.hpp>
#include <missio/format/adapters/pointer.hpp>

#include <boost/timer.hpp>
#include <boost/format.hpp>

#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>


#if _MSC_VER
#define snprintf _snprintf
#endif


namespace
{

int const run_count(1000000);

int const       int_            = 123456;
double const    float_          = 987.654321;
bool const      bool_           = false;
char const      literal_[]      = "test";
void const*     pointer         = &float_;

}   // namespace

void test_performance_sprintf()
{
    std::cout << "snprintf: ";

    char buffer[2048];
    std::string result;
    boost::timer timer;

    for(int i = 0; i < run_count; ++i)
    {
        snprintf(buffer, sizeof(buffer), "integer = %d, float = %f, boolean = %s, literal string = %s, pointer = %p", int_, float_, bool_ ? "true" : "false", literal_, pointer);
        result.assign(std::string(buffer));
    }

    std::cout << timer.elapsed() << " s" << std::endl;
    std::cout << result << std::endl << std::endl;
}

void test_performance_sprintf_char_buffer()
{
    std::cout << "snprintf (char buffer): ";

    char result[2048];
    boost::timer timer;

    for(int i = 0; i < run_count; ++i)
    {
        snprintf(result, sizeof(result), "integer = %d, float = %f, boolean = %s, literal string = %s, pointer = %p", int_, float_, bool_ ? "true" : "false", literal_, pointer);
    }

    std::cout << timer.elapsed() << " s" << std::endl;
    std::cout << result << std::endl << std::endl;
}

void test_performance_ostringstream()
{
    std::cout << "std::ostringstream: ";

    std::string result;
    boost::timer timer;

    for(int i = 0; i < run_count; ++i)
    {
        std::ostringstream stream;
        stream << "integer = " << int_ << ", float = " << std::fixed << std::setprecision(6) << float_ << ", boolean = " << std::boolalpha << bool_ << ", literal string = " << literal_ << ", pointer = " << pointer;
        result.assign(stream.str());
    }

    std::cout << timer.elapsed() << " s" << std::endl;
    std::cout << result << std::endl << std::endl;
}

void test_performance_ostringstream_reused()
{
    std::cout << "std::ostringstream (reused): ";

    std::string result;
    boost::timer timer;

    std::ostringstream stream;

    for(int i = 0; i < run_count; ++i)
    {
        stream.str("");
        stream << "integer = " << int_ << ", float = " << std::fixed << std::setprecision(6) << float_ << ", boolean = " << std::boolalpha << bool_ << ", literal string = " << literal_ << ", pointer = " << pointer;
        result.assign(stream.str());
    }

    std::cout << timer.elapsed() << " s" << std::endl;
    std::cout << result << std::endl << std::endl;
}

void test_performance_boost_format()
{
    std::cout << "boost::format: ";

    std::string result;
    boost::timer timer;

    for(int i = 0; i < run_count; ++i)
    {
        result = boost::str(boost::format("integer = %1%, float = %2%, boolean = %3%, literal string = %4%, pointer = %5%")
            % int_ % boost::io::group(std::fixed, std::setprecision(6), float_) % boost::io::group(std::boolalpha, bool_) % literal_ % pointer);
    }

    std::cout << timer.elapsed() << " s" << std::endl;
    std::cout << result << std::endl << std::endl;
}

void test_performance_boost_format_reused()
{
    std::cout << "boost::format (reused): ";

    std::string result;
    boost::timer timer;

    boost::format format("integer = %1%, float = %2%, boolean = %3%, literal string = %4%, pointer = %5%");

    for(int i = 0; i < run_count; ++i)
    {
        result = boost::str(format % int_ % boost::io::group(std::fixed, std::setprecision(6), float_) % boost::io::group(std::boolalpha, bool_) % literal_ % pointer);
    }

    std::cout << timer.elapsed() << " s" << std::endl;
    std::cout << result << std::endl << std::endl;
}

void test_performance_format_print()
{
    std::cout << "format::print: ";

    std::string result;
    boost::timer timer;

    for(int i = 0; i < run_count; ++i)
    {
        result.erase();
        missio::format::print(result, "integer = {0}, float = {1}, boolean = {2}, literal string = {3}, pointer = {4}", int_, float_, bool_, literal_, pointer);
    }

    std::cout << timer.elapsed() << " s" << std::endl;
    std::cout << result << std::endl << std::endl;
}

void test_performance_format_print_sink()
{
    std::cout << "format::print (sink): ";

    missio::format::sink result;
    boost::timer timer;

    for(int i = 0; i < run_count; ++i)
    {
        result.clear();
        missio::format::print(result, "integer = {0}, float = {1}, boolean = {2}, literal string = {3}, pointer = {4}", int_, float_, bool_, literal_, pointer);
    }

    std::cout << timer.elapsed() << " s" << std::endl;
    std::cout << result << std::endl << std::endl;
}

void test_performance_format_print_reused()
{
    std::cout << "format::print (reused): ";

    std::string result;
    boost::timer timer;

    missio::format::string format("integer = {0}, float = {1}, boolean = {2}, literal string = {3}, pointer = {4}");

    for(int i = 0; i < run_count; ++i)
    {
        result.erase();
        missio::format::print(result, format, int_, float_, bool_, literal_, pointer);
    }

    std::cout << timer.elapsed() << " s" << std::endl;
    std::cout << result << std::endl << std::endl;
}

void test_performance_format_print_sink_reused()
{
    std::cout << "format::print (sink; reused): ";

    missio::format::sink result;
    boost::timer timer;

    missio::format::string format("integer = {0}, float = {1}, boolean = {2}, literal string = {3}, pointer = {4}");

    for(int i = 0; i < run_count; ++i)
    {
        result.clear();
        missio::format::print(result, format, int_, float_, bool_, literal_, pointer);
    }

    std::cout << timer.elapsed() << " s" << std::endl;
    std::cout << result << std::endl << std::endl;
}

void test_performance_format_print_char_buffer_reused()
{
    std::cout << "format::print (char buffer; reused): ";

    char result[2048];
    boost::timer timer;

    missio::format::string format("integer = {0}, float = {1}, boolean = {2}, literal string = {3}, pointer = {4}");

    for(int i = 0; i < run_count; ++i)
    {
        missio::format::print(result, format, int_, float_, bool_, literal_, pointer);
    }

    std::cout << timer.elapsed() << " s" << std::endl;
    std::cout << result << std::endl << std::endl;
}

void test_performance_format_write()
{
    std::cout << "format::write: ";

    std::string result;
    boost::timer timer;

    for(int i = 0; i < run_count; ++i)
    {
        result.erase();
        missio::format::write(result, "integer = ", int_, ", float = ", float_, ", boolean = ", bool_, ", literal string = ", literal_, ", pointer = ", pointer);
    }

    std::cout << timer.elapsed() << " s" << std::endl;
    std::cout << result << std::endl << std::endl;
}

void test_performance_format_write_sink()
{
    std::cout << "format::write (sink): ";

    missio::format::sink result;
    boost::timer timer;

    for(int i = 0; i < run_count; ++i)
    {
        result.clear();
        missio::format::write(result, "integer = ", int_, ", float = ", float_, ", boolean = ", bool_, ", literal string = ", literal_, ", pointer = ", pointer);
    }

    std::cout << timer.elapsed() << " s" << std::endl;
    std::cout << result << std::endl << std::endl;
}

void test_performance_format_write_char_buffer()
{
    std::cout << "format::write (char buffer): ";

    char result[2048];
    boost::timer timer;

    for(int i = 0; i < run_count; ++i)
    {
        missio::format::write(result, "integer = ", int_, ", float = ", float_, ", boolean = ", bool_, ", literal string = ", literal_, ", pointer = ", pointer);
    }

    std::cout << timer.elapsed() << " s" << std::endl;
    std::cout << result << std::endl << std::endl;
}

int main(int argc, char *argv[])
{
    try
    {
        test_performance_sprintf();
        test_performance_sprintf_char_buffer();
        test_performance_ostringstream();
        test_performance_ostringstream_reused();
        test_performance_boost_format();
        test_performance_boost_format_reused();
        test_performance_format_print();
        test_performance_format_print_sink();
        test_performance_format_print_reused();
        test_performance_format_print_sink_reused();
        test_performance_format_print_char_buffer_reused();
        test_performance_format_write();
        test_performance_format_write_sink();
        test_performance_format_write_char_buffer();
    }
    catch(std::exception const& e)
    {
        std::cout << std::endl << "caught std::exception: " << e.what() << std::endl;

        return EXIT_FAILURE;
    }
    catch(...)
    {
        std::cout << std::endl << "caught unknown exception" << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
