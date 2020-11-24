#include<iostream>
#include<vector>

using namespace std;

struct node {
	char val;
	node* lchild, * rchild;
};

node* createTree(vector<char> pre, vector<char> mid) {
	node* root = new node;
	root->val = pre[0];
	root->lchild = NULL;
	root->rchild = NULL;

	if (pre.size() == 1)
		return root;

	int rootMid = 0;
	while (rootMid < mid.size() && mid[rootMid] != root->val)
		rootMid++;

	int lenL = rootMid;
	int lenR = mid.size() - lenL - 1;
	vector<char> leftMid;
	vector<char> rightMid;
	leftMid.insert(leftMid.begin(), mid.begin(), mid.begin() + lenL);
	rightMid.insert(rightMid.begin(), mid.begin() + lenL + 1, mid.end());
	vector<char> leftPre;
	vector<char> rightPre;
	leftPre.insert(leftPre.begin(), pre.begin() + 1, pre.end());
	rightPre.insert(rightPre.begin(), pre.begin() + lenL + 1, pre.end());
	if (lenL > 0)
		root->lchild = createTree(leftPre, leftMid);
	if (lenR > 0)
		root->rchild = createTree(rightPre, rightMid);

	return root;
}

int heightTree(node* root) {
	int leftH, rightH;
	if (root == NULL)
		return 0;
	leftH = heightTree(root->lchild);
	rightH = heightTree(root->rchild);
	return leftH > rightH ? leftH + 1 : rightH + 1;
}

int main() {
	int n;
	char ch;
	node* root;
	vector<char> mid;
	vector<char> pre;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> ch;
		pre.push_back(ch);
	}
	for (int i = 0; i < n; i++) {
		cin >> ch;
		mid.push_back(ch);
	}

	root = createTree(pre, mid);
	cout << heightTree(root);
	return 0;
}