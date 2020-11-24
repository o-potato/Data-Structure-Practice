#include<iostream>
#include<queue>
#include<cstdio>

using namespace std;

struct node {
	int val;
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

node* getAncestor(node* root, int x, int y) {
	node* leftAnc, * rightAnc;

	if (root == NULL)
		return NULL;
	if (root->val == x || root->val == y)
		return root;
	leftAnc = getAncestor(root->lchild, x, y);
	rightAnc = getAncestor(root->rchild, x, y);
	if (leftAnc == NULL && rightAnc != NULL)
		return rightAnc;
	if (rightAnc == NULL && leftAnc != NULL)
		return leftAnc;
    if (leftAnc == NULL && rightAnc == NULL)
        return NULL;
	return root;
}

int main() {
	vector<int> a;
	int x, y, k;
	node* root, * anc;
	
	//int i = 0;
	while (cin >> k) {
		a.push_back(k);
		//i++;
		if (getchar() == '\n')
			break;
	}
	cin >> x >> y;
	
	root = createTree(a);
	anc = getAncestor(root, x, y);
	cout << anc->val << endl;
	return 0;
}