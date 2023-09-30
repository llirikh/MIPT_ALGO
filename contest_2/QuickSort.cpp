#include <iostream>

int Arranging(int* array, int left_bound, int right_bound, int pivot_val) {
  while (left_bound != right_bound) {
    if (array[left_bound] == pivot_val) {
      left_bound++;
      continue;
    }
    if (array[right_bound] > pivot_val) {
      right_bound--;
      continue;
    }
    if (array[left_bound] > pivot_val && array[right_bound] == pivot_val) {
      std::swap(array[left_bound], array[right_bound]);
    }
  }

  int right_bound_of_arrange = left_bound;
  if (array[left_bound] == pivot_val && array[left_bound + 1] != pivot_val) {
    right_bound_of_arrange = left_bound;
  }
  if (array[left_bound - 1] == pivot_val && array[left_bound] != pivot_val) {
    right_bound_of_arrange = left_bound - 1;
  }

  return right_bound_of_arrange;
}

std::pair<int, int> Partition(int* array, int left_bound, int right_bound,
                              int pivot_val) {
  int left_ptr = left_bound, right_ptr = right_bound;
  while (left_ptr != right_ptr) {
    if (array[left_ptr] < pivot_val) {
      left_ptr++;
      continue;
    }
    if (array[right_ptr] >= pivot_val) {
      right_ptr--;
      continue;
    }
    if (array[left_ptr] >= pivot_val && array[right_ptr] < pivot_val) {
      std::swap(array[left_ptr], array[right_ptr]);
    }
  }

  int left_bound_of_arrange = left_ptr;
  int right_bound_of_arrange =
      Arranging(array, left_ptr, right_bound, pivot_val);

  return {left_bound_of_arrange, right_bound_of_arrange};
}

void QuickSort(int* array, int left_bound, int right_bound) {
  if (right_bound - left_bound <= 0) {
    return;
  }

  int pivot_val = array[left_bound + rand() % (right_bound - left_bound + 1)];
  std::pair<int, int> lr = Partition(array, left_bound, right_bound, pivot_val);

  int left_bound_of_arrange = lr.first - 1;
  int right_bound_of_arrange = lr.second + 1;
  QuickSort(array, left_bound, left_bound_of_arrange);
  QuickSort(array, right_bound_of_arrange, right_bound);
}