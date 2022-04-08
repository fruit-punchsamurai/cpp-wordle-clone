#include "gamemechanics.h"

// static initialization
std::string Game_mec::hidword = "";
int Game_mec::random = 0;
int Game_mec::a = 0;
int Game_mec::status = 0;
int Game_mec::posn[5] = {0};
bool Game_mec::game_started = false;
int Game_mec::no_of_guesses = 0;

// void Game_mec::gethidword(std::string s)
// {
//     a = 1;
//     hidword = s;
// }

void Game_mec::gethidword()
{
    a = 1;
    std::ifstream fptr(PATH_TO_WORDFILE_SELECT);
    randnum(); // function generates random number
    // cout<<random<<endl;
    if (random < 2)
    {
        fptr.seekg((random * 5), std::ios::beg); // places file pointer to 1st word of file if random number=0 and 2nd word if random number =1
    }
    else
    {
        fptr.seekg((random * 5) + (2 * (random - 1)), std::ios::beg); // places file pointer based on random number (eg. if num=4 place in 5th word)
    }
    fptr >> hidword;
    fptr.close();
    Game_mec::game_started = true;
}

std::string Game_mec::puthidword() // use this function to display hiddenword
{
    if (a == 0)
    {
        a = 1;
        gethidword();
    }
    return hidword;
}

void Game_mec::randnum() // generates random number between 0 to 5757 .i.e. no of lines in text file
{
    srand(time(NULL));
    random = (rand() % 1000);
}

bool Game_mec::val_checker(std::string s) // checks if word is valid or not and return 0 if invalid return 1 if valid
{
    std::string q;
    std::ifstream fptr(PATH_TO_WORDFILE);
    while (fptr.peek() != EOF)
    {
        fptr >> q;
        if (s == q)
        {
            fptr.close();
            return true;
        }
    }
    fptr.close();
    return false;
}

bool Game_mec::len_checker(std::string s) // check if length of hidword and entered word match or not return 1 if match if not match return 0
{
    if (hidword.length() != s.length())
    {
        return false;
    }
    return true;
}

void Game_mec::let_checker(std::string s) // check if word is correct or incorrect or correct letter in wrong position

/*
    if status =1 entered guess is correct
    if status =0 entered guess is incorrect
    if status =2 entered guess has some correct letters(position may not be correct)
*/
/*
    posn[0]=1 1st letter; posn[1]=2nd letter and so on
    if posn[x]=0 wrong letter
    if posn[x]=1 right letter in right position
    if posn[x]=2 right letter in wrong position
*/
{
    for (int i = 0; i < hidword.length(); i++)
    {
        posn[i] = 0;
    }
    if (hidword == s)
    {
        status = 1;
        for (int i = 0; i < hidword.length(); i++)
        {
            posn[i] = 1;
        }
    }
    else
    {
        for (int i = 0; i < hidword.length(); i++)
        {
            int y = 0;
            for (int j = 0; j < hidword.length(); j++)
            {

                if (s[i] != hidword[j] && y == 0)
                {
                    posn[i] = 0;
                }
                else if (s[i] == hidword[j])
                {
                    status = 2;
                    if (i == j)
                    {
                        posn[i] = 1;
                        break;
                    }
                    else
                    {
                        posn[i] = 2;
                        y = 1;
                    }
                }
            }
        }
    }
    std::string repeat = s;
    for (int i = 0; i < s.length(); i++)
    {
        for (int j = 0; j < repeat.length(); j++)
        {
            if (i == j)
            {
                continue;
            }
            if (s[i] == repeat[j])
            {
                if (posn[i] == 1 && posn[j] == 2)
                {
                    posn[j] = 0;
                }
                if (posn[i] == 2 && posn[j] == 1)
                {
                    posn[i] = 0;
                }
                if (posn[i] == 2 && posn[j] == 2)
                {
                    if (i < j)
                    {
                        posn[j] = 0;
                    }
                    else if (j < i)
                    {
                        posn[i] = 0;
                    }
                }
            }
        }
    }
}
