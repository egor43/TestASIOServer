#ifndef MYCLIENT
#define MYCLIENT

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <string>
#include <time.h>
#include <boost/filesystem.hpp>

// Проект "Клиент - Сервер. Передача файлов".
// Клиентская часть "MyClient"
// Мышко Егор Викторович 01.02.2017г.

// Задачи:


class MyClient
{
private:
    std::string file_name="File"; //Переменная для хрпнения имени файла, инициализированная значением по умолчанию.
    void Start_Connect(boost::asio::ip::tcp::endpoint &client_endpoint, boost::asio::ip::tcp::socket &client_socket); //Запускает подключение к серверу
    void Print_FileList(boost::asio::ip::tcp::socket &client_socket); //Выводит на консоль список файлов, хранящихся на сервере
    void Send_NumberFile(boost::asio::ip::tcp::socket &client_socket); //Отправляет номер файла серверу для дальнейшего его получения
    void Get_File(boost::asio::ip::tcp::socket &client_socket, std::string &file_name); //Получает файл от сервера
    void Get_FileName(boost::asio::ip::tcp::socket &client_socket); //Получает имя файла от сервера
public:
    void Start_Client(std::string &&ip_adress, int port); //Запуск клиента
};

#endif // MYCLIENT
