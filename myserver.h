#ifndef MYSERVER
#define MYSERVER

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include <iterator>
#include <time.h>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

class MyServer
{
private:
    void Get_files_in_resources(boost::asio::ip::tcp::socket &socket); //Отправка списка файлов, находящихся на сервере в папке "Resourses"
    void Start_acceptor(boost::asio::ip::tcp::acceptor &acceptor, boost::asio::ip::tcp::socket &socket); //Метод начинает прослушиватьь подключение
    void Send_file(std::string file_name, boost::asio::ip::tcp::socket &socket); //Отправка файла
public:
    void Start_server(int port=2102); //Запуск сервера
};

#endif // MYSERVER_H

