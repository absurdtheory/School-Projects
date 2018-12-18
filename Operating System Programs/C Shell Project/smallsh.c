/******************************************************************
* Author: Alexis Tucker
* email: tuckera6@oregonstate.edu
* Program 3: smallsh.c
* Date: 11/10/2018
* Class: CS 344
******************************************************************/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

#define MAXCHAR 2048	 //max number of characters supported on command line
#define MAXCOM 512	 //max number of commands supported on command line

pid_t bgPIDS[1000];	 //array for holding background PIDs
int count = 0;		 //number of of PIDs in bgPIDS array
int exitStatus = 0;	 //holds exit value or signal number of last foreground procss
int exitSignalFlag = 0;  //flag to determine if exit value or signal termination message should be printed
int fgOnlyFlag = 0;	 //flag to tell program to only run processes in the foreground
int printFgStart = 0;	 //flag to indicate where SIGTSTP start message should print
int printFgStop = 0;	 //flag to indicate where SIGTSTP message should print
int printStartFlag = 0;	 //flag to indicated where SIGTSTP is called
int printStopFlag = 0;	 //flag to indicated where SIGTSTP is called


//sig action structs
struct sigaction SIGINT_action = {0}, SIGTSTP_action = {0},  ignore_action = {0};

/**********************************************************
* SIGTSTP signal handler function, switches foreground
* only mode off and on
**********************************************************/
void catchSIGTSTP(int signo){
	
	//if not in foreground only mode, change flag to 
	//indicate foreground only mode
	if(fgOnlyFlag == 0){
		//if at getline, print message about starting FG only mode
		if(printFgStart ==0){
			char* message = "\nEntering foreground-only mode (& is now ignored)\n:";
			write(STDOUT_FILENO, message, 52);
			printStartFlag = 0;	//do not print message in main()
		}//else print a newline
		else{
			char* newline = "\n";
			write(STDOUT_FILENO, newline, 2);
			printStartFlag = 1;		//print message in main
		}		

		fgOnlyFlag = 1;		//flag to indicated in FG only mode
		
		
	}//else, change flag to indicate not in foreground only mode
	else{
		//if at getline, print message about exiting FG only mode
		if(printFgStop == 0){
			char* message = "\nExiting foreground-only mode\n: ";
			write(STDOUT_FILENO, message, 33);
			printStopFlag = 0;	//do not print message in main
		}//else print newline
		else{
			char* newline = "\n";
			write(STDOUT_FILENO, newline, 2);
			printStopFlag = 1;	//print message in main
		}
		fgOnlyFlag = 0;	//change flag to indicate not in FG only mode
	}
}

/*****************************************************************************
* function that repaces $$ with the main process ID, takes a string that
* holds the users input as an argument
* source: https://www.intechgrity.com/c-program-replacing-a-substring-from-a-string/#
******************************************************************************/
void insertPID(char *str){

        char buffer[MAXCHAR];	//stores new string with inserted PID
        char* strPtr;		//stores PIT as a string
        int  pid = getpid();	//stores PID as an int
        char strPid[10];	//
        char* expand = "$$";	//what to replace with PID

	//write PID to strPID
        sprintf(strPid, "%d", pid);

	//if there is no case of $$, return
        if(!(strPtr = strstr(str, expand)))
                return;

	//copy original string up to first occurance of $$ 
	//and add a null terminator
        strncpy(buffer, str, strPtr - str);
        buffer[strPtr - str] = '\0';

	//append PID to the string
        sprintf(buffer + (strPtr - str), "%s%s", strPid, strPtr + strlen(expand));

	//clear the original string
        memset(str, '\0', strlen(str));

	//copy buffer back to original string
        strcpy(str, buffer);

	//recursively check for other occurences of $$
        return insertPID(str);
}


