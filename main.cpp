#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::tcp;

int main()
{
    std::cout << "Start server." << std::endl;

    boost::asio::io_service io_service; //Должен быть как минимум один такой объект
    std::cout << "io_service - OK" << std::endl;

    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(),2101)); //Прослушиватель для ожидания подкючения и его обработки. Приимает параметры: объект типа io_service и что собственно слушать (любой адрес и порт 444)
    std::cout << "acceptor - OK" << std::endl;

    while(true)
    {
        tcp::socket socket(io_service); //Создаем подключение, которое будет в ВЕЧНОМ цикле крутиться и ждать подключение клиента.
        std::cout << "socket - OK" << std::endl;

        acceptor.accept(socket); //Слушаем подключение. На сколько я понял, программа тут застрянет пока не дождется подключения клиента.
        std::cout << "Client connected - OK" << std::endl;

        boost::asio::write(socket,boost::asio::buffer("Connect complited")); //пишем в подключенный сокет сообщение.
        std::cout << "Message send - OK" << std::endl;
    }
    return 0;
}
