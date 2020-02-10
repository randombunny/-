#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
#define INFINITY 9999999
struct Node {
	int dest;
	int time;
};
Node G[500][500];
int N, M, parent[500] = { 0 }, pass[500], dest[500], _time[500], cnt = 0, tpath[500], dpath[500], Time = 0, Dist = 0;
int S, End, count1 = 0, count2 = 0;
bool visit[500] = { 0 };
void Creat() {
	for (int i = 0; i < N; i++)
		pass[i] = dest[i] = _time[i] = INFINITY;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			G[i][j].dest = G[i][j].time = INFINITY;
	int x, y, w, t, a;
	while (M--) {
		cin >> x >> y >> a >> w >> t;
		if (a) {
			G[x][y].time = t;
			G[x][y].dest = w;
		}
		else {
			G[y][x].time = G[x][y].time = t;
			G[y][x].dest = G[x][y].dest = w;
		}
	}
}
int FindMinTime() {
	int MinTime = INFINITY, index = 0, NowDest = INFINITY;
	for (int i = 0; i < N; i++)
		if (_time[i] < MinTime && visit[i] == false) {
			MinTime = _time[i];
			index = i;
			NowDest = dest[i];
		}
		else if (_time[i] == MinTime && dest[i] < NowDest && visit[i] == false) {
			MinTime = _time[i];
			index = i;
			NowDest = dest[i];
		}
	return index;
}
void DijkstraTime() {
	visit[S] = true;
	dest[S] = _time[S] = 0;
	parent[S] = -1;
	cnt++;
	int Now = S;
	while (cnt < N) {
		for (int i = 0; i < N; i++)
			if (visit[i] == false) {
				if (G[Now][i].time + _time[Now] < _time[i]) {
					dest[i] = G[Now][i].dest + dest[Now];
					_time[i] = G[Now][i].time + _time[Now];
					parent[i] = Now;
				}
				else if (G[Now][i].time + _time[Now] == _time[i] && dest[i] > G[Now][i].dest + dest[Now]) {
					dest[i] = G[Now][i].dest + dest[Now];
					_time[i] = G[Now][i].time + _time[Now];
					parent[i] = Now;
				}
			}
		Now = FindMinTime();
		visit[Now] = true;
		dest[Now] = dest[parent[Now]] + G[parent[Now]][Now].dest;
		_time[Now] = _time[parent[Now]] + G[parent[Now]][Now].time;
		parent[Now] = parent[Now];
		cnt++;
	}
	Time = _time[End];
	stack <int> SS;
	SS.push(End);
	while (parent[SS.top()] != -1)SS.push(parent[SS.top()]);
	SS.pop();
	int i = 0;
	while (SS.size() != 0) {
		tpath[i++] = parent[SS.top()];
		SS.pop();
		count1++;
	}
	tpath[i++] = End;
	count1++;

}

int FindMinDest() {
	int MinTime = INFINITY, index = 0, Nowpass = INFINITY;
	for (int i = 0; i < N; i++)
		if (_time[i] < MinTime && visit[i] == false) {
			MinTime = _time[i];
			index = i;
			Nowpass = pass[i];
		}
		else if (_time[i] == MinTime && pass[i] < Nowpass && visit[i] == false) {
			MinTime = _time[i];
			index = i;
			Nowpass = pass[i];
		}
	return index;
}
void DijkstraDest() {
	visit[S] = true;
	dest[S] = 0;
	pass[S] = 1;
	parent[S] = -1;
	cnt++;
	int Now = S;
	while (cnt < N) {
		for (int i = 0; i < N; i++)
			if (visit[i] == false) {
				if (G[Now][i].dest + dest[Now] < dest[i]) {
					pass[i] = pass[Now] + 1;
					dest[i] = G[Now][i].dest + dest[Now];
					parent[i] = Now;
				}
				else if (G[Now][i].dest + dest[Now] == dest[i] && pass[i] > pass[Now] + 1) {
					pass[i] = pass[Now] + 1;
					dest[i] = G[Now][i].dest + dest[Now];
					parent[i] = Now;
				}
			}
		Now = FindMinDest();
		visit[Now] = true;
		dest[Now] = dest[parent[Now]] + G[parent[Now]][Now].dest;
		parent[Now] = parent[Now];
		cnt++;
	}
	Dist = dest[End];
	stack <int> SS;
	SS.push(End);
	while (parent[SS.top()] != -1)SS.push(parent[SS.top()]);
	SS.pop();
	int i = 0;
	while (SS.size() != 0) {
		dpath[i++] = parent[SS.top()];
		count2++;
		SS.pop();
	}
	dpath[i++] = End;
	count2++;
}

int main() {
	cin >> N >> M;
	Creat();
	cin >> S >> End;
	DijkstraTime();
	for (int i = 0; i < N; i++)
		pass[i] = dest[i] = _time[i] = INFINITY;
	memset(visit, 0, 500 * sizeof(bool));
	memset(parent, 0, 500 * sizeof(bool));
	cnt = 0;
	DijkstraDest();

	bool flag = true;
	if (count1 == count2) {
		for (int i = 0; i < count1; i++)
			if (tpath[i] != dpath[i]) {
				flag = false;
				break;
			}
	}
	else flag = false;
	if (flag) {
		printf("Time = %d; Distance = %d: ", Time, Dist);
		for (int i = 0; i < count1; i++) {
			cout << tpath[i];
			if (i != count1 - 1)cout << " => ";
		}
	}
	else {
		printf("Time = %d: ", Time);
		for (int i = 0; i < count1; i++) {
			cout << tpath[i];
			if (i != count1 - 1)cout << " => ";
		}
		printf("\n");
		printf("Distance = %d: ", Dist);
		for (int i = 0; i < count2; i++) {
			cout << dpath[i];
			if (i != count2 - 1)cout << " => ";
		}
	}
}