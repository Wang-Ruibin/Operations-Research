#include <bits/stdc++.h>
using namespace std;

const int N = 10000;
int num = 1, s, t, ans, head[N], cur[N], dep[N], n, p, q;
bool vis[N];
struct edge
{
    int v, nxt, w;
} e[N << 1];

void add(int u, int v, int w)
{
    e[++num].nxt = head[u];
    e[num].v = v;
    e[num].w = w;
    head[u] = num;
}

bool bfs()
{
    for (int i = 0; i <= t; i++)
        cur[i] = head[i], vis[i] = dep[i] = 0;
    queue<int> q;
    q.push(s);
    vis[s] = dep[s] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].v, w = e[i].w;
            if (w && !dep[v])
            {
                dep[v] = dep[u] + 1;
                if (!vis[v])
                    vis[v] = 1, q.push(v);
            }
        }
    }
    return dep[t];
}

int dfs(int u, int in)
{
    if (u == t)
        return in;
    int out = 0, res;
    for (int i = cur[u]; i && in; i = e[i].nxt)
    {
        cur[u] = i;
        int v = e[i].v, w = e[i].w;
        if (w && dep[v] == dep[u] + 1)
        {
            res = dfs(v, min(w, in));
            e[i].w -= res, e[i ^ 1].w += res;
            in -= res, out += res;
        }
    }
    if (!out)
        dep[u] = 0;
    return out;
}

int main()
{
    freopen("output.txt", "w", stdout);
    scanf("%d%d%d", &n, &p, &q);
    s = 0, t = n * 2 + p + q + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1, a; j <= p; j++)
        {
            scanf("%d", &a);
            if (a)
                add(j, i + p, 1), add(i + p, j, 0);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1, a; j <= q; j++)
        {
            scanf("%d", &a);
            if (a)
                add(i + n + p, j + n * 2 + p, 1), add(j + n * 2 + p, i + n + p, 0);
        }
    for (int i = 1; i <= p; i++)
        add(s, i, 1), add(i, s, 0);
    for (int i = 1; i <= n; i++)
        add(i + p, i + p + n, 1), add(i + p + n, i + p, 0);
    for (int i = 1; i <= q; i++)
        add(i + p + n * 2, t, 1), add(t, i + p + n * 2, 0);
    while (bfs())
        ans += dfs(s, 1e9);
    return printf("%d", ans), 0;
}