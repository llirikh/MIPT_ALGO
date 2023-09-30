#include <iomanip>
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
  std::cout << std::fixed << std::setprecision(10);
  const int kN = 100'001;
  int cnt_page[kN] = {};
  Node* root = Build(0, kN - 1, cnt_page);

  int user_page[kN] = {};
  int cnt_user = 0;

  int q;
  std::cin >> q;
  for (int i = 0; i < q; i++) {
    std::string query;
    std::cin >> query;
    if (query == "CHEER") {
      int user;
      std::cin >> user;
      if (user_page[user] == 0) {
        std::cout << 0 << '\n';
      } else {
        if (cnt_user == 1) {
          std::cout << 1 << '\n';
        } else {
          std::cout << Sum(0, user_page[user] - 1, root) / (cnt_user - 1.0)
                    << '\n';
        }
      }
    } else {
      int user, page;
      std::cin >> user >> page;
      if (user_page[user] == 0) {
        cnt_page[page]++;
        Update(page, cnt_page[page], root);
        cnt_user++;
      } else {
        cnt_page[user_page[user]]--;
        Update(user_page[user], cnt_page[user_page[user]], root);
        cnt_page[page]++;
        Update(page, cnt_page[page], root);
      }
      user_page[user] = page;
    }
  }

  Delete(root);
  return 0;
}