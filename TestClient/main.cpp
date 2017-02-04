#include "myclient.h"

using boost::asio::ip::tcp;

bool Exit_Menu()
{
    std::cout<<"Для выхода из программы нажмите: q "<<'\n';
    char character=' ';
    std::cin>>character; //Считываем символ
    std::cin.clear(); //Очищаем поток ввода (на всякий случай)
    if(character=='q') return false;
    else return true;
}

int main()
{
    MyClient client;
    do
    {
        client.Start_Client("127.0.0.1",2102);
    } while(Exit_Menu());
    std::cout<<"Good Bye!"<<'\n';
    return 0;
}
