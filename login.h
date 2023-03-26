#pragma pack(1)
#include "header.h"
#include "player.h"

void printLogin()
{
    system("cls");
    //Doc thong tin tu file
    Player player,tmp;
    player.maxScore = player.level = -1;
    cout <<  "dang nhap:\n";
    bool sucess = false;
    cout <<  "Username: ";
    gets(player.username);
    cout <<  "Password: ";
    gets(player.password); 
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
            sucess = true;
            break;
        }   
    }
    fin.close();
    if(!sucess)
    {
        cout << "Thong tin khong hop le!";
        printLogin();
    }
    else
        choiceLevel(player);
    return;
}
