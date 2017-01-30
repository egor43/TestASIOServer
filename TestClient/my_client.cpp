#include "myclient.h"

bool MyClient::Exit_Menu()
{
    std::cout<<"Для выхода из программы нажмите: q "<<'\n';
    char ch=' ';
    std::cin>>ch;
    std::cin.clear();
    if(ch=='q') return false;
    else return true;
}

bool MyClient::Start_Client(std::__cxx11::string &&ip_adress, int port)
{
    try
    {
        boost::asio::io_service io_service; //Создали обязательный объект класса io_service
        boost::asio::ip::tcp::endpoint client_endpoint; //Создаем точку для подключения (куда будем стучаться то :D )
        client_endpoint.port(port); //Задаем порт для подключения
        client_endpoint.address(boost::asio::ip::address_v4::from_string(ip_adress)); //Задаем адрес подключения
        boost::asio::ip::tcp::socket client_socket (io_service); //Создаем сокет клиента
        Start_Connect(client_endpoint,client_socket); //Подключаемся к серверу
        Print_FileList(client_socket); //Выводим список файлов
        Send_NumberFile(client_socket); //Передаем номер файла
        Get_FileName(client_socket); //Получаем имя файла
        Get_File(client_socket,file_name); //Получаем файл
    }
    catch(...)
    {
        std::cout<<"Возникла ошибка"<<'\n';
    }
    return Exit_Menu();
}

void MyClient::Start_Connect(boost::asio::ip::tcp::endpoint &client_endpoint, boost::asio::ip::tcp::socket &client_socket)
{
    try
    {
        client_socket.connect(client_endpoint); //Начинаем стучаться по указанному адресу
    }
    catch(...)
    {
        throw("Warning Start_Connect");
    }
}
void MyClient::Print_FileList(boost::asio::ip::tcp::socket &client_socket)
{

    try
    {
        int package_length=0;
        boost::array <char,34> Buffer_system;
        while(package_length<34)
        {
            package_length+=boost::asio::read(client_socket, boost::asio::buffer(Buffer_system),boost::asio::transfer_at_least(1)); //Читаем ответ со списком файлов сервера
            for(int i=0; i<package_length;i++)
            {
                if(Buffer_system[i]=='%') std::cout<<std::endl;
                else if(Buffer_system[i]!='\0') std::cout<<Buffer_system[i];
            }
        }
    }
    catch (...)
    {
        throw("Warning Print_FileList");
    }
}

void MyClient::Send_NumberFile(boost::asio::ip::tcp::socket &client_socket)
{
    try
    {
        boost::array<std::string,1> n;
        std::cout<<"Enter number:" <<'\n';
        std::cin>>n[0];
        boost::asio::write(client_socket,boost::asio::buffer(n[0]));
        boost::asio::write(client_socket,boost::asio::buffer("%"));
    }
    catch(...)
    {
        throw("Warning Send_NumberFile");
    }
}

void MyClient::Get_File(boost::asio::ip::tcp::socket &client_socket, std::string &file_name)
{
    std::ofstream Out_File_Stream(file_name, std::ios::binary); //Поток ввода в файл
    boost::array <char,256> Buffer; //Буфер для хранения полученных данных
    int package_length=0;
    try
    {
        while(true)
        {
            package_length+=boost::asio::read(client_socket, boost::asio::buffer(Buffer),boost::asio::transfer_at_least(1)); //Читаем ответ сервера
            for(int i=0; i<Buffer.size();i++)
            {
                Out_File_Stream<<Buffer[i];
            }
        }
    }
    catch(boost::system::system_error error)
    {
        std::cout<<"Файл загружен"<<'\n';
    }
    catch(...)
    {
        throw("Warning Get_File");
    }

    Out_File_Stream.close();
    client_socket.close();
}

void MyClient::Get_FileName(boost::asio::ip::tcp::socket &client_socket)
{
    try
    {
        int package_length=0;
        boost::array <char,34> Buffer;
        package_length+=boost::asio::read(client_socket, boost::asio::buffer(Buffer),boost::asio::transfer_at_least(1));
        file_name="";
        for(int i=0; i<package_length;i++)
        {
            if(Buffer[i]!='%') file_name+=Buffer[i];
            else break;
        }
    }
    catch(...)
    {
        throw("Warning Get_FileName");
    }
}

