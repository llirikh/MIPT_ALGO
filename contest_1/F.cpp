#include <iostream>

int a[100000];
int min_start[100000];
int min_end[100000];

void InitializeMinStartArr(int n) {
  int m = 1000000000;
  for (int i = 0; i < n; i++) {
    m = std::min(m, a[i]);
    min_start[i] = m;
  }
}
void InitializeMinEndArr(int n) {
  int m = 1000000000;
  for (int i = n - 1; i >= 0; i--) {
    m = std::min(m, a[i]);
    min_end[i] = m;
  }
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  InitializeMinEndArr(n);
  InitializeMinStartArr(n);
  int q, l, r;
  std::cin >> q;
  for (int i = 0; i < q; i++) {
    std::cin >> l >> r;
    std::cout << std::min(min_start[l - 1], min_end[r - 1]) << '\n';
  }
  return 0;
}