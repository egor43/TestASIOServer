#include "myclient.h"

void MyClient::Start_Client(std::__cxx11::string &&ip_adress, int port)
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
    catch(const char* er) //Сюда придут все исключения, которые мы викинули сами для дальнейшей обработки
    {
        if(er!="0") std::cout<<"Возникла ошибка"<<'\n'; //Если в сообщении приходит "0" - значит мы уже оповестили пользователя об ошибке, если приходит иное - выводим сообщение.
    }
    catch(...) //Для ловли всего остального
    {
        std::cout<<"Возникла ошибка"<<'\n';
    }
}

void MyClient::Start_Connect(boost::asio::ip::tcp::endpoint &client_endpoint, boost::asio::ip::tcp::socket &client_socket)
{
    try
    {
        client_socket.connect(client_endpoint); //Начинаем стучаться по указанному адресу
    }
    catch(boost::system::system_error &er)
    {
        boost::system::error_code error = er.code(); //Получаем исключение
        if(error.value()==111)
        {
            std::cout<<"Не удалось подключиться к серверу. Попробуйте перезапустить клиент."<<'\n';
            throw("0");
        }
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
        int count_number_file=0; //Счетчик номера файла
        int count_end_filelist=0; //Счетчик для подсчета символов конца списка. (Сервер отправляет "//////////" если список закончен).
        boost::array <char,5> Buffer_system; //Создали буфер для хранения ответа от сервера.
        while(true)
        {
            count_end_filelist=0; //Зануляем счетчик после каждой записи пакета, полученного от сервера
            boost::asio::read(client_socket, boost::asio::buffer(Buffer_system),boost::asio::transfer_all()); //Читаем ответ со списком файлов сервера
            for(int i=0; i<Buffer_system.size();i++) //В теле цикла выводим на экран список файлов сервера
            {
                switch(Buffer_system[i])
                {
                    case '%':
                    {
                        std::cout<<" <--- ("<<count_number_file++<<") "; //Выводим номер файла в списке
                        std::cout<<std::endl; //Когда нашли разделитель, переносим строчку
                        break;
                    }
                    case '/':
                    {
                        count_end_filelist++; //Когда нашли символ конца строки => увеличиваем счетчик
                        break;
                    }
                    default:
                    {
                        std::cout<<Buffer_system[i]; //Выводим посимвольно имя файла
                        break;
                    }
                }
            }
            if(count_end_filelist>1) break; //Больше 1 сделано на всякий случай.
        }
    }
    catch(boost::system::system_error &er)
    {
        boost::system::error_code error = er.code(); //Получаем исключение
        if(error.value()==104)
        {
            std::cout<<"Соединение сброшено. Попробуйте перезапустить клиент"<<'\n';
            throw("0");
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
        std::cin.clear(); //Очищаем поток ввода
        boost::array<std::string,1> buffer; //Создали буфер для хранения номера файла.
        std::cout<<"Enter number:" <<'\n';
        std::cin>>buffer[0]; //Записали номер файла в буфер
        boost::asio::write(client_socket,boost::asio::buffer(buffer[0])); //Отправляем номер файла
        boost::asio::write(client_socket,boost::asio::buffer("%%%%%%%%%%")); //Отправляем разделитель, чтобы сервер смог разобраться, где необходимая информация, а где мусор.
    }
    catch(boost::system::system_error &er)
    {
        boost::system::error_code error = er.code();  //Получаем исключение
        if(error.value()==32)
        {
            std::cout<<"Сервер не отвечает. Попробуйте перезапустить клиент."<<'\n';
            throw("0");
        }
    }
    catch(...)
    {
        throw("Warning Send_NumberFile");
    }
}

void MyClient::Get_File(boost::asio::ip::tcp::socket &client_socket, std::string &file_name)
{
    std::ofstream out_file_stream(file_name, std::ios::binary); //Поток ввода в файл
    boost::array<char,256> buffer; //Буфер для получения информации от сервера
    //int count=0; //Переменная для подсчета полученных данных (для отладки)
    try
    {
        std::cout<<"Началась загрузка..."<<'\n';
        while(true)
        {
            boost::asio::read(client_socket, boost::asio::buffer(buffer,256),boost::asio::transfer_all()); //Читаем ответ сервера
            for(int i=0; i<buffer.size();i++)
            {
                out_file_stream<<buffer[i]; //Пишем информацию из буфера в файл
            }
            //std::cout<<count<<'\n'; //Для отладки
        }
    }
    catch(boost::system::system_error &er)
    {
        boost::system::error_code error = er.code(); //Получаем исключение
        if(error.value()==104)
        {
            sleep(1); //Даем время клиенту все записать
            std::cout<<"Передача завершена. Соединение закрыто."<<'\n';
        }
    }
    catch(...)
    {
        throw("Warning Get_File");
    }
    client_socket.close(); //Закрываем соединение
    out_file_stream.close(); //Закрываем поток вывода в файл    
}

void MyClient::Get_FileName(boost::asio::ip::tcp::socket &client_socket)
{
    try
    {
        boost::asio::streambuf buffer; //Создали буфер для хранения информации полученной от сервера
        boost::asio::read(client_socket, buffer,boost::asio::transfer_at_least(128)); //Получаем ответ от сервера, заполняя 128 байт, т.к. сервер выделяет именно такое колличество информации на имя файла. (Если эта цифра не совпадет с сервером - файл будет передаваться иногда не полностью, т.к. данные файла улетят в этот метод и он их отсечет разделителем)
        file_name.clear(); //Очищаем переменную имени cоздаваемого файла
        std::istream stream_in_string (&buffer); //Для получения строки из буфера создаем поток
        std::string string_name=""; //Временная переменная для хранения информации из буфера
        stream_in_string >> string_name; //Пишем буфер во временную переменную
        for(char i : string_name) //В теле цикла, если встречаем '%' - значит полезная информация закончена, если '\0' или '/', значит мы встретили более-менее адекватный символ и можем добавить его в переменную для хранения имени файла.
        {
            if(i=='%') break;
            if(i!='\0' && i!='/') file_name+=i;
        }
        std::cout<<"Вы выбрали: " <<file_name<<'\n';
    }
    catch(boost::system::system_error &er)
    {
        boost::system::error_code error = er.code(); //Получаем исключение
        if(error.value()==104)
        {
            std::cout<<"Соединение сброшено. Попробуйте перезапустить клиент"<<'\n';
            throw("0");
        }
    }
    catch(...)
    {
        throw("Warning Get_FileName");
    }
}

