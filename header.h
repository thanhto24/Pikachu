#pragma once
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#define ppc(a,n,m) a = new char * [n]; for(int i = 0; i < n; i++) a[i] = new char [m]
#define ppb(a,n,m) a = new bool * [n]; for(int i = 0; i < n; i++) a[i] = new bool [m]
#define ii pair<int, int>
#define f first
#define s second 
#define mp make_pair
// #define hei 5
// #define wid 11

using namespace std;

void gotoxy(int x, int y) 
{ 
    COORD coord;
    coord.X = x; 
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void TextColor(int x) // X là mã màu
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}