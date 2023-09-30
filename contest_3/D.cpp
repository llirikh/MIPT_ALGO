#include <algorithm>
#include <iostream>
#include <vector>

void Action(long long* a, long long* b) {
  *a = *a + 1;
  *b = *b + 1;
}

void Merge(std::pair<long long, long long>* arr, long long start,
           long long end) {
  std::pair<long long, long long>* sub_arr =
      new std::pair<long long, long long>[end - start + 1];
  long long middle = start + (end - start) / 2;
  long long ptr1 = start, ptr2 = middle + 1, cnt = 0;
  while (ptr1 <= middle && ptr2 <= end) {
    if (arr[ptr1].first < arr[ptr2].first) {
      sub_arr[cnt] = arr[ptr1];
      ptr1++;
    } else {
      if (arr[ptr1].first == arr[ptr2].first) {
        if (arr[ptr1].second > arr[ptr2].second) {
          sub_arr[cnt] = arr[ptr1];
          ptr1++;
        } else {
          sub_arr[cnt] = arr[ptr2];
          ptr2++;
        }
      } else {
        if (arr[ptr1].first > arr[ptr2].first) {
          sub_arr[cnt] = arr[ptr2];
          ptr2++;
        }
      }
    }
    cnt++;
  }
  while (ptr1 <= middle) {
    sub_arr[cnt] = arr[ptr1];
    Action(&ptr1, &cnt);
  }
  while (ptr2 <= end) {
    sub_arr[cnt] = arr[ptr2];
    Action(&ptr2, &cnt);
  }
  for (long long i = 0; i < cnt; i++) {
    arr[start + i] = sub_arr[i];
  }
  delete[] sub_arr;
}

void MergeSort(std::pair<long long, long long>* arr, long long start,
               long long end) {
  if (end - start == 0) {
    return;
  }
  if (end - start == 1) {
    if (arr[start] > arr[end]) {
      std::swap(arr[start], arr[end]);
    }
    if (arr[start].first == arr[end].first &&
        arr[start].second < arr[end].second) {
      std::swap(arr[start], arr[end]);
    }
    return;
  }
  long long middle = start + (end - start) / 2;
  MergeSort(arr, start, middle);
  MergeSort(arr, middle + 1, end);
  Merge(arr, start, end);
}

struct Node {
 public:
  long long left, right;
  long long sum;
  Node* child_left;
  Node* child_right;
};

Node* Build(long long left, long long right, std::vector<long long>& a) {
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

long long Sum(long long left, long long right, Node* root) {
  if (right < root->left || root->right < left) {
    return 0;
  }
  if (left <= root->left && root->right <= right) {
    return root->sum;
  }
  return Sum(left, right, root->child_left) +
      Sum(left, right, root->child_right);
}

void Update(long long idx, long long val, Node* root) {
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
  long long n;
  std::cin >> n;
  std::pair<long long, long long>* arr = new std::pair<long long, long long>[n];
  for (long long i = 0; i < n; i++) {
    std::cin >> arr[i].first >> arr[i].second;
  }
  MergeSort(arr, 0, n - 1);
  long long* sub_arr = new long long[n];
  for (long long i = 0; i < n; i++) {
    sub_arr[i] = arr[i].second;
  }
  std::sort(sub_arr, sub_arr + n);
  std::vector<long long> val;
  std::vector<long long> cnt_val;
  long long last = -1;
  for (long long i = 0; i < n; i++) {
    if (last != sub_arr[i]) {
      val.push_back(sub_arr[i]);
      cnt_val.push_back(1);
    } else {
      cnt_val[val.size() - 1]++;
    }
    last = sub_arr[i];
  }
  Node* root = Build(0, (long long)val.size() - 1, cnt_val);
  long long ans = 0;
  for (long long i = 0; i < n; i++) {
    long long cur_val = arr[i].second;
    long long idx =
        std::lower_bound(val.begin(), val.end(), cur_val) - val.begin();
    ans += Sum(0, idx, root) - 1;
    cnt_val[idx]--;
    Update(idx, cnt_val[idx], root);
  }
  long long delta = 0;
  long long cnt = 1;
  bool flag = true;
  for (long long i = 1; i < n; i++) {
    flag = true;
    if (arr[i] == arr[i - 1]) {
      cnt++;
    } else {
      delta += (cnt - 1) * (cnt) / 2;
      cnt = 1;
      flag = false;
    }
  }
  if (flag) {
    delta += (cnt - 1) * (cnt) / 2;
  }
  long long zero = 0;
  std::cout << std::max(ans - delta, zero);
  Delete(root);
  delete[] arr;
  delete[] sub_arr;
  return 0;
}