#pragma once
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#include <fstream>
#define ppc(a,n,m) a = new char * [n]; for(int i = 0; i < n; i++) a[i] = new char [m]
#define ppb(a,n,m) a = new bool * [n]; for(int i = 0; i < n; i++) a[i] = new bool [m]
#define ii pair<int, int>
#define f first
#define s second 
#define mp make_pair

// SOUNDTRACK
#define MOVE_SOUND 0
#define ENTER_SOUND 1
#define ERROR_SOUND 2
#define WIN_SOUND 4
#define BACKGROUND_SOUND 5
#define EFFECT_SOUND 6

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

// void playSound(int i)
// {
//     const wchar_t *soundFile = {L"move.wav", L"enter.wav", L"error.wav", L"placed.wav", L"win.wav",  L"background.wav", L"effect.wav" };
// 	PlaySound(soundFile[i], NULL, SND_FILENAME | SND_ASYNC);
// }