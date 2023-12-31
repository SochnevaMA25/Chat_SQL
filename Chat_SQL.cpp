﻿#include <iostream>
#include <winsock2.h>
#include <string>
#include <mysql.h>
#include "Chat.h"
#include <winsock2.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib") // Winsock Library
#pragma warning(disable:4996) 

#define BUFLEN 512
#define PORT 8888

using namespace std;

int main() {
	Chat ch;
    system("title UDP Server");

    sockaddr_in server, client;

    // initialise winsock
    WSADATA wsa;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        exit(0);
    }
    printf("Initialised.\n");

    // create a socket
    SOCKET server_socket;
    SOCKET server_socket_mes;
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket: %d", WSAGetLastError());
    }


   

    // prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // bind
    if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code: %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    
   

    while (true)
    {
        fflush(stdout);
        char message[BUFLEN] = {};

        // try to receive some data, this is a blocking call
        int message_len;
        int slen = sizeof(sockaddr_in);
        //check login, pass
        if (message_len = recvfrom(server_socket, message, BUFLEN, 0, (sockaddr*)&client, &slen) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code: %d", WSAGetLastError());
            return false;
        }
        string mes = message;
        mes = mes + ";";
        //send list user
        string user = "Users: " + ch.print();
        if (ch.parser(mes.c_str()))
        {
            if (sendto(server_socket, user.c_str(), strlen(user.c_str()), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
            {
                printf("sendto() failed with error code: %d", WSAGetLastError());
                return false;
            }
        }
        //get mes
        char message_mes[BUFLEN] = {};
        if (message_len = recvfrom(server_socket, message_mes, BUFLEN, 0, (sockaddr*)&client, &slen) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code: %d", WSAGetLastError());
            return false;
        }
        ch.parser_mes(message_mes);
        string message_recv = ch.receive(ch.get(message));
        //history mes
        if (sendto(server_socket, message_recv.c_str(), strlen(message_recv.c_str()), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code: %d", WSAGetLastError());
            return false;
        }
    }

    closesocket(server_socket);
    WSACleanup();
	system("Pause");

	return 0;
}