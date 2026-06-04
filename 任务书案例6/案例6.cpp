#include <bits/stdc++.h>
using namespace std;

int f[5001], sum, k;

struct edge
{
    int x, y, w;
} a[200001];

bool cmp(edge a, edge b)
{
    return a.w < b.w;
}
int find(int x)
{
    if (f[x] != x)
        f[x] = find(f[x]);
    return f[x];
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        f[i] = i;
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].w);
    sort(a + 1, a + m + 1, cmp);
    for (int i = 1; i <= m; i++)
    {
        if (f[a[i].x] != f[a[i].y])
        {
            int lx = find(a[i].x);
            int ly = find(a[i].y);
            if (ly != lx)
            {
                f[ly] = lx;
                sum += a[i].w;
                k++;
            }
        }
        if (k == n - 1)
            break;
    }
    printf("%d\n%lf\n", sum, (double)sum * 100 * (double)(10 + 5 + 1 * 0.6 * 3));
    return 0;
}
