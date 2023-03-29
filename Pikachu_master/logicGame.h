#include "header.h"

bool checkEnd(int n, int m, bool ate[200][200])
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!ate[i][j])
                return false; // Có 1 ô chưa đi thì chưa end
    return true;
}

bool bfs(int hei, int wid, int y1, int x1, int y2, int x2, int n, int m, bool type, bool ate[200][200], char view[200][200], char pic[200][200], bool movingOn[200][200], bool selected[200][200], char cpy[200][200])
{
    int graph[200][200];
    ii trace[200][200];
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
            while (x >= 0 && x <= m + 1 && y >= 0 && y <= n + 1 && graph[y][x] == 0)
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

    drawLine(hei, wid, n, m, view, pic, movingOn, selected, route, cpy);

    return true;
}

// bool checkUup(int y1, int x1, int y2, int x2, int n, int m, bool type, char C[200][200], char view[200][200], char pic[200][200], bool movingOn[200][200], bool selected[200][200], char cpy[200][200])
// {
//     for (int i = y1 - 1; i > 0; i--)
//         if (C[i][x1] != '0')
//             return false;

//     for (int i = y2 - 1; i > 0; i--)
//         if (C[i][x2] != '0')
//             return false;

//     if (!type)
//         return true;

//     vector<ii> route;

//     route.push_back(mp(y1, x1));
//     route.push_back(mp(0, x1));
//     route.push_back(mp(0, x2));
//     route.push_back(mp(y2, x2));

//     drawLine(n, m, view, pic, movingOn, selected, route, cpy);

//     return true;
// }

bool finalCheck(int hei, int wid, int y1, int x1, int y2, int x2, int n, int m, bool type, char C[200][200], char view[200][200], char pic[200][200], bool ate[200][200], bool movingOn[200][200], bool selected[200][200], char cpy[200][200])
{
    if (y1 == y2 && x1 == x2)
        return false;
    if (C[y1][x1] != C[y2][x2])
        return false;

    // if (bfs(y1, x1, y2, x2, n, m, type, ate, view, pic, movingOn, selected, cpy))
    //     return true;
    // return checkUup(y1, x1, y2, x2, n, m, type, C, view, pic, movingOn, selected, cpy);

    return bfs(hei, wid, y1, x1, y2, x2, n, m, type, ate, view, pic, movingOn, selected, cpy);
}