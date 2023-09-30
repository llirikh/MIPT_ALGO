#include <cmath>
#include <iomanip>
#include <iostream>

void Initialize(int counter, double* prefix_sum, double current_volume) {
  if (counter == 0) {
    prefix_sum[counter] = current_volume;
  } else {
    prefix_sum[counter] =
        pow(prefix_sum[counter - 1], counter / (counter + 1.00)) *
        pow(current_volume, 1 / (counter + 1.00));
  }
}

void PrintAnswer(const double* prefix_sum, int left_bound, int right_bound) {
  if (left_bound == 0) {
    std::cout << prefix_sum[right_bound] << std::endl;
  } else {
    std::cout << pow((prefix_sum[right_bound] /
                      pow(prefix_sum[left_bound - 1],
                          left_bound / (right_bound + 1.00))),
                     (right_bound + 1) / (right_bound - left_bound + 1.00))
              << std::endl;
  }
}

int main() {
  int number_of_mandragores;
  std::cin >> number_of_mandragores;

  auto* prefix_sum = new double[number_of_mandragores];
  for (int i = 0; i < number_of_mandragores; i++) {
    double current_volume;
    std::cin >> current_volume;

    Initialize(i, prefix_sum, current_volume);
  }

  int number_of_requests;
  std::cin >> number_of_requests;

  std::cout << std::fixed << std::setprecision(6);

  for (int i = 0; i < number_of_requests; i++) {
    int left_bound, right_bound;
    std::cin >> left_bound >> right_bound;

    PrintAnswer(prefix_sum, left_bound, right_bound);
  }

  delete[] prefix_sum;

  return 0;
}