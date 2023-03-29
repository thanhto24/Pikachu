#include "header.h"

void slideLeft(int hei, int wid, int &y, int &x, int n, int m, char C[200][200], char view[200][200])
{
    for (int i = x; i < m; i++)
    {
        if (C[y][i + 1] == '0')
            break;
        C[y][i] = C[y][i + 1];
        x = i + 1;
    }
    C[y][x] = '0';
    updateView(hei,wid,n, m, C, view);
}

void slideRight(int hei, int wid, int &y, int &x, int n, int m, char C[200][200], char view[200][200])
{
    for (int i = x; i > 1; i--)
    {
        if (C[y][i - 1] == '0')
            break;
        C[y][i] = C[y][i - 1];
        x = i - 1;
    }
    C[y][x] = '0';
    updateView(hei,wid,n, m, C, view);
}

void slideDown(int hei, int wid, int &y, int &x, int n, int m, char C[200][200], char view[200][200])
{
    for (int i = y; i > 1; i--)
    {
        if (C[i - 1][x] == '0')
            break;
        C[i][x] = C[i - 1][x];
        y = i - 1;
    }
    C[y][x] = '0';
    updateView(hei,wid,n, m, C, view);
}

void slideUp(int hei, int wid, int &y, int &x, int n, int m, char C[200][200], char view[200][200])
{
    for (int i = y; i < n; i++)
    {
        if (C[i + 1][x] == '0')
            break;
        C[i][x] = C[i + 1][x];
        y = i + 1;
    }
    C[y][x] = '0';
    updateView(hei,wid,n, m, C, view);
}

void doSlideLeft(int hei, int wid, int y1, int x1, int y2, int x2, int n, int m, char C[200][200], char view[200][200], bool ate[200][200])
{
    if (y1 == y2)
        x2--;
    slideLeft(hei, wid, y1, x1, n, m, C, view);
    setAte(hei, wid, y1, x1, C, view, ate);

    slideLeft(hei, wid, y2, x2, n, m, C, view);
    setAte(hei, wid, y2, x2, C, view, ate);
}

void doSlideRight(int hei, int wid, int y1, int x1, int y2, int x2, int n, int m, char C[200][200], char view[200][200], bool ate[200][200])
{
    if (y1 == y2)
        x1++;

    slideRight(hei, wid, y2, x2, n, m, C, view);
    setAte(hei, wid, y2, x2, C, view, ate);

    slideRight(hei, wid, y1, x1, n, m, C, view);
    setAte(hei, wid, y1, x1, C, view, ate);
}

void doSlideUp(int hei, int wid, int y1, int x1, int y2, int x2, int n, int m, char C[200][200], char view[200][200], bool ate[200][200])
{
    if (x1 == x2)
    {
        if (y1 > y2)
            swap(y1, y2);
        y2--;
    }

    slideUp(hei, wid, y1, x1, n, m, C, view);
    setAte(hei, wid, y1, x1, C, view, ate);

    slideUp(hei, wid, y2, x2, n, m, C, view);
    setAte(hei, wid, y2, x2, C, view, ate);
}

void doSlideDown(int hei, int wid, int y1, int x1, int y2, int x2, int n, int m, char C[200][200], char view[200][200], bool ate[200][200])
{
    if (x1 == x2)
    {
        if (y1 < y2)
            swap(y1, y2);
        y2++;
    }

    slideDown(hei, wid, y1, x1, n, m, C, view);
    setAte(hei, wid, y1, x1, C, view, ate);

    slideDown(hei, wid, y2, x2, n, m, C, view);
    setAte(hei, wid, y2, x2, C, view, ate);
}
