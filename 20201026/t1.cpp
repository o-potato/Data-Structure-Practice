#include<iostream>
#include<vector>
#include<stack>
using namespace std;

int min(int a, int b) {
	return a < b ? a : b;
}

//递归方法
int leastPress(int N, int S, int E, vector<vector<int> > K) {
	int res = 0;
	
	//Both going up and going down are invalid
	if (K[S - 1][0] == 0 && K[S - 1][1] == 0)
		return -1;

	//Reach E
	if (S + K[S - 1][0] == E || S + K[S - 1][1] == E)
		return ++res;

	//To judge if going up or going down is valid
	if (S + K[S - 1][0] > N)
		K[S - 1][0] = 0;
	if (S + K[S - 1][1] <= 0)
		K[S - 1][1] = 0;

	//Only going down is valid
	if (K[S - 1][0] == 0 && K[S - 1][1] ) {
		int Sdown = S + K[S - 1][1];
		K[S - 1][1] = 0;
		res = leastPress(N, Sdown, E, K) + 1;

		if (res == 0) return -1;
		return res;
	}
	//Only going up is valid
	if (K[S - 1][0] && K[S - 1][1] == 0) {
		int Sup = S + K[S - 1][0];
		K[S - 1][0] = 0;
		res = leastPress(N, Sup, E, K) + 1;
	
		if (res == 0) return -1;
		return res;
	}
	//Both going up and going down are valid, then return the smaller one
	if (K[S - 1][0] && K[S - 1][1]) {
		int Sup = S + K[S - 1][0];
		int Sdown = S + K[S - 1][1];
		K[S - 1][0] = 0;
		int resUp = leastPress(N, Sup, E, K);
		K[S - 1][1] = 0;
		int resDown = leastPress(N, Sdown, E, K);
		

		if (resUp == -1 && resDown != -1)
			res = resDown + 1;
		if (resUp != -1 && resDown == -1)
			res = resUp + 1;
		if (resUp == -1 && resDown == -1)
			res = -1;
		if (resUp != -1 && resDown != -1)
			res = min(resUp, resDown) + 1;
		
		return res;
	}
}


int main() {
	int n, s, e;
	vector<vector<int> > k;

	cin >> n >> s >> e;
	
	k.resize(n);
	for (int i = 0; i < n; i++) {
		k[i].resize(2);
	}
	for (int j = 0; j < n; j++) {
		int tmp;
		cin >> tmp;
		k[j][0] = tmp;
		k[j][1] = -tmp;
	}
	
	/* 当用这种方法给K[]赋值时，在visual studio中是正常的，
	*  在洛谷中会有running error。原因不详。
	*  for (int i = 0; i < n; i++){
	*	  int tmp;
	*	  cin >> tmp;
	*	  k.push_back({tmp, -tmp});
	*  }
	*/
	cout << leastPress(n, s, e, k);
	return 0;
}