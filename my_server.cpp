#include "myserver.h"


void MyServer::Start_Server(int port)
{
    try
    {
        list_of_files.clear(); //Очищаем список файлов.
        boost::asio::io_service io_service; //Необходимо для работы boost::asio
        boost::asio::ip::tcp::socket socket(io_service); //Создаем подключение
        boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port)); //Создаем "прослушиватель" подключения
        Start_Acceptor(acceptor,socket); //Ждем подключения. (Вернет управление только после подключения клиента)
        Send_Resources_List(socket); //Передаем список файлов
        std::string filename=Get_Fille_Name(socket);
        Send_Filename(filename, socket); //Передаем имя файла
        Send_File(filename,socket); //Передаем файл, получая сначала имя файла
        std::cout<<"Сеанс завершен успешно!"<<'\n';
    }
    catch(const char* er)
    {
        std::cout<<er<<'\n';
        std::cout<<"соединение сброшено. Жду следующего подключения..."<<'\n';
    }
}

std::string MyServer::Get_Fille_Name(boost::asio::ip::tcp::socket &socket)
{
    boost::array <char,10> buffer; //Массив нужен небольшой, т.к. отправляется только номер файла
    int index=0;
    try
    {
        boost::asio::read(socket, boost::asio::buffer(buffer),boost::asio::transfer_all()); //Читаем ответ клиента (номер файла).
        index=std::atoi(buffer.data()); //Преобразуем в число
        if(index<list_of_files.size()) return list_of_files[index]; //Если номер файла корректен dозвращаем название файла
        else throw ("Файл не выбран"); //Иначе Шлем все нахуй!
    }
    catch (...)
    {
        throw("Warning Get_Fille_Name"); //Если произошел сбой
    }
}

void MyServer::Start_Acceptor(boost::asio::ip::tcp::acceptor &acceptor, boost::asio::ip::tcp::socket &socket)
{
    acceptor.accept(socket); //Запускаем ожидание подключения
}

void MyServer::Send_File(std::string &file_name, boost::asio::ip::tcp::socket &socket)
{
    try
    {
        std::string file_path="./Resourses/"+file_name; //Переменная для хранения пути файла. Собирается из имени папки и имени файла.
        std::ifstream in_file_stream(file_path, std::ios::binary); //Открываем в файловом потоке файл "file_name"
        boost::array<char,256> file_buffer; //Создаем буфер для хранения пакетов
        int size_package=file_buffer.size(); //Узнаем размер буфера
        while (in_file_stream) //Пока файловый поток считывает файл
        {
            in_file_stream.read(file_buffer.data(),size_package); //Записываем в буфер порцию данных
            boost::asio::write(socket,boost::asio::buffer(file_buffer)); //Отправляем даные
        }
        in_file_stream.close(); // Закрываем файловый поток
        socket.close();         // Закрываем подключение
    }
    catch(...)
    {
        throw("Warning Send_file"); //Если произошел сбой
    }
}

void MyServer::Send_Resources_List(boost::asio::ip::tcp::socket &socket)
{

    try
    {
        DIR *directory = opendir("./Resourses"); //Указываем директорию
        struct dirent *file; //Структура представляющая НЕЧТО (файл, папка)
        while((file = readdir(directory)) != NULL) //Пока не все из директории считано
        {
            if(file->d_type!=4) //Если не делать эту проверку, то появится два две строчки "." и ".." А нам нужны файлы
            {
                boost::asio::write(socket,boost::asio::buffer((std::string)file->d_name)); //Отправляем название файла
                MyServer::list_of_files.insert(list_of_files.end(),(std::string)file->d_name); //Записываем имена файлов в хранилище
                boost::asio::write(socket,boost::asio::buffer("%")); //Отправляем разделитель, т.к. TCP протокол сам решает когда нужно отправить очередной пакет. В следствие чего там может оказаться мусор (он там всегда есть) и он может отправить все за один раз и за несколько. Разделитель принимается клиентом и делает перенос строки.
            }
        }
        boost::asio::write(socket,boost::asio::buffer("//////")); //Для указания конца списка отправляем строку из символов, которые не могут встретиться в названии файла.
    }
    catch(...)
    {
        throw("Warning Send_files_in_resources"); //Если произошел сбой
    }
}

void MyServer::Send_Filename(std::__cxx11::string &file_name, boost::asio::ip::tcp::socket &socket)
{

    try
    {
        boost::asio::write(socket,boost::asio::buffer(file_name+"%")); //Отправляем название файла и разделитель (%)
    }
    catch(...)
    {
        throw("Warning Send_filename"); //Если произошел сбой
    }
}
