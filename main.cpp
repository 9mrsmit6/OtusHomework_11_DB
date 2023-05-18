#include <iostream>
#include "Net/Server.hpp"
#include "Options/Options.hpp"
using namespace std;


int main(int argc, const char *argv[])
{
    //Это из первой лабы про boost. Избыточно, но boost подключен в проект и модуль уже существует.
    auto rawOptions=Options::getRawOptions(argc,argv);

    if(!rawOptions)
    {
        std::cout<<"Options Parse Error";
        return -1;
    }

    //Сервер из 10 работы
    boost::asio::io_context io_context;
    Net::Server server(io_context, rawOptions.value().port);
    //Запускаем контекст на выполнение
    io_context.run();
    return 0;
}