/***********************************************************************
* function to get input from user, takes a string as an arguement
***********************************************************************/
int getInput(char* str){

	int numCharEntered = -5;//holds number of characters entered returned by getline()
	char* buffer;		//buffer used for input
	char comment = '#';	//used to check if line is a comment
	char firstChar; 	//used to check what the first character entered is
	size_t bufferSize = 0;	//buffer size
	
	//get input with getsize
	numCharEntered = getline(&buffer, &bufferSize, stdin);

	//if input is only enter, change numCharEntered to -1
	if((buffer)[numCharEntered - 1] == '\n' & numCharEntered == 1){
               numCharEntered = -1;
        }

	//if input is longer than allowed, print error and return 1
	if(numCharEntered > MAXCHAR){
		printf("Error: input too long. Must be %d characters or less.\n", MAXCHAR);
		fflush(stdout);
		return 1;
	}

	//get the first character entered
	firstChar = buffer[0];

	//if -1 clear any error, free buffer, and return 1
	if(numCharEntered == -1){
		clearerr(stdin);
		free(buffer);
		return 1;
	}//else if first char is #, free buffer and return 1;
	else if(firstChar  ==  comment){
		free(buffer);
		return 1;
	}//else strip input of newline, copy it to str, free the buffer, expand $$ as needed, and return 0
	else{
		if((buffer)[numCharEntered - 1] == '\n'){
			(buffer)[numCharEntered - 1] = '\0';
		}
		strcpy(str, buffer);
		free(buffer);
		insertPID(str);
		return 0;
	}	
}


/********************************************************************
* function to parse input into an array of strings, takes a str
* containing the user's input and an array of strings as arguments
* source: https://www.geeksforgeeks.org/making-linux-shell-c/
********************************************************************/
int parseInput(char* str, char** parsed){

	int i = 0;		//keeps track of location in parsed array
	char* and = "&";	//checks for background process command
	char* lastCmd;		//holds the last command entered
	char* buffer;		//holds strings returned by strtok

	//separate input by spaces using strtok and add it to parsed array
	buffer = strtok(str, " ");
	while(buffer != NULL & i < MAXCOM){
		parsed[i] = buffer;
		i++;
		buffer = strtok(NULL, " ");
	}

	//get the last Command entered
	lastCmd = parsed[i - 1];

	//if the last commande is &, return 1 to indicated 
	//background process command and change the last command to NULL
	if(strcmp(lastCmd, and) == 0){
		parsed[i - 1] = NULL;
		return 1;
	}//else attack NULL to the end of the array and return 0
	else
		parsed[i] = NULL; 
		return 0;

}


