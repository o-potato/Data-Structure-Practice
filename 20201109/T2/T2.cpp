#include<iostream>
#include<string>

using namespace std;

struct node
{
	string val;
	node* lchild, * rchild;
};

void splitNode(node* p) {
	string parent, left, right;
	node* leftNode, * rightNode;

	parent = p->val;
	if (parent.length() == 1)
		return;
	left = parent.substr(0, parent.length() / 2);
	right = parent.substr(parent.length() / 2);

	leftNode = new node;
	rightNode = new node;

	leftNode->val = left;
	leftNode->lchild = NULL;
	leftNode->rchild = NULL;

	rightNode->val = right;
	rightNode->lchild = NULL;
	rightNode->rchild = NULL;

	p->lchild = leftNode;
	p->rchild = rightNode;
}

string fdu(node* p) {
	string s = p->val;
	int flag_1 = 0;
	int flag_0 = 0;
	int i = 0;
	while (i < s.length()) {
		if (s[i] == '0')
			flag_0 = 1;
		if (s[i] == '1')
			flag_1 = 1;
		i++;
	}
	if (flag_0) {
		if (flag_1)
			return "U";
		else
			return "F";
	}
	return "D";
}

void createTree(node* root) {
	splitNode(root);
	if (root->val.length() > 2) {
		createTree(root->lchild);
		createTree(root->rchild);
	}
}

void r_posorder(node* p) {
	if (p != NULL) {
		r_posorder(p->lchild);
		r_posorder(p->rchild);
		cout << fdu(p);
	}
}

int main() {
	int n;
	string s;
	node* root;

	cin >> n >> s;
	root = new node;
	root->val = s;
	root->lchild = NULL;
	root->rchild = NULL;

	createTree(root);
	r_posorder(root);
	return 0;
}