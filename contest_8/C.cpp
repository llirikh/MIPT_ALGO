#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int least_reachable_city(int n, vector<vector<int>>& edges, int mileage) {
  // Create adjacency list
  map<int, vector<pair<int, int>>> graph;
  for (auto& e : edges) {
    int u = e[0], v = e[1], w = e[2];
    if (graph.find(u) == graph.end()) {
      graph[u] = {{v, w}};
    } else {
      graph[u].push_back({v, w});
    }
    if (graph.find(v) == graph.end()) {
      graph[v] = {{u, w}};
    } else {
      graph[v].push_back({u, w});
    }
  }
  // Local function to compute shortest paths to reachable cities
  auto num_reachable_neighbors = [&](int city) {
    // Create a min-heap with the starting city at distance 0
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
    heap.push({0, city});
    // Keep track of distances to cities
    map<int, int> distances;
    // Process the heap until it's empty
    while (!heap.empty()) {
      int currDist = heap.top().first, neighb = heap.top().second;
      heap.pop();
      // Skip if we already know the shortest distance to this city
      if (distances.find(neighb) != distances.end()) {
        continue;
      }
      // Add this city to the distances map if it's reachable
      if (neighb != city) {
        distances[neighb] = currDist;
      }
      // Process all neighbors of this city
      for (auto& p : graph[neighb]) {
        int node = p.first, d = p.second;
        // Add to the heap if the neighbor is reachable and we haven't visited it before
        if (distances.find(node) == distances.end() && currDist + d <= mileage) {
          heap.push({currDist + d, node});
        }
      }
    }
    // Return the number of reachable cities
    return distances.size();
  };
  // Compute the number of reachable neighbors for each city
  map<int, int> cities_neighbors;
  for (int city = 0; city < n; city++) {
    int num_neighbors = num_reachable_neighbors(city);
    cities_neighbors[num_neighbors] = city;
  }
  // Return the city with the fewest reachable neighbors
  return cities_neighbors.begin()->second;
}

