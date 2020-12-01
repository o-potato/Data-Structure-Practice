#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;

struct node {
	int val;
	node* lchild, * rchild;
};

node* createTree(vector<int> pre, vector<int> mid) {
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
	vector<int> leftMid;
	vector<int> rightMid;
	leftMid.insert(leftMid.begin(), mid.begin(), mid.begin() + lenL);
	rightMid.insert(rightMid.begin(), mid.begin() + lenL + 1, mid.end());
	vector<int> leftPre;
	vector<int> rightPre;
	leftPre.insert(leftPre.begin(), pre.begin() + 1, pre.end());
	rightPre.insert(rightPre.begin(), pre.begin() + lenL + 1, pre.end());
	if (lenL > 0)
		root->lchild = createTree(leftPre, leftMid);
	if (lenR > 0)
		root->rchild = createTree(rightPre, rightMid);

	return root;
}

node* delete_n(node* root, int n) {
	if (root->val > n) {
		root->lchild = delete_n(root->lchild, n);
		return root;
	}
	if (root->val < n) {
		return delete_n(root->rchild, n);
	}
	if (root->val == n) {
		return root->rchild;
	}
}

vector<int> levelOrder(node* root) {
	vector<int> res;
	queue<node*> q;
	node* p = root;
	int count = 0;
	q.push(p);
	while (!q.empty()) {
		p = q.front();
		if (p != NULL) {
			while (count != 0) {
				res.push_back(-1);
				//cout << -1 << ' ';
				count--;
			}
			res.push_back(p->val);
			//cout << p->val << ' ';
			/*
			if (p->lchild != NULL || p->rchild != NULL) {
				q.push(p->lchild);
				q.push(p->rchild);
			}
			*/
			q.push(p->lchild);
			q.push(p->rchild);
		}
		else
			count++;
			//cout << -1 << ' ';
		q.pop();
	}
	return res;
}

int main() {
	node* root;
	vector<int> help;
	vector<int> pre, mid, res;
	int n;
	int k;
	ifstream in_file("input_11_2.txt");
	while (in_file >> k) {
		help.push_back(k);
	}
	int i = 0;
	for (i = 0; i < (help.size() - 1) / 2; i++) {
		pre.push_back(help[i]);
	}
	for (i = (help.size() - 1) / 2; i < (help.size() - 1); i++) {
		mid.push_back(help[i]);
	}
	n = help[i];
	/*while (cin >> k) {
		pre.push_back(k);
		if (getchar() == '\n')
			break;
	}
	while (cin >> k) {
		mid.push_back(k);
		if (getchar() == '\n')
			break;
	}*/
	//cin >> n;
	root = createTree(pre, mid);
	root = delete_n(root, n);
	res = levelOrder(root);

	ofstream out_file("output_11_2.txt");
	for (int i = 0; i < res.size(); i++) {
		out_file << res[i] << ' ';
	}

	in_file.close();
	out_file.close();
	return 0;
}