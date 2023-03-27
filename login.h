#pragma pack(1)
#include "header.h"
#include "player.h"

void printLogin()
{
    system("cls");
    //Doc thong tin tu file
    Player player,tmp;

    TextColor(5);
    cout <<  "Type your account information to login!\n";
    TextColor(7);

    bool sucess = false;

    cout <<  "Username: ";
    gets(player.username);

    cout <<  "Password: ";
    char ch;
    string pass = "";
    int x = 1, dem = 0;
    while((ch = _getch()) != 13 && ch != ' ')
    {
        dem++;
        if(ch == 8 && pass.size()>0)
            pass.erase(pass.begin()+pass.size()-1);
        else
        if(ch != 8 )
        pass += ch;
        gotoxy(0,2);
        cout <<  "Password: ";
        for(int i = 0; i < pass.size(); i++)
            cout << '*';
        for(int i = pass.size(); i <= dem; i++)
            cout << ' ';
        cout << endl;
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

    bool existUsername = false;

    ifstream fin;
    fin.open("account\\account.dat", ios::binary);
    while(!fin.eof())
    {
        fin.read((char *) &(tmp), sizeof(Player));
        if(fin.eof())
            break;
        if(strcmp(tmp.username,player.username) == 0 )
        {
            existUsername = true;
            if(strcmp(tmp.password,player.password) == 0)
            {
                player.level = tmp.level;
                player.maxScore = tmp.maxScore;
                fin.close();

                cout <<  "Login successfully!";
                TextColor(6);
                cout << "\nPress any key to continue\n";
                TextColor(7);

                ch = _getch();
                choiceLevel(player);
                return;
            }
        }   
    }
    if(!sucess)
    {
        TextColor(4);
        if(existUsername)
            cout << "Your password is wrong!";
        else
            cout << "Your username is not exist!";
        TextColor(6);
        cout << "\nPress any key to login again\n";
        TextColor(7);
        ch = _getch();
        printLogin();
    }
}
