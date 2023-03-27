#include "header.h"

bool cantMove(int hei, int wid, int n, int m, char C[200][200], char view[200][200], char pic[200][200], bool ate[200][200], bool movingOn[200][200], bool selected[200][200], char cpy[200][200])
{
    if (checkEnd(n, m, ate))
        return false;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = 1; k <= n; k++)
            {
                for (int l = 1; l <= m; l++)
                {
                    if (!ate[i][j] && !ate[k][l]) // Nếu 2 ô chưa đi
                        if (finalCheck(hei, wid, i, j, k, l, n, m, 0, C, view, pic, ate, movingOn, selected, cpy))
                        {
                            // TextColor(4);
                            // cout <<  i << " " << j << "   " << k << " " << l << endl; // Turn on to cheat
                            // TextColor(7);
                            // Sleep(500);
                            return false;
                        }
                }
            }
        }
    }
    return true;
}
