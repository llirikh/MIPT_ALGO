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

int main() {
  int n;
  std::cin >> n;

  int* even_arr = new int[n];
  int* odd_arr = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> even_arr[i];
    odd_arr[i] = even_arr[i];
    if (i % 2 == 0) {
      odd_arr[i] *= -1;
    } else {
      even_arr[i] *= -1;
    }
  }

  Node* root_even = Build(0, n - 1, even_arr);
  Node* root_odd = Build(0, n - 1, odd_arr);

  int m;
  std::cin >> m;

  for (int i = 0; i < m; i++) {
    int request;
    std::cin >> request;
    if (request == 0) {
      int idx, val;
      std::cin >> idx >> val;
      if (idx % 2 == 0) {
        Update(idx - 1, -val, root_even);
        Update(idx - 1, val, root_odd);
      } else {
        Update(idx - 1, val, root_even);
        Update(idx - 1, -val, root_odd);
      }
    } else {
      int l, r;
      std::cin >> l >> r;
      if (l % 2 == 0) {
        std::cout << Sum(l - 1, r - 1, root_odd) << '\n';
      } else {
        std::cout << Sum(l - 1, r - 1, root_even) << '\n';
      }
    }
  }

  delete[] even_arr;
  delete[] odd_arr;
  Delete(root_even);
  Delete(root_odd);

  return 0;
}