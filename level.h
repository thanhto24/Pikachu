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

void makeLevel(int n, int m,Player player)
{
    char C[200][200], a[200][200];
    bool ate[200][200];
    bool movingOn[200][200], selected[200][200];
    char view[200][200], pic[200][200], cpy[200][200];
    system("cls");
    init(n, m, C, view);
    makePic(n, m, pic, 1);
    process(n, m, C, view, pic, ate, movingOn, selected, cpy, player);
}

void choiceLevel(Player player)
{
    system("cls");

    string levelName[5];

    levelName[0] = "    EASY MODE";
    levelName[1] = "    NORMAL MODE";
    levelName[2] = "    MEDIUM MODE";
    levelName[3] = "    HARD MODE";
    levelName[4] = "    CUSTOM MODE";

    int x = 0;

    levelName[x][0] = '>';

    for (int i = 0; i < 5; i++)
    {
        if (i > player.level + 1 && i != 4)
            TextColor(4);
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
                    x = 4;
            }
            if (toupper(key) == 'S' || key == 80) // Di chuyển phải
            {
                x++;
                if (x > 4)
                    x = 0;
            }

            if (key == 13)
            {
                if(x==4)
                while (true)
                {
                    Sleep(5000);
                    system("cls");
                    cout << "Input heigth and width: ";
                    int h, w;
                    cin >> h >> w;
                    if (h > 20 || w > 20)
                        cout << "Data error, please input heigth and width smaller than 20";
                    else if (h <= 0 || w <= 0)
                        cout << "Data error, please input heigth and width greater than 0";
                    else
                    {
                        if (h & 1 || w & 1)
                        {
                            cout << "Data error, input must be even number\nSo we change " << h << " x " << w << " to ";
                            if (h & 1)
                                h++;
                            h = min(h, 20);
                            if (w & 1)
                                w++;
                            w = min(w, 20);
                            cout << h << " x " << w;
                        }
                        return void(makeLevel(h, w,player));
                    }
                }
                if(x>player.level+1)
                    continue;
                if (x != 4)
                {
                    if(x==0)
                        makeLevel(2,2,player);
                    if(x==1)
                        makeLevel(4,4,player);
                    if(x==2)
                        makeLevel(6,6,player);
                    if(x==3)
                        makeLevel(10,10,player);

                    return;
                }
            }
            levelName[x][0] = '>';
            for (int i = 0; i < 5; i++)
            {
                if (i > player.level + 1 && i != 4)
                    TextColor(4);
                cout << levelName[i] << endl;
                TextColor(7);
            }
            levelName[x][0] = ' ';
            cout << endl;
        }
    }
}