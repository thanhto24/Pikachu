#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

using namespace std;

int wid = 11, hei = 5; // Phair laf so le

void makePic(int n, int m, char pic[100][100])
{
    for (int i = 0; i <= n * hei - (n - 2); i++)
    {
        for (int j = 0; j <= m * wid - (m - 2); j++)
        {
            pic[i][j] = ' ';
            if (j & 1)
                pic[i][j] = '.';
        }
    }
}

void init(int &n, int &m, char C[100][100], char view[100][100], char pic[100][100])
{
    // cin >> n;
    n = 4;
    m = n;
    bool was[n * m];
    int x;
    memset(was, false, sizeof(was));
    char c[n * m];
    for (int i = 1; i <= n * m / 2; i++)
    {
        x = 65 + rand() % (90 - 65 + 1);
        for (int i = 1; i <= 2; i++)
        {
            int pos = rand() % (n * n);
            while (was[pos])
                pos = rand() % (n * n);
            was[pos] = true;
            c[pos] = (char)(x);
        }
    }
    int dem = 0;
    for (int i = 0; i <= n + 1; i++)
    {
        for (int j = 0; j <= m + 1; j++)
        {
            if (i == 0 || i == n + 1 || j == 0 || j == m + 1)
                C[i][j] = '&';
            else
                C[i][j] = c[dem++];
            // cin >> C[i][j];
        }
    }

    for (int i = 0; i <= n * hei - (n - 2); i++)
    {
        for (int j = 0; j <= m * wid - (m - 2); j++)
        {
            if (i == 0 || i == n * hei - (n - 2) || j == 0 || j == m * wid - (m - 2))
                view[i][j] = '&';
            else
            {
                if ((i - 1) % (hei - 1) == 0 && (j - 1) % (wid - 1) == 0)
                    view[i][j] = '+';
                else if ((i - 1) % (hei - 1) == 0)
                    view[i][j] = '-';
                else if ((j - 1) % (wid - 1) == 0)
                    view[i][j] = '|';
                else if ((i - 1 - hei / 2) % (hei - 1) == 0 && (j - 1 - wid / 2) % (wid - 1) == 0)
                    view[i][j] = C[(i - 1 - hei / 2) / (hei - 1) + 1][(j - 1 - wid / 2) / (wid - 1) + 1];
                else
                    view[i][j] = '@';
            }
        }
    }

    makePic(n, m, pic);
}

void TextColor(int x) // X là mã màu
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

void setAte(int y, int x, char C[100][100], char view[100][100], bool ate[100][100])
{
    ate[y][x] = true;
    C[y][x] = '0';
    x = (x - 1) * (wid - 1) + 1;
    y = (y - 1) * (hei - 1) + 1;
    for (int i = y; i < y + hei; i++)
        for (int j = x; j < x + wid; j++)
        {
            if (i == y && view[i - 1][j] == '@')
                continue;
            if (i == y + hei - 1 && view[i + 1][j] == '@')
                continue;
            if (j == x && view[i][j - 1] == '@')
                continue;
            if (j == x + wid - 1 && view[i][j + 1] == '@')
                continue;
            if ((i - 1) % (hei - 1) == 0 && (j - 1) % (wid - 1) == 0)
                continue;
            view[i][j] = '$';
        }
}

