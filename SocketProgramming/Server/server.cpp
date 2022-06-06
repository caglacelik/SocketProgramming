#pragma comment(lib,"Ws2_32.lib") // link with Ws2_32.lib
#include<iostream>
#include <winsock2.h>
#include<Ws2tcpip.h>

using namespace std;

int main() {
    WSADATA WinSockData;
    int portnum, tcpclientadress;
    SOCKET tcpserversocket, acceptedsocket;
    char servermessage[512] = "";
    char receivemessage[512];
    struct sockaddr_in server_information;
    struct sockaddr_in client_information;
    if (WSAStartup(MAKEWORD(2, 2), &WinSockData) == SOCKET_ERROR) //start WSADATA to use WSAGetLastError() func
    {
        cout << "WSAStartup Failed" << endl;
    }
    tcpserversocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//create socket
    if (tcpserversocket == INVALID_SOCKET)//check socket
        cout << "TCP socket server could not be created. " << WSAGetLastError() << endl;
    else
        cout << "TCP socket server was created succesfully." << endl;
    server_information.sin_family = AF_INET;//set address family. AF_INET = The Internet Protocol version 4 (IPv4)
    inet_pton(AF_INET, "127.0.0.1", &server_information.sin_addr);// set localhost ip address
    cout << "Please enter the port number: ";
    cin >> portnum;
    server_information.sin_port = htons(portnum);//set port
    while (1) {
        if (bind(tcpserversocket, (SOCKADDR*)&server_information, sizeof(server_information)) == SOCKET_ERROR)//associate a local address with a socket.
            if (WSAGetLastError() == WSAEADDRINUSE) //check port using
            {
                cout << "Port Already Used. Please enter the new port: ";
                cin >> portnum;
                server_information.sin_port = htons(portnum);
            }
            else //check different error
            {
                cout << "Binding Error! Error code: " << WSAGetLastError() << endl;
                break;
            }
        else {
            cout << "Binding Successfully!!!" << endl;
            break;
        }
    }
    if (listen(tcpserversocket, 0) == SOCKET_ERROR)// check listening socket
        cout << "Listening Error! Error code: " << WSAGetLastError() << endl;
    else
        cout << "Listening Successfully!!!" << endl;
    tcpclientadress = sizeof(client_information);
    acceptedsocket = accept(tcpserversocket, (SOCKADDR*)&client_information, &tcpclientadress);//convert to acceptedsocket via accept func
    if (acceptedsocket == SOCKET_ERROR)//check acceptedsocket
        cout << "Accept Error! Error code: " << WSAGetLastError() << endl;
    else
        cout << "Accept Successfully!!!" << endl;
    cout << "Please enter the message: ";
    cin.ignore();
    cin.getline(servermessage, 512);
    if (send(acceptedsocket, servermessage, sizeof(servermessage), 0) == SOCKET_ERROR)//send message to client
        cout << "Sending Error! Error code: " << WSAGetLastError() << endl;
    else
        cout << "Sending Successfully!!!" << endl;
    if (recv(acceptedsocket, receivemessage, sizeof(receivemessage), 0) == SOCKET_ERROR)//receive message from client
        cout << "Receiving Error! Error code: " << WSAGetLastError() << endl;
    else
        cout << "Message Received From Client: " << receivemessage << endl;

    if (closesocket(tcpserversocket) == SOCKET_ERROR)//close and check socket
        cout << "TCP socket server could not be closed. " << WSAGetLastError() << endl;
    else
        cout << "TCP socket server was closed successfully" << endl;
    if (WSACleanup() == SOCKET_ERROR)//close WSADATA
        cout << "WSA Cleanup Error! Error code: " << WSAGetLastError() << endl;

    system("PAUSE");
    return 0;
}