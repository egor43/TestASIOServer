#include "myserver.h"


void MyServer::Start_server(int port)
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);
    boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port));
    Start_acceptor(acceptor,socket);
    Get_files_in_resources(socket);
    //Send_file("video.mp4",socket);
}

void MyServer::Start_acceptor(boost::asio::ip::tcp::acceptor &acceptor, boost::asio::ip::tcp::socket &socket)
{
    acceptor.accept(socket);
}

void MyServer::Send_file(std::string file_name, boost::asio::ip::tcp::socket &socket)
{
    std::ifstream in_file_stream(file_name, std::ios::binary);
    int file_size = boost::filesystem::file_size(file_name);
    boost::array<char,256> File_Buffer;
    int size_package=File_Buffer.size();
    while (in_file_stream)
    {
        in_file_stream.read(File_Buffer.data(),size_package);
        boost::asio::write(socket,boost::asio::buffer(File_Buffer));
    }
    in_file_stream.close();
    socket.close();
}

void MyServer::Get_files_in_resources(boost::asio::ip::tcp::socket &socket)
{
    DIR *dir = opendir("./Resourses");
    struct dirent *ent;
    while((ent = readdir(dir)) != NULL)
        {
            if(ent->d_type!=4)
            {
                boost::asio::write(socket,boost::asio::buffer((std::string)ent->d_name));
                boost::asio::write(socket,boost::asio::buffer("%"));
            }

        }
}
