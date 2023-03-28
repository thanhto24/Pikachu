#pragma once
#pragma pack(1)
#include "player.h"
#include "play.h"

#define NAMESIZE 50
#define PASSSIZE 50
#define BOARDSIZE 999
#define URLSIZE 100

struct State
{                                  
    int p, q;                      
    int p_, q_;                    
    char board[BOARDSIZE];         
    char file_background[URLSIZE]; 
};

struct Date
{
    int dd, mm, yy;
};

struct Record
{
    Date date;    // Date of completed record
    int points; // points achieved
};

struct savefile
{
    char mask;               // You are required to transfer all char-type variables by performing xor each with
    char name[NAMESIZE];     // username
    char password[PASSSIZE]; // password
    Record record[5]; // List of sorted best records
    State state[5];   // List of save state
};

void updateFile(Player player);

bool getSaveFile(Player &player)
{
    savefile tmp;
    ifstream fin;
    fin.open("account\\template.bin", ios::in | ios:: binary);

    if(!fin.is_open())
        return false;

    while(!fin.eof())
    {
        fin.read((char *) &tmp, sizeof(tmp));
        if(fin.eof())
            break;
        for(int i = 0; i < strlen(tmp.name); i++)
            tmp.name[i] = tmp.name[i] ^ tmp.mask;

        for(int i = 0; i < strlen(tmp.password); i++)
            tmp.password[i] = tmp.password[i] ^ tmp.mask;

        if(strcmp(tmp.name,player.username) == 0 && strcmp(tmp.password,player.password) == 0)
        {
            for(int i = 0; i < 5; i++)
            {
                if(tmp.record[i].points == 0)
                    break;
                player.level = i+1;
                player.maxScore = max(tmp.record[i].points, player.maxScore);
            }
            fin.close();
            updateFile(player);
            return true;
        }
    }
    fin.close();
    return false;
}