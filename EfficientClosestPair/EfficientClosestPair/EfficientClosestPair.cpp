#include <ctime>
#include <cmath>
#include <iostream>  
#include <algorithm>

using namespace std;

#define INFINITE_DISTANCE 65535    // 无限大距离
#define COORDINATE_RANGE 100    // 横纵坐标范围为[-100,100]

#ifndef Closest_pair

typedef struct Point
{// 二维坐标上的点Point
	double x;
	double y;
}Point;

double Distance(Point a, Point b)
{//平面上任意两点对之间的距离公式计算
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

bool compareX(Point a, Point b)
{//自定义排序规则：依照结构体中的x成员变量升序排序
	return a.x < b.x;
}

bool compareY(Point a, Point b)
{//自定义排序规则：依照结构体中的x成员变量升序排序
	return a.y < b.y;
}

double min(int a, int b) {
	return a < b ? a : b;
}

double ClosestPair(Point P[], Point Q[], int length, Point &a, Point &b)
{// 求出最近点对记录，并将两点记录再a、b中
	double dminsq,d;                   //记录集合points中最近两点距离 
	double d1, d2;                     //记录分割后两个子集中各自最小点对距离
	int i = 0, j = 0, k = 0, x = 0;    //用于控制for循环的循环变量
	Point a1, b1, a2, b2;              //保存分割后两个子集中最小点对
	
	if (length < 2)
		return INFINITE_DISTANCE;    //若子集长度小于2，定义为最大距离，表示不可达
	else if (length == 2)
	{//若子集长度等于2，直接返回该两点的距离
		a = P[0];
		b = P[1];
		dminsq = Distance(P[0], P[1]);
		return dminsq;
	}
	else if (length == 3) {
		a = P[0];
		b = P[1];
		dminsq = Distance(P[0], P[1]);
		if (Distance(P[1], P[2])< dminsq) {
			a = P[1];
			b = P[2];
			dminsq = Distance(P[1], P[2]);
		}
		if (Distance(P[2], P[0]) < dminsq) {
			a = P[0];
			b = P[2];
			dminsq = Distance(P[0], P[2]);
		}
		return dminsq;
	}
	else {
		//子集长度大于3，进行分治求解
		Point *P1 = new Point[length];     //开辟4个子集
		Point *P2 = new Point[length];
		Point *Q1 = new Point[length];
		Point *Q2 = new Point[length];
		
		

		for (i = 0; i < length / 2; i++)
			P1[i] = P[i];
		for (int j = 0, i = length / 2; i < length; i++)
			P2[j++] = P[i];

		for (i = length / 2; i < length / 2; i++)
			Q1[i] = Q[i];
		for (int j = 0, i = length / 2; i < length; i++)
			Q2[j++] = Q[i];

		d1 = ClosestPair(P1, Q1,length / 2, a1, b1);             //分治求解左半部分子集的最近点  
		d2 = ClosestPair(P2, Q2,length - length / 2, a2, b2);    //分治求解右半部分子集的最近点  
		
		//记录最近点，最近距离
		if (d1 < d2) {
			d = d1; a = a1; b = b1; 
		}            
		else {
			d = d2; a = a2; b = b2; 
		}
		double mid = P[(length / 2) - 1].x;    //中间下标值，即中位数

		Point *S = new Point[length];
		for (i = 0,j=0; i < length; i++) {
			if (fabs(Q[i].x - mid) < d) {
				S[j++].x = Q[i].x;
				S[j].y = Q[i].y;
			}
		}
		dminsq = d * d;

		for (i = 0; i < j-2; i++)
		{
			for (k = i + 1; k <= j - 1 && (S[k].y - S[i].y)*(S[k].y - S[i].y) < dminsq; k++)
			{
				if (dminsq > Distance(S[k], S[i])) {
					dminsq = Distance(S[k], S[i]);
					a = S[i];
					b = S[k];
				}
			}
		}
		return sqrt(dminsq);
	}
	
}

void SetPoints(Point *points, int length)
{//随机函数对点数组points中的二维点进行初始化
	srand(unsigned(time(NULL)));
	for (int i = 0; i < length; i++)
	{
		points[i].x = (rand() % int(COORDINATE_RANGE * 2)) - COORDINATE_RANGE;
		points[i].y = (rand() % int(COORDINATE_RANGE * 2)) - COORDINATE_RANGE;
	}
}

int main()
{
	int num;            //随机生成的点对个数
	Point a, b;            //最近点对
	double diatance;    //点对距离

	cout << "请输入二维点对个数:";
	cin >> num;
	if (num < 2)
		cout << "请输入大于等于2的点个数！！" << endl;
	else
	{
		cout << endl << "随机生成的" << num << "个二维点对如下：" << endl;
		Point *points = new Point[num];
		Point *pointsY = new Point[num];
		SetPoints(points, num);

		memcpy(pointsY, points, sizeof(Point)*num);

		for (int i = 0; i < num; i++)
			cout << "(" << points[i].x << "," << points[i].y << ")" << endl;

		sort(points, points + num, compareX);
		cout << endl << endl << "按横坐标排序后的点对:" << endl;
		for (int i = 0; i < num; i++)
			cout << "(" << points[i].x << "," << points[i].y << ")" << endl;
		
		sort(pointsY, pointsY + num, compareY);
		cout << endl << endl << "按纵坐标排序后的点对:" << endl;
		for (int i = 0; i < num; i++)
			cout << "(" << pointsY[i].x << "," << pointsY[i].y << ")" << endl;

		diatance = ClosestPair(points,pointsY, num, a, b);

		cout << endl << "最近点对为：" << "(" << a.x << "," << a.y << ")和" << "(" << b.x << "," << b.y << ")" << endl << "最近点对距离为：" << diatance << endl;
	}
	system("pause");
}

#endif // !Closest_pair