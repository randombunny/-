#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
using namespace std;
struct Node {
	char name[4];
	int arrival;
	int need;
	int wait;
	int leave;
	Node* next = NULL;
	Node* Friend;
};

char Friend[100][100][4] = { 0 };
Node* head = new Node;
int N;
int moments, num[100];//朋友圈的个数,每个朋友圈的人数

void CreatFriend() {
	cin >> moments;
	for (int i = 0; i < moments; i++) {
		cin >> num[i];
		for (int j = 0; j < num[i]; j++) {
			cin >> Friend[i][j];
		}
	}
}

void Renew(Node* head) {
	while (head->next) {
		head->next->wait = head->leave - head->next->arrival;
		if (head->next->wait < 0)head->next->wait = 0;
		Node* tmp = head->next;
		int sum = 0;
		sum += tmp->arrival + tmp->wait + tmp->need;
		while (tmp->Friend) {
			sum += tmp->Friend->need;
			tmp->Friend->leave = sum;
			tmp->Friend->wait = tmp->Friend->leave - tmp->Friend->need - tmp->Friend->arrival;
			tmp = tmp->Friend;
		}
		head->next->leave = sum;
		head = head->next;
	}
}

void Output() {
	int sum = 0;
	while (head->next) {
		printf("%s\n", head->next->name);
		Node* tmp = head->next;
		sum += tmp->wait;
		while (tmp->Friend) {
			printf("%s\n", tmp->Friend->name);
			sum += tmp->Friend->wait;
			tmp = tmp->Friend;
		}
		head = head->next;
	}
	printf("%.1f", sum / (double)N);
}

void CreatQueue(char s[4], int arrival, int need) {
	bool flag = false;
	int i, j;
	for (i = 0; i < moments; i++) {
		for (j = 0; j < num[i]; j++) {
			if (strcmp(Friend[i][j], s) == 0) {
				flag = true;
				break;
			}
		}
		if (flag)break;
	}
	Node* tmp = head;
	while (tmp->next) {
		if (arrival <= tmp->next->leave) {
			if (flag) {
				for (int x = 0; x < num[i]; x++) {
					if (strcmp(Friend[i][x], tmp->next->name) == 0 && tmp->next->leave >= arrival) {
						tmp = tmp->next; //将tmp置为tmp.next为接下来找tmp的Friend的末尾做准备
						Node* tmp1 = tmp;//为下面的更新做准备
						int sum = 0;//区分next的等待时间，与Friend的等待时间
						tmp->leave += need;
						sum += tmp->arrival + tmp->wait + tmp->need;
						while (tmp->Friend) {
							sum += tmp->Friend->need;
							tmp = tmp->Friend;
						}
						tmp->Friend = new Node;
						strcpy(tmp->Friend->name, s);
						tmp->Friend->arrival = arrival;
						tmp->Friend->need = need;
						tmp->Friend->next = NULL;
						tmp->Friend->Friend = NULL;
						tmp->Friend->wait = sum - tmp->Friend->arrival;
						tmp->Friend->leave = tmp->Friend->arrival + tmp->Friend->wait + tmp->Friend->need;
						Renew(tmp1);
						return;
					}
				}
			}
		}
		tmp = tmp->next;
	}
	tmp->next = new Node;
	strcpy(tmp->next->name, s);
	tmp->next->arrival = arrival;
	tmp->next->need = need;
	tmp->next->Friend = NULL;
	tmp->next->next = NULL;
	tmp->next->wait = tmp->leave - tmp->next->arrival;
	if (tmp->next->wait < 0)tmp->next->wait = 0;
	tmp->next->leave = tmp->next->arrival + tmp->next->need + tmp->next->wait;
}

int main() {
	head->next = NULL;
	head->Friend = NULL;
	head->leave = 0;
	cin >> N;
	CreatFriend();
	char s[4];
	int arrival, need;
	for (int i = 0; i < N; i++) {
		cin >> s >> arrival >> need;
		if (need > 60)need = 60;
		CreatQueue(s, arrival, need);
	}
	Output();
}