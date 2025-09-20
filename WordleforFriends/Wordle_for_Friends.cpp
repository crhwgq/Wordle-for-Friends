// Programmer: Caitlin Hayes
// Date: 2/27/2023
// File: Wordle_for_Friends.cpp
// Assignment: HW4
// Purpose: To let two users play a game where one user has to guess the
// word set by the other user.

#include <iostream>
#include <string>
#include <ctype.h>
#include <limits>
using namespace std;

// Desc: This function is used to output a greeting to the user
// Pre: None
// Post: The greeting is printed out to the console (nothing is returned)
void greet();

// Desc: This function is used to determine if an input meets the requirements // of the program
// Pre: Argument must be a uppercase string
// Post: A valid string will be returned
string validateWord(string &input);

// Desc: This function is used to give the user feedback on their guess
// Pre: The arguments must be valid, uppercase strings
// Post: The feedback will be printed to the console (nothing is returned)
void displayFeedback(string key, string guess);

// Desc: This function is used to display the summary of the game to the users
// Pre: The first two arguments must be strings and the last two arguments 
// must be integers
// Post: The game summary will be printed to the console (nothing is returned)
void printGameSummary(string player1, string player2, int initFriendLevel, int newFriendLevel);

// Desc: This function is used to validate the input for the friendship level
// Pre: The argument must be an integer
// Post: A valid friendship level will be returned
int validateFriendshipLevel(int &friendshipLevel);

// Desc: This function is used to calculate the new friendship level
// Pre: The first argument must be a valid friendship level, and both 
// arguments must be integers
// Post: A new, valid friendship level will be returned
int calcFriendshipLevel(int initial, int numAttempts);

