#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct node {
	int val;
	int parent;
	vector<int> childs;
};

int findRoot(vector<node*> tree) {
	for (int i = 0; i < tree.size(); i++)
		if (tree[i]->parent == -1)
			return i;
	return 0;
}

int mostChilds(vector<node*> tree) {
	int p = 0;
	int maxNum = tree[0]->childs.size();
	for (int i = 0; i < tree.size(); i++) {
		if (tree[i]->childs.size() > maxNum) {
			maxNum = tree[i]->childs.size();
			p = i;
		}
		if (tree[i]->childs.size() == maxNum) {
			if (tree[i]->val > tree[p]->val)
				p = i;
		}
	}
	return p;
}

void recordChilds(vector<node*> tree) {
	int i, j, k;
	for (i = 0; i < tree.size(); i++) {
		for (j = 0; j < tree.size(); j++) {
			if (tree[i]->val == tree[j]->parent) {
				for (k = 0; k < tree[i]->childs.size(); k++) {
					if (tree[j]->val == tree[i]->childs[k])
						break;
				}
				if (k == tree[i]->childs.size())
					tree[i]->childs.push_back(tree[j]->val);
			}
		}
	}
}

int main() {
	int n, k;
	//node* root = new node;
	cin >> n;
	cin >> k;

	vector<node*> tree;
	//tree.push_back(root);
	for (int i = 0; i < k; i++) {
		int parent, value;
		bool hasParent = false;	//parent is in tree
		bool inTree = false;
		cin >> parent >> value;
		for (int j = 0; j < tree.size(); j++) {
			if (tree[j]->val == parent) {
				hasParent = true;
				tree[j]->childs.push_back(value);
			}
			if (tree[j]->val == value) {
				inTree = true;
				tree[j]->parent = parent;
			}
		}
		if (hasParent == false) {
			node* r = new node;
			r->val = parent;
			r->parent = -1;
			tree.push_back(r);
		}
		if (inTree == false) {
			node* tmp = new node;
			tmp->val = value;
			tmp->parent = parent;
			tree.push_back(tmp);
		}
	}

	recordChilds(tree);
	int root, maxC;
	root = findRoot(tree);
	maxC = mostChilds(tree);
	cout << tree[root]->val << endl;
	cout << tree[maxC]->val << endl;
	sort(tree[maxC]->childs.begin(), tree[maxC]->childs.end());
	for (int s = 0; s < tree[maxC]->childs.size(); s++) {
		cout << tree[maxC]->childs[s] << ' ';
	}
	return 0;
}