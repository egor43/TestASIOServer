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
    return Exit_Menu(); //В любом случае вызываем метод "меню выхода".
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
        int count_end_filelist=0;
        boost::array <char,5> Buffer_system; //Создали буфер для хранения ответа от сервера.
        while(true)
        {
            count_end_filelist=0;
            boost::asio::read(client_socket, boost::asio::buffer(Buffer_system),boost::asio::transfer_all()); //Читаем ответ со списком файлов сервера
            for(int i=0; i<Buffer_system.size();i++) //В теле цикла выводим на экран список файлов сервера
            {
                switch(Buffer_system[i])
                {
                    case '%':
                    {
                        std::cout<<std::endl; //Когда нашли разделитель, переносим строчку
                        break;
                    }
                    case '/':
                    {
                        count_end_filelist++;
                        break;
                    }
                    default:
                    {
                        std::cout<<Buffer_system[i]; //Выводим посимвольно имя файла
                        break;
                    }
                }
            }
            if(count_end_filelist>1) break;
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
        boost::array<std::string,1> n; //Создали буфер для хранения номера файла.
        std::cout<<"Enter number:" <<'\n';
        std::cin>>n[0]; //Записали номер файла в буфер
        boost::asio::write(client_socket,boost::asio::buffer(n[0])); //Отправляем номер файла
        boost::asio::write(client_socket,boost::asio::buffer("%%%%%%%%%%")); //Отправляем разделитель, чтобы сервер смог разобраться, где необходимая информация, а где мусор.
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
    try
    {
        while(true)
        {
            boost::asio::read(client_socket, boost::asio::buffer(Buffer),boost::asio::transfer_all()); //Читаем ответ сервера
            for(int i=0; i<Buffer.size();i++) //В теле цикла поэлементно записываем информацию в поток.
            {
                Out_File_Stream<<Buffer[i]; //Если так не делать, то часть информации пропадает
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

    Out_File_Stream.close(); //Закрываем поток вывода в файл
    client_socket.close(); //Закрываем соединение
}

void MyClient::Get_FileName(boost::asio::ip::tcp::socket &client_socket)
{
    try
    {
        boost::asio::streambuf Buffer; //Создали буфер для хранения информации полученной от сервера
        boost::asio::read_until(client_socket, Buffer,'%'); //Получаем ответ от сервера
        file_name.clear(); //Очищаем переменную имени cоздаваемого файла
        std::istream stream_in_string (&Buffer);
        std::string string_name="";
        stream_in_string >> string_name;
        for(char i : string_name)
        {
            if(i=='%') break;
            if(i!='\0' && i!='/') file_name+=i;
        }
        std::cout<<file_name<<'\n';
    }
    catch(...)
    {
        throw("Warning Get_FileName");
    }
}

