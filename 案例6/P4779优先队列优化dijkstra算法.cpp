#include <bits/stdc++.h>
using namespace std;
int num, head[100001], k, minn[100001], minx, tot;
bool vis[100001];
struct edge
{
	int next, v, dis;
} e[200001];
void lian(int u, int v, int dis)
{
	e[++num].next = head[u];
	e[num].v = v;
	e[num].dis = dis;
	head[u] = num;
}
typedef pair<int, int> p;
priority_queue<p, vector<p>, greater<p>> q;
int main()
{
	freopen("output.txt", "w", stdout);
	int n, m, s, x, y, z;
	cin >> n >> m >> s;
	for (int i = 1; i <= m; i++)
	{
		cin >> x >> y >> z;
		lian(x, y, z);
	}
	for (int i = 1; i <= n; i++)
		minn[i] = 2147483647;
	minn[s] = 0;
	q.push(make_pair(0, s));
	while (!q.empty() && tot < n)
	{
		int b = q.top().first;
		int d = q.top().second;
		q.pop();
		if (vis[d])
			continue;
		tot++;
		vis[d] = true;
		for (int i = head[d]; i != 0; i = e[i].next)
		{
			if (minn[e[i].v] > b + e[i].dis)
			{
				minn[e[i].v] = b + e[i].dis;
				q.push(make_pair(minn[e[i].v], e[i].v));
			}
		}
	}
	for (int i = 1; i <= n; i++)
		cout << minn[i] << " ";
	return 0;
}
