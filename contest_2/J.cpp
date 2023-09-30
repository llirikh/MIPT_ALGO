#include <iostream>

using namespace std;

int ans[100'000] = {0};

void Merge(pair<int, int>* a, int left, int mid, int right) {
  int iter1 = 0, iter2 = 0;
  pair<int, int>* sub_arr = new pair<int, int>[right - left];

  while (left + iter1 < mid && mid + iter2 < right) {
    if (a[left + iter1] < a[mid + iter2]) {
      sub_arr[iter1 + iter2] = a[left + iter1];
      ans[a[left + iter1].second] += iter2;
      iter1++;
    } else {
      sub_arr[iter1 + iter2] = a[mid + iter2];
      iter2++;
    }
  }

  while (left + iter1 < mid) {
    sub_arr[iter1 + iter2] = a[left + iter1];
    ans[a[left + iter1].second] += iter2;
    iter1++;
  }

  while (mid + iter2 < right) {
    sub_arr[iter1 + iter2] = a[mid + iter2];
    iter2++;
  }

  for (int i = 0; i < iter1 + iter2; i++) {
    a[left + i] = sub_arr[i];
  }
  delete[] sub_arr;
}

void MergeSort(pair<int, int>* a, int left, int right) {
  if (left + 1 >= right) {
    return;
  }
  int mid = (left + right) / 2;
  MergeSort(a, left, mid);
  MergeSort(a, mid, right);
  Merge(a, left, mid, right);
}

int main() {
  int n;
  cin >> n;
  pair<int, int> a[100'000];
  for (int i = 0; i < n; i++) {
    cin >> a[i].first;
    a[i].second = i;
  }
  MergeSort(a, 0, n);
  for (int i = 0; i < n; i++) {
    cout << ans[i] << ' ';
  }
}