#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

struct node {
	int val;
	int level;
	node* lchild, * rchild;
};

node* createTree(vector<int> a) {
	queue<node*> nodes;
	queue<node*> intree;
	node* p, * root;
	int i = 0;
	while (i < a.size()) {
		if (a[i] == -1)
			nodes.push(NULL);
		else {
			p = new node;
			p->val = a[i];
			p->lchild = NULL;
			p->rchild = NULL;
			nodes.push(p);
		}
		i++;
	}
	root = nodes.front();
	nodes.pop();
	intree.push(root);
	while (!nodes.empty()) {
		p = intree.front();
		intree.pop();
		p->lchild = nodes.front();
		nodes.pop();
		if (!nodes.empty()) {
			p->rchild = nodes.front();
			nodes.pop();
		}
		if (p->lchild != NULL)
			intree.push(p->lchild);
		if (p->rchild != NULL)
			intree.push(p->rchild);
	}
	return root;
}

void midOrder(node* root, vector<vector<int> >* mid) {
	if (root == NULL)
		return;
	midOrder(root->lchild, mid);
	(*mid).push_back({ root->val, root->level });
	midOrder(root->rchild, mid);
}

vector<vector<int> > minDiff(vector<vector<int> > mid) {
	vector<vector<int> > re1;
	vector<vector<int> > re2;
	int minD = abs(mid[0][0] - mid[1][0]);
	int maxLevelD;
	int i;
	for (i = 0; i < mid.size() - 1; i++) {
		if (abs(mid[i][0] - mid[i + 1][0]) < minD) {
			minD = abs(mid[i][0] - mid[i + 1][0]);
		}
	}
	for (i = 0; i < mid.size() - 1; i++) {
		if (abs(mid[i][0] - mid[i + 1][0]) == minD) {
			re1.push_back(mid[i]);
			re1.push_back(mid[i + 1]);
		}
	}
	maxLevelD = abs(re1[0][1] - re1[1][1]);
	for (i = 0; i < re1.size() - 1; i = i + 2) {
		if (abs(re1[i][1] - re1[i + 1][1]) > maxLevelD) {
			maxLevelD = abs(re1[i][1] - re1[i + 1][1]);
		}
	}
	for (i = 0; i < re1.size() - 1; i = i + 2) {
		if (abs(re1[i][1] - re1[i + 1][1]) == maxLevelD) {
			re2.push_back({ re1[i][0], re1[i + 1][0] });
		}
	}
	return re2;
}

void setLevel(node* root, int lev) {
	if (root == NULL)
		return;
	root->level = lev;
	setLevel(root->lchild, lev + 1);
	setLevel(root->rchild, lev + 1);
}

int main() {
	/*
	ifstream infile("input_11_1.txt");
	if (!infile)
		exit(1);
	*/
	vector<int> tree;
	vector<vector<int> > midTree;
	vector<vector<int> > results;
	node* root;
	int k;
	int i = 0;
	//int base = 1;
	//int count = 0;
	/*while (cin >> k) {
		tree.push_back(k);
		if (getchar() == '\n')
			break;
	}*/
	
	ifstream in_file("input_11_1.txt");
	while (in_file >> k) {
		tree.push_back(k);
	}

	//get_heap(tree, tree.size());
	root = createTree(tree);
	setLevel(root, 1);
	midOrder(root, &midTree);
	results = minDiff(midTree);

	ofstream out_file("output_11_1.txt");
	for (i = 0; i < results.size(); i++) {
		//cout << results[i][0] << ' ' << results[i][1] << endl;
		out_file << results[i][0] << ' ' << results[i][1] << endl;
	}
	return 0;
}