#include "header.h"

void doTab(int cnt)
{
    for(int i = 0; i < cnt; i++)
        cout <<  '\t';
}

void printBoard(int n, int m, int type, char view[200][200], char pic[200][200], bool movingOn[200][200], bool selected[200][200], char cpy[200][200])
{
    // Note: & là viền ngoài map, $ là đã bị ăn, @ là phần trong của ô, + là giao điểm

    // system("cls");
    gotoxy(0,(20-n)/2-4); // Them hang nay de no ko bi giat
    for (int i = 0; i <= n * hei - (n - 2); i++)
    {
        for (int j = 0; j <= m * wid - (m - 2); j++)
        {
            if(j==0)
                doTab(max(1,(20-m)/2)); // Cach ra xa khoi goc trai, vi man hinh co chieu dai khoang 20 tab nen co cong thuc tren
            if (type == 0)
                TextColor(7);
            if (type == 1)
                TextColor(4);
            if (type == 2)
                TextColor(6);

            if (view[i][j] == '^' || view[i][j] == '>' || view[i][j] == 'x')
            {
                TextColor(9);
                if (view[i][j] == '^')
                {
                    if (view[i - 1][j] >= 'A' && view[i - 1][j] <= 'Z')
                        view[i][j] = '^';
                    else if (view[i + 1][j] >= 'A' && view[i + 1][j] <= 'Z')
                        view[i][j] = 'v';
                    else
                        view[i][j] = '|';
                }
                if (view[i][j] == '>')
                {
                    if (view[i][j + 1] >= 'A' && view[i][j + 1] <= 'Z')
                        view[i][j] = '>';
                    else if (view[i][j - 1] >= 'A' && view[i][j - 1] <= 'Z')
                        view[i][j] = '<';
                    else
                        view[i][j] = '-';
                }
                cout <<  view[i][j];
                view[i][j] = cpy[i][j];
                // if (i == 0 || i == n * hei - (n - 2) || j == 0 || j == m * wid - (m - 2))
                //     view[i][j] = '&'; // Neu la vien ngoai thi tra ve ki tu ban dau cua no, dam bao trat tu cua board
                // else
                //     view[i][j] = '$'; // Vi khi noi thi chac chan da bi an, nen ghi dau nay
                TextColor(7);
                continue;
            }

            if (view[i][j] == '&')
            {
                cout <<  ' ';
                continue;
            }

            if (view[i][j] == '+')
            {
                if (view[i - 1][j] == '|' || view[i + 1][j] == '|' || view[i][j + 1] == '-' || view[i][j - 1] == '-')
                    cout <<  view[i][j];
                else
                {
                    TextColor(10);
                    cout <<  pic[i][j];
                    TextColor(7);
                }
                continue;
            }

            if (view[i][j] >= 'A' && view[i][j] <= 'Z') // Nếu là chữ thì đổi màu
                // TextColor(((int)(view[i][j]-'A')/2)+1); // Vì 0 là màu đen k thấy được
                TextColor((i + j) % 15 + 1);

            if (view[i][j] == '@' || view[i][j] == '$' || view[i][j] == '0')
            {
                if (movingOn[(i - 1) / (hei - 1)][(j - 1) / (wid - 1)])
                {
                    if ((i - 1) % (hei - 1) == 0 || (j - 1) % (wid - 1) == 0) // Cái viền thì cout khoảng trắng, để con trỏ nhìn nhỏ hơn cái viền
                        cout <<  ' ';
                    else
                        cout <<  (char)177;
                }
                else if (selected[(i - 1) / (hei - 1)][(j - 1) / (wid - 1)])
                {
                    if (view[i][j] == '@')
                        cout <<  (char)47;
                    else
                    {
                        TextColor(10);
                        cout <<  pic[i][j];
                        TextColor(7);
                    }
                }
                else if (view[i][j] == '$')
                {
                    TextColor(10);
                    cout <<  pic[i][j];
                    TextColor(7);
                } // Them o day de ve cai vien trai va duoi
                else
                    cout <<  ' ';
            }
            else
            {
                cout <<  view[i][j];
            }

            // Sau khi viết ra thì đổi lại
        }
        cout <<  endl;
    }
}


void cpyView(int n, int m, char view[200][200], char cpy[200][200])
{
    for (int i = 0; i <= n * hei - (n - 2); i++)
        for (int j = 0; j <= m * wid - (m - 2); j++)
            cpy[i][j] = view[i][j];
}

void drawLine(int n, int m, char view[200][200], char pic[200][200], bool movingOn[200][200], bool selected[200][200], vector<ii> route, char cpy[200][200])
{
    int Y1, X1, Y2, X2;
    cpyView(n, m, view, cpy);
    for (int i = 0; i < route.size() - 1; i++)
    {
        Y1 = route[i].f;
        if (Y1) // Neu y1 khac 0, co nghia la neu lay o hang tren cung
        {
            if (Y1 == n + 1)
                Y1 = n * hei - (n - 2);
            else
                Y1 = (Y1 - 1) * (hei - 1) + hei / 2 + 1;
        }

        X1 = route[i].s;
        if (X1)
        {
            if (X1 == m + 1)
                X1 = m * wid - (m - 2);
            else
                X1 = (X1 - 1) * (wid - 1) + wid / 2 + 1;
        }

        Y2 = route[i + 1].f;
        if (Y2)
        {
            if (Y2 == n + 1)
                Y2 = n * hei - (n - 2);
            else
                Y2 = (Y2 - 1) * (hei - 1) + hei / 2 + 1;
        }

        X2 = route[i + 1].s;
        if (X2)
        {
            if (X2 == m + 1)
                X2 = m * wid - (m - 2);
            else
                X2 = (X2 - 1) * (wid - 1) + wid / 2 + 1;
        }

        if (X1 == X2)
            for (int i = max(Y1, Y2) - 1; i >= min(Y1, Y2) + 1; i--)
                view[i][X1] = '^';
        if (Y1 == Y2)
            for (int i = max(X1, X2) - 1; i >= min(X1, X2) + 1; i--)
                view[Y1][i] = '>';

        if (i != 0)
            view[Y1][X1] = 'x'; // Giao diem giua cac line va khac dinh dau voi dinh cuoi
    }

    printBoard(n, m, 0, view, pic, movingOn, selected, cpy);
    Sleep(500);
}