#pragma pack(1)
#include "header.h"
#include "player.h"

void printLogin()
{
    system("cls");
    //Doc thong tin tu file
    Player player,tmp;
    player.maxScore = player.level = -1;
    cout <<  "Type your account information to login:\n";
    bool sucess = false;

    cout <<  "Username: ";
    gets(player.username);

    cout <<  "Password: ";
    char ch;
    string pass = "";
    int x = 1;
    while((ch = _getch()) != 13)
    {
        pass += ch;
        cout <<  '*';
    }
    strcpy(player.password,pass.c_str());

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

    ifstream fin;
    fin.open("account\\account.dat", ios::binary);
    while(!fin.eof())
    {
        fin.read((char *) &(tmp), sizeof(Player));
        if(fin.eof())
            break;
        if(strcmp(tmp.username,player.username) == 0 && strcmp(tmp.password,player.password) == 0)
        {
            player.level = tmp.level;
            player.maxScore = tmp.maxScore;
            cout <<  "Dang nhap thanh cong!";
            Sleep(2000);
            sucess = true;
            break;
        }   
    }
    fin.close();
    if(!sucess)
    {
        cout << "Thong tin khong hop le!";
        Sleep(2000);
        cin >> ch; // Nếu user ngứa tay bấm lung tung sẽ k bị sai
        printLogin();
    }
    else
        choiceLevel(player);
    return;
}
