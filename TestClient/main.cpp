#include "myclient.h"

using boost::asio::ip::tcp;

int main()
{
    MyClient client;
    while(client.Start_Client("127.0.0.1",2102)) {}
    std::cout<<"Good Bye!"<<'\n';
    return 0;
}
