#include "myclient.h"

using boost::asio::ip::tcp;

int main()
{
    MyClient client;
    while(true)
    {
            client.Start_Client("127.0.0.1",2102);
    }


{
//    std::cout << "Client - started!" << std::endl;

//    boost::asio::io_service io_service; //Создали обязательный объект класса io_service
//    std::cout << "io_service - OK" << std::endl;

//    tcp::endpoint client_endpoint; //Создаем точку для подключения (куда будем стучаться то :D )
//    std::cout << "client_endpoint - OK" << std::endl;

//    client_endpoint.port(2102); //Задаем порт для подключения
//    std::cout << "port - OK" << std::endl;

//    client_endpoint.address(boost::asio::ip::address_v4::from_string("127.0.0.1")); //Задаем адрес подключения
//    std::cout << "ip_adress - OK" << std::endl;

//    tcp::socket client_socket (io_service); //Создаем сокет клиента
//    std::cout << "socket - OK" << std::endl;

//    client_socket.connect(client_endpoint); //Начинаем стучаться по указанному адресу
//    std::cout << "connected - OK" << std::endl;

//    std::ofstream Out_File_Stream("OutTestFile.mp3", std::ios::binary); //Создаем поток для записи файла
//    std::cout << "Out_File_Stream - OK" << std::endl;

//    boost::array <char,256> Buffer; //Буфер для хранения полученных данных
//    std::cout << "Buffer - OK" << std::endl;


//    int len=0;

//    try
//    {
//        boost::array <char,256> Buffer_system;
//        while(len<34)
//        {

//            len+=boost::asio::read(client_socket, boost::asio::buffer(Buffer_system),boost::asio::transfer_at_least(1)); //Читаем ответ сервера
//            for(int i=0; i<len;i++)
//            {
//                if(Buffer_system[i]=='%') std::cout<<std::endl;
//                else if(Buffer_system[i]!='/0') std::cout<<Buffer_system[i];
//                //Out_File_Stream<<Buffer[i];

//            }
//            std::cout << "Length: "<< len << std::endl;
//        }
//        boost::array<std::string,1> n;
//        std::cout<<"Enter number:" <<std::endl;
//        std::cin>>n[0];
//        boost::asio::write(client_socket,boost::asio::buffer(n[0]));
//        boost::asio::write(client_socket,boost::asio::buffer("%"));
//    }
//    catch(...)
//    {
//    }



//    //Out_File_Stream<<Buffer; //Эта хуйня возможно только все испортит
//    sleep(2);
//    std::cout << "Zz-zz file "<< len << std::endl;
//    len=0;
//    while(len<5340685)
//    {
//        len+=boost::asio::read(client_socket, boost::asio::buffer(Buffer),boost::asio::transfer_at_least(1)); //Читаем ответ сервера
//        for(int i=0; i<Buffer.size();i++)
//        {
//            Out_File_Stream<<Buffer[i];
//        }
//        std::cout << "Length: "<< len << std::endl;//
//    }
//    Out_File_Stream.close();
//    client_socket.close();
//    std::cout << "Write in cout - OK" << std::endl;
}
    return 0;
}
