#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#define max 10000
typedef struct Edge* edge;
struct Edge {
	int num;
	int from;
	int to;
	int time;
	edge next;
};
struct Node {
	int num;
	edge fe; //fistedge
}node[102];
int es[102] = { 0 },last[102] , ls[1002], Nv, Ne, in[102] = { 0 }, topu[102];
void creat() {
	scanf("%d %d", &Nv, &Ne);
	for (int i = 1; i <= Nv; i++) {
		node[i].fe = NULL;
		node[i].num = i;
		last[i] = max;
	}
	for (int i = 1; i <= Ne; i++) {
		edge tmp = new struct Edge;
		ls[i] = max;
		tmp->num = i;
		tmp->next = NULL;
		scanf("%d %d %d", &tmp->from, &tmp->to, &tmp->time);
		in[tmp->to] = in[tmp->to] + 1;
		edge t = node[tmp->from].fe;
		if (t == NULL)node[tmp->from].fe = tmp;
		else {
			while (t->next)t = t->next;
			t->next = tmp;
		}
	}
}
bool tuopu() {
	int flag = 0;
	int i,count = 1;
	for (i = 1; i <= Nv; i++) {
		if (in[i] == 0) {
			flag = 1;
			topu[count++] = i;
			in[i] = -1;
			break;
		}
	}
	while (flag) {
		edge tmp = node[i].fe;
		while (tmp) {
			in[tmp->to]--;
			tmp = tmp->next;
		}
		flag = 0;
		for (i = 1; i <= Nv; i++) {
			if (in[i] == 0) {
				flag = 1;
				topu[count++] = i;
				in[i] = -1;
				break;
			}
		}
	}
	
	if (--count < Nv)return false;
	else return true;
}
void output() {
	for (int i = 1; i <= Nv; i++) {
		edge tmp = node[topu[i]].fe;
		while (tmp) {
			if (es[tmp->to] < es[tmp->from] + tmp->time)
				es[tmp->to] = es[tmp->from] + tmp->time;
			tmp = tmp->next;
		}
	}
	last[topu[Nv]] = es[topu[Nv]];
	for (int i = Nv; i >0; i--) {
		for (int j = 1; j <= Nv; j++) {
			edge tmp = node[topu[j]].fe;
			while (tmp) {
				if (tmp->to == i) {
					ls[tmp->num] = last[i] - tmp->time;
					if (last[tmp->from] > ls[tmp->num])
						last[tmp->from] = ls[tmp->num];
				}
				tmp = tmp->next;
			}
		}
	}

	printf("%d\n", es[topu[Nv]]);

	for (int i = 1; i <= Nv; i++) {
		edge tmp = node[topu[i]].fe;
		while (tmp) {
			if (ls[tmp->num] == es[tmp->from])printf("%d->%d\n", tmp->from, tmp->to);
			tmp = tmp->next;
		}
	}

}
int main() {
	creat();

	if (tuopu()) {
		output();
	}
	else printf("0");
}