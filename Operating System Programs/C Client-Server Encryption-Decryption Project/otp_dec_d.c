/*************************************************************************
 * ** Author: Alexis Tucker
 * ** Program: Program 4 (otp_dec_d.c)
 * ** Date: 11/29/2018
 * ** Class: CS 344
 * ** email: tuckera6@gmail.com
 * **************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) { perror(msg); exit(1); } // Error function used for reporting issues

int main(int argc, char *argv[])
{
	int listenSocketFD, establishedConnectionFD, portNumber, charsRead;
	socklen_t sizeOfClientInfo;
	char buffer[256];
	struct sockaddr_in serverAddress, clientAddress;

	if (argc < 2) { fprintf(stderr,"USAGE: %s port\n", argv[0]); exit(1); } // Check usage & args

	// Set up the address struct for this process (the server)
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

	// Set up the socket
	listenSocketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (listenSocketFD < 0) error("ERROR opening socket");

	// Enable the socket to begin listening
	if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
		error("ERROR on binding");
	listen(listenSocketFD, 5); // Flip the socket on - it can now receive up to 5 connections

	//loop continuously to accept new connections
	while(1){

		// Accept a connection, blocking if one is not available until one connects
		sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
		establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
		if (establishedConnectionFD < 0) error("ERROR on accept");

		//fork to child process
		pid_t childPID = fork();
		int childExitMethod;

		switch(childPID){
		case -1:
			fprintf(stderr, "Error forking to child process\n");
			break;
		case 0:
			// Get the message from the client and display it
			memset(buffer, '\0', 256);
			charsRead = recv(establishedConnectionFD, buffer, 255, 0); // Read the client's message from the socket
			if (charsRead < 0) error("ERROR reading from socket");

			// Send a Success message back to the client
			charsRead = send(establishedConnectionFD, "Hello from dec_d", 16, 0); // Send success back
			if (charsRead < 0) error("ERROR writing to socket");
		
			//read cipher
			int cchars;
			char cbuffer[100000];
			char readbuffer[2000];
			
			memset(cbuffer, '\0', sizeof(cbuffer));

			//loop until terminating character "@" indicating all data sent has been received
			while(strstr(cbuffer, "@") == NULL){
				memset(readbuffer, '\0', sizeof(readbuffer));
				cchars = recv(establishedConnectionFD, readbuffer, sizeof(readbuffer) - 1, 0);
				strcat(cbuffer, readbuffer);
				if(cchars < 0){
					error("ERROR reading cipher from socket");
					break;
				}
				if(cchars == 0){
					break;
				}
			}

			//remove terminating character
			int terminalLocation = strstr(cbuffer, "@") - cbuffer;
			cbuffer[terminalLocation] = '\0';			

			//tell client cipher was received
			charsRead = send(establishedConnectionFD, "cipher received", 16, 0); // Send success back
                        if (charsRead < 0) error("ERROR writing to socket");

			//read key text
			int kchars;
                        char kbuffer[100000];
			char kreadbuffer[2000];
	                memset(kbuffer, '\0', sizeof(kbuffer));

			//loop until terminating character "@" is recieved, indicating all data sent has been received
			while(strstr(kbuffer, "@") == NULL){
				memset(kreadbuffer, '\0', sizeof(kreadbuffer));
	                        kchars = recv(establishedConnectionFD, kreadbuffer, sizeof(kreadbuffer) - 1, 0);
				strcat(kbuffer, kreadbuffer); 
                        	if(kchars < 0){
					error("ERROR reading key from socket");
					break;
				}
                        	if(kchars == 0){
                                	break;
                        	}		
			}
			//remove terminating character
			terminalLocation = strstr(kbuffer, "@") - kbuffer;
                        kbuffer[terminalLocation] = '\0';

			//check for bad characters in cipher
			//if so, print error to stderr and close connection
			int l;
		        for(l = 0; l < strlen(cbuffer); l++){
                		if(cbuffer[l] != ' ' & cbuffer[l] < 'A' || cbuffer[l] > 'Z'){
                        		fprintf(stderr, "otp_dec_d cipher error: input contains bad characters\n");
                       			close(establishedConnectionFD);
                        		exit(1);
        		        }
		        }	

			//check for bad characters in key
			//if so, print error to stderr and close connection
			for(l = 0; l < strlen(kbuffer); l++){
	 	               if(kbuffer[l] != ' ' & kbuffer[l] < 'A' || kbuffer[l] > 'Z'){
                	        	fprintf(stderr, "otp_dec_d error: input contains bad characters\n");
                        		close(establishedConnectionFD);
                        		exit(1);
               	 		}

    			}		

			//encode plaintext
			char plaintext[100000]; //holds decoded text
			int cArray[100000];	//holds numeric value of chars in cipher
			int kArray[100000];	//holds numeric value of chars in key
			int i, c;
			//character array is used to conver chars to int for cipher and key
			char character[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};
			//charactersting is used to convert ints to decoded plaintext
			char* characterstring[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", " "};	
	
			//convert cipher chars to int
			//if the cipher char matches the character array char, add appropriate number to cipher int array
			for(i = 0; i < strlen(cbuffer); i++){
				for(c = 0; c < 27; c++){
					if(cbuffer[i] == character[c]){
						cArray[i] = c;
						break;
					}
				}
			}

			//conver key chars to int
			//if the key char matches the character array char, add appropriate number to key int array
			for(i = 0; i < strlen(kbuffer); i++){
				for(c = 0; c < 27; c++){
					if(kbuffer[i] ==  character[c]){
						kArray[i] = c;
						break;
					}
				}
			}

			//subtract arrays and modulus
			//if the resulting number is negative, add 27
			for(i = 0; i < strlen(cbuffer); i++){
				cArray[i] = cArray[i] - kArray[i];
				cArray[i] = cArray[i] % 27;
				if(cArray[i] < 0){
					cArray[i] = cArray[i] + 27;
				}
			}
		
			//convert cipher text to plain text using the new values in the cipher int array
			//by finding the associated char in the characterstring array
			for(i = 0; i < strlen(cbuffer); i++){
				strcat(plaintext, characterstring[cArray[i]]);
			}	

			//send cipher text back to client
			//attach terminating character "@" to let client know all data has been sent
			plaintext[strlen(plaintext)] = '@';
			int ptRemain = strlen(plaintext);
			char *ptPtr = plaintext;
			
			//loop until all data has been sent
			while(ptRemain > 0){
		                charsRead = send(establishedConnectionFD, ptPtr, ptRemain, 0);
                		if (charsRead < 0){
                        		error("SERVER: ERROR writing to socket");
                        		break;
                		}
                		ptRemain -= charsRead;
                		ptPtr += charsRead;
        		}

			close(establishedConnectionFD);	
			exit(0); //exit child
		default:
			waitpid(-1, &childExitMethod, WNOHANG);	//check for any previous finished child process
			close(establishedConnectionFD);
			break;
		}
	}
	close(listenSocketFD); // Close the listening socket
	return 0; 
}
