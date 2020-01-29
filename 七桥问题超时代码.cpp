#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
struct edge {
	int destnation;
	edge* next;
};
struct point {
	edge* next;
};
int N, M, du[1001] = { 0 }, visit[1001];
point G[1001] = { 0 };

void creat() {
	cin >> N >> M;
	int source, dest;
	for (int i = 1; i <= M; i++) {
		cin >> source >> dest;
		du[dest]++;
		du[source]++;
		if (G[source].next == NULL) {
			G[source].next = new edge;
			G[source].next->next = NULL;
			G[source].next->destnation = dest;
		}
		else {
			edge* tmp = G[source].next;
			while (tmp->next != NULL)tmp = tmp->next;
			tmp->next = new edge;
			tmp->next->next = NULL;
			tmp->next->destnation = dest;
		}
	}
}

void Visit(int n) {
	visit[n] = 1;
	edge* tmp = G[n].next;
	G[n].next = NULL;
	while (tmp) {
		Visit(tmp->destnation);
		tmp = tmp->next;
	}
}

bool Judge() {
	Visit(1);
	for (int i = 1; i <= N; i++) {
		if (visit[i] == 0 || du[i]%2 != 0)
			return false;
	}
	return true;
}

int main() {
	creat();
	if (Judge())cout << 1;
	else cout << 0;
}