/*
*		Server.c
*		Author : Paolo Ingusci - De Matteis Davide
*/

#include "TCP_protocol.h"
#include "calculation.h"
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

int main(int argc, char *argv[]){

	int port = PROTOPORT;

#if defined WIN32

	WSADATA wsa_data;
	WORD version_requested;

	version_requested = MAKEWORD(2,2);
	int result = WSAStartup(version_requested, &wsa_data);

	if(result != NO_ERROR) {

		printf("Error at WSAStartup() \n");
		printf("A usable WinSock DLL cannot be found\n");
		return 0;
	}
#endif

	int my_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(my_socket < 0) {

		errorhandler("Socket creation failed. \n");
		clearWinsock();
		return -1;
	}

	struct sockaddr_in sad;
	memset(&sad, 0, sizeof(sad));

	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr("127.0.0.1");
	sad.sin_port = htons(port);

	if(bind(my_socket, (struct sockaddr*) &sad, sizeof(sad)) < 0) {

		errorhandler("bind() failed. \n");
		closesocket(my_socket);
		return -1;
	}

	if(listen(my_socket, QLEN) < 0) {

		errorhandler("listen() failed. \n");
		system("pause");
		closesocket(my_socket);
		clearWinsock();
		return -1;
	}

	struct sockaddr_in cad;
	int client_socket;
	int client_len;
	printf( "Waiting for a client to connect... \n");

	//loop that keeps the server listening
	while(1) {
		client_len = sizeof(cad);

		if((client_socket = accept(my_socket, (struct sockaddr*) &cad, &client_len)) < 0) {
			errorhandler("accept() failed. \n");
			system("pause");
			closesocket(my_socket);
			clearWinsock();
			return -1;
		}

		printf( "\nConnection established with %s:%d\n", inet_ntoa(cad.sin_addr), ntohs(cad.sin_port));

		//string " Connection established\n" sent to the client
		char* input_string = " Connection established\n";
		int string_len = strlen(input_string);
		if (send(client_socket, input_string, string_len, 0) != string_len)
		{
			errorhandler("send() sent a different number of bytes than expected\n");
			system("pause");
			closesocket(client_socket);
			clearWinsock();
			return -1;
		}

		int bytes_rcvd;
		char str_in[BUFFER_SIZE]; // buffer for data from the server
		memset(str_in, '\0', BUFFER_SIZE); // ensures extra bytes contain '\0'
		printf("Received: "); // Setup to print the echoed string

		//string reception from server
		if ((bytes_rcvd = recv(client_socket, str_in, BUFFER_SIZE - 1, 0)) <= 0)
		{
			errorhandler("recv() failed or connection closed prematurely\n");
			system("pause");
			closesocket(my_socket);
			clearWinsock();
			return -1;
		}
		str_in[bytes_rcvd] = '\0';
		printf("%s\n", str_in);

		//receives strings from server until "=" is received
		while(strcmp(str_in,"=") != 0){
			//calculation
			int num1 = 0, num2 = 0; // numbers between which the operation will be performed
			char op, result_out[100]; //operator
			float result; //result of the operation
			set_operation(str_in, &num1, &num2, &op);
			result = calculation(num1, num2, op); //result calculation

			if(num2==0 && op=='/')
				strcpy(result_out,"inf");
			else
				sprintf(result_out, "%.3f", result);
			string_len = strlen(result_out);
			//send result to server
			if (send(client_socket, result_out, string_len, 0) != string_len)
			{
				errorhandler("\nsend() sent a different number of bytes than expected\n");
				system("pause");
				closesocket(client_socket);
				clearWinsock();
				return -1;
			}
			printf("Received: "); // Setup to print the echoed string
			//receive new string from server
			if ((bytes_rcvd = recv(client_socket, str_in, BUFFER_SIZE - 1, 0)) <= 0)
			{
				errorhandler("\nrecv() failed or connection closed prematurely\n");
				system("pause");
				closesocket(client_socket);
				clearWinsock();
				return -1;
			}
			str_in[bytes_rcvd] = '\0'; // ridondante se si fa memset prima
			printf("%s\n", str_in); //stampa a schermo della stringa ricevuta
		}

	}
}
