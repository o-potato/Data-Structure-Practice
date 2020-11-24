#include<iostream>
#include<vector>
#include<queue>

using namespace std;

//class TreeNode {
//private:
//	int value;
//	TreeNode* leftchild, * rightchild;
//public:
//	TreeNode(int v) {
//		value = v;
//		leftchild = NULL;
//		rightchild = NULL;
//	}
//	
//};

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

void print_vector(vector<double> v) {
	int i = 0;
	for (i = 0; i < v.size(); i++) {
		cout << v[i] << ' ';
	}
	cout << endl;
}


void dfs(TreeNode* root, int level, vector<double>& sum, vector<int>& count) {
	if (root == NULL) {
		return;
	}
	if (level < sum.size()) {
		if (root->value != -1) {
			sum[level] += 1.0 * root->value;
			count[level] += 1;
		}
	}
	else {
		if (root->value != -1) {
			sum.push_back(1.0 * root->value);
			count.push_back(1);
		}
		else {
			sum.push_back(0);
			count.push_back(0);
		}
	}
	dfs(root->leftchild, level + 1, sum, count);
	dfs(root->rightchild, level + 1, sum, count);
}

vector<double> average_of_levels(TreeNode* root) {
	vector<double> sum;
	vector<int> count;
	dfs(root, 0, sum, count);
	vector<double> res;
	for (int i = 0; i < sum.size(); i++) {
		res.push_back(sum[i] / count[i]);
	}
	return res;
}






int main() {
	int v;
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
	average = average_of_levels(root);
	print_vector(average);

	return 0;
}