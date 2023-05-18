#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <iostream>
#include <boost/program_options.hpp>
#include <filesystem>

#include <optional>

//Опции как в работе 8
namespace Options
{
    //Хранение сырых опций
    struct RawOptions
    {
        unsigned short port{9000};
    };


    //Парсим опции
    std::optional<RawOptions> getRawOptions(int argc, const char *argv[])
    {
        namespace po = boost::program_options;

        RawOptions opt;

        try
        {
            po::options_description desc{"Options"};
            desc.add_options()
                    ("help,h", "Show help")
                    ("port,P",      po::value<  unsigned short> (&opt.port),            "TCP Port DEF: 9000");


            po::variables_map vm;
            po::store(parse_command_line(argc, argv, desc), vm);
            po::notify(vm);



            if (vm.count("help")) {
                std::cout << desc << "\n";
            }


        }
        catch(...)
        {
            return std::nullopt;
        }

        return opt;
    }


}
#endif // OPTIONS_HPP
