#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

#define PATH_TO_WORDFILE "../../dictionary/5lettersword.txt"
#define PATH_TO_WORDFILE_SELECT "../../dictionary/words_alpha.txt"

class Game_mec
{

public:
    static std::string hidword;
    static bool game_started;
    static int no_of_guesses;
    static int random;
    static int a;
    static int status;
    static int posn[5];
    static void gethidword(std::string s); // for 2-player

    static void gethidword();        // For 1-player
    static std::string puthidword(); // use this function to display hiddenword

    static void randnum(); // generates random number between 0 to 15917

    static bool val_checker(std::string s); // checks if word is valid or not and return 0 if invalid return 1 if valid

    static bool len_checker(std::string s); // check if length of hidword and entered word match or not return 1 if match if not match return 0

    static void let_checker(std::string s); // check if word is correct or incorrect or correct letter in wrong position

    /*
        if status =1 entered guess is correct
        if status =0 entered guess is incorrect
        if status =2 entered guess has some correct letters(position may not be correct)
    */
    /*
        posn[0]=1st letter; posn[1]=2nd letter and so on
        if posn[x]=0 wrong letter
        if posn[x]=1 right letter in right position
        if posn[x]=2 right letter in wrong position
    */
};