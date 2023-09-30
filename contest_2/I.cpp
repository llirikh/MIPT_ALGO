#include <iostream>

using namespace std;

long int ans = 0;

void Merge(int* a, int left, int mid, int right) {
  int iter1 = 0, iter2 = 0;
  int* sub_arr = new int[right - left];

  while (left + iter1 < mid && mid + iter2 < right) {
    if (a[left + iter1] < a[mid + iter2]) {
      sub_arr[iter1 + iter2] = a[left + iter1];
      ans += iter2;
      iter1++;
    } else {
      sub_arr[iter1 + iter2] = a[mid + iter2];
      iter2++;
    }
  }

  while (left + iter1 < mid) {
    sub_arr[iter1 + iter2] = a[left + iter1];
    ans += iter2;
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

void MergeSort(int* a, int left, int right) {
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
  int* a = new int[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  MergeSort(a, 0, n);

  cout << ans;

  delete[] a;
  return 0;
}