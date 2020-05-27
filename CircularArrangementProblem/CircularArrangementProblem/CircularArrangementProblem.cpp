#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

class Circle {
private:
	//圆总数
	int N;
	//最小圆排列长度
	double minlen = 100000;
	//各圆心横坐标
	double *x;
	//各圆半径
	double *r;
	//最小圆排列的半径顺序
	double *bestr;
	//计算最小圆排列长度
	void compute()
	{
		double low = 0, high = 0;
		for (int i = 0; i < N; ++i)
		{
			if (x[i] - r[i] < low)
				low = x[i] - r[i];
			if (x[i] + r[i] > high)
				high = x[i] + r[i];
		}
		if (high - low < minlen)
		{
			minlen = high - low;
			for (int i = 0; i < N; ++i)
				bestr[i] = r[i];
		}
	}
	double center(int t)//得到每个圆的圆心坐标
	{
		double temp = 0;
		double xvalue;
		for (int i = 0; i < t; ++i)
		{
			//随意取一圆相切，计算圆X坐标
			xvalue = x[i] + 2.0*sqrt(r[t] * r[i]);
			if (xvalue > temp) {
				temp = xvalue;
			}
		}
		return temp;
	}
	void backtrack(int t)
	{
		if (t == N)
		{
			compute();
		}
		else
		{
			//计算当前最优排列长度
			for (int i = t; i < N; ++i)
			{
				swap(r[t], r[i]);
				double centerx = center(t);
				//剪枝条件
				if (centerx + r[t] + r[0] < minlen)
				{
					x[t] = centerx;
					backtrack(t + 1);
				}
				swap(r[t], r[i]);//回溯，开始下一种排列
			}
		}
	}
public:
	Circle() {};
	Circle(int _N,  double *_r) {
		this->N = _N;
		this->x = (double *)malloc(sizeof(double)*_N);
		this->r = _r;
		this->bestr = (double *)malloc(sizeof(double)*_N);
	}
	void calculate() {
		backtrack(0);
		cout << "最小圆排列长度为：" << minlen << endl;
		cout << "最优圆排列的顺序对应的半径分别为：";
		for (int i = 0; i < N; ++i) {
			cout << bestr[i];
			if (i==N-1) {
				cout << endl;
			}
			else {
				cout << " ";
			}
		}
	}
};

int main()
{
	int n;
	cout << "请输入待排列圆总数：";
	cin >> n;
	double * r = (double *)malloc(sizeof(double)*n);
	cout << "请输入每个圆的半径：";
	for (int i = 0; i < n;i++) {
		cin >> r[i];
	}
	Circle c = Circle(n, r);
	c.calculate();
	return 0;
}