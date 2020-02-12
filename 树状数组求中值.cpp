#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
#include <string>
using namespace std;
const int maxn = 1e+5 + 1;
int c[maxn] = { 0 };
stack<int> s;
//����ó���֮��صĽ��
int lowbit(int i) {
	return (i & (-i));
}
//��Ӧ��λ��+1������Ӧλ�ô�������ж��ٸ������ϲ�������Ϊ�˽��ǰ�ж�������
void updata(int x, int v) {
	for (int i = x; i < maxn; i += lowbit(i)) 
		c[i] += v;
}
//ͳ�Ƹýڵ�֮ǰ�ж�������
int getnum(int x) {
	int sum = 0;
	for (int i = x; i >= 1; i -= lowbit(i))
		sum += c[i];
	return sum;
}
//���ֲ��ң�ֱ������ȥ���midΨһ��mid����Ϊmidǰ�ж���������mid����ջ��Ԫ�ص�һ��ʱ����ָ�����ƣ�����mid��������ָ�����ƣ�ֱ�������ཻ����ʱ��ָ�뼴Ϊmid������m��ָ��
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