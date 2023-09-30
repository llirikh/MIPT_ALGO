#include <iostream>
#include <vector>

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

struct Node {
 public:
  int left_bound, right_bound;
  int max;
  Node* child_left;
  Node* child_right;
};

Node* Build(int left_bound, int right_bound, std::vector<int>& array) {
  if (left_bound > right_bound) {
    return nullptr;
  }

  Node* result = new Node;
  result->left_bound = left_bound;
  result->right_bound = right_bound;

  if (left_bound == right_bound) {
    result->child_left = nullptr;
    result->child_right = nullptr;
    result->max = array[left_bound];
  } else {
    int middle = (left_bound + right_bound) / 2;
    result->child_left = Build(left_bound, middle, array);
    result->child_right = Build(middle + 1, right_bound, array);
    result->max = std::max(result->child_left->max, result->child_right->max);
  }

  return result;
}

void Update(Node* root, int index, int value) {
  if (index < root->left_bound || root->right_bound < index) {
    return;
  }

  if (root->left_bound == root->right_bound) {
    root->max = value;
    return;
  }

  Update(root->child_left, index, value);
  Update(root->child_right, index, value);
  root->max = std::max(root->child_left->max, root->child_right->max);
}

int Get(Node* root, int index, int value) {
  if (root->right_bound < index) {
    return -2;
  }
  if (value > root->max) {
    return -2;
  }

  if (root->left_bound == root->right_bound) {
    return root->left_bound;
  }

  int answer = Get(root->child_left, index, value);
  if (answer == -2) {
    answer = Get(root->child_right, index, value);
    if (answer == -2) {
      return -2;
    }
  }

  return answer;
}

void Delete(Node* root) {
  if (root->child_left == nullptr && root->child_right == nullptr) {
    delete root;
    return;
  }

  Delete(root->child_left);
  Delete(root->child_right);
  delete root;
}

int main() {
  SpeedUp();

  int number, request_number;
  std::cin >> number >> request_number;

  std::vector<int> array;
  for (int i = 0; i < number; i++) {
    int current_value;
    std::cin >> current_value;
    array.push_back(current_value);
  }

  Node* root = Build(0, number - 1, array);

  for (int i = 0; i < request_number; i++) {
    int operation_type, index, value;
    std::cin >> operation_type >> index >> value;

    if (operation_type == 0) {
      Update(root, index - 1, value);
    } else {
      std::cout << Get(root, index - 1, value) + 1 << '\n';
    }
  }

  Delete(root);

  return 0;
}