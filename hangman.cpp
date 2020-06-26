#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <conio.h>
#include <fstream>
#include <vector>
using namespace std;

const int MAX_TRIES = 5; 

class hangman // class with a name hangman
{
    string name;
    char letter;
    char ans;
    int num_of_wrong_guesses = 0;
    int total_lines = 0;
    string word, line;
    vector<string> lines;

    public: 
        hangman() {}
        string fetch ();
        bool process (string word);
        int letterFill (char, string, string&);



};
   // fetch a random word from the word.txt by file handling, vector array and rand() function.
    string hangman :: fetch()
    {
        srand(time(0));
        ifstream file("word.txt"); 
        while( getline(file, line))
        {
            total_lines++;
            lines.push_back(line);
        }

        int random = rand() % total_lines;
        word = lines[random];

        return word;
    }

    bool hangman :: process(string word)
    {
       string unknown(word.length(), '*');
        system( "cls" );
       	cout << "Hangman! \n\n";
		cout << "Here you need to guess the name of random place. \n";
		cout << "Each letter is represented by a star.\n";
		cout << "Don't include spaces, if space is present in the actual name.\n"; 
		cout << "You have to type only one character for each attempt.\n";
		cout << "You have " << MAX_TRIES << " attempts. The number of attempts decreases for each wrong answer.\n";
		cout << "__________________________________________________________________________________________________________";


        while (num_of_wrong_guesses < MAX_TRIES)
        {
            cout << "\n\n\t" << unknown;
            cout << "\n\nGuess a letter: ";
            cin >> letter;

            if (letterFill(letter, word, unknown)==0)  // function call to check if the letter is present or not in the sceret word.
            {
                cout << endl << "Whoops! Your guess was wrong." <<endl;
                num_of_wrong_guesses++;
            }
            else 
            {
                cout << endl << "You are right!" << endl;
            }

            cout << "You have " <<MAX_TRIES - num_of_wrong_guesses;
            cout << " guesses left. " << endl;

            if (word == unknown)
            {
                cout << endl;
                cout << word << " was correct "<< endl;
                goto choice;

            }
        }

        if (num_of_wrong_guesses == MAX_TRIES)
        {
            cout << "\nSorry, you lost... you've been hanged." << endl;
            cout << "The word was :" << word << endl;
            goto choice;
        }

        cin.ignore();
        cin.get();

        // check if player wants to play the game again.
        choice:
            cout << "\n Would you like to play again?[y/n]\n";
            cin  >> ans;
            if (ans == 'y' || ans == 'Y')
                return true;

            else if ( ans == 'n' || ans == 'N')
                return false;

    }
    
    // function to check if the guessed letter is present or not, if present corresponding position in guessword or unknown is assigned with the character.
    int hangman :: letterFill (char guess, string secretword, string &guessword)
        {	
            int i;
            int matches = 0;
            int len = secretword.length();
            for (i = 0; i< len; i++)
            {
                
                if (guess == guessword[i])
                    return 0;
                
                if (guess == secretword[i])
                {
                    guessword[i] = guess;
                    matches++;
                }
            }
            return matches;
        }

int main()
{
 system( "cls" );
 repeat:hangman O; 
        string word;
        bool check;
        word = O.fetch();
        check = O.process(word);
        if (check)          // if player wants to play again then repeat.
            goto repeat;
        else 
            exit(0);

}