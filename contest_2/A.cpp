#include <iostream>
#include <vector>

using namespace std;

int number;
vector<int> ans_l, ans_r;

void Action(int* a, int* b) {
  *a = *a + 1;
  *b = *b + 1;
}

void Read(int** arr) {
  for (int i = 0; i < number; i++) {
    cin >> arr[i][0] >> arr[i][1];
  }
}

void Print() {
  cout << ans_l.size() << endl;
  int n = static_cast<int>(ans_l.size());
  for (int i = 0; i < n; i++) {
    cout << ans_l[i] << ' ' << ans_r[i] << endl;
  }
}

void Merge(int** arr, int start, int end) {
  int** sub_arr = new int*[end - start + 1];
  for (int i = 0; i < end - start + 1; i++) {
    sub_arr[i] = new int[2];
  }
  int middle = start + (end - start) / 2;
  int ptr1 = start, ptr2 = middle + 1, cnt = 0;
  while (ptr1 <= middle && ptr2 <= end) {
    if (arr[ptr1][0] <= arr[ptr2][0]) {
      sub_arr[cnt] = arr[ptr1];
      ptr1++;
    } else {
      sub_arr[cnt] = arr[ptr2];
      ptr2++;
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
  for (int i = 0; i < cnt; i++) {
    arr[start + i] = sub_arr[i];
  }
  delete[] sub_arr;
}

void MergeSort(int** arr, int start, int end) {
  if (end - start == 0) {
    return;
  }
  if (end - start == 1) {
    if (arr[start][0] > arr[end][0]) {
      swap(arr[start][0], arr[end][0]);
      swap(arr[start][1], arr[end][1]);
    }
    return;
  }
  int middle = start + (end - start) / 2;
  MergeSort(arr, start, middle);
  MergeSort(arr, middle + 1, end);
  Merge(arr, start, end);
}

int main() {
  cin >> number;
  int** arr = new int*[number];
  for (int i = 0; i < number; i++) {
    arr[i] = new int[2];
  }
  Read(arr);
  MergeSort(arr, 0, number - 1);
  int l = arr[0][0], r = arr[0][1];
  for (int i = 1; i < number; i++) {
    if (l <= arr[i][0] && arr[i][0] <= r) {
      r = max(r, arr[i][1]);
    } else {
      ans_l.push_back(l);
      ans_r.push_back(r);
      l = arr[i][0];
      r = arr[i][1];
    }
  }
  for (int i = 0; i < number; i++) {
    delete[] arr[i];
  }
  delete[] arr;
  if (ans_l.empty() ||
      (l != ans_l[ans_l.size() - 1] && r != ans_r[ans_r.size() - 1])) {
    ans_l.push_back(l);
    ans_r.push_back(r);
  }
  Print();
  return 0;
}