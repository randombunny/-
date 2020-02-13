#define _CRT_SECURE_NO_WARNINGS
//1.不用储存顶点，没意义，结构体为边：第一次是否被用过，是否被删除，起始顶点，指向顶点，权重
//2.这道题用Kruskal算法，prime算法太麻烦，3.第一次用Kruskal算法求出最小生成树权重，接下来执行一个循环（见下一行） 然后结束
//循环内容：删除有相同权重的边，再次进行Kruskal算法生成最小生成树，若权重相同，则最小生成树不唯一，否则将删除的边还原，再去找下一个有相同权重的边，直到遍历完所有边

//Kruskal算法：1.输入边，并对其进行排序（升序）2.遍历边，若两个顶点属于不同集合，则加入此边到最小生成树
//查两个顶点是否属于同一集合：初始化每个顶点的父节点都为自己，然后find时返回自己的父节点，比较两个父节点是否相同，若父节点的父节点不为自己，则递归，直到父节点的父节点为父节点本身

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
	int v;//顶点
	int w;//权值
	int equals;//是否存在与该边权值相同的其他边
	int used;//在第一次求得的MST中是否包含该边。1包含，0不包含
	int del;//边是否删除的标志
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
}//查找并返回节点x所属集合的根节点
void Union(int x, int y){
	x = Find(x);
	y = Find(y);
	if (x == y){
		return;
	}
	parent[y] = x;
}//将两个不同集合的元素进行合并
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
		edg[i].equals = 0;//一开始这个地方eq没有初始化，WA了好几发
	}
	//标记相同权值的边
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
	counts1 = Kruskal();//第1次求MST
	if (counts1 < 0) {
		printf("No MST\n%d", -counts1 + 1);
		return 0;
	}
	flag = 0;
	flag2 = 1;
	for (j = 0; j < m; j++) {
		//在第一次MST中包含该边，并且该边具有权值相同的边
		if (edg[j].used && edg[j].equals) {
			edg[j].del = 1;//删除掉该边，进行第二次MST
			counts2 = Kruskal();//printf("%d %d\n",i,s);
			if (counts2 == counts1) {
				flag2 = 0;
				break;
			}
			edg[j].del = 0;//恢复被删掉的边
		}
	}
	printf("%d\n", counts1);
	if (flag2)cout << "Yes" << endl;
	else cout << "No" << endl;
	return 0;
}