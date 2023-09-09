//library for printing strings, integers, characters on the output screen...(for basics)
#include <stdio.h>
//library for general purpose (functions involving memory allocation, process control, conversions...)
#include <stdlib.h>
//library for characters-string
#include <string.h>
//library for random number
#include <time.h>
//library for funtions "islower()" and "isalpha()" that are useful for testing and mapping characters
#include <ctype.h>

//Possible words to choose from
//Mutable pointer to an immutable string/character
//The const keyword makes a string/character immutable, meaning its content is read-only
//Source-idea: https://www.geeksforgeeks.org/program-generate-random-alphabets/
const char* sRandom[] = {
  "americano",
  "espresso",
  "cortado",
  "affogato",
  "latte",
  "cappuccino",
  "macchiato",
  "mocha",
  "ristretto"
};

void showRules(){ //print rules and info
  printf("\n\t HANGMAN GAME");
  printf("\n\t Be aware a man can be hanged!");
  printf("\n\n\t Rules and information: ");
  printf("\n\t - Guess the word and save the man.");
  printf("\n\t - Maximum 6 mistakes are possible.");
  printf("\n\t - Enter letters ONLY in lower case.");
  printf("\n\t - Words are choosen randomly.");
  printf("\n\t - Hint: words are names of coffee drinks.\n");
  printf("\n\t - Good luck! :)\n");

  /*I will ask the user to enter only lower case letters
  because all the words are in lower case and don't need to be written with upper.
  The task for user is to guess a word, not casing of letters*/
}

/*Function is to print the body of the hangman. 
The body is drawn based on the number of wrong guesses made by the player. 
If the number of wrong guesses is greater than 0, the head of the hangman is printed. 
If it is greater than 1, the torso is printed, and so on. This continues until the number
of wrong guesses is greater than 5, at which point the hangman is fully drawn. 
The function takes in an integer called dWrongGuess which represents the number of wrong guesses 
made by the player and prints the hangman accordingly.*/
void printMan(short dWrongGuess) { //print the body of man
   if (dWrongGuess > 0) { //could also be done with switch
      printf("\n  ________\n");
    }
    if (dWrongGuess > 1) {
      printf("  |      |\n");
    }
    if (dWrongGuess > 2) {
      printf("  |    ('_')\n");
    }
    if (dWrongGuess > 3) {
      printf("  |     /|\\ \n");
    }
    if (dWrongGuess > 4) {
      printf("  |     / \\ \n");
    }
    if (dWrongGuess > 5) {
      printf("  | \n");
    }
    if (dWrongGuess > 6) {
      printf("  |__________ \n");
    }
}
short checkGuess(char cGuess, const char* sWord, char* sCurWord, short dWordLength) {
  short dRight = 0;
  //For loop goes throught all the characters and checks if there are matches
  for (int i = 0; i < dWordLength; i++) {
    if (sWord[i] == cGuess) {
      sCurWord[i] = cGuess; //changes "_" of word with matched character
      dRight = 1;
    }
  }
  return dRight;
}

int main() {
  //Add the random number generator
  srand(time(NULL));

  //Program chooses a random word from the array
  //Mutable pointer to an immutable string/character
  const char* sWord = sRandom[rand() % 10]; //there is 10 words to choose from
  short dWordLength = strlen(sWord);

  //Create an array to store the current state of the word
  char sCurWord[dWordLength + 1];
  for (int i = 0; i < dWordLength; i++) {
      sCurWord[i] = '_';
  }
  sCurWord[dWordLength] = '\0';
  
  //Print the rules of game and information for the user
  showRules();

  //Initialize the number of incorrect guesses
  short dWrongGuess = 0;

  //Continue the game until the player has won or lost
  while (dWrongGuess < 8 ) {
    //Print the current word
    printf("\nCurrent word: %s\n", sCurWord);

    //Print the hangman with respect to amount of wrong answers
    printMan(dWrongGuess);

    //Check if the user is a winner
    short dVictory = 1;
    for (int i = 0; i < dWordLength; i++) {//For loop checks if there are any characters that are not filled 
      if (sCurWord[i] == '_') {
        dVictory = 0;
        break;
      }
    }
    //Print a message if the user won
    if (dVictory) {
      printf("\nGAME IS OVER!\nCongratulations!\nYou won!\n \n");
      printf("  ('o')     thank you!\n");
      printf("   _|_ \n");
      printf("   / \\ \n \n");
      break;
    }
    //Print a message if the user lost
    if (dWrongGuess == 7) {
        printf("\nGAME IS OVER!\nYou lost! The word: %s\n \n", sWord);
        break;
    }

    //Ask for input from the user
    //Declare a variable for user's input
    char cGuess;
    while (dWrongGuess < 7) { //until the amount of mistakes is not 7
    printf("\nEnter a letter: ");
    scanf(" %c", &cGuess);

    //Check the input
    if (isalpha(cGuess)) { //isalfa checks if the input is a character
        if (islower(cGuess)) {//islower() checks if the character is in lower case
            //character is in lower case
            break;
        }
        else {
          //ask the user to insert lowercase letters until the user enters it
          printf("Please, insert a lowercase character.\n");
        }
    }
    else {
        //ask the user to insert character until the user enters it
        printf("Please, insert a character\n");
    }
    }//endOfWhile

    //Check if the guess fits and get value for dRight
    short dRight=checkGuess(cGuess, sWord, sCurWord, dWordLength);

    //Update the number of wrong guesses
    if (!dRight) {
      dWrongGuess++;
    }
  }//endOfWhile
  return 0;
}//endOfMain

//done by Kristina Piiarska
