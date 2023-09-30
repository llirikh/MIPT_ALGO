#include <iostream>

int q[100000];
int q_size = 0;

std::string Push(int x) {
  q_size++;
  q[q_size - 1] = x;
  return "ok";
}

int Pop() {
  if (q_size == 0) {
    return 0;
  }
  if (q_size > 0) {
    q_size--;
    return q[q_size];
  }
  return 0;
}

int Back() {
  if (q_size == 0) {
    return 0;
  }
  if (q_size > 0) {
    return q[q_size - 1];
  }
  return 0;
}

int Size() { return q_size; }

void StartScobe(char c) {
  if (c == '(') {
    Push(1);
  }
  if (c == '[') {
    Push(2);
  }
  if (c == '{') {
    Push(3);
  }
}

void EndScobe(char c) {
  if (c == ')') {
    if (Size() > 0 && Back() - 1 == 0) {
      Pop();
    } else {
      Push(-1);
    }
  }
  if (c == ']') {
    if (Size() > 0 && Back() - 2 == 0) {
      Pop();
    } else {
      Push(-2);
    }
  }
  if (c == '}') {
    if (Size() > 0 && Back() - 3 == 0) {
      Pop();
    } else {
      Push(-3);
    }
  }
}

int main() {
  char s[100000];
  std::cin >> s;
  for (int i = 0; s[i] != 0; ++i) {
    if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
      StartScobe(s[i]);
    }
    if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
      EndScobe(s[i]);
    }
  }
  if (Size() == 0) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}