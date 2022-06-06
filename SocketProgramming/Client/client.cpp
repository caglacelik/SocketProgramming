#pragma comment(lib,"Ws2_32.lib") // link with Ws2_32.lib
#include<iostream>
#include<winsock2.h>
#include<Ws2tcpip.h>
using namespace std;


int main() {
	WSADATA WinSockData;
	SOCKET tcpclientsocket;
	char recivemessage[512];
	char message[512];
	struct sockaddr_in server_information;
	int portnum;
	if (WSAStartup(MAKEWORD(2, 2), &WinSockData) == SOCKET_ERROR)//start WSADATA to use WSAGetLastError() func
	{
		cout << "WSAStartup Failed" << endl;
	}
	tcpclientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (tcpclientsocket == INVALID_SOCKET)//check creating socket
		cout << "TCP socket client could not be created. " << WSAGetLastError() << endl;
	else
		cout << "TCP socket client was created succesfully." << endl;
	server_information.sin_family = AF_INET;//set address family. AF_INET = The Internet Protocol version 4 (IPv4)
	inet_pton(AF_INET, "127.0.0.1", &server_information.sin_addr);//set Localhost ip adress
	cout << "Please enter the port number: ";
	cin >> portnum;
	server_information.sin_port = htons(portnum);//set port
	if (connect(tcpclientsocket, (SOCKADDR*)&server_information, sizeof(server_information)) == SOCKET_ERROR)//check socket connection
		cout << "Connecting Error! Error code: " << WSAGetLastError() << endl;
	else
		cout << "Connecting Successfully!!!" << endl;
	if (recv(tcpclientsocket, recivemessage, sizeof(recivemessage), 0) == SOCKET_ERROR)//receive message from server
		cout << "Receiving Error! Error code: " << WSAGetLastError() << endl;
	else
		cout << "Message Received From Server: " << recivemessage << endl;
	cout << "Please enter the message: ";
	cin.ignore();
	cin.getline(message, 512);
	if (send(tcpclientsocket, message, sizeof(message), 0) == SOCKET_ERROR)//send message to server
		cout << "Sending Error! Error code: " << WSAGetLastError() << endl;
	else
		cout << "Sending Successfully!!!" << endl;
	if (closesocket(tcpclientsocket) == SOCKET_ERROR)//close and check socket
		cout << "TCP socket server could not be closed. " << WSAGetLastError() << endl;
	else
		cout << "TCP socket server was closed successfully" << endl;
	if (WSACleanup() == SOCKET_ERROR)//close WSADATA
		cout << "WSA Cleanup Error! Error code: " << WSAGetLastError() << endl;

	system("PAUSE");
	return 0;
}