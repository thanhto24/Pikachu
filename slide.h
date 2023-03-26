#include "header.h"

void slideLeft(int &y, int &x, int n, int m, char C[200][200], char view[200][200])
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

void slideRight(int &y, int &x, int n, int m, char C[200][200], char view[200][200])
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

void slideDown(int &y, int &x, int n, int m, char C[200][200], char view[200][200])
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

void slideUp(int &y, int &x, int n, int m, char C[200][200], char view[200][200])
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

void doSlideLeft(int y1, int x1, int y2, int x2, int n, int m, char C[200][200], char view[200][200], bool ate[200][200])
{
    if (y1 == y2)
        x2--;
    slideLeft(y1, x1, n, m, C, view);
    setAte(y1, x1, C, view, ate);

    slideLeft(y2, x2, n, m, C, view);
    setAte(y2, x2, C, view, ate);
}

void doSlideRight(int y1, int x1, int y2, int x2, int n, int m, char C[200][200], char view[200][200], bool ate[200][200])
{
    if (y1 == y2)
        x1++;

    slideRight(y2, x2, n, m, C, view);
    setAte(y2, x2, C, view, ate);

    slideRight(y1, x1, n, m, C, view);
    setAte(y1, x1, C, view, ate);
}

void doSlideUp(int y1, int x1, int y2, int x2, int n, int m, char C[200][200], char view[200][200], bool ate[200][200])
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

void doSlideDown(int y1, int x1, int y2, int x2, int n, int m, char C[200][200], char view[200][200], bool ate[200][200])
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
