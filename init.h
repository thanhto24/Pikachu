#include "header.h"

void init(int n, int m, char C[200][200], char view[200][200])
{
    // cin >> n;
    bool was[n * m];
    int x;
    memset(was, false, sizeof(was));
    char c[n * m];
    for (int i = 1; i <= n * m / 2; i++)
    {
        x = 65 + rand() % (90 - 65 + 1);
        for (int i = 1; i <= 2; i++)
        {
            int pos = rand() % (n * m);
            while (was[pos])
                pos = rand() % (n * m);
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
}