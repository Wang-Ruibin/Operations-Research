#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int inf = 0x3f3f3f3f;
const int N = 3005;
int n, m, cnt, head[N], dis[N], d[N], num[N];
bool vis[N];
queue<int> q;

struct edge
{
    int v, w, next;
} e[N << 3];

void add(int u, int v, int w)
{
    e[++cnt].next = head[u];
    e[cnt].v = v;
    e[cnt].w = w;
    head[u] = cnt;
}

bool spfa(int s)
{
    q.push(s);
    dis[s] = 0, vis[s] = 1, num[s]++;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = 0;
        for (int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v, w = e[i].w;
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                if (!vis[v])
                {
                    q.push(v);
                    vis[v] = 1, num[v]++;
                    if (num[v] == n + 1)
                        return false;
                }
            }
        }
    }
    return true;
}

struct pa
{
    int dis, id;
};

bool operator<(pa x, pa y) { return x.dis > y.dis; }

void dijkstra(int s)
{
    priority_queue<pa> p;
    d[s] = 0;
    pa u;
    u.dis = 0, u.id = s;
    p.push(u);
    while (!p.empty())
    {
        pa u = p.top();
        p.pop();
        if (vis[u.id])
            continue;
        vis[u.id] = true;
        for (int i = head[u.id]; i; i = e[i].next)
        {
            int v = e[i].v, w = e[i].w;
            if (d[v] > d[u.id] + w)
            {
                d[v] = d[u.id] + w;
                pa to;
                to.dis = d[v], to.id = v;
                p.push(to);
            }
        }
    }
}

int main()
{
    freopen("output.txt", "w", stdout);
    memset(dis, inf, sizeof(dis));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
    }
    for (int i = 1; i <= n; i++)
        add(n + 1, i, 0);
    if (!spfa(n + 1))
    {
        cout << -1;
        return 0;
    }
    for (int i = 1; i <= n; i++)
        for (int j = head[i]; j; j = e[j].next)
            e[j].w += dis[i] - dis[e[j].v];
    for (int i = 1; i <= n; i++)
    {
        memset(d, inf, sizeof(d));
        memset(vis, false, sizeof(vis));
        dijkstra(i);
        ll ans = 0;
        for (int j = 1; j <= n; j++)
        {
            if (d[j] == inf)
                ans += 1ll * 1e9 * j;
            else
                ans += 1ll * (d[j] - dis[i] + dis[j]) * j;
        }
        printf("%lld\n", ans);
    }
    return 0;
}