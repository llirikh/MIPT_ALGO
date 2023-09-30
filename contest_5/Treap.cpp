#include <iostream>

struct Node {
  int key;
  int priority;
  Node* left;
  Node* right;
  int size;

  Node(int value);
  ~Node();
};

Node::Node(int value) {
  key = value;
  priority = rand();
  left = nullptr;
  right = nullptr;
  size = 1;
}

Node::~Node() {
  delete left;
  delete right;
}

int GetSize(Node* root) {
  if (root == nullptr) {
    return 0;
  }

  return root->size;
}

void Update(Node* root) {
  if (root == nullptr) {
    return;
  }

  root->size = 1 + GetSize(root->left) + GetSize(root->right);
}

bool Exists(Node* root, int value) {
  if (root == nullptr) {
    return false;
  }

  if (root->key == value) {
    return true;
  }
  if (root->key < value) {
    return Exists(root->right, value);
  }

  return Exists(root->left, value);
}

std::pair<Node*, Node*> Split(Node* root, int value) {
  if (root == nullptr) {
    return {nullptr, nullptr};
  }

  if (root->key <= value) {
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

  if (root1->priority < root2->priority) {
    root1->right = Merge(root1->right, root2);
    Update(root1);
    return root1;
  }

  root2->left = Merge(root1, root2->left);
  Update(root2);

  return root2;
}

Node* Insert(Node* root, int value) {
  if (Exists(root, value)) {
    return root;
  }

  auto result = Split(root, value);
  Node* result_left = result.first;
  Node* result_right = result.second;

  Node* sub_node = new Node(value);

  return Merge(Merge(result_left, sub_node), result_right);
}

Node* Delete(Node* root, int value) {
  if (!Exists(root, value)) {
    return root;
  }

  auto result = Split(root, value);
  Node* result_temporary = result.first;
  Node* result_right = result.second;

  result = Split(result_temporary, value - 1);
  Node* result_left = result.first;
  Node* result_value = result.second;

  delete result_value;

  return Merge(result_left, result_right);
}

int GetKth(Node* root, int index) {
  const int kInfinity = 1e9 + 1;
  if (root == nullptr) {
    return kInfinity;
  }

  int left_size = GetSize(root->left);

  if (index < left_size) {
    return GetKth(root->left, index);
  }
  if (index > left_size) {
    return GetKth(root->right, index - left_size - 1);
  }

  return root->key;
}

int Next(Node* root, int value, int save) {
  if (root == nullptr) {
    return save;
  }

  if (root->key > value) {
    save = root->key;
    return Next(root->left, value, save);
  }

  return Next(root->right, value, save);
}

int Previous(Node* root, int value, int save) {
  if (root == nullptr) {
    return save;
  }

  if (root->key < value) {
    save = root->key;
    return Previous(root->right, value, save);
  }

  return Previous(root->left, value, save);
}