#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 10001;
int cur[N << 1], head[N << 1], num = 1, n, m, s, t, ans, dep[N];
bool vis[N];
struct edge
{
    int v, nxt, w;
} e[200010];

void add(int u, int v, int w)
{
    e[++num].nxt = head[u];
    e[num].v = v;
    e[num].w = w;
    head[u] = num;
}

bool bfs()
{
    for (int i = s; i <= t; i++)
        cur[i] = head[i], vis[i] = 0, dep[i] = 0;
    queue<int> q;
    q.push(s);
    dep[s] = 1;
    vis[s] = 1;
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
    if (out == 0)
        dep[u] = 0;
    return out;
}

signed main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%lld%lld%lld%lld", &n, &m, &s, &t);
    int cnt = 0;
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%lld%lld%lld", &u, &v, &w);
        add(u, v, w), add(v, u, 0);
        if (v == t || u == t)
            cnt += w;
    }
    while (bfs())
        ans += dfs(s, 1e18);
    printf("%lld\n", ans);
    if (cnt != ans)
        puts("NO");
    else
        puts("YES");
    return 0;
}