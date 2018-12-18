/*************************************************************************
 * ** Author: Alexis Tucker
 * ** Program: Program 4 (otp_dec.c)
 * ** Date: 11/29/2018
 * ** Class: CS 344
 * ** email: tuckera6@gmail.com
 * **************************************************************************/




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <ctype.h>

void error(const char *msg) { perror(msg); exit(0); } // Error function used for reporting issues

int main(int argc, char *argv[])
{
	int socketFD, portNumber, charsWritten, charsRead;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	char buffer[256];
    
	if (argc < 4) { fprintf(stderr,"USAGE: %s hostname port\n", argv[0]); exit(0); } // Check usage & args

	// Set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[3]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname("localhost"); // Convert the machine name into a special form of addres
	if (serverHostInfo == NULL) { fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(0); }
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

	// Set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) error("CLIENT: ERROR opening socket");
	
	// Connect to server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to address
		error("CLIENT: ERROR connecting");

	//test for correct connection to enc_d
	memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer array
	strcpy(buffer, "Hello from dec");

	// Send message to server
	charsWritten = send(socketFD, buffer, strlen(buffer), 0); // Write to the server
	if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
	if (charsWritten < strlen(buffer)) printf("CLIENT: WARNING: Not all data written to socket!\n");

	// Get return message from server
	memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer again for reuse
	charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); // Read data from the socket, leaving \0 at end
	if (charsRead < 0) error("CLIENT: ERROR reading from socket");

	//check if return message is from dec_d
	if(strcmp(buffer, "Hello from dec_d") != 0){
		fprintf(stderr, "Error: could not contact otp_dec_d on port %d\n", portNumber);
		close(socketFD);
		exit(2);
	}

	//read data from cipher file
	FILE *cipher = fopen(argv[1], "r");
	if(cipher == NULL){
		fprintf(stderr, "Error: could not open %s\n", argv[1]);
		exit(1);
	}
	char cbuffer[100000];
	memset(cbuffer, '\0', sizeof(cbuffer));
	fgets(cbuffer, sizeof(cbuffer) - 1, cipher);	
	cbuffer[strcspn(cbuffer, "\n")] = '\0'; //remove newline
	int clength = strlen(cbuffer);	
	fclose(cipher);

	//read data from key file
	FILE *key = fopen(argv[2], "r");	
	if(key == NULL){
		fprintf(stderr, "Error could not open %s\n", argv[2]);
		exit(1);
	}
	char kbuffer[100000];
	memset(kbuffer, '\0', sizeof(kbuffer));
	fgets(kbuffer, sizeof(kbuffer) - 1, key);
	kbuffer[strcspn(kbuffer, "\n")] = '\0';	//remove newline
	int klength = strlen(kbuffer);
	fclose(key);

	//check that key is not shorter than plaintext file
	//print error to stderr and close socket if so
	if(clength > klength){
		fprintf(stderr, "Error: key '%s' is too short\n", argv[2]);
		close(socketFD);
		exit(1);
	}

	//check for bad characters in plaintext
	//if so, print error to stderr and close socket 
	int l;
	for(l = 0; l < clength; l++){
		if(cbuffer[l] != ' ' & cbuffer[l] < 'A' || cbuffer[l] > 'Z'){
			fprintf(stderr, "otp_dec error: input contains bad characters\n");
			close(socketFD);
			exit(1);
		} 

	}

	//check for bad characters in key
	//if so, print error to stderr and close socket
	for(l = 0; l < klength; l++){
               if(kbuffer[l] != ' ' & kbuffer[l] < 'A' || kbuffer[l] > 'Z'){
                        fprintf(stderr, "otp_dec key error: input contains bad characters\n");
                        close(socketFD);
                        exit(1);
                }

        }

	
	//send plaintext to end_d
	//source: https://www.ibm.com/support/knowledgecenter/en/SSB23S_1.1.0.15/gtpc2/cpp_send.html
	//add terminating character "@" so server knows all data has been received
	//source: Lecture 4.2 Network Clients slide 18
	cbuffer[strlen(cbuffer)] = '@';
	int cWritten;
	int cRemain = strlen(cbuffer);
	char *c = cbuffer;
	
	while(cRemain > 0){
		cWritten = send(socketFD, c, cRemain, 0); 
		if (cWritten < 0){
			error("CLIENT: ERROR writing to socket");
			break;
        	}
		cRemain -= cWritten;
		c += cWritten;
	}
	
	//check that cipher was recieved
	memset(buffer, '\0', sizeof(buffer));
	charsRead = recv(socketFD, buffer, sizeof(buffer)-1, 0);

	//send key to enc_d
	//add terminating character to let server know all data has been
	//received
	kbuffer[strlen(kbuffer)] = '@';
	int kWritten;
	int kRemain = strlen(kbuffer);
	char *k = kbuffer;

        while(kRemain > 0){
                kWritten = send(socketFD, k, kRemain, 0);
                if (kWritten < 0){
                        error("CLIENT: ERROR writing to socket");
                        break;
                }
                kRemain -= kWritten;
                k += kWritten;
        }

	//receive cipher text
	char readbuffer[2000];
	memset(cbuffer, '\0', sizeof(cbuffer)); // Clear out the buffer again for reuse
	while(strstr(cbuffer, "@") == NULL){
		memset(readbuffer, '\0', sizeof(readbuffer));
	        charsRead = recv(socketFD, readbuffer, sizeof(readbuffer) - 1, 0);
		strcat(cbuffer, readbuffer);
        	if (charsRead < 0){
			error("CLIENT: ERROR reading from socket");
			break;
		}
		if (charsRead == 0){
			break; 
		}
	}

	//remove terminating character from cipher, add newline and output cipher
	int terminalLocation = strstr(cbuffer, "@") - cbuffer;
	cbuffer[terminalLocation] = '\n';
	printf("%s", cbuffer);
	

	close(socketFD); // Close the socket
	return 0;
}
