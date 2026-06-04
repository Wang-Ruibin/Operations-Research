#include <bits/stdc++.h>
using namespace std;
int num, cnt, sum;
int head[5001], minn[5001];
bool vis[5001];
struct edge
{
	int next, v, w;
} e[400005];
void lian(int from, int to, int div)
{
	e[++num].next = head[from];
	e[num].v = to;
	e[num].w = div;
	head[from] = num;
}
typedef pair<int, int> p;
priority_queue<p, vector<p>, greater<p>> q;
int main()
{
	freopen("output.txt", "w", stdout);
	int n, m, x, y, z;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> x >> y >> z;
		lian(x, y, z);
		lian(y, x, z);
	}
	memset(minn, 0x7f, sizeof(minn));
	minn[1] = 0;
	q.push(make_pair(0, 1));
	while (!q.empty() && cnt < n)
	{
		int b = q.top().first, d = q.top().second;
		q.pop();
		if (vis[d])
			continue;
		++cnt;
		sum += b;
		vis[d] = true;
		for (int i = head[d]; i != 0; i = e[i].next)
			if (minn[e[i].v] > e[i].w)
			{
				minn[e[i].v] = e[i].w;
				q.push(make_pair(minn[e[i].v], e[i].v));
			}
	}
	cout << sum;
	return 0;
}
