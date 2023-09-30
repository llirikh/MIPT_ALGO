#include <iostream>
#include <string>

void Push(int x, int* stack, int* stack_min, int* size) {
  if (*size == 0) {
    stack[*size] = x;
    stack_min[*size] = x;
  } else {
    stack[*size] = x;
    stack_min[*size] = std::min(x, stack_min[*size - 1]);
  }
  *size += 1;
}

void Pop(int* size) { *size -= 1; }

int Front(int* stack, int const* size) {
  if (*size == 0) {
    return -1;
  }
  return stack[*size - 1];
}

void Clear(int* start_size, int* end_size) {
  *start_size = 0;
  *end_size = 0;
}

void MinOperation(int* start_stack_min, int* end_stack_min,
                  int const* start_size, int const* end_size) {
  if (*start_size == 0 && *end_size == 0) {
    std::cout << "error" << std::endl;
  }
  if (*start_size == 0 && *end_size != 0) {
    std::cout << end_stack_min[*end_size - 1] << std::endl;
  }
  if (*start_size != 0 && *end_size == 0) {
    std::cout << start_stack_min[*start_size - 1] << std::endl;
  }
  if (*start_size != 0 && *end_size != 0) {
    std::cout << std::min(start_stack_min[*start_size - 1],
                          end_stack_min[*end_size - 1])
              << std::endl;
  }
}

void Move(int* start_stack, int* start_stack_min, int* end_stack,
          int* start_size, int* end_size) {
  while (*end_size != 0) {
    Push(end_stack[*end_size - 1], start_stack, start_stack_min, start_size);
    Pop(end_size);
  }
}

void EnqueueOperation(int* end_stack, int* end_stack_min, int* end_size) {
  int x;
  std::cin >> x;
  Push(x, end_stack, end_stack_min, end_size);
  std::cout << "ok" << std::endl;
}

void DequeueOperation(int* start_stack, int* start_size, int const* end_size) {
  if (*start_size + *end_size == 0) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << Front(start_stack, start_size) << std::endl;
    Pop(start_size);
  }
}

void FrontOperation(int* start_stack, int* start_size, int const* end_size) {
  if (*start_size + *end_size == 0) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << Front(start_stack, start_size) << std::endl;
  }
}

void ClearOperation(int* start_size, int* end_size) {
  Clear(start_size, end_size);
  std::cout << "ok" << std::endl;
}

int main() {
  int start_stack[200'000], start_stack_min[200'000], end_stack[200'000],
      end_stack_min[200'000], start_size = 0, end_size = 0, m;
  std::string request;
  std::cin >> m;
  for (int i = 0; i < m; i++) {
    if (start_size == 0) {
      Move(start_stack, start_stack_min, end_stack, &start_size, &end_size);
    }
    std::cin >> request;
    if (request == "enqueue") {
      EnqueueOperation(end_stack, end_stack_min, &end_size);
    }
    if (request == "dequeue") {
      DequeueOperation(start_stack, &start_size, &end_size);
    }
    if (request == "front") {
      FrontOperation(start_stack, &start_size, &end_size);
    }
    if (request == "size") {
      std::cout << start_size + end_size << std::endl;
    }
    if (request == "clear") {
      ClearOperation(&start_size, &end_size);
    }
    if (request == "min") {
      MinOperation(start_stack_min, end_stack_min, &start_size, &end_size);
    }
  }
  return 0;
}