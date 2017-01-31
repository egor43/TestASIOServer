#include <iostream>
#include "myserver.h"
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main()
{

    MyServer server;
    std::cout<<"Server start..."<<'\n';
    while(true)
    {
        server.Start_server();
    }




{
    //server.Start_acceptor();
    //server.Send_file("video.mp4");


//    std::cout << "Start server." << std::endl;

//    boost::asio::io_service io_service; //Должен быть как минимум один такой объект
//    std::cout << "io_service - OK" << std::endl;

//    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(),2102)); //Прослушиватель для ожидания подкючения и его обработки. Приимает параметры: объект типа io_service и что собственно слушать (любой адрес и порт 444)
//    std::cout << "acceptor - OK" << std::endl;

//    tcp::socket socket(io_service); //Создаем подключение, которое будет в ВЕЧНОМ цикле крутиться и ждать подключение клиента.
//    std::cout << "socket - OK" << std::endl;

//    std::ifstream in_file_stream("video.mp4", std::ios::binary); //Создаем файловый поток на чтение файла (бинарно).
//    std::cout << "File_Stream - OK" << std::endl;

//    int file_size = boost::filesystem::file_size("video.mp4");
//    std::cout << "File Size = " << file_size << " Bytes" << std::endl;

//    boost::array<char,256> File_Buffer; //Создаем буфер для файла;
//    std::cout << "File_Buffer - OK" << std::endl;

//    int size_package=File_Buffer.size();
//    int size_send=0;

//    acceptor.accept(socket);

//    while (in_file_stream)
//    {
//        std::cout << "while - OK" << std::endl;
//        in_file_stream.read(File_Buffer.data(),size_package);
//        std::cout << "read - OK" << std::endl;
//        size_send+=boost::asio::write(socket,boost::asio::buffer(File_Buffer));
//        std::cout << "sended: "<< size_send << std::endl;
//    }

//    in_file_stream.close();
//    socket.close();
}

    return 0;
}
