#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int N = 4;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
char dir[4] = {'L', 'R', 'U', 'D'};

struct State {
  int a[N][N];
  int x, y; // position of '0'
  int f, g; // f = g + h
  int pre; // previous state's index in the queue

  bool operator < (const State& other) const {
    return f > other.f;
  }
};

int h(State& s) {
  int res = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (s.a[i][j] != 0) {
        int x = (s.a[i][j] - 1) / N;
        int y = (s.a[i][j] - 1) % N;
        res += abs(x - i) + abs(y - j);
      }
    }
  }
  return res;
}

bool is_valid(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < N;
}

void print_ans(vector<State>& states, int cur) {
  if (cur == -1) return;
  print_ans(states, states[cur].pre);
  for (int i = 0; i < 4; i++) {
    int nx = states[cur].x + dx[i];
    int ny = states[cur].y + dy[i];
    if (is_valid(nx, ny) && states[cur].a[nx][ny] == 0) {
      printf("%c", dir[i]);
      break;
    }
  }
}

int main() {
  State start;
  memset(&start, 0, sizeof(start));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      scanf("%d", &start.a[i][j]);
      if (start.a[i][j] == 0) {
        start.x = i;
        start.y = j;
      }
    }
  }
  start.g = 0;
  start.f = h(start);
  start.pre = -1;

  priority_queue<State> q;
  q.push(start);

  vector<State> states;
  while (!q.empty()) {
    State cur = q.top();
    q.pop();
    if (cur.f == cur.g) {// reach the goal
      printf("%d\n", cur.g);
      print_ans(states, states.size() - 1);
      printf("\n");
      return 0;
    }
    states.push_back(cur);
    int cur_idx = states.size() - 1;

    for (int i = 0; i < 4; i++) {
      int nx = cur.x + dx[i];
      int ny = cur.y + dy[i];
      if (is_valid(nx, ny)) {
        State next = cur;
        swap(next.a[cur.x][cur.y], next.a[nx][ny]);
        next.x = nx;
        next.y = ny;
        next.g = cur.g + 1;
        next.f = next.g + h(next);
        next.pre = cur_idx;
      }
    }
  }
}