#include <iostream>

struct Node {
  long long x;
  long long y;
  Node* left;
  Node* right;
  long long size;

  Node(long long value) {
    x = value;
    y = rand();
    left = nullptr;
    right = nullptr;
    size = value;
  }

  ~Node() {
    delete left;
    delete right;
  }
};

long long GetSize(Node* root) {
  if (root == nullptr) {
    return 0;
  }

  return root->size;
}

void Update(Node* root) {
  if (root == nullptr) {
    return;
  }

  root->size = root->x + GetSize(root->left) + GetSize(root->right);
}

bool Exists(Node* root, long long value) {
  if (root == nullptr) {
    return false;
  }

  if (root->x == value) {
    return true;
  }
  if (root->x < value) {
    return Exists(root->right, value);
  }

  return Exists(root->left, value);
}

std::pair<Node*, Node*> Split(Node* root, long long value) {
  if (root == nullptr) {
    return {nullptr, nullptr};
  }

  if (root->x <= value) {
    auto result = Split(root->right, value);
    Node* result_left = result.first;
    Node* result_right = result.second;

    root->right = result_left;
    Update(root);

    return {root, result_right};
  }

  auto result = Split(root->left, value);
  Node* result_left = result.first;
  Node* result_right = result.second;

  root->left = result_right;
  Update(root);

  return {result_left, root};
}

Node* Merge(Node* root1, Node* root2) {
  if (root1 == nullptr) {
    return root2;
  }
  if (root2 == nullptr) {
    return root1;
  }

  if (root1->y < root2->y) {
    root1->right = Merge(root1->right, root2);
    Update(root1);
    return root1;
  }

  root2->left = Merge(root1, root2->left);
  Update(root2);

  return root2;
}

Node* Insert(Node* root, long long value) {
  if (Exists(root, value)) {
    return root;
  }

  auto result = Split(root, value);
  Node* result_left = result.first;
  Node* result_right = result.second;

  Node* sub_node = new Node(value);

  return Merge(Merge(result_left, sub_node), result_right);
}

long long PrevSize(Node* root, long long value, long long save) {
  if (root == nullptr) {
    return save;
  }
  if (root->x < value) {
    save += GetSize(root->left) + root->x;
    return PrevSize(root->right, value, save);
  }
  if (root->x == value) {
    save += GetSize(root->left) + root->x;
    return save;
  }
  return PrevSize(root->left, value, save);
}

int main() {
  long long n;
  std::cin >> n;

  Node* root = nullptr;
  char request;
  long long x, l, r;
  long long y = 0;
  long long min = 1000000001;
  long long max = -1000000001;

  for (long long i = 0; i < n; ++i) {
    std::cin >> request;

    if (request == '+') {
      std::cin >> x;
      x = (x + y) % 1'000'000'000;
      min = std::min(min, x);
      max = std::max(max, x);
      root = Insert(root, x);
      y = 0;
    }

    if (request == '?') {
      std::cin >> l >> r;
      if (l > max || r < min) {
        y = 0;
      } else {
        y = PrevSize(root, r, 0) - PrevSize(root, l - 1, 0);
      }
      std::cout << y << '\n';
    }
  }

  delete root;
}