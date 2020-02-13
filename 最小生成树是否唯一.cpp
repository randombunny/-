#define _CRT_SECURE_NO_WARNINGS
//1.���ô��涥�㣬û���壬�ṹ��Ϊ�ߣ���һ���Ƿ��ù����Ƿ�ɾ������ʼ���㣬ָ�򶥵㣬Ȩ��
//2.�������Kruskal�㷨��prime�㷨̫�鷳��3.��һ����Kruskal�㷨�����С������Ȩ�أ�������ִ��һ��ѭ��������һ�У� Ȼ�����
//ѭ�����ݣ�ɾ������ͬȨ�صıߣ��ٴν���Kruskal�㷨������С����������Ȩ����ͬ������С��������Ψһ������ɾ���ı߻�ԭ����ȥ����һ������ͬȨ�صıߣ�ֱ�����������б�

//Kruskal�㷨��1.����ߣ������������������2.�����ߣ��������������ڲ�ͬ���ϣ������˱ߵ���С������
//�����������Ƿ�����ͬһ���ϣ���ʼ��ÿ������ĸ��ڵ㶼Ϊ�Լ���Ȼ��findʱ�����Լ��ĸ��ڵ㣬�Ƚ��������ڵ��Ƿ���ͬ�������ڵ�ĸ��ڵ㲻Ϊ�Լ�����ݹ飬ֱ�����ڵ�ĸ��ڵ�Ϊ���ڵ㱾��

#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 502;
int n, m, cnt;
int parent[N];
int flag;
struct edge{
	int u;
	int v;//����
	int w;//Ȩֵ
	int equals;//�Ƿ������ñ�Ȩֵ��ͬ��������
	int used;//�ڵ�һ����õ�MST���Ƿ�����ñߡ�1������0������
	int del;//���Ƿ�ɾ���ı�־
} edg[N];
int  cmp(edge x, edge y){
	return x.w < y.w;
}
void init(){
	int i;
	for (i = 0; i < N; i++){
		parent[i] = i;
	}
}
int Find(int x){
	if (parent[x] != x){
		parent[x] = Find(parent[x]);
	}
	return parent[x];
}//���Ҳ����ؽڵ�x�������ϵĸ��ڵ�
void Union(int x, int y){
	x = Find(x);
	y = Find(y);
	if (x == y){
		return;
	}
	parent[y] = x;
}//��������ͬ���ϵ�Ԫ�ؽ��кϲ�
int Kruskal(){
	init();
	int sum = 0;
	int num = 0;
	for (int i = 0; i < m; i++){
		if (edg[i].del == 1){
			continue;
		}
		int u = edg[i].u;
		int v = edg[i].v;
		int w = edg[i].w;
		if (Find(u) != Find(v)){
			sum += w;
			if (flag){
				edg[i].used = 1;
			}
			num++;
			Union(u, v);
		}
		if (num >= n - 1){
			break;
		}
	}
	if (num < n - 1)return num - (n - 1);
	return sum;
}
int main() {
	int i, j;
	int counts1, counts2, flag2;
	counts1 = 0;
	scanf("%d%d", &n, &m);
	for (i = 0; i < m; i++) {
		scanf("%d%d%d", &edg[i].u, &edg[i].v, &edg[i].w);
		edg[i].del = 0;
		edg[i].used = 0;
		edg[i].equals = 0;//һ��ʼ����ط�eqû�г�ʼ����WA�˺ü���
	}
	//�����ͬȨֵ�ı�
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			if (i == j) {
				continue;
			}
			if (edg[i].w == edg[j].w) {
				edg[i].equals = 1;
			}
		}
	}
	sort(edg, edg + m, cmp);
	flag = 1;
	counts1 = Kruskal();//��1����MST
	if (counts1 < 0) {
		printf("No MST\n%d", -counts1 + 1);
		return 0;
	}
	flag = 0;
	flag2 = 1;
	for (j = 0; j < m; j++) {
		//�ڵ�һ��MST�а����ñߣ����Ҹñ߾���Ȩֵ��ͬ�ı�
		if (edg[j].used && edg[j].equals) {
			edg[j].del = 1;//ɾ�����ñߣ����еڶ���MST
			counts2 = Kruskal();//printf("%d %d\n",i,s);
			if (counts2 == counts1) {
				flag2 = 0;
				break;
			}
			edg[j].del = 0;//�ָ���ɾ���ı�
		}
	}
	printf("%d\n", counts1);
	if (flag2)cout << "Yes" << endl;
	else cout << "No" << endl;
	return 0;
}