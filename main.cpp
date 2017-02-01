#include <iostream>
#include "myserver.h"
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main()
{

    MyServer server;
    std::cout<<"Server start..."<<'\n';
    while(true)
    {
        server.Start_Server();
    }

    return 0;
}
