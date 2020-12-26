/*WORD GUESSING GAME
                    In this game, the user has to guess a word in limited number of tries.
                    The number of tries depends on the difficulty level of the round.
                    The difficulty level and associated number of tries are:
                    Hard:   3 tries
                    Medium: 6 tries
                    Easy:   10 tries
                    User can also keep track of the number of rounds won and lost*/

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <iomanip>
#include <conio.h>
#include <cstdlib>

using namespace std;

//Forward Declaration of functions
string randomWord();                     //Defined on line 196
void diff_info(int tries, string level); //Defined on line 216
int chooseDifficultyLevel();             //Defined on line 147
string hint(string word);                //Defined on line 226
bool playAnotherRound();                 //Defined on line 278
int findLength(string word);             //Defined on line 314
/*.......................................*/

//Main Function
int main()
{
    int rounds_won = 0;
    int rounds_lost = 0;
    bool play_another_game = true;

    //Keep running this loop untill the user hits n or N
    while (play_another_game)
    {
        play_another_game = false;
        string rand_word = randomWord();              //Generates a random word and stores it in a variable. Defined on line 196
        int rand_word_length = findLength(rand_word); //Function of finding legth of string. Defined on line 314
        string secret_word(rand_word_length, '*');    //Prints * rand_word_length times

        /*UI formatting*/
        cout << "\n\n\t------------------------------------------------------------------------------------------------------\n"
             << endl;
        cout << setw(70) << "Welcome to Word Guessing Game" << endl;
        cout << setw(67) << "Let's guess some words!" << endl;
        cout << "\n\t------------------------------------------------------------------------------------------------------\n"
             << endl;
        cout << "\n\n";
        /*****************************************/

        const int TRIES = chooseDifficultyLevel(); //Difficulty level is associated with the number of tries. Function defined on line 147
        int count = 0;                             //Holds the current count of attempts made
        string hint_word = hint(rand_word);        //Passing the random word generated to the hint fuction to produce a hint. Function defined on line 226
        char char_input;                           //Holds user's current input character

        while (count < TRIES)
        {
            //UI Formatting
            cout << "\t------------------------------------------------------------------------------------------------------\n"
                 << endl;
            cout << "\t\t\t" << secret_word << "\t\tHINT:(" << hint_word << ")"
                 << "\t\tTries Left: " << TRIES - count << endl;
            cout << "\t\t\tEnter a character: ";
            cin >> char_input;
            cout << "\n\t------------------------------------------------------------------------------------------------------" << endl;
            /**************************************************/

            //The code below checks if the entered character is correct, incorrect or repeated
            bool prev_entered = false;
            int matched = 0;
            for (int i = 0; i < rand_word_length; i++)
            {
                if (char_input == secret_word[i])
                {
                    prev_entered = true;
                    continue;
                }

                if (char_input == rand_word[i])
                {
                    secret_word[i] = char_input;
                    matched++;
                }
            }

            //Informs the user about the input whether it is correct, incorrect or repeated
            if (matched > 0)
            {
                cout << "\n\t\t\tGreat!!! Correct guess.\n"
                     << endl;
                cout << "\n\t\t\tMatched characters: " << matched << endl;
            }
            else if (matched == 0 && prev_entered != true)
            {
                cout << "\n\t\t\tOops!!! Incorrect guess.\n"
                     << endl;
                count++;
            }
            else if (prev_entered == true)
            {
                cout << "\n\t\t\tYou already entered that character once.\n"
                     << endl;
            }

            /********************************************************/

            //Condition for winning the round
            if (rand_word == secret_word)
            {
                cout << setw(70) << "\t\t\tCongratulations! You guessed the word correctly." << endl;
                break;
            }
            /******************************************************/
        }

        /*Checks if the round is lost or won
        If round is won, overall score increases by 1 and vice versa*/
        if (rand_word != secret_word)
        {
            rounds_lost++;
        }
        else
        {
            rounds_won++;
        }
        /************************************************************/

        //UI formatting
        cout << "\t\t\t";
        cout << "\n\n";
        cout << "\t------------------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\tRounds Won: " << rounds_won << "\t\t\tRounds lost: " << rounds_lost << endl;
        cout << "\t------------------------------------------------------------------------------------------------------" << endl;
        cout << "\n\n";
        /*******************************/

        //Asks the user for another game
        play_another_game = playAnotherRound(); //Defined on line 278
        /*******************************/
    }

    system("pause"); //This line of code might not work on a MAC
    return 0;
}
/*..................................................................................*/

