#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <string>
#include <time.h>
#include <boost/filesystem.hpp>

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

    std::ofstream Out_File_Stream("OutTestFile.mp3", std::ios::binary); //Создаем поток для записи файла
    std::cout << "Out_File_Stream - OK" << std::endl;

    boost::array <char,5000> Buffer; //Буфер для хранения полученных данных
    std::cout << "Buffer - OK" << std::endl;


    int len=0;

    while(len<1922612)
    {
        len+=boost::asio::read(client_socket, boost::asio::buffer(Buffer),boost::asio::transfer_at_least(1)); //Читаем ответ сервера
        for(int i=0; i<Buffer.size();i++)
        {
            Out_File_Stream<<Buffer[i];
            //usleep(10);
        }

        std::cout << "Length: "<< len << std::endl;
    }
    //Out_File_Stream<<Buffer; //Эта хуйня возможно только все испортит
    sleep(2);           //
    Out_File_Stream.close();
    client_socket.close();
    std::cout << "Write in cout - OK" << std::endl;

    return 0;
}
