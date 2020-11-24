#include<iostream>

using namespace std;

void siftdown(int a[], int i, int n) {
	int j;     int t = a[i];
	while ((j = 2 * i + 1) < n) {
		if (j < n - 1 && a[j] > a[j + 1]) j++;
		if (t > a[j]) { a[i] = a[j];     i = j; }
		else break;
	}
	a[i] = t;
}

//将a[]调整为堆
void get_heap(int a[], int n) {
	for (int i = (n - 2) / 2; i >= 0; i--)
		siftdown(a, i, n);
}

//void heap_sort(int a[], int n) {
//	int i;   int t;
//	//for (i = (n - 2) / 2; i >= 0; i--) siftdown(a, i, n); 
//	for (i = n - 1; i > 0; i--) {     //进行堆排序
//		t = a[0];    a[0] = a[i];   a[i] = t;   siftdown(a, 0, i);
//	}
//}

int main() {
	int* a = new int[10000];
	int n;
	int currentSize;
	int sum = 0;
	//node* root;

	cin >> n;
	currentSize = n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	//a[n] = 0;

	get_heap(a, n);
	/*for (int i = 0; i < n; i++)
		cout << a[i] << ' ';*/

	while (currentSize){
		sum += a[0];
		int t = a[0];
		a[0] = a[currentSize - 1];
		currentSize--;
		if (currentSize) {
			get_heap(a, currentSize);
			sum += a[0];
			a[0] += t;
			get_heap(a, currentSize);
		}
	}

	cout << sum;
	return 0;
}