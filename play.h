#pragma once
#include "header.h"
#include "player.h"
#include "menu.h"
#include "level.h"

void unSelect(int n, int m, bool ate[200][200], bool selected[200][200])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (selected[i][j] && !ate[i + 1][j + 1])
                selected[i][j] = false;
}

void calcTime(const int TIME, int &timeLeft, int &prevTime, int m1, int s1, int m2, int s2, int &Point)
{
    timeLeft = TIME - (m2 - m1) * 60 - (s2 - s1);
    if (timeLeft >= 0)
    {
        if (prevTime != timeLeft)
        {
            gotoxy(0, 2);

            if (timeLeft <= 30)
                TextColor(4);

            cout << "Time left: ";
            cout << setw(2) << setfill('0') << timeLeft / 60 << " : " << setw(2) << setfill('0') << timeLeft % 60;
            TextColor(7);

            doTab(1);

            if(timeLeft&1)
                Point--; // 2 giay mat 1 diem, de neu dung help hoac swap kho bi phat hien
            cout << "Your Point: ";
            TextColor(3);
            cout << Point << "   " << endl;
            TextColor(7);
        }
        prevTime = timeLeft;
    }
    else
        timeLeft = -1;
}

void printInfo(Player player, int Swap, int Hint)
{
    gotoxy(0, 1);
    cout << "Hello ";
    TextColor(1);
    cout << player.username;
    TextColor(7);

    doTab(1);
    cout << "Swap left: ";
    TextColor(6);
    cout << Swap;
    TextColor(7);

    doTab(1);
    cout << "Hint left: ";
    TextColor(2);
    cout << Hint;
    TextColor(7);

    doTab(2);
    TextColor(4);
    cout << "Double press Backspace button to Back to menu!";
    TextColor(7);
}

void move(int hei, int wid, int n, int m, int &y, int &x, bool &stop, char C[200][200], char view[200][200], char pic[200][200], bool ate[200][200], bool movingOn[200][200], bool selected[200][200], char cpy[200][200], int &Swap, int &Hint, const int TIME, int &timeLeft, const int m1, const int s1, int &Point, const int choosenLevel)
{
    int X[2], Y[2], cnt = 0;
    int prevTime = timeLeft;
    bool isSlide = true;
    // select va  movingOn chay tu 0 den n - 1
    while (true)
    {
        int m2, s2;
        time_t now = time('\0');
        tm *t = localtime(&now);
        m2 = t->tm_min;
        s2 = t->tm_sec;

        calcTime(TIME, timeLeft, prevTime, m1, s1, m2, s2, Point);

        if (TIME == -1)
            return;

        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            char key = getch(), prevKey; // Lấy ký tự người dùng vừa bấm

            if(key == prevKey && prevKey == 8)
            {
                stop = true;
                return;                
            }

            if (toupper(key) == 'A' || key == 75) // Di chuyển trái
            {
                x--;
                if (x < 0)
                    x = m - 1;
            }
            if (toupper(key) == 'D' || key == 77) // Di chuyển phải
            {
                x++;
                if (x >= m)
                    x = 0;
            }
            if (toupper(key) == 'W' || key == 72) // Di chuyển lên
            {
                y--;
                if (y < 0)
                    y = n - 1;
            }
            if (toupper(key) == 'S' || key == 80) // Di chuyển xuống
            {
                y++;
                if (y >= n)
                    y = 0;
            }

            if (toupper(key) == 'R')
            {
                Swap--;
                if (Swap < 0)
                {
                    Swap = 0;
                    continue;
                }
                Point -= 10;
                unSelect(n, m, ate, selected); // Neu player da chon 1 o ma bam R thi se bug, nen neu bam R thi thao select het
                refreshArray(hei, wid, n, m, C, view, ate);
                printBoard(hei, wid, n, m, 2, view, pic, movingOn, selected, cpy);
                Sleep(300);

                movingOn[y][x] = true;
                printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);
                movingOn[y][x] = false;

                return;
            }

            // Nhấn z để tháo select

            if (toupper(key) == 'Z')
            {
                unSelect(n, m, ate, selected);
                cnt = 0;
            }

            if (key == '!')
            {
                Hint--;
                if (Hint < 0)
                {
                    Hint = 0;
                    continue;
                }
                Point -= 10;
                unSelect(n, m, ate, selected);
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= m; j++)
                        for (int k = 1; k <= n; k++)
                            for (int l = 1; l <= m; l++)
                                if (!ate[i][j] && !ate[k][l]) // Nếu 2 ô chưa đi
                                    if (finalCheck(hei, wid, i, j, k, l, n, m, 0, C, view, pic, ate, movingOn, selected, cpy))
                                    {
                                        setHint(hei, wid, i, j, view);
                                        setHint(hei, wid, k, l, view);
                                        printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);
                                        Sleep(300);

                                        movingOn[y][x] = true;
                                        printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);
                                        movingOn[y][x] = false;

                                        return;
                                    }
            }

            if (key != 13)
            {
                memset(movingOn, false, sizeof(movingOn));
                movingOn[y][x] = true;
                printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);
                movingOn[y][x] = false; // Neu khong gan lai thi no se movingOn tat ca cac o da di qua
            }

            // Nhấn enter để chọn ô y x
            if (key == 13)
            {
                if (ate[y + 1][x + 1])
                    continue;
                selected[y][x] = true;
                Y[cnt] = y;
                X[cnt] = x;
                if (cnt == 1)
                {
                    int y1 = Y[1 - 1] + 1, y2 = Y[2 - 1] + 1, x1 = X[1 - 1] + 1, x2 = X[2 - 1] + 1;

                    if (x1 > x2)
                    {
                        swap(x1, x2);
                        swap(y1, y2);
                    }

                    if (finalCheck(hei, wid, y1, x1, y2, x2, n, m, 1, C, view, pic, ate, movingOn, selected, cpy))
                    {
                        if (isSlide)
                        {
                            int tmp = min(4, choosenLevel);
                            if (tmp == 1)
                                doSlideUp(hei, wid, y1, x1, y2, x2, n, m, C, view, ate);
                            if (tmp == 2)
                                doSlideDown(hei, wid, y1, x1, y2, x2, n, m, C, view, ate);
                            if (tmp == 3)
                                doSlideRight(hei, wid, y1, x1, y2, x2, n, m, C, view, ate);
                            if (tmp == 4)
                                doSlideLeft(hei, wid, y1, x1, y2, x2, n, m, C, view, ate);
                        }
                        else
                        {
                            setAte(hei, wid, y1, x1, C, view, ate);
                            setAte(hei, wid, y2, x2, C, view, ate);
                        }
                        Point += 5;
                    }
                    else
                    {
                        for (int i = 0; i < n; i++)
                            for (int j = 0; j < m; j++)
                                if (selected[i][j] && !ate[i + 1][j + 1])
                                    selected[i][j] = false;

                        printBoard(hei, wid, n, m, 1, view, pic, movingOn, selected, cpy);
                        Point--;
                        Sleep(300);
                    }
                    unSelect(n, m, ate, selected);
                    movingOn[y][x] = true;
                    printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);
                    return;
                }
                printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);
                cnt++;
            }
            prevKey = key;
        }
    }
}

