#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <fstream>
#include <iterator>

using boost::asio::ip::tcp;

int main()
{
    std::cout << "Start server." << std::endl;

    boost::asio::io_service io_service; //Должен быть как минимум один такой объект
    std::cout << "io_service - OK" << std::endl;

    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(),2101)); //Прослушиватель для ожидания подкючения и его обработки. Приимает параметры: объект типа io_service и что собственно слушать (любой адрес и порт 444)
    std::cout << "acceptor - OK" << std::endl;

    tcp::socket socket(io_service); //Создаем подключение, которое будет в ВЕЧНОМ цикле крутиться и ждать подключение клиента.
    std::cout << "socket - OK" << std::endl;

    std::ifstream in_file_stream("test", std::ios::binary); //Создаем файловый поток на чтение файла (бинарно).
    std::cout << "File_Stream - OK" << std::endl;

    std::vector <char> File_Buffer; //Создаем буфер для файла;
    std::cout << "File_Stream - OK" << std::endl;

    File_Buffer.insert(std::begin(File_Buffer), std::istreambuf_iterator <char> {in_file_stream}, std::istreambuf_iterator<char>{}); //Заполняем буфер данным файлом, открытым в бинарном режиме
    std::cout << "File_Buffer inserted - OK" << std::endl;

    while(true)
    {
        acceptor.accept(socket); //Слушаем подключение. На сколько я понял, программа тут застрянет пока не дождется подключения клиента.
        std::cout << "Client connected - OK" << std::endl;

        boost::asio::write(socket,boost::asio::buffer(File_Buffer.data(),File_Buffer.size())); //пишем в подключенный сокет буфер (файл).
        std::cout << "Message send - OK" << std::endl;
        socket.close(); //Закрываем подключение
    }
    return 0;
}