void printBoard(int n, int m, int type, char view[100][100], char pic[100][100], bool movingOn[100][100], bool selected[100][100], char cpy[100][100])
{
    // Note: & là viền ngoài map, $ là đã bị ăn, @ là phần trong của ô, + là giao điểm

    system("cls");
    for (int i = 0; i <= n * hei - (n - 2); i++)
    {
        for (int j = 0; j <= m * wid - (m - 2); j++)
        {
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

void updateView(int n, int m, char C[100][100], char view[100][100])
{
    for (int i = hei / 2 + 1; i <= n * hei - (n - 2); i += hei - 1)
        for (int j = wid / 2 + 1; j <= m * wid - (m - 2); j += wid - 1)
            if ((i - 1 - hei / 2) % (hei - 1) == 0 && (j - 1 - wid / 2) % (wid - 1) == 0)
                view[i][j] = C[(i - 1 - hei / 2) / (hei - 1) + 1][(j - 1 - wid / 2) / (wid - 1) + 1];
}

void cpyView(int n, int m, char view[100][100], char cpy[100][100])
{
    for (int i = 0; i <= n * hei - (n - 2); i++)
        for (int j = 0; j <= m * wid - (m - 2); j++)
            cpy[i][j] = view[i][j];
}

void drawLine(int n, int m, char view[100][100], char pic[100][100], bool movingOn[100][100], bool selected[100][100], vector<ii> route, char cpy[100][100])
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
    Sleep(300);
}

bool checkEnd(int n, int m, bool ate[100][100])
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!ate[i][j])
                return false; // Có 1 ô chưa đi thì chưa end
    return true;
}

bool bfs(int y1, int x1, int y2, int x2, int n, int m, bool type, bool ate[100][100], char view[100][100], char pic[100][100], bool movingOn[100][100], bool selected[100][100], char cpy[100][100])
{
    int graph[100][100];
    ii trace[100][100];
    ii end = mp(y1, x1);
    ii start = mp(y2, x2);
    queue<ii> q;

    for (int i = 0; i <= n + 1; i++)
    {
        for (int j = 0; j <= m + 1; j++)
        {
            trace[i][j] = mp(-1, -1);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            graph[i][j] = !(ate[i][j]);
        }
    }

    graph[y1][x1] = graph[y2][x2] = 0;
    trace[y1][x1] = mp(-2, -2);
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, -1, 0, 1};

    q.push(end);

    while (!q.empty())
    {
        ii u = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int y = u.f + dy[i];
            int x = u.s + dx[i];
            while (x >= 0 && x <= n + 1 && y >= 0 && y <= m + 1 && graph[y][x] == 0)
            {
                if (trace[y][x] == mp(-1, -1))
                {
                    trace[y][x] = u;
                    q.push(mp(y, x));
                }
                x += dx[i];
                y += dy[i];
            }
        }
    }

    vector<ii> route;

    if (trace[start.f][start.s] == mp(-1, -1))
        return false;

    while (start != end)
    {
        route.push_back(mp(start.f, start.s));
        start = trace[start.f][start.s];
        if (route.size() > 3)
            return false;
    }

    if (!type)
        return true;
    route.push_back(mp(start.f, start.s));

    drawLine(n, m, view, pic, movingOn, selected, route, cpy);

    return true;
}

bool checkUup(int y1, int x1, int y2, int x2, int n, int m, bool type, char C[100][100], char view[100][100], char pic[100][100], bool movingOn[100][100], bool selected[100][100], char cpy[100][100])
{
    for (int i = y1 - 1; i > 0; i--)
        if (C[i][x1] != '0')
            return false;

    for (int i = y2 - 1; i > 0; i--)
        if (C[i][x2] != '0')
            return false;

    if (!type)
        return true;

    vector<ii> route;

    route.push_back(mp(y1, x1));
    route.push_back(mp(0, x1));
    route.push_back(mp(0, x2));
    route.push_back(mp(y2, x2));

    drawLine(n, m, view, pic, movingOn, selected, route, cpy);

    return true;
}

bool finalCheck(int y1, int x1, int y2, int x2, int n, int m, bool type, char C[100][100], char view[100][100], char pic[100][100], bool ate[100][100], bool movingOn[100][100], bool selected[100][100], char cpy[100][100])
{
    if (y1 == y2 && x1 == x2)
        return false;
    if (C[y1][x1] != C[y2][x2])
        return false;
    if (bfs(y1, x1, y2, x2, n, m, type, ate, view, pic, movingOn, selected, cpy))
        return true;
    return checkUup(y1, x1, y2, x2, n, m, type, C, view, pic, movingOn, selected, cpy);
}

