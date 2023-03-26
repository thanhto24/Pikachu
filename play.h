#include "header.h"
#include "player.h"

void unSelect(int n, int m, bool ate[200][200], bool selected[200][200])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (selected[i][j] && !ate[i + 1][j + 1])
                selected[i][j] = false;
}

void move(int n, int m, int &y, int &x, char C[200][200], char view[200][200], char pic[200][200], bool ate[200][200], bool movingOn[200][200], bool selected[200][200], char cpy[200][200])
{
    int X[2], Y[2], cnt = 0;
    bool isSlide = true;
    // select va  movingOn chay tu 0 den n - 1
    while (true)
    {
        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            char key = getch(); // Lấy ký tự người dùng vừa bấm

            if (toupper(key)== 'A'||key==75) // Di chuyển trái
            {
                x--;
                if (x < 0)
                    x = n - 1;
            }
            if (toupper(key)== 'D'||key==77) // Di chuyển phải
            {
                x++;
                if (x >= n)
                    x = 0;
            }
            if (toupper(key)== 'W'||key==72) // Di chuyển lên
            {
                y--;
                if (y < 0)
                    y = m - 1;
            }
            if (toupper(key)== 'S'||key==80) // Di chuyển xuống
            {
                y++;
                if (y >= m)
                    y = 0;
            }

            if (toupper(key) == 'R')
            {
                refreshArray(n, m, C, view, ate);
                printBoard(n, m, 2, view, pic, movingOn, selected, cpy);
                Sleep(300);
                printBoard(n, m, 0, view, pic, movingOn, selected, cpy);
                unSelect(n, m, ate, selected); // Neu player da chon 1 o ma bam R thi se bug, nen neu bam R thi thao select het
            }

            // Nhấn z để tháo select

            if (toupper(key)== 'Z')
            {
                unSelect(n, m, ate, selected);
                cnt = 0;
            }

            if (key != 13)
            {
                memset(movingOn, false, sizeof(movingOn));
                movingOn[y][x] = true;
                printBoard(n, m, 0, view, pic, movingOn, selected, cpy);
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

                    if (finalCheck(y1, x1, y2, x2, n, m, 1, C, view, pic, ate, movingOn, selected, cpy))
                    {
                        if (isSlide)
                        {
                            int tmp = rand() % 4 + 1;
                            tmp = 4;
                            if(tmp==1)
                                doSlideUp(y1,x1,y2,x2,n,m,C,view,ate);
                            if(tmp==2)
                                doSlideDown(y1,x1,y2,x2,n,m,C,view,ate);
                            if(tmp==3)
                                doSlideRight(y1,x1,y2,x2,n,m,C,view,ate);
                            if(tmp==4)
                                doSlideLeft(y1,x1,y2,x2,n,m,C,view,ate);
                        }
                        else
                        {
                            setAte(y1, x1, C, view, ate);
                            setAte(y2, x2, C, view, ate);
                        }
                    }
                    else
                    {
                        for (int i = 0; i < n; i++)
                            for (int j = 0; j < m; j++)
                                if (selected[i][j] && !ate[i + 1][j + 1])
                                    selected[i][j] = false;

                        printBoard(n, m, 1, view, pic, movingOn, selected, cpy);
                        Sleep(300);

                    }
                    unSelect(n, m, ate, selected);
                    movingOn[y][x] = true;
                    printBoard(n, m, 0, view, pic, movingOn, selected, cpy);
                    return;
                }
                printBoard(n, m, 0, view, pic, movingOn, selected, cpy);
                cnt++;
            }
        }
    }
}

void updateFile(Player player);

void process(int n, int m, char C[200][200], char view[200][200], char pic[200][200], bool ate[200][200], bool movingOn[200][200], bool selected[200][200], char cpy[200][200],Player &player)
{
    int x = 0, y = 0;
    memset(movingOn, false, sizeof(movingOn));
    movingOn[y][x] = true;
    printBoard(n, m, 0, view, pic, movingOn, selected, cpy);

    while (!checkEnd(n, m, ate))
    {
        while (cantMove(n, m, C, view, pic, ate, movingOn, selected, cpy))
        {
            refreshArray(n, m, C, view, ate);
            printBoard(n, m, 2, view, pic, movingOn, selected, cpy);
        }
        move(n, m, y, x, C, view, pic, ate, movingOn, selected, cpy);
        movingOn[y][x] = false;
    }

    memset(movingOn, false, sizeof(movingOn));
    printBoard(n, m, 0, view, pic, movingOn, selected, cpy);
    Sleep(1234);
    system("cls");
    cout <<  "GAME OVER!";
    system("cls");
    player.level ++;
    updateFile(player);
}

void updateFile(Player player)
{
    Player tmp;
    vector <Player> adj;
    ifstream fin;
    fin.open("account\\account.dat", ios::binary);
    while(!fin.eof())
    {
        fin.read((char *) &(tmp), sizeof(Player));
        if(fin.eof())
            break;
        if(strcmp(tmp.username,player.username) == 0 && strcmp(tmp.password,player.password) == 0)
        {
            tmp.level = min(player.level,4);
            tmp.maxScore = max(player.maxScore, tmp.maxScore);
        }   
        adj.push_back(tmp);
    }
    fin.close();

    ofstream fout;
    fout.open("account\\account.dat",ios::binary);
    for(int i = 0; i < adj.size(); i++)
        fout.write((char *) &(adj[i]), sizeof(Player));
    fout.close();
}