/***************************************************************************
* function to redirect STDOUT in the foreground child process
* loops through the parsed array until > string is found or NULL is reached
****************************************************************************/
void redirectGT(char** parsed){
	int i = 0;

	while(parsed[i] != NULL){
		char* gt = ">";
		int result;

		//if > is found
		if(strcmp(parsed[i], gt)== 0){
			//open, create, or truncate the file named at 
			//the next location in the array
			int targetFD = open(parsed[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			//check for errors
			if(targetFD == -1){
				printf("");
				exit (1);
			}

			//redirect STDOUT to opened file using dup2
			result = dup2(targetFD, 1);
			//check for errors
			if(result == -1){
				perror("");
				exit (2);
			
			}

			//remove > and the filename from the parsed 
			//array by copying over them
			int l = i;
			while(parsed[l] != NULL){
				parsed[l] = parsed[l+2];
				l++;
			}	
	
			return;
		}
		i++;
	}

	return;

}


/***************************************************************
* function to redirect STDIN in the foreground child process
* loops until < is found or NULL is reached
****************************************************************/
void redirectLT(char** parsed){
	int i = 0;
        while(parsed[i] != NULL){
                char* lt = "<";
                int result;
		
		//if < is found
		if(strcmp(parsed[i], lt) == 0){
			//open the file named at the next location in the array
			//for reading
                        int sourceFD = open(parsed[i+1], O_RDONLY);
			//check for errors
                        if(sourceFD == -1){
                                printf("cannot open %s for input\n", parsed[i+1]);
				fflush(stdout);
                                exit(1);
                        }

			//redirect STDIN to opened file with dup2
                        result = dup2(sourceFD, 0);
			//check for errors
                        if(result == -1){
                                perror("");
                                exit(2);
                        }

			//remove < and the filename from the array
                        int l = i;
                        while(parsed[l] != NULL){
                                parsed[l] = parsed[l+2];
                                l++;
                        }

                        return;
                }
                i++;

        }

        return;


}


/******************************************************************
* function that redirects the background process's output to 
* /dev/null unless another file location is specified
*******************************************************************/
void bgRedirectGT(char** parsed){
	//open /dev/null for writing
	char* nullout = "/dev/null";
	int targetFD = open(nullout, O_WRONLY);
	//check for erros
	if(targetFD == -1){
		perror("");
		exit(1);
	}

	int i = 0;
	int result;
	
	while(parsed[i] != NULL){
		char* gt = ">";
		//if >, close /dev/null and open file named at 
		//next location in the array		
		if(strcmp(parsed[i], gt) == 0){
			close(targetFD);
			targetFD = open(parsed[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			//check for errors
			if(targetFD == -1){
				perror("");
				exit(1);
			}
		
			//over write > and file name in array
			int l = i;
			while(parsed[i] != NULL){
				parsed[l] = parsed[l+2];
				l++;
			}
			break;
		}

		i++;

	}
	
	//redirect STDOUT to either /dev/null or file named in array
	result = dup2(targetFD, 1);
	//check for errors
	if(result == -1){
		perror("");
		exit(2);
	}

	return;
}


/*************************************************************
* function that redirects the background process's STDIN to 
* /dev/null unless another file location is specified
*************************************************************/
void bgRedirectLT(char** parsed){
	//open /dev/null for reading
	char* nullin = "/dev/null";
        int sourceFD = open(nullin, O_RDONLY);
	//check for errors
        if(sourceFD == -1){
                perror("");
                exit(1);
        }
        int i = 0;
        int result;

        while(parsed[i] != NULL){
                char* lt = "<";
		//if <, close /dev/null and open file named at 
		//the next location in the array
                if(strcmp(parsed[i], lt) == 0){
                        close(sourceFD);
                        sourceFD = open(parsed[i+1], O_RDONLY);
			//check for errors
                        if(sourceFD == -1){
                                printf("cannot open %s for input\n", parsed[i+1]);
                                exit(1);
                        }

			//overwrite < and filename in array
                        int l = i;
                        while(parsed[i] != NULL){
                                parsed[l] = parsed[l+2];
                                l++;
                        }
                        break;
                }

                i++;

        }

	//redirect STDIN using dup2
        result = dup2(sourceFD, 0);
	//check for errors
        if(result == -1){
                perror("");
                exit(2);
        }
        return;
}


/******************************************************************************
* function that forks off child process in foreground and evecvps the commands
* takes an array of strings that holds the parsed user input
******************************************************************************/
void fgCmd(char** parsed){

        ignore_action.sa_handler = SIG_IGN;	//used to ignore SIGTSTP

	//fork off main and child process
	pid_t childPID = fork();
		
	int childExitMethod = -5;	//initialize child exit method

	//switch based on childPID
	//case -1, there was an error in forking
	//case 0, child process
	//default, parent
	switch (childPID){
	case -1:
		perror("");
		exit(1);
		break;
	case 0:
		//set up sigaction in child to used default action for SIGINT
		sigaction(SIGINT, &SIGINT_action, NULL);
		//set up sigaction in child to ignore SIGTSTP
		sigaction(SIGTSTP, &ignore_action, NULL);

		//check for STDOUT redirection and redirect as needed
		redirectGT(parsed);
		//check for STDIN redirection and redirect as needed
		redirectLT(parsed);	

		//execvp the parsed array and check for error
		//if error set exitStatus to 1
		if(execvp(*parsed, parsed) < 0){
			perror(parsed[0]);
			exitStatus = 1;
			exit(1);
		}

	default:
		//in main process, wait until child process completes and 
		//check for errors
		waitpid(childPID, &childExitMethod, 0);
		if(childPID == -1){
			perror("");
			exit(1);
		}

		//check for method of exit of child process and update 
		//exitStatus and exitSignalFlag appropriately
		if(WIFEXITED(childExitMethod)){
			exitStatus = WEXITSTATUS(childExitMethod);
			exitSignalFlag = 0;
		}
		else if (WIFSIGNALED(childExitMethod)){
			exitStatus = WTERMSIG(childExitMethod);
			exitSignalFlag = 1;
			printf("terminated by signal %d\n", exitStatus);
			fflush(stdout);
		}
	}
}


/*************************************************************************
* function that forks off child process in the background and execvps the
* commandes. Takes an array of strings holding the parsed input
**************************************************************************/
void bgCmd(char** parsed){

	ignore_action.sa_handler = SIG_IGN; //used to ignore SIGTSTP and SIGINT

	//fork off main and child processes
	pid_t childPID = fork();

	int childExitMethod = -5;		//initialize childExitMethod

	//switch based on childPID
        //case -1, there was an error in forking
        //case 0, child process
	//default, parent
	switch(childPID){
	case -1:
		perror("");
		exit(1);
		break;
	case 0:
		//ignore SIGTSTP signal
		sigaction(SIGTSTP, &ignore_action, NULL);
		//ignore IGINT signal
		sigaction(SIGINT, &ignore_action, NULL);
		//check for STDOUT redirection and redirect as needed
		bgRedirectGT(parsed);
		//check for STDIN redirection and redirect as needed
		bgRedirectLT(parsed);

		//execvp parsed array
		//and check for error
		if(execvp(*parsed, parsed) < 0){
			perror(parsed[0]);
			exit(1);
		}
	default:
		//add the PID of the child process to the background PID array
		bgPIDS[count] = childPID;
		count++;
		if(count >= 1000){
			count = 0;
		}		
	}
}


/****************************************************************
* function that takes array of strings containing user's input 
* and checks if a built-in command was entered
* returns 1 (if not exiting) to indicate a built-in command
* was entered, otherwise returns 0
* source: https://www.geeksforgeeks.org/making-linux-shell-c/
****************************************************************/
int commandHandler(char** parsed){

	//initialize list of commands
	const char* listCmds[] = {"exit", "cd", "status"};
	int i;
	int cmd = 0;

	//compare parsed input to list of commands and change
	//the switch cmd accordingly
	for(i = 0; i < 3; i++){
		if(strcmp(parsed[0], listCmds[i]) == 0){
			cmd = i + 1;
			break;
		}		
	}
	
	int p;		//declare for use in switch

	//switch to correct command
	//case 1: exit and kill all bg processes
	//case 2: cd (change directory)
	//case 3: print exit status of last foreground process
	//default: no built in command was entered, break
	switch(cmd){
	case 1:
		//loop through all bgPIDS and kill any still active
		for(p = 0; p < count; p++){
			kill(bgPIDS[p], 15);
		}
		exit(0);	//exit the program
	case 2:
		//if a directory name is given, add "./" to front
		if(parsed[1] != NULL){
			char cwd[100];
			char buffer[100] = "./";
			strcat(buffer, parsed[1]);
			int ret = -5;
			//check for errors
			if( chdir(buffer) < 0){
				perror("");
			}
		}//else, no directory name, cd to home
		else{
			char* name = "HOME";
			char* value;
			value = getenv(name);
			int ret;
			if(value != NULL){
				if(ret = chdir(value) < 0){
                                	perror("");
				}
                        }
		}
		return 1;
	case 3:
		//if the last foreground process ended normally or with error
		//print the exit value
		if(exitSignalFlag == 0){
			printf("exit value %d\n", exitStatus);
			fflush(stdout);
		}//else print terminating signal
		else{
			printf("terminated by signal %d\n", exitStatus);
			fflush(stdout);
		}
		return 1;
	default:
		break;

	}
	//no built in command was entered, return 0
	return 0;
}



//main function, loops through prompt until user enters "exit"
int main(){
	
	//set up for signal handling
	SIGTSTP_action.sa_handler = catchSIGTSTP;
	ignore_action.sa_handler = SIG_IGN;
	sigfillset(&SIGINT_action.sa_mask);
	sigfillset(&SIGTSTP_action.sa_mask);
	SIGTSTP_action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &ignore_action, NULL);
	sigaction(SIGTSTP, &SIGTSTP_action, NULL);


	char inputBuffer[MAXCHAR];	//holds user input
	char* parsedInput[MAXCOM + 1];	//holds parsed user input to MAXCOM + 1 in case max commands reached to add NULL to the end of the array
	int inputReceived = -1;		//initialize variable to hold return value of the get input function
	int parsedReceived = -1;	//initialized variable to hold return value of the parsed input function (holds 0 if fg command, 1 if bg command)
	int builtCmd = -1;		//initialize variable to hold return value of the command handler function

	while(1){
		//print prompt
		printf(": ");
		fflush(stdout);
		//indicate to SIGTSTP handler that if signaled,
		//it will be in getline function
		printFgStart = 0;
		printFgStop = 0;
		//clear printStartFlag and printStopFlag from
		//previous loop, it will be used to indicate
		//if the SIGTSTP message is already printed in
		//the handler or needs to be printed in main
		printStartFlag = 0;
		printStopFlag = 0;
		//call get input function 
		inputReceived =	getInput(inputBuffer);
		//indicated to SIGTSTP handler that if signaled,
		//it is outside of getline
		printFgStart = 1;
		printFgStop = 1;

		if(inputReceived == 0){	
			//send input to be parsed into array of strings
			parsedReceived = parseInput(inputBuffer, parsedInput);
			//if not & not at end or if fgOnly flag is active
			if(parsedReceived == 0 || fgOnlyFlag == 1){
				//send to commandHandler to check for
				//built in commands and execute as needed
				builtCmd = commandHandler(parsedInput);

				//if a non-built in command was entered,
				//send input to be executed in a foreground
				//child process
				if(builtCmd == 0)
					fgCmd(parsedInput);

				//print SIGTSTP message upon completion of 
				//foreground process as appropriate
				if(printStartFlag == 1){
					printf("Entering foreground-only mode (& is now ignored)\n");
					fflush(stdout);
				}	
				if(printStopFlag == 1){
					printf("Exiting foreground-only mode\n");
					fflush(stdout);
				}
			}//else & at end of input
			else{
				//check for built in commands and execute
				//them as a foreground process
				builtCmd = commandHandler(parsedInput);

				//if no built in command, send commands to
				//be executed in background as a child process
				//and print the PID
				if(builtCmd == 0){
					bgCmd(parsedInput);
					printf("background pid is %d\n", bgPIDS[count-1]);
					fflush(stdout);
				}
			}
			//clear out input buffer
			memset(inputBuffer, '\0', strlen(inputBuffer));
	
		}		
		//loop through background PIDs to see if any have complete,
		//if they have, print appropriate message
		int l;
		for(l = 0; l < count; l++){
			int childExitMethod;
                	int tempStatus;
                	pid_t childPID = waitpid(bgPIDS[l], &childExitMethod, WNOHANG);
			//if the child process has just completed
                	if(childPID > 0){
				//if it exited normally or with error
                		if(WIFEXITED(childExitMethod)){
                        		tempStatus = WEXITSTATUS(childExitMethod);
                                	printf("background pid %d is done: exit value %d\n", childPID, tempStatus);
					fflush(stdout);
                        	}//if it exited by a signal
                        	else if(WIFSIGNALED(childExitMethod)){
                                	tempStatus = WTERMSIG(childExitMethod);
                                	printf("background pid %d is done: terminated by signal %d\n", childPID, tempStatus);
					fflush(stdout);
				}
			}
		}
	}
	return 0;

}