bool cantMove(int n, int m, char C[100][100], char view[100][100], char pic[100][100], bool ate[100][100], bool movingOn[100][100], bool selected[100][100], char cpy[100][100])
{
    if (checkEnd(n, m, ate))
        return false;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = i; k <= n; k++)
            {
                for (int l = 1; l <= m; l++)
                {
                    if (!ate[i][j] && !ate[k][l]) // Nếu 2 ô chưa đi
                        if (finalCheck(i, j, k, l, n, m, 0, C, view, pic, ate, movingOn, selected, cpy))
                        {
                            cout <<  i << " " << j << "   " << k << " " << l << endl; // Turn on to cheat
                            // Sleep(500);
                            return false;
                        }
                }
            }
        }
    }
    return true;
}

void refreshArray(int n, int m, char C[100][100], char view[100][100], bool ate[100][100])
{
    vector<ii> adj;
    adj.push_back(mp(-1, -1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!ate[i][j])
                adj.push_back(mp(i, j));

    int N = adj.size() - 1, dem = 1;
    bool was[N + 1];
    memset(was, false, sizeof(was));

    if (N == 4) // Vì khi còn 2 cặp mà ko move được thì chúng bị chéo, khi đó xử lí riêng cho nhanh
    {
        // Tạo 4 cách random cho vui
        int x = rand() % 4;
        if (!x)
            swap(C[adj[2].f][adj[2].s], C[adj[1].f][adj[1].s]);
        if (x == 1)
            swap(C[adj[3].f][adj[3].s], C[adj[1].f][adj[1].s]);
        if (x == 2)
            swap(C[adj[2].f][adj[2].s], C[adj[4].f][adj[4].s]);
        if (x == 3)
            swap(C[adj[2].f][adj[2].s], C[adj[1].f][adj[1].s]);
    }
    else
        while (dem < N)
        {
            int tmp1 = rand() % (N) + 1;
            int tmp2 = rand() % (N) + 1;

            while (was[tmp1])
                tmp1 = rand() % (N) + 1;
            was[tmp1] = true;

            while (was[tmp2])
                tmp2 = rand() % (N) + 1;
            was[tmp2] = true;

            swap(C[adj[tmp1].f][adj[tmp1].s], C[adj[tmp2].f][adj[tmp2].s]);

            dem += 2;
        }

    updateView(n, m, C, view);
}

void slideLeft(int &y, int &x, int n, int m, char C[100][100], char view[100][100])
{
    for (int i = x; i < m; i++)
    {
        if (C[y][i + 1] == '0')
            break;
        C[y][i] = C[y][i + 1];
        x = i + 1;
    }
    C[y][x] = '0';
    updateView(n, m, C, view);
}

void slideRight(int &y, int &x, int n, int m, char C[100][100], char view[100][100])
{
    for (int i = x; i > 1; i--)
    {
        if (C[y][i - 1] == '0')
            break;
        C[y][i] = C[y][i - 1];
        x = i - 1;
    }
    C[y][x] = '0';
    updateView(n, m, C, view);
}

void slideDown(int &y, int &x, int n, int m, char C[100][100], char view[100][100])
{
    for (int i = y; i > 1; i--)
    {
        if (C[i - 1][x] == '0')
            break;
        C[i][x] = C[i - 1][x];
        y = i - 1;
    }
    C[y][x] = '0';
    updateView(n, m, C, view);
}

void slideUp(int &y, int &x, int n, int m, char C[100][100], char view[100][100])
{
    for (int i = y; i < n; i++)
    {
        if (C[i + 1][x] == '0')
            break;
        C[i][x] = C[i + 1][x];
        y = i + 1;
    }
    C[y][x] = '0';
    updateView(n, m, C, view);
}

void doSlideLeft(int y1, int x1, int y2, int x2, int n, int m, char C[100][100], char view[100][100], bool ate[100][100])
{
    if (y1 == y2)
        x2--;
    slideLeft(y1, x1, n, m, C, view);
    setAte(y1, x1, C, view, ate);

    slideLeft(y2, x2, n, m, C, view);
    setAte(y2, x2, C, view, ate);
}

void doSlideRight(int y1, int x1, int y2, int x2, int n, int m, char C[100][100], char view[100][100], bool ate[100][100])
{
    if (y1 == y2)
        x1++;

    slideRight(y2, x2, n, m, C, view);
    setAte(y2, x2, C, view, ate);

    slideRight(y1, x1, n, m, C, view);
    setAte(y1, x1, C, view, ate);
}

void doSlideUp(int y1, int x1, int y2, int x2, int n, int m, char C[100][100], char view[100][100], bool ate[100][100])
{
    if (x1 == x2)
    {
        if (y1 > y2)
            swap(y1, y2);
        y2--;
    }

    slideUp(y1, x1, n, m, C, view);
    setAte(y1, x1, C, view, ate);

    slideUp(y2, x2, n, m, C, view);
    setAte(y2, x2, C, view, ate);
}

void doSlideDown(int y1, int x1, int y2, int x2, int n, int m, char C[100][100], char view[100][100], bool ate[100][100])
{
    if (x1 == x2)
    {
        if (y1 < y2)
            swap(y1, y2);
        y2++;
    }

    slideDown(y1, x1, n, m, C, view);
    setAte(y1, x1, C, view, ate);

    slideDown(y2, x2, n, m, C, view);
    setAte(y2, x2, C, view, ate);
}

void unSelect(int n, int m, bool ate[100][100], bool selected[100][100])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (selected[i][j] && !ate[i + 1][j + 1])
                selected[i][j] = false;
}

