#pragma pack(1)
#include "header.h"
#include "player.h"

void displayMenu(int  &n, int &m);

bool neverExist(char S[])
{
    Player tmp;
    ifstream fin;
    fin.open("account\\account.dat", ios::binary);
    while(!fin.eof())
    {
        fin.read((char *) &(tmp), sizeof(Player));
        if(fin.eof())
        break;
        if(strcmp(S,tmp.username)==0)
        {
            fin.close();
            return false;
        }    
    }
    fin.close();
    return true;
}

void printSignUp()
{
    system("cls");
    Player dangky;
    string pass ="";
    char ch;
    dangky.maxScore = -1;
    dangky.level = -1;
    while(1)
    {
        gotoxy(0,0);
        cout <<  "Username: ";
        gets(dangky.username);
        if(neverExist(dangky.username))
            break;
        cout <<  "This username was existed!";
    }
    cout <<  "\nPassword: ";

    while((ch = _getch()) != 13)
    {
        pass += ch;
        cout <<  '*';
    }
    strcpy(dangky.password,pass.c_str());

    int x = 1;

    gotoxy(0,4);
    cout <<  "Press [" << char(176) << "S" << char(176) << "] to show password, or [ H ] to hide";

    while(1)
    {
        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            gotoxy(0,4);

            char key = getch(); // Lấy ký tự người dùng vừa bấm

            if (toupper(key)== 'A'||toupper(key)== 'D'||key==75||key==77) // Di chuyển trái
            {
                ++x;
            }
            

            if(key==13||toupper(key)=='S'||toupper(key)=='H')
            {
                if(x&1||toupper(key)=='S')
                {
                    gotoxy(0, 2);
                    cout <<  "Password: " << pass;
                }
                gotoxy(0, 4);
                cout <<  endl;
                break;
            }

            if(x&1)
                cout <<  "Press [" << char(176) << "S" << char(176) << "] to show password, or [ H ] to hide";
            else
                cout <<  "Press [ S ] to show password, or [" << char(176) << "H" << char(176) << "] to hide";
            cout <<  endl;
        }

    }

    // Ghi vao file
    ofstream fout;

    fout.open("account\\account.dat",ios::binary | ios::app);
    fout.write((char *) &(dangky), sizeof(Player));
    fout.close();


    cout <<  "\nSign up sucessfully!\nPress any key to back to menu!";
    
    ch = _getch();
    system("cls");
    int tmp = 0;
    displayMenu(tmp,tmp);
}
