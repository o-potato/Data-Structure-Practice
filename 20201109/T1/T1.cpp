#include<iostream>

using namespace std;

struct node
{
    int data;
    struct node* lchild, * rchild;
    int ltag, rtag;
};

node* create_thread_tree(int a[], int n)
{
    node* root, * head, * p, * r;
    int i;
    if (n == 0) return NULL;
    root = new node;
    root->data = a[0];
    root->lchild = NULL;
    root->rchild = NULL;
    root->ltag = 0;
    root->rtag = 0;
    head = root;
    for (i = 1; i < n; i++) {
        r = new node;
        r->data = a[i];
        p = root;
        while (1) {
            if (r->data <= p->data) {
                if (p->ltag == 0 && p->lchild != NULL) p = p->lchild;
                else break;
            }
            else {
                if (p->rtag == 0 && p->rchild != NULL) p = p->rchild;
                else break;
            }
        }
        if (r->data < p->data) {
            r->lchild = p->lchild;
            r->ltag = p->ltag;
            r->rchild = p;
            r->rtag = 1;
            p->lchild = r;
            p->ltag = 0;
            if (r->lchild == NULL) head = r;
        }
        else {
            r->rchild = p->rchild;
            r->rtag = p->rtag;
            r->lchild = p;
            r->ltag = 1;
            p->rchild = r;
            p->rtag = 0;
        }
    }
    return head;
}

node* succ(node* t) {
    if (t->rtag == 1 || t->rchild == NULL)
        return t->rchild;
    t = t->rchild;
    while (t->ltag == 0)
        t = t->lchild;
    return t;
}

void midorder(node* head) {
    node* p = head;
    while (p != NULL) {
        cout << p->data << ' ';
        p = succ(p);
    }
}

void thread_sort(int a[], int n)
{
    node* head;
    head = create_thread_tree(a, n);
    midorder(head);
}

int main()
{
    int n;
    int a[100];
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    thread_sort(a, n);
    return 0;
}
