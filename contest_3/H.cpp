#include <algorithm>
#include <iostream>

std::pair<int, int> TwoMin(std::pair<int, int> first_pair,
                           std::pair<int, int> second_pair, int* main_array) {
  std::pair<int, int> array[4] = {
      {main_array[first_pair.first], first_pair.first},
      {main_array[first_pair.second], first_pair.second},
      {main_array[second_pair.first], second_pair.first},
      {main_array[second_pair.second], second_pair.second}};
  std::sort(std::begin(array), std::end(array));

  if (array[0] == array[1]) {
    if (array[0] == array[2]) {
      return {array[0].second, array[3].second};
    }
    return {array[0].second, array[2].second};
  }
  return {array[0].second, array[1].second};
}

void InitializeDegree(int* degree, int number) {
  degree[0] = 0;
  degree[1] = 0;
  for (int x = 2; x < number; x++) {
    degree[x] = degree[x / 2] + 1;
  }
}

void InitializeSparse(std::pair<int, int>** sparse, int degree_of_number,
                      int number, int* main_array) {
  for (int i = 0; i < number; i++) {
    sparse[0][i] = {-1, -1};
  }
  for (int i = 0; i < number - 1; i++) {
    sparse[1][i] = {i, i + 1};
  }
  for (int i = 2; i < degree_of_number; i++) {
    for (int j = 0; j < number; j++) {
      int length = (1 << (i - 1));
      if ((j + length) >= number) {
        break;
      }
      sparse[i][j] =
          TwoMin(sparse[i - 1][j], sparse[i - 1][j + length], main_array);
    }
  }
}

int main() {
  int number, number_of_requests;
  std::cin >> number >> number_of_requests;

  auto array = new int[number];
  for (int i = 0; i < number; i++) {
    std::cin >> array[i];
  }

  int* degree = new int[number + 1];
  InitializeDegree(degree, number + 1);

  int degree_of_number = degree[number];
  auto** sparse = new std::pair<int, int>*[degree_of_number + 1];
  for (int i = 0; i < degree_of_number + 1; i++) {
    sparse[i] = new std::pair<int, int>[number];
  }
  InitializeSparse(sparse, degree_of_number + 1, number, array);

  for (int i = 0; i < number_of_requests; i++) {
    int left_bound, right_bound;
    std::cin >> left_bound >> right_bound;

    int current_degree = degree[right_bound - left_bound + 1];

    auto pair = TwoMin(
        sparse[current_degree][left_bound - 1],
        sparse[current_degree][right_bound - (1 << current_degree)], array);
    std::cout << std::max(array[pair.first], array[pair.second]) << '\n';
  }

  delete[] array;
  delete[] degree;
  for (int i = 0; i < degree_of_number + 1; i++) {
    delete[] sparse[i];
  }
  delete[] sparse;

  return 0;
}