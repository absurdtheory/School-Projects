#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){

	if(argc == 1 || argc > 2){
                fprintf(stderr, "Error: Program requires one argument\n");
                exit(1);
        }


	int i;
	time_t t;
	int argv1 = atoi(argv[1]);
	char buffer[argv1 + 1];
	memset(buffer, '\0', strlen(buffer));	

	srand((unsigned) time(&t));
	char* character[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J",				     "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
			     "U", "V", "W", "X", "Y", "Z", " "};

	for(i = 0; i < argv1; i++){

		int randNum = rand() % 27;
//		printf("randNum: %d\n", randNum);
//		printf("character[randNum]: %s\n", character[randNum]);
		strcat(buffer, character[randNum]);
//		printf("buffer: %s\n", buffer);

	}

	char* newline = "\n";
	strcat(buffer, newline);
	printf("%s", buffer);

	return 0 ;
	
}
