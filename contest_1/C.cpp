#include <iostream>
#include <stack>

using namespace std;

int main() {
  long long n, h, l, r;
  long long s = 0;
  int a[1'000'002];
  cin >> n;
  a[0] = -2;
  a[n + 1] = -1;
  for (int i = 1; i < n + 1; i++) {
    cin >> a[i];
  }
  stack<int> idx_stack;
  idx_stack.push(0);
  for (int i = 1; i < n + 2; i++) {
    while (a[i] < a[idx_stack.top()]) {
      h = a[idx_stack.top()];
      idx_stack.pop();
      l = idx_stack.top();
      r = i;
      s = max(s, h * (r - l - 1));
    }
    idx_stack.push(i);
  }
  cout << s;
  return 0;
}