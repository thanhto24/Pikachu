#pragma once
#include "header.h"

void makePic(int hei, int wid, int n, int m, char pic[200][200],int num)
{
    for (int i = 0; i <= n * hei - (n - 2); i++)
    {
        for (int j = 0; j <= m * wid - (m - 2); j++)
        {
            pic[i][j] = ' ';
        }
    }
    string picName = "picture\\pic";
    picName += num + '0';
    picName += ".txt";
    ifstream fin;
    fin.open(picName.c_str());
    int dem = 0;
    string S;
    while(!fin.eof())
    {
        getline(fin,S);
        for(int i = 0; i < S.size(); i++)
            pic[dem][i] = S[i];
        dem++;
    }
    fin.close();
}