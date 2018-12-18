//progam name: tuckera6.adventure.c
//date: 10/16/2018
//Name: Alexis Tucker
//Class: CS 344

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//initialize mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//initialize global variable to detect when second thread needs to exit at end
//of the program
int exitThread = 0;


//function that prints the current time to the file. It is the start_routine
//argument of the second thread
void* checkTime(){

	//call lock mutex to block itself until main thread unlocks
	pthread_mutex_lock(&mutex);

	//if exitThread global variable is 1, exit without printing to file
	if(exitThread == 1)
		pthread_exit(NULL);

	char outstr[200];
	time_t t;
	struct tm *tmp;
	FILE *tempF;
	
	t= time(NULL);
	tmp= localtime(&t);

	//write current time in correct format to outstr
	strftime(outstr, sizeof(outstr), "%I:%M%p, %A, %B %d, %Y\n", tmp);

	//create currentTime.txt if it doesn't exist, overwrite it if it does
	tempF = fopen("currentTime.txt", "w+");

	//send outstr to currentTime.txt file"
	fprintf(tempF, outstr);

	fclose(tempF);
	
	//unlock mutex
	pthread_mutex_unlock(&mutex);
}




int main(){

//loop through directories starting with "tuckera6.rooms." and find the most
//most recent one
//source: readDirectory.c from 2.4 Manipulating Directories reading by Benjamin Brewster (instructor)

	int newestDirTime =-1;
	char targetDirPrefix[32] = "tuckera6.rooms.";
	char newestDirName[256];
	memset(newestDirName, '\0', sizeof(newestDirName));

	DIR* dirToCheck;
	struct dirent *fileInDir;
	struct stat dirAttributes;

	dirToCheck = opendir(".");

	if(dirToCheck > 0)
	{
		while((fileInDir = readdir(dirToCheck)) != NULL)
		{
			if(strstr(fileInDir->d_name, targetDirPrefix) != NULL)
			{
				stat(fileInDir->d_name, &dirAttributes);

				if((int)dirAttributes.st_mtime > newestDirTime)
				{
					newestDirTime = (int)dirAttributes.st_mtime;
					memset(newestDirName, '\0', sizeof(newestDirName));
					strcpy(newestDirName, fileInDir->d_name);

				}	
			
			}	


		}

	}

	closedir(dirToCheck);


//open most recent directory and read the room data
	DIR* roomDirectory;
	roomDirectory = opendir(newestDirName);
	struct dirent *curFile;

//struct room to recreate structs from data
	struct room
        {
                char* name;
                char* type;
                int numConnections;         //holds number of string connections
		int numActiveConnections;   //holds number of struct connections
		char* sConnections[6];       //string names of connected rooms
                struct room* connections[6]; //pointers to connected rooms
        };


	struct room roomArray[7];  //array to hold all seven rooms
	FILE* fileArray[7];        //array to hold all seven files
	
	int x = 0;

	char filePath[100];

        //add each file to the fileArray in the room directory
        //with the exception of the hidden files
	if(roomDirectory > 0){
		while((curFile = readdir(roomDirectory)) != NULL){
			//create the file path to each file in room directory
			memset(filePath, '\0', 100);
       			strcpy(filePath, newestDirName);
	        	strcat(filePath, "/");

			strcat(filePath, curFile->d_name);
			 
			if((strcmp(curFile->d_name, ".") == 0 ) || (strcmp(curFile->d_name, "..") == 0))
				continue;
			else{
				fileArray[x] = fopen(filePath, "r") ;
	
			}
			x++;
		}
	}

	//close the room directory
	closedir(roomDirectory);


//create first room
	char tempstring[20];
	int count;
	int i=0;
	char tempArray[30][20];
	
	//add each word into a an array
	while(fscanf(fileArray[0], "%s", tempstring) != EOF){
		strcpy(tempArray[i], tempstring);
		i++;
	}

	//since each file is the same format, it can be hardcoded which 
	//array element is assigned to which struct attribute
	roomArray[0].name = tempArray[2];
	roomArray[0].type = tempArray[i-1];
	
	if(i == 15)
        	roomArray[0].numConnections = 3;
        else if(i == 18)
        	roomArray[0].numConnections = 4;
	else if(i == 21)
		roomArray[0].numConnections = 5;
	else if(i == 24)
		roomArray[0].numConnections = 6;
	
	//initialize numActive connections to zero, after all struct pointers
	//are added to connections later, this should be the same as
	//numConnections
	roomArray[0].numActiveConnections=0;

	//add the name of each connected room to sConnections
	int l;
	int k=5;
	for(l=0; l<roomArray[0].numConnections; l++){
		roomArray[0].sConnections[l] = tempArray[k];
		k= k+3;
	}


//the following creation of rooms followes the same formate as the first one

//create second room
	char tempArray2[30][20];
	i=0;
        while(fscanf(fileArray[1], "%s", tempstring) != EOF){
          	strcpy(tempArray2[i], tempstring);
                i++;
        }

	roomArray[1].name = tempArray2[2];
        roomArray[1].type = tempArray2[i-1];

        if(i == 15)
                roomArray[1].numConnections = 3;
        else if(i == 18)
                roomArray[1].numConnections = 4;
        else if(i == 21)
                roomArray[1].numConnections = 5;
        else if(i == 24)
                roomArray[1].numConnections = 6;

	roomArray[1].numActiveConnections=0;

	k=5;
        for(l=0; l<roomArray[1].numConnections; l++){
                roomArray[1].sConnections[l] = tempArray2[k];
                k= k+3;
        }

//create third room

        char tempArray3[30][20];
        i=0;
        while(fscanf(fileArray[2], "%s", tempstring) != EOF){
                strcpy(tempArray3[i], tempstring);
                i++;
        }

        roomArray[2].name = tempArray3[2];
        roomArray[2].type = tempArray3[i-1];

        if(i == 15)
                roomArray[2].numConnections = 3;
        else if(i == 18)
                roomArray[2].numConnections = 4;
        else if(i == 21)
                roomArray[2].numConnections = 5;
        else if(i == 24)
                roomArray[2].numConnections = 6;

	roomArray[2].numActiveConnections=0;


        k=5;
        for(l=0; l<roomArray[2].numConnections; l++){
                roomArray[2].sConnections[l] = tempArray3[k];
                k= k+3;
        }

//create fourth room

        char tempArray4[30][20];
        i=0;
        while(fscanf(fileArray[3], "%s", tempstring) != EOF){
                strcpy(tempArray4[i], tempstring);
                i++;
        }

        roomArray[3].name = tempArray4[2];
        roomArray[3].type = tempArray4[i-1];

        if(i == 15)
                roomArray[3].numConnections = 3;
        else if(i == 18)
                roomArray[3].numConnections = 4;
        else if(i == 21)
                roomArray[3].numConnections = 5;
        else if(i == 24)
                roomArray[3].numConnections = 6;

	roomArray[3].numActiveConnections=0;

        k=5;
        for(l=0; l<roomArray[3].numConnections; l++){
                roomArray[3].sConnections[l] = tempArray4[k];
                k= k+3;
        }

//create 5th room

	char tempArray5[30][20];
        i=0;
        while(fscanf(fileArray[4], "%s", tempstring) != EOF){
                strcpy(tempArray5[i], tempstring);
                i++;
        }

        roomArray[4].name = tempArray5[2];
        roomArray[4].type = tempArray5[i-1];

        if(i == 15)
                roomArray[4].numConnections = 3;
        else if(i == 18)
                roomArray[4].numConnections = 4;
        else if(i == 21)
                roomArray[4].numConnections = 5;
        else if(i == 24)
                roomArray[4].numConnections = 6;

	roomArray[4].numActiveConnections=0;

        k=5;
        for(l=0; l<roomArray[4].numConnections; l++){
                roomArray[4].sConnections[l] = tempArray5[k];
                k= k+3;
        }

//create sixth room

        char tempArray6[30][20];
        i=0;
        while(fscanf(fileArray[5], "%s", tempstring) != EOF){
                strcpy(tempArray6[i], tempstring);
                i++;
        }

        roomArray[5].name = tempArray6[2];
        roomArray[5].type = tempArray6[i-1];

        if(i == 15)
                roomArray[5].numConnections = 3;
        else if(i == 18)
                roomArray[5].numConnections = 4;
        else if(i == 21)
                roomArray[5].numConnections = 5;
        else if(i == 24)
                roomArray[5].numConnections = 6;

	roomArray[5].numActiveConnections=0;

        k=5;
        for(l=0; l<roomArray[5].numConnections; l++){
                roomArray[5].sConnections[l] = tempArray6[k];
                k= k+3;
        }

//create seventh room

        char tempArray7[30][20];
        i=0;
        while(fscanf(fileArray[6], "%s", tempstring) != EOF){
                strcpy(tempArray7[i], tempstring);
                i++;
        }

        roomArray[6].name = tempArray7[2];
        roomArray[6].type = tempArray7[i-1];

        if(i == 15)
                roomArray[6].numConnections = 3;
        else if(i == 18)
                roomArray[6].numConnections = 4;
        else if(i == 21)
                roomArray[6].numConnections = 5;
        else if(i == 24)
                roomArray[6].numConnections = 6;

	roomArray[6].numActiveConnections=0;

        k=5;
        for(l=0; l<roomArray[6].numConnections; l++){
                roomArray[6].sConnections[l] = tempArray7[k];
                k= k+3;
        }

	for(l=0; l<7; l++){
		fclose(fileArray[l]);
	}

//reconnect room structures


//function takes two rooom structs and returns true(1) if they are already 
//connected in connections of struct x
	int ConnectionAlreadyExists(struct room x, struct room y){
                int i;
	        for(i=0; i < x.numActiveConnections; i++){
                        if(strcmp(x.connections[i]->name, y.name) == 0){
                                return 1;
                        }
                }
                return 0;
        }

//function connects room x to room y
	void ConnectRoom(struct room x, struct room y){
                int s;
                for(s=0; s<7; s++){
			if(strcmp(roomArray[s].name, y.name) ==0){
				int z;
				for(z=0; z<7; z++){
				   if(strcmp(roomArray[z].name, x.name) == 0){
					roomArray[z].connections[roomArray[z].numActiveConnections] = &roomArray[s];
					roomArray[z].numActiveConnections++;
					break;

				   }
				}
				break;
			}
		
		}
	}

//for each room in the roomArray, reconnect the connections
	int w;
	for(w=0; w< 7; w++){
		int g;
		for(g=0; g<roomArray[w].numConnections; g++){
			//create a temp struct with the name of one of 
			//roomArray[w]'s connections so the correct room
			//can be found and connected in ConnectRoom()
			struct room temp;
			temp.name = roomArray[w].sConnections[g];
			//if the connection does not already exist, connect
			//the rooms to each other
			if(ConnectionAlreadyExists(roomArray[w], temp) == 0){
				ConnectRoom(roomArray[w], temp);
				ConnectRoom(temp, roomArray[w]);
			}
		}
	}


//set up game
	struct room *current; //points to the current room

	//initialize current room pointer to room with type "START_ROOM"
	for(w=0; w<7; w++){
		if(strcmp(roomArray[w].type, "START_ROOM") == 0){
			current = &roomArray[w];
			break;
		}
	}

	int steps=0;		//initialize player steps to zero
	int startingsteps;	//variable to keep track steps at start of room
	char* path[1000];	//create path array to hold room names 


//game output

	char* buffer = NULL;
	size_t bufsize= 0;
	size_t characters = -5;

	//define second thread
	pthread_t threads[2];
	//lock main thread
	pthread_mutex_lock(&mutex);
	//create second thread
	pthread_create(&threads[0], NULL, checkTime, NULL);		
	

//while the player has not reached room with type "END_ROOM" loop
	while(strcmp(current->type, "END_ROOM") != 0){

		//set starting steps equal to steps
		startingsteps = steps;

		printf("CURRENT LOCATION: %s\n", current->name);
		printf("POSSIBLE CONNECTIONS: ");
		//display names of connected rooms
		int h;
		for(h=0; h<current->numConnections - 1; h++){
			printf("%s, ",current->connections[h]->name);
		}
		printf("%s.\n", current->connections[current->numConnections-1]->name);

		printf("WHERE TO? >");
		characters = getline(&buffer, &bufsize, stdin);

//remove newline from the buffer by replacing it with null terminator
//source:https://stackoverflow.com/questions/13000047/function-to-remove-newline-has-no-effect
		if((buffer)[characters - 1] == '\n'){
			(buffer)[characters - 1] = '\0';
			--characters;
		}

//check if input matches a connecting room, if it does, set current room
//pointer to that room, add new curretnt room name to path, increment steps
		for(h=0; h<current->numConnections; h++){
			if(strcmp(current->connections[h]->name, buffer)==0){
				current = current->connections[h];
				path[steps] = current->name;
				steps++;
				break;
			}
		}

//while the buffer has "time" as input
		while(strcmp(buffer, "time") == 0){
			//unlock mutex so second thread will run	
			pthread_mutex_unlock(&mutex);

			//join to have main thread wait until second thread
			//is complete
			pthread_join(threads[0], NULL);

			//open "currentTime.txt"
			FILE *tempfile = fopen("currentTime.txt","r");
			char buff[255];
			
			//read contents of currentTime.txt to buffer string
			fgets(buff, 255, (FILE*)tempfile);

			//print string to screen
			printf("\n%s\n",buff);

			//close file
			fclose(tempfile);
			
			//lock mutex
			pthread_mutex_lock(&mutex);
			
			//recreate second thread
			pthread_create(&threads[0], NULL, checkTime, NULL);

			//get next input from user
			printf("WHERE TO? >");
	                characters = getline(&buffer, &bufsize, stdin);
			if((buffer)[characters - 1] == '\n'){
                       		(buffer)[characters - 1] = '\0';
                        	--characters;
	                }
			
			//if input matches connection name, change current ptr
			for(h=0; h<current->numConnections; h++){
				if(strcmp(current->connections[h]->name, buffer)==0){
        	                        current = current->connections[h];
                	                path[steps] = current->name;
                        	        steps++;
                                	break;
                        	}
              	 	}
		 	//if the user inputs "time" again, loops
                }
		
		//if the user did not take a step (switch rooms) or call time
		if(startingsteps == steps & strcmp(buffer, "time") !=0) {
			printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
		}		
	
		printf("\n");

	}	

	//display victory message, number of steps, and path
	printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", steps);
	int y;
	for(y=0; y<steps; y++){
		printf("%s\n", path[y]);
	}

	//free input buffer
	free(buffer);

	//set global variable exitThread to one so second thread will exit
	//without printing to currentTime.txt
	exitThread =1;

	//unlock the mutex
	pthread_mutex_unlock(&mutex);

	//join so main thread will wait for second thread to complete
	pthread_join(threads[0], NULL);

	//destroy mutex
	pthread_mutex_destroy(&mutex);	
	return 0;
}
