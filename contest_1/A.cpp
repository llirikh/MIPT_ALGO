#include <iostream>
#include <string>

int q[100];
int q_size = 0;

std::string Push(int x) {
  q_size++;
  q[q_size - 1] = x;
  return "ok";
}

std::string Pop() {
  if (q_size == 0) {
    return "error";
  }
  if (q_size > 0) {
    q_size--;
    return std::to_string(q[q_size]);
  }
  return "None";
}

std::string Back() {
  if (q_size == 0) {
    return "error";
  }
  if (q_size > 0) {
    return std::to_string(q[q_size - 1]);
  }
  return "None";
}

std::string Size() { return std::to_string(q_size); }

std::string Clear() {
  q_size = 0;
  return "ok";
}

int main() {
  std::string s;
  int x;

  while (s != "exit") {
    std::cin >> s;
    if (s == "push") {
      std::cin >> x;
      std::cout << Push(x);
    }
    if (s == "pop") {
      std::cout << Pop();
    }
    if (s == "back") {
      std::cout << Back();
    }
    if (s == "size") {
      std::cout << Size();
    }
    if (s == "clear") {
      std::cout << Clear();
    }
    std::cout << "\n";
  }
  std::cout << "bye";
  return 0;
}