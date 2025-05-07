//Ryan Rogers Project 10
//wordle
//5/2/25

#include <stdio.h>
#define FILENAME "mystery.txt"
#define size 50
//prototype

void prompt(int guessNum);
void getMysteryWord(char word[size]);
void getUserGuess(char guess[size], int guessNum);
void lowerCase(char guess[]);
void exactMatch(char guess[], char word[], char display[12][6], int row);
void plantCarrots(char guess[], char word[], char display[12][6], int row);
void displayGuesses(char display[12][6], int row);
int isCorrect(char guess[], char word[]);
void displayVictory(int guessNum, char word[]);

//main



int main(){
	int guessNum = 1, row = 0;
	char word[size];
	char guess[size];
	char display[12][6];
	for(int i = 0; i < 12; i++){
	    for(int j = 0; j < 5; j++){
		display[i][j] = ' ';
	    }
	    
	}
	getMysteryWord(word);
	
	do{
		prompt(guessNum);
		
		getUserGuess(guess, guessNum);	
		lowerCase(guess);
		exactMatch(guess, word, display, row);
		plantCarrots(guess, word, display, row);
		if(isCorrect(guess, word) == 1){
			displayVictory(guessNum, word);
			return 0;
		}
		else{
			row += 2;
			displayGuesses(display, row);
		}
		guessNum ++;
		
	}while(guessNum <= 6 || isCorrect(guess, word) == 1);	
	
	if(guessNum == 7 && isCorrect(guess, word) == 0){
		printf("You lost, better luck next time!\n");
	}
	
	return 0; 
}



//definitions

void getMysteryWord(char word[size]){
	FILE* fptr;
	fptr = fopen(FILENAME, "r");
	if(fptr == NULL){
		printf("Sorry, could not get today's word. Try again tomorrow.\n");
	}
	for(int i = 0; i < size; i++){
		fscanf(fptr, "%c", &word[i]);
	}
	fclose(fptr);	

}

void prompt(int guessNum){
	if(guessNum >= 1 && guessNum <= 5){
		printf("GUESS %d! Enter your guess: ", guessNum);
	}
	else if(guessNum == 6){
		printf("FINAL GUESS : ");
	}
}

void getUserGuess(char guess[size], int guessNum){
	char fail = 'n';
	int length = 0;
	
	scanf(" %s", guess);
	
	
	
	
		for(int i = 0; guess[i] != '\0'; i++){
			length++;
			if (!(guess[i] >= 'A' && guess[i] <= 'Z' || guess[i] >= 'a' && guess[i] <= 'z')){
				fail = 'y';
			}	
		}
		while(length != 5 || fail == 'y'){
			if(length != 5 && fail == 'y'){
				printf("Your guess must be 5 letters long.Your guess must contain only letters.\n");	
			}
			else if(length != 5){
				printf("Your guess must be 5 letters long.\n");
			}
			else if(fail == 'y'){
				printf("Your guess must contain only letters.\n");
			}
			
			printf("Please try again: ");
			scanf(" %s", guess);
			
			fail = 'n';
			length = 0;
			
			for(int i = 0; guess[i] != '\0'; i++){
				length++;
				if (!(guess[i] >= 'A' && guess[i] <= 'Z' || guess[i] >= 'a' && guess[i] <= 'z')){
				fail = 'y';
				}	
			}
		
		}	

	
}

void lowerCase(char guess[size]){
	for (int i = 0; guess[i] != '\0'; i++){
		if(guess[i] >= 'A' && guess[i] <= 'Z'){
			guess[i] = guess[i] + 32;
		}
	}

}

void exactMatch(char guess[size], char word[size], char display[12][6], int row){
	

	for(int i = 0; guess[i] != '\0'; i++){
		if(guess[i] == word[i]){
			display[row][i] = guess[i] - 32;
		}
		else{
			display[row][i] = guess[i];
		}
	}
			 

}
void plantCarrots(char guess[size], char word[size], char display[12][6], int row){
	char used[5];
	
	for(int i = 0; i < 5; i++){
		used[i] = 'n';
	}
	for(int i = 0; i < 5; i++){
        	display[row + 1][i] = ' ';
       		if(guess[i] == word[i]){
            		used[i] = 'y';
        	}
    	}
	for(int i = 0; i < 5; i++){
		if(guess[i] != word[i]){
			
			int found = 0;
			for(int j = 0; j < 5; j++){
				if(found == 0){
				 	if (i != j && word[j] == guess[i] && used[j] != 'y'){
				 		display[row + 1][i] = '^';
				 		used[j] = 'y';
				 		found = 1;
				 	}
			 	}
			 }
		}
	}	
}

void displayGuesses(char display[12][6], int row){
	printf("================================\n");
	for(int rowIndex = 0; rowIndex < row; rowIndex++){
  		for(int colIndex = 0; colIndex < 5; colIndex++){
    			printf("%c", display[rowIndex][colIndex]);
    			
  		}
  		printf("\n");
	}
}
int isCorrect(char guess[], char word[]){
	for (int i = 0; i < 5; i++) {
		if (guess[i] != word[i]) {
			return 0;
		}
	}
	return 1;
}


void displayVictory(int guessNum, char word[size]){
	char wordUpper[6];
	for(int i = 0; i < 5; i++){
		wordUpper[i] = word[i] - 32;
	}
	printf("================================\n");
	printf("		%s\n", wordUpper);
	if(guessNum == 1){
		printf("	You won in %d guess!\n", guessNum);
	}
	else{
		printf("	You won in %d guesses!\n", guessNum);
	}
	
	if(guessNum == 1){
		printf("		GOATED!\n");
	}
	else if (guessNum == 2 || guessNum == 3){
		printf("		Amazing!\n");
	}
	else if(guessNum == 4 || guessNum == 5){
		printf("		Nice!\n");
	}
		
}





/* algo
1. have to have code know correct msyetry word
file io
create pointer
open file
scanf word into array
close file

for until user guesses or runs out of guesses (6) ->

1. prompt user for guess
from executable guess %d until final guess (6)

2. get user guess
save as array/string

3. from github, turn user guess into lower case
had to look up, use ascii values, +- 32 to go from lower 2 upper and vice versa

4. compare guess to mystery word
create a 2d array for later
if elements match exact, save as upper case version of letter (- 32)
put in same spot as array ion 2d array

if letter occurs but not right spot, put ^ under (so 2 rows per guess)

5. display
if exact, upper case
else jsut normally print guess elements into 2d array

in next row print ^ where needed

if guess and myserty match, end with viucotry
otherwise repeat 1-5 with new prompt

if fail print failure

executable specs

diffferent congrats based on performance. goated amazing nice nothing
======== lines each time



*/
