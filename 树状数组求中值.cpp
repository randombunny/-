#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
#include <string>
using namespace std;
const int maxn = 1e+5 + 1;
int c[maxn] = { 0 };
stack<int> s;
//计算得出与之相关的结点
int lowbit(int i) {
	return (i & (-i));
}
//对应的位置+1，即对应位置储存的是有多少该数，上层结点意义为此结点前有多少数字
void updata(int x, int v) {
	for (int i = x; i < maxn; i += lowbit(i)) 
		c[i] += v;
}
//统计该节点之前有多少数字
int getnum(int x) {
	int sum = 0;
	for (int i = x; i >= 1; i -= lowbit(i))
		sum += c[i];
	return sum;
}
//二分查找，直到给定去点的mid唯一（mid含义为mid前有多少数），mid多于栈中元素的一半时，右指针左移，减少mid，否则左指针右移；直到左右相交，此时右指针即为mid，返回m右指针
void PeekMedian() {
	int left = 1, right = maxn, k = (s.size() + 1) >> 1;
	while (right > left) {
		int mid = (left + right) >> 1;
		if (getnum(mid) >= k) right = mid;
		else left = mid + 1;
	}
	printf("%d\n", right);
}
int main() {
	int n, m;
	string str;
	scanf("%d", &n);
	while (n--) {
		cin >> str;
		if (str == "Pop") {
			if (s.empty()) printf("Invalid\n");
			else {
				updata(s.top(), -1);
				printf("%d\n", s.top());
				s.pop();
			}
		}
		else if (str == "Push") {
			scanf("%d", &m);
			s.push(m);
			updata(m, 1);
		}
		else {
			if (s.empty()) printf("Invalid\n");
			else PeekMedian();
		}
	}
	return 0;
}