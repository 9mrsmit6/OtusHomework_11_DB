#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <memory>
#include <utility>
#include <iostream>
#include <boost/asio.hpp>


//Соединение. Аналогично примерам.
namespace Net
{
    using ba=boost::asio::ip::tcp;

    //Это обьект для обработки строк от СУБД
    struct SocketPrinter
    {
        SocketPrinter(ba::socket& socket_):
            socket(socket_)
        {

        }
        //Отправляем в сокет
        void executeResponse(std::string&& mes)
        {
            boost::asio::streambuf out;
            std::ostream ost{&out};
            ost<<mes<<std::endl;
            boost::asio::write(socket, out);
        }
    private:
        ba::socket& socket;
    };

    //Соединение из предыдущей работы
    //С небольшими изменениями в виде синхронной отправки
    template<class Handler>
    struct Connection: public std::enable_shared_from_this<Connection<Handler>>
    {
        Connection(ba::socket& socket_, Handler& handler_):
            socket(std::move(socket_)),
            handler{handler_},
            printer{socket}
        {
        }

        void read()
        {
            auto self(this->shared_from_this());

           //Так как чтение построчное то выбрал вариант async_read_until
            boost::asio::async_read_until(socket, buf, "\n",
                    [this, self](boost::system::error_code ec, std::size_t length)
                    {
                        //Всегда обработать поток.
                        std::istream is{&buf};
                        auto retStr=handler.execute(is, printer);

                        //Отвечаем
                        boost::asio::streambuf out;
                        std::ostream ost{&out};
                        ost<<retStr<<std::endl;
                        boost::asio::write(socket, out);


                        if (!ec)
                        {
                            //Если ошибки нет то продолжаю цепочку обработки. Иначе соединение уничтожается
                            read();
                        }

                    });


        }

        ~Connection()=default;
        private:
            ba::socket socket;
            boost::asio::streambuf buf;
            Handler& handler;
            SocketPrinter printer;
    };
}

#endif // CONNECTION_HPP
