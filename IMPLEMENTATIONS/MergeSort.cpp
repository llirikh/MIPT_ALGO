#include <iostream>

void Action(int* a, int* b) {
  *a = *a + 1;
  *b = *b + 1;
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
      std::swap(arr[start][0], arr[end][0]);
      std::swap(arr[start][1], arr[end][1]);
    }
    return;
  }
  int middle = start + (end - start) / 2;
  MergeSort(arr, start, middle);
  MergeSort(arr, middle + 1, end);
  Merge(arr, start, end);
}