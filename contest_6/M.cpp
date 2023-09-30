#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("no-stack-protector")

#include <iostream>
#include <vector>

std::pair<long long, long long> Doubling(long long n) {
  const long long kModulo = 1e9 + 9;
  if (n == 0) {
    return {0, 1};
  }
  std::pair<long long, long long> a = Doubling(n / 2);
  long long c =
      a.first * ((a.second * 2) % kModulo - a.first + kModulo) % kModulo;
  c %= kModulo;
  long long d = (a.first * a.first) % kModulo + (a.second * a.second) % kModulo;
  d %= kModulo;
  if (n % 2 == 0) {
    return {c, d};
  }
  return {d, (c + d) % kModulo};
}

long long Fibbonacci(long long n) { return Doubling(n).first; }

void SpeedUp() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
}

int main() {
  SpeedUp();
  const long long kModulo = 1e9 + 9;
  int airports_number, coefficent_number;
  std::cin >> airports_number >> coefficent_number;

  std::vector<std::vector<long long>> coord(airports_number,
                                            std::vector<long long>(2, 0));
  std::vector<long long> way_count(airports_number);
  for (long long i = 0; i < airports_number; ++i) {
    std::cin >> coord[i][0] >> coord[i][1] >> way_count[i];
    way_count[i] %= kModulo;
  }

  long long current_coefficent;
  long long current_answer;
  for (int i = 0; i < coefficent_number; ++i) {
    std::cin >> current_coefficent;
    current_answer = 0;
    for (int j = 0; j < airports_number; ++j) {
      long long distance = coord[j][1] - coord[j][0] - current_coefficent;
      if (distance >= 0) {
        current_answer += (way_count[j] * Fibbonacci(distance + 1)) % kModulo;
        current_answer %= kModulo;
      }
    }
    std::cout << current_answer << '\n';
  }
}