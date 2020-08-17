//***************************************
//Bello abarchi
//Date 11/04/2017
//Professor: Dennis Hunchuck
//***************************************
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define PAUSE getchar()
#define CLS system("cls")
#define FLUSH myFlush();

typedef struct {
	char* mo;
	int length; 

}WORD;

//funtion prototype
WORD* addWord();
void displayCertain(WORD **word, int wordCount);
void displayMenu();
char getChoice();
WORD ** load(int* wordCount, int size);
void myFlush();
void printWord(WORD **word, int wordCount);
void save(WORD **word, int wordCount);
void sortTheArray(WORD **word, int wordCount);

main() {
	char choice;
	int wordCount = 0;
	int size = 0;
	WORD **word;
	printf("=============================================\n");
	printf("\t\nEnter the number of words to enter(>1500): ");
	scanf("%i", &size); FLUSH;
	
	word = load(&wordCount, size);
	//Menu System
	do {
		choice = getChoice();
		switch (choice) {
		case 'A'://add new word			
			if (wordCount <= 1500){
				word[wordCount] = addWord();
				wordCount++;
			}
			else {
				printf("Cannot enter any more cars\n");
				PAUSE;
			}
			PAUSE;
			break;
		
		case 'B'://display all words that begin with a certain word
		if (wordCount > 0){
			 if (wordCount > 1)
				 sortTheArray(word, wordCount);
			displayCertain(word, wordCount);
			PAUSE;
		}
			else {
				printf("No words have been entered yet!\n");
				PAUSE;
			}
			break;
		case 'C'://print all word
			if (wordCount > 0) {
				if (wordCount > 1)
					sortTheArray(word, wordCount);
				printWord(word, wordCount); }
			else {
				printf("No student has been entered yet!\n");
				PAUSE;
			}
			break;
		case 'Q':// Quits the program
			save(word, wordCount);
			printf("\t===========SAVED SUCCESSFULLY==========\n");
			printf("\t===========HAVE A NICE DAY!============\n");
			printf("\t=======================================\n");
			PAUSE;
			break;
		default:
			break;
		}//end switch
	} while (choice != 'Q');

	//Destroy word array

}//end of main
void displayMenu() {
	CLS;
	printf("\t=======================================\n");
	printf("\t==         M A I N   M E N U         ==\n");
	printf("\t=======================================\n");
	printf("\t[A] Add new Word\n");
	printf("\t[B] Display words beginning w/ a certain letter\n");
	printf("\t[C] Print all words\n");
	printf("\t[Q]Save all words & Quit \n");
	printf("\t=======================================\n");
	printf("\tEnter choice: ");
}//end displayMenu
char getChoice() {
	char choice;
	displayMenu();
	scanf(" %c", &choice); FLUSH;

	return toupper(choice);
}//end getChoice
void myFlush() {
	char nothing;
	while (scanf("%c", &nothing) == NULL);
}//end of myFlush

WORD* addWord(){
	int length = 0;
	WORD* word = NULL;
	char input[21] = { 0 };
	//get the word from user
	printf("enter a word [20]" );
	scanf("%s", input);

	length = strlen(input);
	word = malloc(sizeof(WORD));
	word->length = length;
	word->mo = malloc((length+1) * sizeof(char));

	strcpy(word->mo, input);
	printf("the word '%s' has %i letters", word->mo, length);
	PAUSE;
	return word;

}//end of addWord
void sortTheArray(WORD **word, int wordCount) {
	char switchMade = 'N';
	int bottom = wordCount - 1;
	WORD* temp = NULL;
	int i;
	
	do {
		switchMade = 'N';
		for (i = 0; i < bottom; i++)
			if (strcmp(word[i]->mo, word[i + 1]->mo) > 0) {
				temp = word[i];
				word[i] = word[i + 1];
				word[i + 1] = temp;
				switchMade = 'Y';
			}
		bottom--;
	} while (switchMade == 'Y');

}//end of sortTheArray
void displayCertain(WORD **word, int wordCount){
	char search = ' ';
	int i = 0;
	int h = 0;
	printf("======================================================\n");
	printf(" what is the initial of the word you are looking for? : ");
	scanf("%c", &search);
	printf("======================================================\n");
	for (i = 0; i < wordCount; i++)
		if (word[i]->mo[0] == search) {
			h++,
				printf("%s\n", word[i]->mo);
		}
			
	printf("========THERE ARE %i WORDS WITH THE INITIAL %c =======\n", h, search);
	
	PAUSE;
}//end of displayCertain
WORD** load(int *wordCount, int size) {
	FILE *ptr;
	WORD** word = NULL;
	int i = 0;

	
	ptr = fopen("StoredWords.bin", "rb");

	if (ptr == NULL) {
		word = calloc(size, sizeof(WORD*));
	}
	else {
		fread(wordCount, sizeof(int), 1, ptr);
		word = calloc(*wordCount + size, sizeof(WORD*));
		for (i = 0; i < *wordCount; i++) {
			word[i] = malloc(sizeof(WORD));
			fread(&word[i]->length, sizeof(int), 1, ptr);
			word[i]->mo = malloc(sizeof(char) * word[i]->length);
			fread(word[i]->mo, sizeof(char), word[i]->length, ptr);
			word[i]->mo[word[i]->length] = '\0';
		}
		fclose(ptr);
	}
	

	return word;
}//end load cars

void printWord(WORD **word, int wordCount) {
	int i = 0;
	printf("========THERE ARE %i WORDS=======\n", wordCount);
	for (i = 0; i < wordCount; i++)
		printf("%s\n", word[i]->mo);
	printf("=================================\n");
	PAUSE;
}//end of printWorld
void save(WORD **word, int wordCount) {
	FILE *ptr;
	int i = 0;
	ptr = fopen("StoredWords.bin", "wb");
	if (ptr == NULL) {
		printf("\nError Could not save words\n");
		PAUSE;
		exit(-1);
	}
	else {
		fwrite(&wordCount, sizeof(int), 1, ptr);
		for (i = 0; i < wordCount; i++) {
			fwrite(&word[i]->length, sizeof(int), 1, ptr); 
			fwrite(word[i]->mo, sizeof(char), word[i]->length, ptr);
		}
	}
	fclose(ptr);

}// end save 