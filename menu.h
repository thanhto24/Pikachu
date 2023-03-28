#pragma once
#include "header.h"
#include "login.h"
#include "signup.h"
#include "makePicture.h"

void doTab(int cnt);

void makePic(int hei, int wid, int n, int m, char pic[200][200], int num);
void menuMove(int &choice);
void printHelp();
void printHighScore();
void printCredit();


void displayMenu()
{
    system("cls");
    const int heii = 5, widd = 7;
    // char pic[heii hei - (heii)+1][widd * wid - (widd - 2) - 7+1];
    char pic[200][200];
    gotoxy(0,5);
    makePic(5,11,heii,widd,pic,0);
    TextColor(14);
    for(int i = 0; i <= heii * 5 - (heii); i++)
    {
        for(int j = 0; j <= widd * 11 - (widd - 2) - 7; j++)
        {
            if(j==0)
                doTab(9);
            cout <<  pic[i][j];
        }
        cout <<  endl;
    }
    TextColor(7);
    cout <<  endl;
    int choice = 0;
    menuMove(choice);
    system("cls");
    if(choice==0)
        printLogin();
    if(choice==1)
        printSignUp();
    if(choice==2)
        printHelp();
    if(choice==3)
        printCredit();
    if(choice==4)
        printHighScore();
    if(choice==5)
    {
        cout << "Exit sucessfully!";
        exit(0);
    }
}

void menuMove(int &x)
{
    string bar[6];
    bar[0] = "  [ LOGIN ]  ";
    bar[1] = "  [ SIGN UP ]  ";
    bar[2] = "  [ HELP ]  ";
    bar[3] = "  [ CREDIT ]  ";
    bar[4] = "  [ TOP HIGH SCORE ]  ";
    bar[5] = "  [ EXIT ]  ";

    bar[x][0] = '>';
    bar[x][bar[x].size()-1] = '<';

    doTab(4);
    for(int i = 0; i < 6; i++)
    {
        cout <<  bar[i];
        doTab(2);
    }
    
    bar[x][0] = ' ';
    bar[x][bar[x].size()-1] = ' ';

    cout <<  endl;

    while(1)
    {

        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            gotoxy(0,27);

            char key = getch(); // Lấy ký tự người dùng vừa bấm

            if (toupper(key)== 'A' || key == 75) // Di chuyển trái
            {
                x--;
                if (x < 0)
                    x = 5;
            }
            if (toupper(key)== 'D' || key == 77) // Di chuyển phải
            {
                x++;
                if (x > 5)
                    x = 0;
            }

            if(key==13)
                return void(system("cls"));

        bar[x][0] = '>';
        bar[x][bar[x].size()-1] = '<';
        doTab(4);
        for(int i = 0; i < 6; i++)
        {
            cout <<  bar[i];
            doTab(2);
        }
        bar[x][0] = ' ';
        bar[x][bar[x].size()-1] = ' ';
        cout <<  endl;
        }
    }
}

void printHelp()
{
    cout <<  "\n\nI/ HOW TO PLAY?\n\n";
    cout <<  "Press A/S/D/W or arrows to move LEFT/DOWN/RIGHT/LEFT.\n";
    cout <<  "Press Enter to select the cell.\n";
    cout <<  "Press Z to undo, H for hint and R to swap all cells.\n";
    cout <<  "The less time you need to finish this game, the more high score you get.\n";
    cout <<  "That's all. Have fun and good luck!\n\n";

    cout <<  "II/ HOW TO LOGIN?\n\n";
    cout <<  "You need to have an account to login.\n\n";

    cout <<  "III/ HOW TO SIGN UP\n\n";
    cout <<  "You need to offer your email, which never be used, and a password strong enough - this will be decide by my code!\n";    
    cout <<  "If you don not have an account, press [ Y ] to sign up, or [ N ] to login";

    string pick[2];
    pick[0] = "[ Y ]";
    pick[1] = "[ N ]";

    int x = 0;

    pick[x][1] = pick[x][3] = 176;

    pick[x][1] = pick[x][3] = ' ';
    
    while(1)
    {
        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            gotoxy(0,17);

            char key = getch(); // Lấy ký tự người dùng vừa bấm

            if (toupper(key)== 'A'|| toupper(key)== 'D'||key==75||key==77) // Di chuyển trái
            {
                ++x;
            }
            

            if(key==13||toupper(key)=='Y'|toupper(key)=='N')
            {
                if(x&1||key=='Y')
                    printSignUp();
                else
                    printLogin();
                return;
            }

            if(x&1)
                cout <<  "If you don not have an account, press [" << char(176) << "Y" << char(176) << "] to sign up, or [ N ] to login";
            else
                cout <<  "If you don not have an account, press [ Y ] to sign up, or [" << char(176) << "N" << char(176) << "] to login";
            cout <<  endl;
        }

    }
}

bool cmp(Player a, Player b)
{
    return a.level > b.level || ( a.level == b. level ) && (a.maxScore > b.maxScore);
}

void printHighScore()
{
    system("cls");

    Player tmp;
    vector <Player> topPlayer;

    ifstream fin;
    fin.open("account\\account.dat", ios::binary);
    while(!fin.eof())
    {
        fin.read((char *) &(tmp), sizeof(Player));
        if(fin.eof())
            break;
        topPlayer.push_back(tmp);
    }
    fin.close();

    sort(topPlayer.begin(),topPlayer.end(),cmp);

    gotoxy(0,5);
    doTab(11);

    cout << "TOP HIGHEST SCORE PLAYER\n\n";
    for(int i = 0; i < topPlayer.size(); i++)
    {
        if(topPlayer[i].level - 1 == 0)
            break;
        doTab(10);
        cout << topPlayer[i].username;
        for(int j = 0; j < 30 - strlen(topPlayer[i].username); j++)
            cout << '.';

        cout << topPlayer[i].maxScore;

        int dem = 0;
        if(!topPlayer[i].maxScore)
            dem++;

        while(topPlayer[i].maxScore > 0)
        {
            topPlayer[i].maxScore /= 10;
            dem++;
        }

        for(int j = 0; j < 6 - dem; j++)
            cout << ' ';
        cout << " ( Level: " << topPlayer[i].level - 1 << " )\n\n";
    }

    TextColor(6);
    cout <<  "\nPress any key to back to menu!\n";
    TextColor(7);
    
    char ch;
    ch = _getch();
    displayMenu();
}

void printCredit()
{
    cout <<  "Credit!";
}