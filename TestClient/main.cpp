#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <string>

using boost::asio::ip::tcp;

int main()
{
    std::cout << "Client - started!" << std::endl;

    boost::asio::io_service io_service; //Создали обязательный объект класса io_service
    std::cout << "io_service - OK" << std::endl;

    tcp::endpoint client_endpoint; //Создаем точку для подключения (куда будем стучаться то :D )
    std::cout << "client_endpoint - OK" << std::endl;

    client_endpoint.port(2102); //Задаем порт для подключения
    std::cout << "port - OK" << std::endl;

    client_endpoint.address(boost::asio::ip::address_v4::from_string("127.0.0.1")); //Задаем адрес подключения
    std::cout << "ip_adress - OK" << std::endl;

    tcp::socket client_socket (io_service); //Создаем сокет клиента
    std::cout << "socket - OK" << std::endl;

    client_socket.connect(client_endpoint); //Начинаем стучаться по указанному адресу
    std::cout << "connected - OK" << std::endl;

    std::ofstream Out_File_Stream("OutTestFile.txt"); //Создаем поток для записи файла
    std::cout << "Out_File_Stream - OK" << std::endl;

    boost::array <char,256> buffer; //Буфер для хранения полученных данных
    std::cout << "Buffer - OK" << std::endl;

    client_socket.read_some(boost::asio::buffer(buffer)); //Читаем ответ сервера
    std::cout << "Read socket - OK" << std::endl;

    Out_File_Stream << buffer.data(); //Пишем в файл полученный ответ
    std::cout << "Write in cout - OK" << std::endl;

return 0;
}