void updateFile(Player player);
void choiceLevel(Player player);

void process(int hei, int wid, int n, int m, char C[200][200], char view[200][200], char pic[200][200], bool ate[200][200], bool movingOn[200][200], bool selected[200][200], char cpy[200][200], Player &player, const int choosenLevel)
{
    int x = 0, y = 0, Swap = 10 - choosenLevel, Hint = 10 - choosenLevel, Point = (Swap + Hint) * 100;
    const int TIME = 600 - choosenLevel * 30;
    int timeLeft = TIME;
    bool stop = false;

    if (choosenLevel == 5)
    {
        timeLeft = 3600;
        Swap = 6666;
        Hint = 3333;
    }

    int m1, s1;
    time_t now = time('\0');
    tm *t = localtime(&now);
    m1 = t->tm_min;
    s1 = t->tm_sec;

    printInfo(player, Swap, Hint);
    memset(movingOn, false, sizeof(movingOn));
    movingOn[y][x] = true;
    printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);

    while (!checkEnd(n, m, ate))
    {
        bool swapped = false;
        while (cantMove(hei, wid, n, m, C, view, pic, ate, movingOn, selected, cpy))
        {
            swapped = true;
            refreshArray(hei, wid, n, m, C, view, ate);
            printBoard(hei, wid, n, m, 2, view, pic, movingOn, selected, cpy);
        }
        if (swapped)
        {
            movingOn[y][x] = true;
            printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);
            movingOn[y][x] = false;
            Sleep(300);
        }
        move(hei, wid, n, m, y, x,stop, C, view, pic, ate, movingOn, selected, cpy, Swap, Hint, TIME, timeLeft, m1, s1, Point, choosenLevel);
        movingOn[y][x] = false;
        printInfo(player, Swap, Hint);
        if(stop)
        {
            displayMenu();
            return;
        }
        if (TIME == -1)
            break;
    }

    memset(movingOn, false, sizeof(movingOn));
    printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);

    Sleep(1234);
    system("cls");

    if (TIME != -1)
    {
        if (choosenLevel == player.level)
        {
            player.level++;
        }

        player.maxScore = Point;
        player.level = min(player.level, 5);

        cout << "Congratulation!! You got: ";
        TextColor(3);
        cout << Point;
        TextColor(7);
        cout << " point!\nGAME OVER!\n";
        updateFile(player);
    }
    else
    {
        TextColor(4);
        cout << "You are looser!\n";
        TextColor(7);
    }

    TextColor(6);
    cout << "Press any key to continue!\n";
    TextColor(7);

    char ch;
    ch = _getch();

    system("cls");

    choiceLevel(player);
}

void updateFile(Player player)
{
    Player tmp;
    vector<Player> adj;
    ifstream fin;
    fin.open("account\\account.dat", ios::binary);
    while (!fin.eof())
    {
        fin.read((char *)&(tmp), sizeof(Player));
        if (fin.eof())
            break;
        if (strcmp(tmp.username, player.username) == 0 && strcmp(tmp.password, player.password) == 0)
        {
            if (tmp.level + 1 == player.level)
            {
                tmp.maxScore = player.maxScore;
            }
            tmp.level = max(player.level, tmp.level);
        }
        adj.push_back(tmp);
    }
    fin.close();

    ofstream fout;
    fout.open("account\\account.dat", ios::binary);
    for (int i = 0; i < adj.size(); i++)
        fout.write((char *)&(adj[i]), sizeof(Player));
    fout.close();
}
