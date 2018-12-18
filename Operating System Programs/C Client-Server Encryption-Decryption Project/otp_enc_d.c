/*************************************************************************
 * ** Author: Alexis Tucker
 * ** Program: Program 4 (otp_enc_d.c)
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
			// Get the message from the client 
			memset(buffer, '\0', 256);
			charsRead = recv(establishedConnectionFD, buffer, 255, 0); // Read the client's message from the socket
			if (charsRead < 0) error("ERROR reading from socket");


			// Send a Success message back to the client
			charsRead = send(establishedConnectionFD, "Hello from enc_d", 16, 0);
			if (charsRead < 0) error("ERROR writing to socket");
		
			//read plaintext
			int ptchars;
			char ptbuffer[100000];
			char readbuffer[2000];
			
			memset(ptbuffer, '\0', sizeof(ptbuffer));

			//loop until terminating symbo "@" is received to indicate end of data
			//source: lecture 4.2 Network Clients Slide 18
			while(strstr(ptbuffer, "@") == NULL){
				memset(readbuffer, '\0', sizeof(readbuffer));
				ptchars = recv(establishedConnectionFD, readbuffer, sizeof(readbuffer) - 1, 0);
				strcat(ptbuffer, readbuffer);
				if(ptchars < 0){
					error("ERROR reading plaintext from socket");
					break;
				}
				if(ptchars == 0){
					break;
				}
			}

			//remove terminating symbol
			int terminalLocation = strstr(ptbuffer, "@") - ptbuffer;
			ptbuffer[terminalLocation] = '\0';			

					
			//confirm plaintext received	
                        charsRead = send(establishedConnectionFD, "received plaintext", 16, 0);
                        if (charsRead < 0) error("ERROR writing to socket");

	
			//read key text
			int kchars;
                        char kbuffer[100000];
			char kreadbuffer[2048];

                        memset(kbuffer, '\0', sizeof(kbuffer));

			//loop until terminating symbol is received
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

			//remove terminating symbol
			terminalLocation = strstr(kbuffer, "@") - kbuffer;
                        kbuffer[terminalLocation] = '\0';

			
			//check for bad characters in plaintext
			//print error to stderr and close socket if found
			int l;
		        for(l = 0; l < strlen(ptbuffer); l++){
                		if(ptbuffer[l] != ' ' & ptbuffer[l] < 'A' || ptbuffer[l] > 'Z'){
                        		fprintf(stderr, "otp_enc_d error: input contains bad characters\n");
                       			close(establishedConnectionFD);
                        		exit(1);
        		        }
		        }	

			//check for bad characters in key
			//print error to stderr and close socket if found
			for(l = 0; l < strlen(kbuffer); l++){
	 	               if(kbuffer[l] != ' ' & kbuffer[l] < 'A' || kbuffer[l] > 'Z'){
                	        	fprintf(stderr, "otp_enc_d error: input contains bad characters\n");
                        		close(establishedConnectionFD);
                        		exit(1);
               	 		}

    			}		

			//encode plaintext
			char cipher[100000];	//holds ciphertext string
			int ptArray[100000];	//holds the numeric value 0-26 of plaintext chars
			int kArray[100000];	//holds the numberic value 0-26 of the key chars
			int i, c;
			//character array is used to convert the plaintext and key to integers
			char character[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};
			//characterstring array is used to generate the ciphertext
			char* characterstring[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", " "};
	
			//convert plaintext chars to int
			//if the character in plaintext matches a character in the character array, assign the
			//plaintext integer array the appropriabe value
			for(i = 0; i < strlen(ptbuffer); i++){
				for(c = 0; c < 27; c++){
					if(ptbuffer[i] == character[c]){
						ptArray[i] = c;
						break;
					}
				}
			}

			//conver key chars to int
			//if the character in key matches a character in the character array, assign the
			//key integer array the appropriate value
			for(i = 0; i < strlen(kbuffer); i++){
				for(c = 0; c < 27; c++){
					if(kbuffer[i] ==  character[c]){
						kArray[i] = c;
						break;
					}
				}
			}


			//add together arrays and modulus the sum to get the new character value for the cipher text
			for(i = 0; i < strlen(ptbuffer); i++){
				ptArray[i] = ptArray[i] + kArray[i];
				ptArray[i] = ptArray[i] % 27;
			}
		
			//convert to cipher text from integers to chars using the characterstring array and
			//the new values in the plaintext array
			for(i = 0; i < strlen(ptbuffer); i++){
				strcat(cipher, characterstring[ptArray[i]]);
			}			


			//send cipher text back to client
			//attach a terminating character
			cipher[strlen(cipher)] = '@';
			int cRemain = strlen(cipher);
			char *cPtr = cipher;
			
			//loop until all data has been sent
			while(cRemain > 0){
		                charsRead = send(establishedConnectionFD, cPtr, cRemain, 0);
                		if (charsRead < 0){
                        		error("SERVER: ERROR writing to socket");
                        		break;
                		}
                		cRemain -= charsRead;
                		cPtr += charsRead;
        		}

			close(establishedConnectionFD);
			exit(0);
		default:
			waitpid(-1, &childExitMethod, WNOHANG); //check for any previous children to be cleaned up
			close(establishedConnectionFD);
			break;
		}
	}
	close(listenSocketFD); // Close the listening socket
	return 0; 
}
