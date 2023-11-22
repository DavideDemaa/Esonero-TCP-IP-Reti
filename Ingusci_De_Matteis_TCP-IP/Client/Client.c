/*
 ============================================================================
 Name        : Client.c
 Author      : Ingusci Paolo - De Matteis Davide
 ============================================================================
 */

#include "TCP_protocol.h"
#include "check.h"
#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void errorhandler(char *errorMessage) {

	printf("%s", errorMessage);
}

void clearWinsock() {

#if defined WIN32
	WSACleanup();
#endif
}


int main(void) {

#if defined WIN32

	WSADATA wsa_data;
	WORD version_requested;

	version_requested = MAKEWORD(2, 2);
	int result = WSAStartup(version_requested, &wsa_data);

	if (result != NO_ERROR) {

		printf("Error at WSAStartup() \n");
		printf("A usable WinSock DLL cannot be found\n");
		return -1;
	}
	#endif

	int c_socket;

	c_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (c_socket < 0) {

		errorhandler("Socket creation failed. \n");
		clearWinsock();
		return -1;
	}

	struct sockaddr_in sad;
	memset(&sad, 0, sizeof(sad));

	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr("127.0.0.1");
	sad.sin_port = htons(PROTOPORT);

	if (connect(c_socket, (struct sockaddr*) &sad, sizeof(sad)) < 0) {

		errorhandler("Failed to connect. \n");
		closesocket(c_socket);
		clearWinsock();
		return -1;
	}


	//receives server data
	int bytes_rcvd;
	char buf[BUFFER_SIZE]; // buffer for data from the server
	memset(buf, 0, BUFFER_SIZE); // ensures extra bytes contain 0
	printf("Waiting for connection --> ");
	if ((bytes_rcvd = recv(c_socket, buf, BUFFER_SIZE - 1, 0)) <= 0)
		{
		errorhandler("recv() failed or connection closed prematurely");
		system("pause");
		closesocket(c_socket);
		clearWinsock();
		return -1;
	}
	//prints a successful connection message received from the server
	buf[bytes_rcvd] = '\0';
	printf("%s", buf);
	system("pause");
	system("cls");

	//insertion of the string that will be sent to the server
	char string_send[BUFFER_SIZE];
	memset(string_send, '\0', BUFFER_SIZE);
    puts("Insert the string useful for the calculation (maximum 64 characters) \n(format: \"operator[space]num1[space]num2\"):");
	gets(string_send);
	//string format controls
	while(lenght_check(strlen(string_send)) || string_check(string_send)) //loop that ends when a string of the correct format is entered
	{
		system("PAUSE");
		system("cls");
		puts("Insert the string useful for the calculation (maximum 64 characters) \n(format: \"operator[space]num1[space]num2\" ):");
		gets(string_send);
	}

	//Sending the string to the server
	int string_len = strlen(string_send);
	if (send(c_socket, string_send, string_len, 0) != string_len)
	{
		errorhandler("send() sent a different number of bytes than expected");
		closesocket(c_socket);
		clearWinsock();
		return -1;
	}
	char result_in[BUFFER_SIZE]; // buffer for data from the server

	//loop that exchanges messages with the client until "=" is entered
	while (strcmp(string_send, "=")!=0)
	{

		memset(result_in, '\0', BUFFER_SIZE);
		printf("Result: ");
		if ((bytes_rcvd = recv(c_socket, result_in, BUFFER_SIZE - 1, 0)) <= 0)
		{
			errorhandler("recv() failed or connection closed prematurely");
			closesocket(c_socket);
			clearWinsock();
			return -1;
		}
		printf("%s\n", result_in); // prints the result of the operation
		system("pause");
		system("cls");
		memset(string_send, '\0', BUFFER_SIZE);
		//inserting the new string
		puts("Insert the string useful for the calculation (maximum 64 characters) \n(format: \"operator[space]num1[space]num2\"):");
		gets(string_send);
		while(string_check(string_send)) //loop that ends when a string of the correct format is entered
		{
			system("PAUSE");
		    system("cls");
		    puts("Insert the string useful for the calculation (maximum 30 characters) \n(format: \"operator[space]num1[space]num2\" ):");
		    gets(string_send);
		}
		////Sending the string to the server
		string_len = strlen(string_send);
		if (send(c_socket, string_send, string_len, 0) != string_len)
		{
			errorhandler("send() sent a different number of bytes than expected");
			closesocket(c_socket);
			clearWinsock();
			return -1;
		}
	}
	system("pause");
	//closing the connection
	closesocket(c_socket);
	clearWinsock();
	printf("\n"); // Print a final linefeed

	return 0;

}



