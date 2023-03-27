#include "header.h"

void setAte(int hei, int wid, int y, int x, char C[200][200], char view[200][200], bool ate[200][200])
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

void setHint(int hei, int wid, int y, int x, char view[200][200])
{
    x = (x - 1) * (wid - 1) + 2;
    y = (y - 1) * (hei - 1) + 2;
    for (int i = y; i < y + hei - 2; i++)
        for (int j = x; j < x + wid - 2; j++)
        {
            if (view[i][j] == '@')
                view[i][j] = '%';
        }
}

void updateView(int hei, int wid, int n, int m, char C[200][200], char view[200][200])
{
    for (int i = hei / 2 + 1; i <= n * hei - (n - 2); i += hei - 1)
        for (int j = wid / 2 + 1; j <= m * wid - (m - 2); j += wid - 1)
            if ((i - 1 - hei / 2) % (hei - 1) == 0 && (j - 1 - wid / 2) % (wid - 1) == 0)
                view[i][j] = C[(i - 1 - hei / 2) / (hei - 1) + 1][(j - 1 - wid / 2) / (wid - 1) + 1];
}

void refreshArray(int hei, int wid, int n, int m, char C[200][200], char view[200][200], bool ate[200][200])
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

    updateView(hei, wid, n, m, C, view);
}