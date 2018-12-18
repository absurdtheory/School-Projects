//program name: tuckera6.buildrooms.c
//date: 10/16/2018
//name: Alexis Tucker
//class: CS 344

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
//create directory using process ID
////source: 2.4 Manipulating Directories reading (hellodirectory program)
////string lecture by Benjamin Brewster (Instructor)
	int pid = getpid();
	char* literal = "tuckera6.rooms.";

	char* directoryName;
	directoryName = malloc(50 * sizeof(char));
	if (directoryName == 0){
		printf("malloc() failed\n");
	}

	memset(directoryName, '\0', 50);
	sprintf(directoryName,"%s%d", literal, pid);

	int result= mkdir(directoryName, 0755);


//room names
	char* name1 = "Cthulhu";
	char* name2 = "Bast";
	char* name3 = "Kthanid";
	char* name4 = "Oryx";
	char* name5 = "Oztalun";
	char* name6 = "Noodles";
	char* name7 = "Shaval";
	char* name8 = "Ulthar";
	char* name9 = "Vorvad";
	char* name10 = "YadThad";
	

//add room names to array to shuffle them	
	char* nameArray[10] = {name1, name2, name3, name4, name5, name6, name7,
			       name8, name9, name10};


//fisheryates shuffle for room naming
//source:https://stackoverflow.com/questions/42321370/fisher-yates-shuffling-algorithm-in-c
	
	time_t t;
	srand((unsigned) time(&t));
	
	void FisherYates(char* array[], int n){

                int i,
                    j;
                char* tmp;

                for(i = n - 1; i > 0; i--){
                        j = rand() % (i + 1);
                        tmp = array[j];
                        array[j] = array[i];
                        array[i] = tmp;
                }
        }

//call fisher yates shuffle to randomize order of room names in array with no
//repetition		
	FisherYates(nameArray, 10);


//define enum for room type
	typedef enum {START_ROOM, END_ROOM, MID_ROOM} roomType;


//create array of a room types with one array element for each room to shuffle
//them
	roomType typeArray[7] = {START_ROOM, MID_ROOM, MID_ROOM, MID_ROOM, MID_ROOM, MID_ROOM, END_ROOM};


//fisheryates shuffle function using the enum
	void FisherYatesType(roomType array[], int n){
	            int i,
                    j;
                roomType tmp;

                for(i = n - 1; i > 0; i--){
                        j = rand() % (i + 1);
                        tmp = array[j];
                        array[j] = array[i];
                        array[i] = tmp;
                }
        }


//call fisheryatestype shuffle to randomize the order of roomType in the array
//with no repetition outside of the hard-coded multiple MID_ROOMs
	FisherYatesType(typeArray, 7);


//define struct room	
	struct room
        {
                char* name;
                roomType type;
                int numConnections;
                struct room* connections[6];
        };


//declare seven unitialized rooms
	struct room room1;
        struct room room2;
        struct room room3;
        struct room room4;
        struct room room5;
        struct room room6;
	struct room room7;


//initialize rooms with room name and type from shuffled arrays and set
//numConnections to zero
	room1.name = nameArray[0];
       	room1.type = typeArray[0];
        room1.numConnections = 0;

        room2.name = nameArray[1];
        room2.type = typeArray[1];
        room2.numConnections = 0;

        room3.name = nameArray[2];
        room3.type = typeArray[2];
        room3.numConnections = 0;

        room4.name = nameArray[3];
        room4.type = typeArray[3];
        room4.numConnections = 0;

	room5.name = nameArray[4];
        room5.type = typeArray[4];
        room5.numConnections = 0;

        room6.name = nameArray[5];
        room6.type = typeArray[5];
        room6.numConnections = 0;

        room7.name = nameArray[6];
        room7.type = typeArray[6];
        room7.numConnections = 0;


//add rooms to array for easy access	
	 struct room roomArray[7] = {room1, room2, room3, room4,
                                    room5, room6, room7};


//add connections. Functions below are outlined in the source.
//source: 2.2 Program Outlining in Program 2 reading by Benjamin Brewster (instructor)


//function returns 1 (true) if all rooms have 3 or more connections
	int IsGraphFull(){
		int i;
		for (i=0; i <7; i++){
			if(roomArray[i].numConnections < 3)
				return 0;
		}
		return 1;
	}


//function returns a random room by generating a number 0-6 then returns the 
//corresponding roomArray element
	struct room GetRandomRoom(){
		int ranRoomNum = (rand() % 7);
                return roomArray[ranRoomNum];
        }


//function returns 1(true) if room passed as an argument has less than 6
//connections, else returns 0 (false)
        int CanAddConnectionFrom(struct room x){
                if(x.numConnections < 6)
                        return 1;
                else
                        return 0;
        }


//function returns 1 (true) if the two room arguments are already connected
//to each other, otherwise returns 0 (false)
        int ConnectionAlreadyExists(struct room x, struct room y){
                int i;
		for(i=0; i < x.numConnections; i++){
                        if(strcmp(x.connections[i]->name, y.name) == 0){
    				return 1;	
			}
                }
                return 0;
        }


