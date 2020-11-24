#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct TreeNode
{
	int value;
	TreeNode* leftchild, * rightchild;
};

TreeNode* buildTree(vector<int> arr) {
	if (arr.size() == 0)
		return NULL;
	TreeNode* root = new TreeNode;
	root->value = arr[0];
	root->leftchild = NULL;
	root->rightchild = NULL;
	queue<TreeNode*> q;
	q.push(root);
	int i = 1;
	while (i < arr.size()) {
		TreeNode* node = q.front();
		q.pop();
		if (node != NULL) {
			TreeNode* l;
			TreeNode* r;
			if (arr[i] != -1) {
				l = new TreeNode;
				l->value = arr[i];
				l->leftchild = NULL;
				l->rightchild = NULL;
			}
			else
				l = NULL;
			if ((i + 1) < arr.size() && arr[i + 1] != -1) {
				r = new TreeNode;
				r->value = arr[i + 1];
				r->leftchild = NULL;
				r->rightchild = NULL;
			}
			else
				r = NULL;
			//TreeNode* l = (arr[i] != -1) ? new TreeNode(arr[i]) : nullptr;
			//TreeNode* r = ((i + 1) < arr.size() && arr[i + 1] != -1) ? new TreeNode(arr[i + 1]) : nullptr;
			node->leftchild = l;
			node->rightchild = r;
			q.push(l);
			q.push(r);
			i += 2;
		}
	}
	return root;
}


bool path_k(TreeNode* root, int k) {
	if (root == NULL) {
		return false;
	}
	if (root->leftchild == NULL && root->rightchild == NULL) {
		return k == root->value;
	}
	return path_k(root->leftchild, k - root->value) ||
		path_k(root->rightchild, k - root->value);
}




int main() {
	int v;
	int k;
	vector<int> a;
	vector<double> average;
	//cout << "enter the values one by one(must be >= 0):" << endl;
	while (cin >> v) {
		a.push_back(v);
		if (cin.get() == '\n')
			break;
	}
	TreeNode* root = buildTree(a);
	//pre_traversal(root);
	
	//cout << "Enter K:";
	cin >> k;
	bool result = path_k(root, k);
	if (result)
		cout << "true" << endl;
	else
		cout << "false" << endl;
	return 0;
}