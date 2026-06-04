#include <bits/stdc++.h>
#define int long long
#define ls (k << 1)
#define rs (k << 1 | 1)
using namespace std;

const int N = 1e6 + 5;
const int inf = 1e18;
int n, m, cnt, num, dep[N], siz[N], f[N], son[N], id[N], a[N], w[N], top[N], head[N];
int fat[N], maxnn;
bool vis[N];
struct edge
{
    int u, v, w, nxt;
} e[N << 1];
struct bian
{
    int u, v, w;
} b[N << 1];

void add(int u, int v, int w)
{
    e[++num].nxt = head[u];
    e[num].v = v;
    e[num].u = u;
    e[num].w = w;
    head[u] = num;
}

inline int read()
{
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch))
    {
        w |= ch == '-', ch = getchar();
    }
    while (isdigit(ch))
        X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}

struct TREE
{
    struct Tree
    {
        int l, r, max;
    } t[N << 2];

    void pushup(int k)
    {
        t[k].max = max(t[ls].max, t[rs].max);
    }

    void build(int l, int r, int k)
    {
        t[k].l = l, t[k].r = r;
        if (l == r)
        {
            t[k].max = w[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, ls);
        build(mid + 1, r, rs);
        pushup(k);
    }

    int findmax(int l, int r, int k)
    {
        int ans = -1;
        if (t[k].l >= l && t[k].r <= r)
            return t[k].max;
        int mid = (t[k].l + t[k].r) >> 1;
        if (l <= mid)
            ans = max(ans, findmax(l, r, ls));
        if (r > mid)
            ans = max(ans, findmax(l, r, rs));
        return ans;
    }

    int findsmax(int l, int r, int k)
    {
        int ans = -1;
        if (t[k].l >= l && t[k].r <= r)
            return t[k].max;
        int mid = (t[k].l + t[k].r) >> 1, aa;
        if (l <= mid)
        {
            aa = findsmax(l, r, ls);
            if (aa < maxnn)
                ans = max(ans, aa);
        }
        if (r > mid)
        {
            aa = findsmax(l, r, rs);
            if (aa < maxnn)
                ans = max(ans, aa);
        }
        return ans;
    }
} T;

int find(int x) { return fat[x] == x ? x : fat[x] = find(fat[x]); }

bool cmp(bian x, bian y) { return x.w < y.w; }

void dfs1(int x, int fa, int deep)
{
    f[x] = fa, dep[x] = deep, siz[x] = 1;
    int mson = -1;
    for (int i = head[x]; i; i = e[i].nxt)
    {
        int v = e[i].v;
        if (v == fa)
            continue;
        dfs1(v, x, deep + 1);
        a[v] = e[i].w;
        siz[x] += siz[v];
        if (siz[v] > mson)
            mson = siz[v], son[x] = v;
    }
}

void dfs2(int x, int topf)
{
    top[x] = topf, id[x] = ++cnt, w[cnt] = a[x];
    if (!son[x])
        return;
    dfs2(son[x], topf);
    for (int i = head[x]; i; i = e[i].nxt)
    {
        int v = e[i].v;
        if (v == f[x] || v == son[x])
            continue;
        dfs2(v, v);
    }
}

int querymax(int x, int y)
{
    int ans = -1;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ans = max(ans, T.findmax(id[top[x]], id[x], 1));
        x = f[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    ans = max(ans, T.findmax(id[x] + 1, id[y], 1));
    return ans;
}

int querysmax(int x, int y)
{
    int ans = -1;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ans = max(ans, T.findsmax(id[top[x]], id[x], 1));
        x = f[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    ans = max(ans, T.findsmax(id[x] + 1, id[y], 1));
    return ans;
}

signed main()
{
    freopen("output.txt", "w", stdout);
    n = read(), m = read();
    for (int i = 1; i <= m; i++)
        b[i].u = read(), b[i].v = read(), b[i].w = read();
    for (int i = 1; i <= n; i++)
        fat[i] = i;
    sort(b + 1, b + 1 + m, cmp);
    int tim = 0, sum = 0, ans = 0;
    for (int i = 1; i <= m; i++)
    {
        if (tim == n - 1)
            break;
        int u = b[i].u, v = b[i].v, w = b[i].w;
        int xx = find(u), yy = find(v);
        if (xx != yy)
        {
            fat[xx] = yy;
            tim++;
            add(u, v, w), add(v, u, w);
            vis[i] = 1;
            sum += w;
        }
    }
    ans = sum;
    dfs1(1, 0, 1), dfs2(1, 1);
    T.build(1, n, 1);
    for (int i = 1; i <= m; i++)
    {
        if (vis[i])
            continue;
        int u = b[i].u, v = b[i].v, w = b[i].w;
        int max = querymax(u, v);
        maxnn = max;
        int smax = querysmax(u, v);
        if (max == w)
        {
            if (ans == sum)
                ans = sum - smax + w;
            else
                ans = min(ans, sum - smax + w);
        }
        else
        {
            if (ans == sum)
                ans = sum - max + w;
            else
                ans = min(ans, sum - max + w);
        }
    }
    printf("%lld\n", ans);
    return 0;
}