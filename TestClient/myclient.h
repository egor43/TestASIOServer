#ifndef MYCLIENT
#define MYCLIENT

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <string>
#include <time.h>
#include <boost/filesystem.hpp>

class MyClient
{
private:
    std::string file_name="File1.mp3";
    void Start_Connect(boost::asio::ip::tcp::endpoint &client_endpoint, boost::asio::ip::tcp::socket &client_socket);
    void Print_FileList(boost::asio::ip::tcp::socket &client_socket);
    void Send_NumberFile(boost::asio::ip::tcp::socket &client_socket);
    void Get_File(boost::asio::ip::tcp::socket &client_socket, std::string &file_name);
    void Get_FileName(boost::asio::ip::tcp::socket &client_socket);
public:
    void Start_Client(std::string &&ip_adress, int port);
};

#endif // MYCLIENT
