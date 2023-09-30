#include <iostream>

int Arranging(int* array, int left_bound, int r_bound, int pivot_val) {
  while (left_bound != r_bound) {
    if (array[left_bound] == pivot_val) {
      left_bound++;
      continue;
    }
    if (array[r_bound] > pivot_val) {
      r_bound--;
      continue;
    }
    if (array[left_bound] > pivot_val && array[r_bound] == pivot_val) {
      std::swap(array[left_bound], array[r_bound]);
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

int QuickSelect(int* array, int left_bound, int right_bound, int k_number) {
  int pivot_val = array[left_bound + (right_bound - left_bound) / 2];
  std::pair<int, int> arrange_bounds =
      Partition(array, left_bound, right_bound, pivot_val);
  int left_bound_of_arrange = arrange_bounds.first;
  int right_bound_of_arrange = arrange_bounds.second;

  if (left_bound_of_arrange <= k_number && k_number <= right_bound_of_arrange) {
    return pivot_val;
  }
  if (k_number < left_bound_of_arrange) {
    return QuickSelect(array, left_bound, left_bound_of_arrange - 1, k_number);
  }
  if (k_number > right_bound_of_arrange) {
    return QuickSelect(array, right_bound_of_arrange + 1, right_bound,
                       k_number);
  }

  return -1;
}

int main() {
  int number, k_idx;
  std::cin >> number >> k_idx;

  int* array = new int[number];
  std::cin >> array[0] >> array[1];
  for (int i = 2; i < number; i++) {
    array[i] = (array[i - 1] * 123 + array[i - 2] * 45) % 10'004'321;
  }

  std::cout << QuickSelect(array, 0, number - 1, k_idx - 1);

  delete[] array;

  return 0;
}