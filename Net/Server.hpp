#ifndef SERVER_HPP
#define SERVER_HPP
#include "Connection.hpp"
#include "../NetReqHandler/Handler.hpp"

//Сервер крайне похожий на примеры из вебинара и examples от boost::asio
namespace Net
{
    using ba=boost::asio::ip::tcp;

    struct Server
    {
        Server(boost::asio::io_context& io_context_, unsigned short port):
            acceptor_(io_context_, ba::endpoint(ba::v4(), port)),
            handler{},
            io_context{io_context_}
        {
            accept();
        }

        ~Server()=default;

        private:
            ba::acceptor acceptor_;
            Handler handler;
            boost::asio::io_context& io_context;

            void accept()
            {
                //Прослушиваем и создаем соединение с обработчиком запросов. Обработчик из предыдущей самостоятельной
                acceptor_.async_accept(
                        [this](boost::system::error_code ec, ba::socket socket)
                        {
                          if (!ec)
                          {
                            socket.set_option(boost::asio::socket_base::keep_alive{true});
                            std::make_shared<Connection<Handler>>(socket, handler)->read();
                          }
                          accept();
                        });
            }


    };

}
#endif // SERVER_HPP
