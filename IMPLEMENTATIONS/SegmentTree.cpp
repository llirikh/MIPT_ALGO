#include <iostream>

struct Node {
 public:
  int left, right;
  int sum;
  Node* child_left;
  Node* child_right;
};

Node* Build(int left, int right, int* a) {
  if (left > right) {
    return nullptr;
  }
  Node* res = new Node;
  res->left = left;
  res->right = right;
  if (left == right) {
    res->child_left = nullptr;
    res->child_right = nullptr;
    res->sum = a[left];
  } else {
    int mid = (left + right) / 2;
    res->child_left = Build(left, mid, a);
    res->child_right = Build(mid + 1, right, a);
    res->sum = res->child_left->sum + res->child_right->sum;
  }
  return res;
}

int Sum(int left, int right, Node* root) {
  if (right < root->left || root->right < left) {
    return 0;
  }
  if (left <= root->left && root->right <= right) {
    return root->sum;
  }
  return Sum(left, right, root->child_left) +
      Sum(left, right, root->child_right);
}

void Update(int idx, int val, Node* root) {
  if (idx < root->left || root->right < idx) {
    return;
  }
  if (root->left == root->right) {
    root->sum = val;
    return;
  }
  Update(idx, val, root->child_left);
  Update(idx, val, root->child_right);
  root->sum = root->child_left->sum + root->child_right->sum;
}

void Delete(Node* root) {
  if (root->child_left == nullptr && root->child_right == nullptr) {
    delete root;
    return;
  }
  Delete(root->child_left);
  Delete(root->child_right);
  delete root;
}