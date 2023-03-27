#pragma once
#include "header.h"
#include "init.h"
#include "makePicture.h"
#include "display.h"
#include "boardSetting.h"
#include "logicGame.h"
#include "checkMove.h"
#include "slide.h"
#include "play.h"
#include "player.h"
#include "menu.h"

void makeLevel(int hei, int wid, int n, int m, int choosenLevel, Player player)
{
    char C[200][200], a[200][200];
    bool ate[200][200];
    bool movingOn[200][200], selected[200][200];
    char view[200][200], pic[200][200], cpy[200][200];
    system("cls");
    init(hei, wid, n, m, C, view);
    makePic(hei,wid,n, m, pic, 1);
    process(hei, wid, n, m, C, view, pic, ate, movingOn, selected, cpy, player, choosenLevel);
}

void choiceLevel(Player player)
{
    system("cls");

    string levelName[6];

    levelName[0] = "    EASY MODE";
    levelName[1] = "    MEDIUM MODE";
    levelName[2] = "    HARD MODE";
    levelName[3] = "    EXTREME HARD MODE";
    levelName[4] = "    CUSTOM MODE";
    levelName[5] = "    BACK TO MENU";

    int x = 0, tmp = -1;

    levelName[x][0] = '>';

    for (int i = 0; i < 6; i++)
    {
        if (i + 1 > player.level)
            TextColor(4);
        if (i >= 4)
            TextColor(7);
        cout << levelName[i] << endl;
        TextColor(7);
    }

    levelName[x][0] = ' ';
    cout << endl;

    while (1)
    {

        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            gotoxy(0, 0);

            char key = getch(); // Lấy ký tự người dùng vừa bấm

            if (toupper(key) == 'W' || key == 72) // Di chuyển trái
            {
                x--;
                if (x < 0)
                    x = 5;
            }
            if (toupper(key) == 'S' || key == 80) // Di chuyển phải
            {
                x++;
                if (x > 5)
                    x = 0;
            }

            if (key == 13)
            {
                if (x == 5)
                {
                    system("cls");
                    displayMenu(x, x);
                    exit(0);
                }
                if (x == 4)
                    while (true)
                    {
                        system("cls");
                        cout << "Input heigth and width: ";
                        int h, w;
                        cin >> h >> w;
                        if (h > 20 || w > 20)
                            cout << "Data error, please input heigth and width smaller than 20\n";
                        else if (h <= 0 || w <= 0)
                            cout << "Data error, please input heigth and width greater than 0\n";
                        else
                        {
                            if (h & 1 || w & 1)
                            {
                                cout << "Data error, input must be even numbers\nSo we change " << h << " x " << w << " to ";
                                if (h & 1)
                                    h++;
                                h = min(h, 20);
                                if (w & 1)
                                    w++;
                                w = min(w, 20);
                                TextColor(4);
                                cout << h;
                                TextColor(7);
                                cout << " x ";
                                TextColor(4);
                                cout << w << endl;
                                TextColor(7);
                            }

                            TextColor(6);
                            cout <<  "Custom game successfully!";
                            cout << "\nPress any key to continue\n";
                            TextColor(7);

                            char ch;
                            ch = _getch();
                            if(h>19)
                                makeLevel(3, 9, h, w, x + 1, player);
                            else
                                makeLevel(5, 11, h, w, x + 1, player);
                            return;
                        }
                        Sleep(3000);
                    }

                if (x + 1 > player.level)
                    continue;

                if (x == 0)
                    // makeLevel(5, 11, 2, 2, x + 1, player); // Turn on to cheat
                    makeLevel(5, 11, 4, 4, x + 1, player);
                if (x == 1)
                    // makeLevel(5, 11, 2, 2, x + 1, player);
                    makeLevel(5, 11, 6, 8, x + 1, player);
                if (x == 2)
                    // makeLevel(5, 11, 2, 2, x + 1, player);
                    makeLevel(5, 11, 8, 14, x + 1, player);
                if (x == 3)
                    // makeLevel(5, 11, 2, 2, x + 1, player);
                    makeLevel(3, 9, 20, 20, x + 1, player);

                return;
            }
            levelName[x][0] = '>';
            for (int i = 0; i < 6; i++)
            {
                if (i + 1 > player.level)
                    TextColor(4);
                if (i == 4)
                    TextColor(7);
                if(i==5)
                    TextColor(6);
                cout << levelName[i] << endl;
                TextColor(7);
            }
            levelName[x][0] = ' ';
            cout << endl;
        }
    }
}