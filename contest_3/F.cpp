#include <iostream>

long long s[128][128][128];
int m = 0, n = 0;

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int F(int i) { return (i & (i + 1)); }

int G(int i) { return (i | (i + 1)); }

void Update(int x, int y, int z, long long val) {
  for (int i = x; i < n; i = G(i)) {
    for (int j = y; j < n; j = G(j)) {
      for (int q = z; q < n; q = G(q)) {
        s[i][j][q] += val;
      }
    }
  }
}

long long Get(int x, int y, int z) {
  long long ans = 0;
  for (int i = x; i >= 0; i = F(i) - 1) {
    for (int j = y; j >= 0; j = F(j) - 1) {
      for (int q = z; q >= 0; q = F(q) - 1) {
        ans += s[i][j][q];
      }
    }
  }
  return ans;
}

long long Sum(int x1, int y1, int z1, int x2, int y2, int z2) {
  long long ans = 0;
  ans += Get(x2, y2, z2);
  if (x1 != 0) {
    ans -= Get(x1 - 1, y2, z2);
  }
  if (z1 != 0) {
    ans -= Get(x2, y2, z1 - 1);
  }
  if (x1 != 0 && z1 != 0) {
    ans += Get(x1 - 1, y2, z1 - 1);
  }
  if (y1 != 0) {
    ans -= Get(x2, y1 - 1, z2);
  }
  if (y1 != 0 && z1 != 0) {
    ans += Get(x2, y1 - 1, z1 - 1);
  }
  if (x1 != 0 && y1 != 0) {
    ans += Get(x1 - 1, y1 - 1, z2);
  }
  if (x1 != 0 && y1 != 0 && z1 != 0) {
    ans -= Get(x1 - 1, y1 - 1, z1 - 1);
  }
  return ans;
}

int main() {
  SpeedUp();
  std::cin >> n;
  while (true) {
    std::cin >> m;
    if (m == 1) {
      int x, y, z;
      long long k;
      std::cin >> x >> y >> z >> k;
      Update(x, y, z, k);
    }
    if (m == 2) {
      int x1, y1, z1;
      int x2, y2, z2;
      std::cin >> x1 >> y1 >> z1;
      std::cin >> x2 >> y2 >> z2;
      std::cout << Sum(x1, y1, z1, x2, y2, z2) << '\n';
    }
    if (m == 3) {
      break;
    }
  }
  return 0;
}