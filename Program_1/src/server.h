#pragma once

#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <thread>

class Server {
    int socket_;
    int listener;
    const int clientLimit = 1;

   public:
    Server(int port);

    void send(std::map<char, int> data);

    void run();

    void startListening(int listener, int connectionCount);
};