int main() 
{
  // Initializing all the necessary variables
  string player1Name; // Stores player 1's name
  string player2Name; // Stores player 2's name
  string word;        // Stores the word to be guessed
  string guess;       // Stores the guess made by player 2

  char keepPlaying = 'y'; // Stores player 1's decision to continue the game
  
  int numRounds = 1;   // Stores the number of rounds played
  int initFriendshipLevel; // Stores the initial friendship level
  int newFriendshipLevel;  // Stores the friendship level after a round
  //-----------------------------------------------------------------------

  greet(); // Call to the greet function

  // Statements prompting player 1 for a name, storing the value, and greeting the user by name
  cout << "\nPlayer 1, please enter your name:" << endl;
  getline(cin, player1Name);
  cout << "\nWelcome, " << player1Name << "!" << endl;

  // Statements prompting player 2 for a name, storing the value, and greeting the user by name
  cout << "\nPlayer 2, please enter your name:" << endl;
  getline(cin, player2Name);
  cout << "\nWelcome, " << player2Name << "!\n\n" << endl;
  //-----------------------------------------------------------------------
  
  // Statements prompting player 1 for the friendship level they have with player 2 and storing it
  cout << player1Name << ", please rate the friendship level you have with " << player2Name << " (enter an integer value in [0, 100]):" << endl;
  cin >> initFriendshipLevel;
  
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  // Calling the validateFriendshipLevel function to validate the input
  initFriendshipLevel = validateFriendshipLevel(initFriendshipLevel);
  //-----------------------------------------------------------------------

  // Loop that will keep the game going if the users choose to do so
  while (keepPlaying == 'y') 
  {
    int numAttempts = 1; // Stores the number of guesses made
    bool guessing = 1;   // Helps determine if player 2 is still guessing

    // Statements prompting player 1 for a word and storing it
    cout << "\nNow " << player1Name << ", please enter a word for " << player2Name << " to guess [it has to be a valid five-letter word all UPPERCASE]:" << endl;
    cin >> word;

    // Calling the validateWord function to validate the word player 1 provided
    word = validateWord(word);
    
    // Statement letting the players know that a valid word has been set
    cout << "\nGot it! The word has been saved." << endl; 

    // Statement letting the player know the game is beginning and informing the number of attempts
    cout << "\nGet ready, " << player2Name << "! It’s now time to Wordle with " << player1Name << "! You will have a total of 6 attempts to guess the word correctly." << endl;
    //-----------------------------------------------------------------------

    // Loop that keeps the game going until word is guessed or all attempts are used
    while (guessing == 1) 
    {
      // Statement prompting player 2 for a guess and storing it
      cout << "\nThis is attempt #" << numAttempts << ", " << player2Name << ", please enter a valid five-letter word (all UPPERCASE):" << endl;
      cin >> guess;

      // Calling the validateWord function to validate player 2's guess
      guess = validateWord(guess);
      displayFeedback(word, guess); // Call to the displayFeedback function to let player 2 see the feedback for their guess

      if (guess == word) // Case that the word is guessed
      {
        // Calling the calcFriendshipLevel function to get correct friendship level
        newFriendshipLevel = calcFriendshipLevel(initFriendshipLevel, numAttempts);

        // Calling the printGameSummary function to output round summary
        printGameSummary(player1Name, player2Name, initFriendshipLevel, newFriendshipLevel);
        guessing = 0;
      } 
      else if (numAttempts == 6) // Case that player 2 uses all the attempts
      {
        cout << "\nI'm sorry, '" << guess << "' is incorrect. The word was '" << word << "', better luck next time!" << endl;

        // Calling the calcFriendshipLevel function to get correct friendship level
        newFriendshipLevel = calcFriendshipLevel(initFriendshipLevel, numAttempts);

        // Calling the printGameSummary function to output round summary
        printGameSummary(player1Name, player2Name, initFriendshipLevel, newFriendshipLevel);
        guessing = 0;
      } 
      else // Case that the word is not guessed nor are all the attempts used
      {
        numAttempts += 1;
      }
    }

    // Statements prompting player 1 to continue the game with player 2 and storing the decision
    cout << "\n" << player1Name << ", would you like to play another round with " << player2Name << "? (y/n):" << endl;
    cin >> keepPlaying;

    if (keepPlaying == 'y') // Case to keep playing with the same player 2
    {
      cout << "\nWonderful, get ready for another round, " << player2Name << "!" << endl;
      numRounds += 1;
      initFriendshipLevel = newFriendshipLevel;
    } 
    else // Case to not play another round with player 2
    {
      // Statement summarizing the round
      cout << "\nAlright. " << player1Name << ", your friendship level with " << player2Name << " is " << newFriendshipLevel << " after " << numRounds << " round(s) of Wordle for Friends." << endl;
      
      // Farewell to player 2
      cout << "\nGoodbye " << player2Name << "! Until next time!" << endl; 

      // Statement prompting player 1 to decide to continue and storing it
      cout << "\n" << player1Name << ", would you like to start a new game with another friend? (y/n):" << endl;
      cin >> keepPlaying;

      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      if (keepPlaying == 'y') // Case to play with a different player 2
      {
        cout << "\nWonderful!" << endl;
        numRounds = 1;

        // Statements prompting player 2 for their name and storing it
        cout << "\nPlayer 2, please enter your name:" << endl;
        getline(cin, player2Name);
        cout << "\nWelcome, " << player2Name << "!\n" << endl;
        
        // Statements prompting player 1 for the frienship level with player 2 and storing it
        cout << player1Name << ", please rate the friendship level you have with " << player2Name << " (enter an integer value in [0, 100]):" << endl;
        cin >> initFriendshipLevel;
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        // Calling the validateFriendshipLevel function to validate input
        initFriendshipLevel = validateFriendshipLevel(initFriendshipLevel);
      } 
      else // Case to not continue the game at all
      {
        cout << "\nAlright, goodbye " << player1Name << "! Until next time!" << endl;
      }
    }
  }
  return 0;
}
//-----------------------------------------------------------------------

void greet()
{
  cout << "\nWelcome to Wordle for Friends!\n" << endl; // Greeting
  return;
}
//-----------------------------------------------------------------------

