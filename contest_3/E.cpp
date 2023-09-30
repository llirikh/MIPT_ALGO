#include <algorithm>
#include <iostream>
#include <vector>

long long cnt = 0;
int q = 0;
long long last = -1;
long long mn = 1'000'000'000, mx = -1;
std::vector<long long> val;
std::vector<long long> add;
std::vector<long long> sub_arr;

struct Node {
 public:
  int left, right;
  long long sum;
  Node* child_left;
  Node* child_right;
};

Node* Build(int left, int right, long long* a) {
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
    long long mid = (left + right) / 2;
    res->child_left = Build(left, mid, a);
    res->child_right = Build(mid + 1, right, a);
    res->sum = res->child_left->sum + res->child_right->sum;
  }
  return res;
}

long long Sum(int left, int right, Node* root) {
  if (right < root->left || root->right < left) {
    return 0;
  }
  if (left <= root->left && root->right <= right) {
    return root->sum;
  }
  return Sum(left, right, root->child_left) +
      Sum(left, right, root->child_right);
}

void Update(int idx, long long value, Node* root) {
  if (idx < root->left || root->right < idx) {
    return;
  }
  if (root->left == root->right) {
    root->sum = value;
    return;
  }
  Update(idx, value, root->child_left);
  Update(idx, value, root->child_right);
  root->sum = root->child_left->sum + root->child_right->sum;
}

void Delete(Node* root) {
  if (root->left == root->right) {
    delete root;
    return;
  }
  Delete(root->child_left);
  Delete(root->child_right);
  delete root;
}

int main() {
  std::cin >> q;
  std::pair<char, long long>* request = new std::pair<char, long long>[q]();
  for (int i = 0; i < q; i++) {
    std::cin >> request[i].first >> request[i].second;
    if (request[i].first == '+') {
      sub_arr.push_back(request[i].second);
    }
  }
  std::sort(sub_arr.begin(), sub_arr.end());
  long long* arr = new long long[sub_arr.size()]();
  Node* root = Build(0, (int)(sub_arr.size() - 1), arr);
  for (int i = 0; i < (int)sub_arr.size(); i++) {
    if (sub_arr[i] != last) {
      val.push_back(sub_arr[i]);
      add.push_back(0);
    }
    last = sub_arr[i];
  }
  for (int i = 0; i < q; i++) {
    if (request[i].first == '+') {
      long long idx =
          std::lower_bound(sub_arr.begin(), sub_arr.end(), request[i].second) -
          sub_arr.begin();
      long long cur_val = sub_arr[idx];
      long long add_idx =
          std::lower_bound(val.begin(), val.end(), cur_val) - val.begin();
      idx += add[add_idx];
      add[add_idx]++;
      arr[idx] = cur_val;
      Update(idx, cur_val, root);
      cnt++;
      mn = std::min(mn, request[i].second);
      mx = std::max(mx, request[i].second);
    } else {
      if (cnt == 0) {
        std::cout << 0 << '\n';
      } else {
        long long idx = std::upper_bound(sub_arr.begin(), sub_arr.end(),
                                         request[i].second) -
            sub_arr.begin() - 1;
        if (request[i].second < mn) {
          std::cout << 0 << '\n';
        } else {
          if (request[i].second > mx) {
            std::cout << Sum(0, sub_arr.size() - 1, root) << '\n';
          } else {
            std::cout << Sum(0, idx, root) << '\n';
          }
        }
      }
    }
  }
  delete[] request;
  delete[] arr;
  if (cnt != 0) {
    Delete(root);
    return 0;
  }
  delete root;
}