//Allows the user to chose a difficuty level for the game
int chooseDifficultyLevel()
{
    int diff_level = 0;
    int tries = 0;

    cout << "\t\t\tChoose difficulty level..." << endl;
    cout << "\t\t\t1) Easy \t2) Medium \t3) Hard" << endl;
    cout << "\t\t\t";

    do
    {
        cout << "\t\t\t";
        cin >> diff_level;
        if (!cin.fail())
        {
            switch (diff_level)
            {
            case 1:
                tries = 10;
                diff_info(tries, "easy"); //Displays difficulty level info. Defined on line 216
                break;
            case 2:
                tries = 6;
                diff_info(tries, "medium"); //Displays difficulty level info. Defined on line 216
                break;
            case 3:
                tries = 3;
                diff_info(tries, "hard"); //Displays difficulty level info. Defined on line 216
                break;
            default:
                break;
            }
        }
        else
        { //if cin fails, then prompt the user and clear the input stream
            cout << "\t\t\tInvalid input...Try again entering only 1, 2 or 3 respectively.\n"
                 << endl;
            cin.clear();
            cin.ignore();
            diff_level = 0;
        }

    } while (diff_level < 1 || diff_level > 3); //Keep the loop running untill diff_level is not equal to 1,2 or 3

    return tries;
}
/*.............................................................................................*/

//Returns a random word from a list of words
string randomWord()
{
    string arrayOfWords[10] = {
        "elephant",
        "basketball",
        "mouse",
        "keyboard",
        "hello",
        "camera",
        "pencil",
        "electricity",
        "register",
        "language"};

    srand(time(0));
    return arrayOfWords[(rand() % 10)];
}
/*..............................................................................................*/

//Gives details about a particuar level. Function written mainly to avoid the repitation of code
void diff_info(int tries, string level)
{
    cout << "\n\n\t------------------------------------------------------------------------------------------------------\n"
         << endl;
    cout << "\t\t\tYou choose to play the game in " << level << " mode." << endl;
    cout << "\t\t\tYou have a total of " << tries << " tries to guess the word." << endl;
    cout << "\n\t------------------------------------------------------------------------------------------------------" << endl;
}
/*...............................................................................................*/

//Hides some of the words in a string. Returns a word that serves as a hint for the user
string hint(string word)
{
    srand(time(0));          //Seeds time to the current time
    string return_hint = ""; //this string will be returned
    char word_arr[50];       //For holding string in array form

    int len = findLength(word); //Finds length of a string. Defined in line 314

    //Converts string into c style string
    for (int i = 0; i < len; i++)
    {
        word_arr[i] = word[i];
    }
    /************************************/

    int current_index = 0, prev_index = 100; /*Stores the random indexes generated.
                                               prev_index set to 100 so that current index and prev_index are not equal for the first time*/
    int chars_to_hide = (len / 2);           //Stores the number of characters to hide

    //If length of string is odd, add 1 to the number 0f characters to hide
    if (len % 2 == 1)
    {
        chars_to_hide++;
    }
    /*************************************/

    //Loop that generate random indexes and hides characters in an array at that index
    for (int i = 0; i < chars_to_hide; i++)
    {
        current_index = rand() % len;
        if (current_index == prev_index)
        {
            do
            {
                current_index = rand() % (len);
            } while (word_arr[current_index] == '_' || word_arr[current_index] == NULL);
        }
        word_arr[current_index] = '_';
        prev_index = current_index;
    }

    //Converting back into string
    for (int i = 0; i < len; i++)
    {
        return_hint = return_hint + word_arr[i];
    }
    /************************************/
    return return_hint;
}

/*...........................................................................*/

//Asks the user for another rounds
bool playAnotherRound()
{
    bool play_another_game;
    char yes_or_no;

    cout << "\t\t\tPlay another round?" << endl;
    cout << "\t\t\tEnter y for yes or n for no: ";

    //The loop will keep running until the user enters y,Y,n or N
    while (true)
    {
        cin >> yes_or_no;
        if (yes_or_no == 'y' || yes_or_no == 'Y')
        { //if input is valid, break the loop
            play_another_game = true;
            break;
        }
        else if (yes_or_no == 'n' || yes_or_no == 'N')
        { //if input is valid, break the loop
            play_another_game = false;
            break;
        }
        else
        { //if input is invalid, run the loop again
            cout << "Invalid input. Try again entering y or n" << endl;
            continue;
        }
    }
    /*************************************************/

    return play_another_game;
}
/*..............................................................*/

//Function that finds length of a string
int findLength(string word)
{
    int i, count = 0;
    for (i = 0; word[i]; i++)
    {
        count++;
    }
    return count;
}
/**************************************************************/