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
#include <stdexcept>

// Проект "Клиент - Сервер. Передача файлов".
// Серверная часть "MyServer"
// Мышко Егор Викторович 01.02.2017г.

// Задачи:
// - Метод Send_Resources_List (ту часть, где в папке ищем файлы) необходимо переписать с использованием boost::filesystem

class MyServer
{
private:
    std::vector<std::string> list_of_files; //Хранилище для имен файлов
    std::string Get_Fille_Name(boost::asio::ip::tcp::socket &socket); //Получаем от клиента имя файла, которое необходимо отправить
    void Send_Resources_List(boost::asio::ip::tcp::socket &socket); //Отправка списка файлов, находящихся на сервере в папке "Resourses"
    void Start_Acceptor(boost::asio::ip::tcp::acceptor &acceptor, boost::asio::ip::tcp::socket &socket); //Метод начинает прослушиватьь подключение
    void Send_File(std::string &file_name, boost::asio::ip::tcp::socket &socket); //Отправка файла
    void Send_Filename(std::string &file_name, boost::asio::ip::tcp::socket &socket); //Отправка имени файла
public:
    void Start_Server(int port=2102); //Запуск сервера
};

#endif // MYSERVER_H

