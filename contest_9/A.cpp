#include <iostream>
#include <vector>

int getRoot(int v, std::vector<int>& parent) {
  if (parent[v] < 0) {
    return v;
  }
  int root = getRoot(parent[v], parent);
  parent[v] = root;
  return root;
}

bool join(int a, int b, std::vector<int>& parent) {
  a = getRoot(a, parent);
  b = getRoot(b, parent);
  if (a == b) {
    return false;
  }
  if (parent[a] < parent[b]) {
    parent[a] += parent[b];
    parent[b] = a;
  } else {
    parent[b] += parent[a];
    parent[a] = b;
  }
  return true;
}

bool sameRoot(int a, int b, std::vector<int>&parent) {
  a = getRoot(a, parent);
  b = getRoot(b, parent);
  return a == b;
};

int main() {
  int nE, nV, nQ;
  std::cin >> nV >> nE >> nQ;
  for (int i = 0; i < nE; ++i) {
    int v1, v2;
    std::cin >> v1 >> v2;
  }

  std::vector<std::string> names;
  std::vector<int> v1s;
  std::vector<int> v2s;
  for (int i = 0; i < nQ; ++i) {
    std::string name;
    int v1, v2;
    std::cin >> name >> v1 >> v2;
    names.push_back(name);
    v1s.push_back(v1 - 1);
    v2s.push_back(v2 - 1);
  }

  std::vector<bool> ans;
  std::vector<int> parent(1 + nV, -1);
  for (int i = nQ - 1; i >= 0; --i) {
    std::string name = names[i];
    int v1 = v1s[i], v2 = v2s[i];
    if (name == "ask") {
      ans.push_back(sameRoot(v1, v2, parent));
    } else {
      join(v1, v2, parent);
    }
  }

  for (int i = ans.size() - 1; i >= 0; --i) {
    if (ans[i]) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
}