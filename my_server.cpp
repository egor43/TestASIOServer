#include "myserver.h"


void MyServer::Start_server(int port)
{
    boost::asio::io_service io_service; //Необходимо для работы boost::asio
    boost::asio::ip::tcp::socket socket(io_service); //Создаем подключение
    boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port)); //Создаем "прослушиватель" подключения
    Start_acceptor(acceptor,socket); //Ждем подключения. (Вернет управление только после подключения клиента)
    Send_files_in_resources(socket); //Передаем список файлов
    Send_file(Get_Fille_Name(socket),socket); //Передаем файл, получая сначала имя файла
}

std::string MyServer::Get_Fille_Name(boost::asio::ip::tcp::socket &socket)
{
    boost::array <char,10> Buffer; //Массив нужен небольшой, т.к. отправляется только номер файла
    int index=0; //Индекс файла
    try
    {
        boost::asio::read(socket, boost::asio::buffer(Buffer),boost::asio::transfer_at_least(1)); //Читаем ответ клиента (номер файла).int index=0;
        for(int i=0;i<Buffer.size();i++)
        {
                if(Buffer[i]!='%') index+=Buffer[i]-'0'; //С помощью этой магии мы получаем ЦИФРУ (% в if() нужен для отделения мусора от значимой части)
                else  break;
        }
        if(index<List_of_Files.size()) return List_of_Files[index]; //Если номер файла корректен dозвращаем название файла
        else throw ("Файл не выбран"); //Иначе Шлем все нахуй!
    }
    catch (...){ throw ("Соединение завершилось тра-та-та-тра-та-та");}
}

void MyServer::Start_acceptor(boost::asio::ip::tcp::acceptor &acceptor, boost::asio::ip::tcp::socket &socket)
{
    acceptor.accept(socket); //Запускаем ожидание подключения
}

void MyServer::Send_file(std::string file_name, boost::asio::ip::tcp::socket &socket)
{
    std::ifstream in_file_stream(file_name, std::ios::binary); //Открываем в файловом потоке файл "file_name"
    int file_size = boost::filesystem::file_size(file_name); //Узнаем размер файла
    boost::array<char,256> File_Buffer; //Создаем буфер для хранения пакетов
    int size_package=File_Buffer.size(); //Узнаем размер буфера
    while (in_file_stream) //Пока файловый поток считывает файл
    {
        in_file_stream.read(File_Buffer.data(),size_package); //Записываем в буфер порцию данных
        boost::asio::write(socket,boost::asio::buffer(File_Buffer)); //Отправляем даные
    }
    in_file_stream.close(); // Закрываем файловый поток
    socket.close();         // Закрываем подключение
}

void MyServer::Send_files_in_resources(boost::asio::ip::tcp::socket &socket)
{
    DIR *dir = opendir("./Resourses"); //Указываем директорию
    struct dirent *ent; //Структура представляющая НЕЧТО (файл, папка)
    while((ent = readdir(dir)) != NULL) //Пока не все из директории считано
        {
            if(ent->d_type!=4) //Если не делать эту проверку, то появится два две строчки "." и ".." А нам нужны файлы
            {
                MyServer::List_of_Files.insert(List_of_Files.end(),(std::string)ent->d_name); //Записываем имена файлов в хранилище
                boost::asio::write(socket,boost::asio::buffer((std::string)ent->d_name)); //Отправляем название файла 
                boost::asio::write(socket,boost::asio::buffer("%")); //Отправляем разделитель, т.к. TCP протокол сам решает когда нужно отправить очередной пакет. В следствие чего там может оказаться мусор (он там всегда есть) и он может отправить все за один раз и за несколько. Разделитель принимается клиентом и делает перенос строки.
            }

        }
}
