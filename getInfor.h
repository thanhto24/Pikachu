#pragma once
#include "header.h"
#include "player.h"

void getInfor(vector <Player> &listPlayer)
{
    listPlayer.clear();
    Player tmp;
    ifstream fin;
    fin.open("account\\account.dat", ios::in | ios::binary);
    while(fin.read((char *) &(tmp), sizeof(Player)))
    {
        listPlayer.push_back(tmp);
    }
    fin.close();
}