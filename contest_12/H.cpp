#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int CalculateF(int n, int a, int b, int p, int q) {
  // Определяем размер вектора для хранения последних значений
  int mod = 119;
  int size = std::max(p, q) + 1;
  vector<int> f(size, 1);  // Инициализируем значениями для k <= 0

  // Вычисляем значения f(k) для k от 1 до n
  for (int k = 1; k <= n; ++k) {
    int fk_p = f[(k - p + size) % size];  // f(k - p)
    int fk_q = f[(k - q + size) % size];  // f(k - q)
    f[k % size] = (a * fk_p + b * fk_q) % mod;
  }

  // Возвращаем f(n)
  return f[n % size];
}

int main() {
  int n, a, b, p, q;
  cin >> n >> a >> b >> p >> q;
  cout << CalculateF(n, a, b, p, q) << "\n";
  return 0;
}