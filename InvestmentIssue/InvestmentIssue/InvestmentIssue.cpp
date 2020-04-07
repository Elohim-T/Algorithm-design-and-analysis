#include <iostream>
#include <vector>

using namespace std;

int main() {

	int m, n;//m元钱，n项投资
	int i, j;
	int tmp_m, tmp_F = 0;
	cout << "请输入投资金额和项目数" << endl;
	cin >> m >> n;
	vector<vector<int>> f(n, vector<int>(m + 1));//f[i][x], 0<i<=n,0<=x<=m；
	vector<vector<int>> F(n, vector<int>(m + 1));//F[i][x]，将x元钱投入到前i个项目上最大的收益
	
	//在第(i+1)个项目上投入0元，收益为0，注意i从0开始
	for (i = 0; i < n; i++) {
		f[i][0] = 0;
	}
	cout << "请输入各项目对应投资金额的收益（从1开始）" << endl;
	for (i = 0; i < n; i++) {
		for (j = 1; j < m + 1; j++) {
			cin >> f[i][j];
		}
	}
	//初始化，给F[0][0-m]赋值
	for (j = 0; j < m + 1; j++) {
		F[0][j] = f[0][j];//第一个项目上投入0-m元钱的最大收益等于f[0][0-m]
	}

	for (i = 1; i < n; i++) {//项目编号，从1开始
		for (j = 0; j < m + 1; j++) {//钱数,从0开始
			for (tmp_m = 0; tmp_m <= j; tmp_m++) {
				//递推公式
				tmp_F = F[i - 1][j - tmp_m] + f[i][tmp_m];
				//取最大值
				if (tmp_F > F[i][j]) {
					F[i][j] = tmp_F;
				}	
			}
		}
	}
	cout << "最大总收益: " << F[n - 1][m] << endl;
}