void move(int n, int m, int &y, int &x, char C[100][100], char view[100][100], char pic[100][100], bool ate[100][100], bool movingOn[100][100], bool selected[100][100], char cpy[100][100])
{
    int X[2], Y[2], cnt = 0;
    bool isSlide = true;
    // select va  movingOn chay tu 0 den n - 1
    while (true)
    {
        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            char key = getch(); // Lấy ký tự người dùng vừa bấm

            if (key == 'a' || key == 'A') // Di chuyển trái
            {
                x--;
                if (x < 0)
                    x = n - 1;
            }
            if (key == 'd' || key == 'D') // Di chuyển phải
            {
                x++;
                if (x >= n)
                    x = 0;
            }
            if (key == 'w' || key == 'W') // Di chuyển lên
            {
                y--;
                if (y < 0)
                    y = m - 1;
            }
            if (key == 's' || key == 'S') // Di chuyển xuống
            {
                y++;
                if (y >= m)
                    y = 0;
            }

            if (key == 'r' || key == 'R')
            {
                refreshArray(n, m, C, view, ate);
                printBoard(n, m, 2, view, pic, movingOn, selected, cpy);
                Sleep(300);
                printBoard(n, m, 0, view, pic, movingOn, selected, cpy);
                unSelect(n, m, ate, selected); // Neu player da chon 1 o ma bam R thi se bug, nen neu bam R thi thao select het
            }

            // Nhấn z để tháo select

            if (key == 'z' || key == 'Z')
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

                        // Nhấp nháy màu đỏ khi không ăn được

                        for (int i = 0; i < 20 / n; i++)
                            printBoard(n, m, 1, view, pic, movingOn, selected, cpy);
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

void process(int n, int m, char C[100][100], char view[100][100], char pic[100][100], bool ate[100][100], bool movingOn[100][100], bool selected[100][100], char cpy[100][100])
{
    //     printBoard(n, m, 0, view, pic, movingOn, selected,tmp);

    // return;

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

        // Sleep(100); // New
    }

    memset(movingOn, false, sizeof(movingOn));
    printBoard(n, m, 0, view, pic, movingOn, selected, cpy);
    Sleep(3000);
    system("cls");
    cout <<  "GAME OVER!";
}

int main()
{
    char C[100][100], a[100][100];
    bool ate[100][100];
    bool movingOn[100][100], selected[100][100];
    char view[100][100], pic[100][100], cpy[100][100];
    int n, m;

    srand(time(0));
    init(n, m, C, view, pic);
    process(n, m, C, view, pic, ate, movingOn, selected, cpy);
    return 0;
}
