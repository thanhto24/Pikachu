#pragma pack(1)
#include "header.h"
#include "player.h"
#include "login.h"

void displayMenu();

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
    int dem = 0;
    dangky.level = 1;
    dangky.maxScore = 0;

    TextColor(5);
    cout <<  "Type your account information to sign up:\n";
    TextColor(7);

    cout <<  "Username: ";
    gets(dangky.username);

    if(strlen(dangky.username)==0)
    {
        TextColor(4);
        cout <<  "Username length must be greater than 3! Try another\n";
        Sleep(1500);
        TextColor(7);
        printSignUp();
        return;
    }

    if(!neverExist(dangky.username))
    {
        TextColor(4);
        cout <<  "This username was existed! Try another\n";
        Sleep(1500);
        TextColor(7);
        printSignUp();
        return;
    }
        
    cout <<  "\nPassword: ";
   
    while((ch = _getch()) != 13 && ch != ' ')
    {
        dem++;
        if(ch == 8 && pass.size()>0)
            pass.erase(pass.begin()+pass.size()-1);
        else
        if(ch != 8 )
        pass += ch;
        gotoxy(0,3);
        cout <<  "Password: ";
        for(int i = 0; i < pass.size(); i++)
            cout << '*';
        for(int i = pass.size(); i <= dem; i++)
            cout << ' ';
        cout << endl;
    }

        
    strcpy(dangky.password,pass.c_str());

    int x = 1;

    gotoxy(0,5);
    cout <<  "Press [" << char(176) << "S" << char(176) << "] to show password, or [ H ] to hide";

    while(1)
    {
        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            gotoxy(0,5);

            char key = getch(); // Lấy ký tự người dùng vừa bấm

            if (toupper(key)== 'A'||toupper(key)== 'D'||key==75||key==77) // Di chuyển trái
            {
                ++x;
            }
            

            if(key==13||toupper(key)=='S'||toupper(key)=='H')
            {
                if(x&1||toupper(key)=='S')
                {
                    gotoxy(0, 3);
                    cout <<  "Password: " << pass;
                }
                gotoxy(0, 5);
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

    TextColor(6);
    cout <<  "\nSign up sucessfully!\nPress L to Login or others key to back to menu!\n";
    TextColor(7);
    
    ch = _getch();
    if(toupper(ch)=='L')
        printLogin();
    else
    displayMenu();
}
