#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

class Color{
private:
	//图的顶点数
	int n;
	//可用的颜色数
	int m;
	//图的邻接矩阵
	int **a;
	//当前解
	int *x;
	//当前已找到的可m着色方案数
	long sum;
	// 检查颜色可用性
	bool isOk(int k) {
		for (int j = 1; j <= n; j++)
		{
			if ((a[k][j] == 1) && (x[j] == x[k])) //相邻且颜色相同
			{
				return false;
			}
		}
		return true;
	}
	void Backtrack(int t) {
		//t为当前节点，若大于总点数，则表示当前结果已计算完，进行输出
		if (t > n)
		{
			sum++;
			for (int i = 1; i <= n; i++) {
				cout << x[i] << " ";
			}
			cout << endl;
		}
		else
		{
			//为当前节点进行依次上色，并判断
			for (int i = 1; i <= m; i++)
			{
				x[t] = i;
				if (isOk(t)) {
					//根据当前上色结果，进行下一次上色
					Backtrack(t + 1);
				}
				//抹去上色结果，回溯
				x[t] = 0;
			}
		}
	}
	
public:
	friend int mColoring(int n, int m, int **a);
};
int mColoring(int n, int m, int **a) {
	Color X;

	//初始化X
	X.n = n;
	X.m = m;
	X.a = a;
	X.sum = 0;
	//初始化当前解空间
	int *p = new int[n + 1];
	for (int i = 0; i <= n; i++)
	{
		p[i] = 0;
	}
	X.x = p;
	X.Backtrack(1);
	delete[]p;
	return X.sum;
}

int main()
{
	int N, M;
	cout << "请输入图的顶点数和色彩数：" << endl;
	cin >> N >> M;
	int **a = new int *[N + 1];
	for (int i = 1; i <= N; i++)
	{
		a[i] = new int[N + 1];
	}


	cout << "请输入图的邻接矩阵:" << endl;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> a[i][j];


		}
	}

	cout << "图的M着色方案如下：" << endl;
	cout << "当m=" << M << "时，图G的可行着色方案数目为：" << mColoring(N, M, a) << endl;
	for (int i = 1; i <= N; i++)
	{
		delete[] a[i];
	}
	delete[]a;
}
/* 样例
5 3
0 1 1 1 0
1 0 1 1 1
1 1 0 1 0
0 1 1 0 1
0 1 0 1 0
*/
/* 结果
6种
1 2 3 1 3
1 3 2 1 2
2 1 3 2 3
2 3 1 2 1
3 1 2 3 2
3 2 1 3 1

*/




