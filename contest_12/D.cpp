#include <cmath>
#include <iostream>
#include <unordered_map>

long long Factor(long long num, long long deg, long long mod) {
  if (deg == 0) {
    return 1;
  }
  if (deg % 2 == 0) {
    long long tmp = Factor(num, deg / 2, mod) % mod;
    return (tmp * tmp) % mod;
  }
  return (num * Factor(num, deg - 1, mod)) % mod;
}

int main() {
  long long mod;
  long long aa;
  long long bb;
  std::unordered_map<int, int> map;
  while (std::cin >> mod >> aa >> bb) {
    long long limit = static_cast<long long>(std::sqrt(mod)) + 1;
    map.clear();
    for (long long i = limit; i >= 1; --i) {
      map[static_cast<int>(Factor(aa, (limit * i) % mod, mod))] =
          static_cast<int>(i);
    }
    long long min = mod;
    for (long long i = 0; i < limit + 1; ++i) {
      int current = static_cast<int>((bb * Factor(aa, i, mod)) % mod);
      if (map.contains(current)) {
        long long ans = map[current] * limit - i;
        if (ans < mod) {
          min = std::min(ans, min);
        }
      }
    }
    if (min == mod) {
      std::cout << "no solution" << '\n';
      continue;
    }
    std::cout << min << '\n';
  }
}