string validateWord(string &input) 
{
  bool isValid = 0; // Stores if the input is valid or not
  int validChars = 0; //  Stores the number of valid characters in the input

  while (isValid == 0) 
  {
    // Loop that prompts for a different input if previous input was not 5 characters long
    while ((input.length() < 5) || (input.length() > 5)) 
    {
      cout << "\nThe word you have entered is not 5 letters long." << endl;
      cout << "Please enter another word (UPPERCASE and 5 letters long):"
           << endl;
      cin >> input;
    }
    
    // Loop that checks the validity of the characters
    for (int i = 0; i < 5; i++) 
    {
      char c = input[i];
      if (isalpha(c)) 
      {
        validChars += 1;
      }
    }
    
    // Case that there are non alphabetic characters in input
    if (validChars < 5) 
    {
      cout << "\nThe word you have entered contains non-alphabetic characters." << endl;
      cout << "Please enter another word (UPPERCASE and 5 letters long):" << endl;
      cin >> input;
    } 
    else // Case that the input is completely valid
    {
      isValid = 1;
    }
  }
  return input;
}
//-----------------------------------------------------------------------

void displayFeedback(string key, string guess) 
{
  int nonMatch = 0; // Stores the number of characters that are not a match

  if (guess == key) // Case that player 2 guesses the key
  {
    cout << "\nYou entered '" << guess << "'. Congratulations, you guessed it! The word was '" << key << "'!" << endl;
  } 
  else // Case that the guess is incorrect
  {
    cout << "\nYou entered '" << guess << "'. Nice try, keep going!" << endl;
    
    // Loop that compares each character in the guess and key
    for (int i = 0; i < 5; i++) 
    {
      char guessC = guess[i];
      char keyC = key[i];

      if (guessC == keyC) // Case that the characters match
      {
        cout << guessC << ": ^o^" << endl;
      } 
      else // Case that the characters do not match
      {
        nonMatch = 0;
        
        // Loop that compares a character in guess to each of the key characters
        for (int k = 0; k < 5; k++) 
        {
          char keyChar = key[k];
          
          if (guessC == keyChar) // Case that the character in guess is in the key
          {
            cout << guessC << ": ^-^" << endl;
            break;
          } 
          else // Case that the character in guess does not match a character of key
          {
            nonMatch += 1;
          }
        }
        
        // Case that the character in guess does not match any of the characters in key
        if (nonMatch == 5) 
        {
          cout << guessC << ": @.@" << endl;
        }
      }
    }
  }
  return;
}
//-----------------------------------------------------------------------

void printGameSummary(string player1, string player2, int initFriendshipLevel, int newFriendshipLevel) 
{
  // Summary with the player names and frienship level evolution
  cout << "\nEnd-of-Round Summary" << endl;
  cout << "\tPlayer 1: " << player1 << endl;
  cout << "\tPlayer 2: " << player2 << endl;
  cout << "\tFriendship Level: " << initFriendshipLevel << " -> " << newFriendshipLevel << endl;
  return;
}
//------------------------------------------------------------------------

int validateFriendshipLevel(int &friendshipLevel)
{
  // Case that the friendship level given is valid
  if (0 <= friendshipLevel && friendshipLevel <= 100)
  {
    cout << "\nHooray! That’s an admirable friendship between you two!" << endl;
  } 
  else // Case that the friendship level given is not valid
  {
    while (!(0 <= friendshipLevel && friendshipLevel <= 100)) 
    {
      cout << "\nThe friendship level you input is invalid!" << endl;
      cout << "Please enter the friendship level again (an integer value in [0, 100]):" << endl;
      cin >> friendshipLevel;
    }
    cout << "\nHooray! That’s an admirable friendship between you two!" << endl;
  }
  return friendshipLevel;
}
//------------------------------------------------------------------------

int calcFriendshipLevel(int initial, int numAttempts)
{
  int newFriendshipLevel; // Stores the new friendship level after calculations
  
  if (initial == 100) // Case that the initial level is 100
  {
    newFriendshipLevel = 100;
  } 
  // Case that the initial level is not 100 and the calculation is over 100
  else if ((initial + numAttempts) > 100) 
  {
    numAttempts += (100 - (initial + numAttempts));
    newFriendshipLevel = initial + numAttempts;
  } 
  else // Case that the level is not 100 nor is the calculation over 100
  {
    newFriendshipLevel = initial + numAttempts;
  }
  return newFriendshipLevel;
}