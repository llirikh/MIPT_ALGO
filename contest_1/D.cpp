#include <deque>
#include <iostream>

int main() {
  std::deque<int> start_queue;
  std::deque<int> finish_queue;
  char goblin_type;
  int n, goblin_number;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> goblin_type;
    if (goblin_type == '-') {
      std::cout << start_queue.front() << std::endl;
      start_queue.pop_front();
    } else {
      std::cin >> goblin_number;
      if (goblin_type == '+') {
        finish_queue.push_back(goblin_number);
      }
      if (goblin_type == '*') {
        if ((start_queue.size() + finish_queue.size()) % 2 != 0) {
          finish_queue.push_front(goblin_number);
        } else {
          start_queue.push_back(goblin_number);
        }
      }
    }
    while (finish_queue.size() > start_queue.size()) {
      start_queue.push_back(finish_queue.front());
      finish_queue.pop_front();
    }
  }
  return 0;
}