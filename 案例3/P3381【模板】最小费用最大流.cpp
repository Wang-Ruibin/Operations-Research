#include <bits/stdc++.h>
using namespace std;

const int N = 5001;
const int M = 50001;
int n, m, s, t, dis[N], head[N], cur[N], num = 1, ans, cost;
bool vis[N];
struct edge
{
    int nxt, v, w, cost;
} e[M << 1];

void add(int u, int v, int w, int cost)
{
    e[++num].nxt = head[u];
    e[num].v = v;
    e[num].w = w;
    e[num].cost = cost;
    head[u] = num;
}

bool spfa()
{
    for (int i = 0; i <= n; i++)
        cur[i] = head[i], vis[i] = 0, dis[i] = 1e9;
    dis[s] = 0, vis[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].v, w = e[i].w;
            if (dis[v] > dis[u] + e[i].cost && w)
            {
                dis[v] = dis[u] + e[i].cost;
                if (!vis[v])
                    q.push(v), vis[v] = 1;
            }
        }
    }
    return dis[t] != 1e9;
}

int dfs(int u, int in)
{
    if (u == t)
    {
        vis[t] = 1;
        return in;
    }
    int out = 0, res;
    vis[u] = 1;
    for (int i = cur[u]; i && in; i = e[i].nxt)
    {
        cur[u] = i;
        int v = e[i].v, w = e[i].w;
        if ((!vis[v] || v == t) && w && dis[v] == dis[u] + e[i].cost)
        {
            res = dfs(v, min(in - out, e[i].w));
            cost += e[i].cost * res;
            e[i].w -= res, e[i ^ 1].w += res;
            out += res, in -= res;
            if (out == in)
                break;
        }
    }
    return out;
}

int main()
{
    freopen("output.txt", "w", stdout);
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1, u, v, w, cost; i <= m; i++)
    {
        scanf("%d%d%d%d", &u, &v, &w, &cost);
        add(u, v, w, cost), add(v, u, 0, -cost);
    }
    while (spfa())
    {
        vis[t] = 1;
        while (vis[t])
        {
            memset(vis, 0, sizeof(vis));
            ans += dfs(s, 1e9);
        }
    }
    printf("%d %d", ans, cost);
    return 0;
}