//function connects the second room argument to the first room argument
	void ConnectRoom(struct room x, struct room y){
        	int s;
		for(s=0; s<7; s++){
			//find room y in roomArray
			if(strcmp(roomArray[s].name, y.name) == 0){
				int z;
				//find room x in roomArray
				for(z=0; z< 7; z++){
					if(strcmp(roomArray[z].name, x.name) == 0){
						//add room y to room z connections in roomArray and increase numConnections of room z in roomArray
						roomArray[z].connections[roomArray[z].numConnections] = &roomArray[s];
						roomArray[z].numConnections++;
						break;
					}
				}
				break;
			}
		}
	}


//function that returns 1 (true) if room x and room y have the same name, 
//else returns 0 (false)
        int IsSameRoom(struct room x, struct room y){
                if(strcmp(x.name, y.name) == 0){
		        return 1;
		}
                else
                        return 0;
        }


//function that selects a random room, verifies it can have an additional
//connection room, then repeatedly selects a second room until a room that is
//not the first room, can have additional connections, and is not already
//connected to the first room is found. Then the rooms are connected together.	
	void AddRandomConnection(){
		struct room A;
		struct room B;
		
		while(1){
			A = GetRandomRoom();
			if (CanAddConnectionFrom(A) == 1)
				break;
		}
		do{
			B = GetRandomRoom();
		}
		 while (CanAddConnectionFrom(B) == 0 || IsSameRoom(A,B) == 1 || ConnectionAlreadyExists(A,B) == 1);
		
		ConnectRoom(A,B);
		ConnectRoom(B,A);
	}


//while not all rooms have 3-6 connections, repeatedly add a random connection
//between rooms
	while (IsGraphFull() == 0){
                AddRandomConnection();

	}


//create and open seven files, adding them to an array of files for easy access
	FILE* fileArray[7];

	FILE* file1;
	char pathFile[50];
        memset(pathFile, '\0', 50);
        sprintf(pathFile, "%s/%s", directoryName, "GreatOldOnes");
	file1 = fopen(pathFile, "w+");
	fileArray[0] = file1;

	FILE* file2;
        memset(pathFile, '\0', 50);
        sprintf(pathFile, "%s/%s", directoryName, "OuterGods");
        file2 = fopen(pathFile, "w+");
	fileArray[1] = file2;

	FILE* file3;
        memset(pathFile, '\0', 50);
        sprintf(pathFile, "%s/%s", directoryName, "ElderGods");
        file3 = fopen(pathFile, "w+");
	fileArray[2] = file3;

        FILE* file4;
        memset(pathFile, '\0', 50);
        sprintf(pathFile, "%s/%s", directoryName, "GreatOnes");
        file4 = fopen(pathFile, "w+");
	fileArray[3] = file4;

	FILE* file5;
        memset(pathFile, '\0', 50);
        sprintf(pathFile, "%s/%s", directoryName, "NamelessCity");
        file5 = fopen(pathFile, "w+");
	fileArray[4] = file5;

        FILE* file6;
        memset(pathFile, '\0', 50);
        sprintf(pathFile, "%s/%s", directoryName, "Innsmouth");
        file6 = fopen(pathFile, "w+");
	fileArray[5] = file6;

        FILE* file7;
        memset(pathFile, '\0', 50);
        sprintf(pathFile, "%s/%s", directoryName, "Arkham");
        file7 = fopen(pathFile, "w+");
	fileArray[6] = file7;


//loop to write each room to a file
	ssize_t nwritten;
	char towrite[100];
	int c;

	for(c=0; c < 7; c++){
		//create a string (towrite) that contains the format 
		//required for the file
		memset(towrite, '\0', 100);
		sprintf(towrite, "ROOM NAME: %s\n", roomArray[c].name);
		int d;
		for(d = 0; d < roomArray[c].numConnections; d++){
			char tempstring[50];
			memset(tempstring, '\0', 50);
			sprintf(tempstring, "CONNECTION %d: %s\n", d + 1, roomArray[c].connections[d]->name);
			strcat(towrite, tempstring);
		}
		char temp2[10];
		memset(temp2, '\0', 10);
		//if statement to add enum text as a string to the room string
		if(roomArray[c].type == 0)
			strcpy(temp2, "START_ROOM");
		else if(roomArray[c].type == 2)
			strcpy(temp2, "MID_ROOM");
		else
			strcpy(temp2, "END_ROOM");

		char temp3[20];
		memset(temp3, '\0', 20);
		sprintf(temp3, "ROOM TYPE: %s\n", temp2);
		strcat(towrite, temp3);
		//write string to file
		fprintf(fileArray[c], towrite);
	}

	//close files
	for(c=0; c<7; c++){
		fclose(fileArray[c]);

	}

	//free any mallocs
	free(directoryName);

	return 0;
}
