#include "Graph.cpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<class T>
void printNeighbors(Graph<T> &g, GraphKey k) {
  cout << "Vertex " << to_string(k) + string(" neighbors") << ": [";
  vector<Vertex<GraphKey, T> > neighbors = g.neighbors(k);
  for(auto it = neighbors.begin(); it != neighbors.end(); ++it) {
    cout << it->key << ": " << it->data;
    if (it+1 != neighbors.end())
      cout << ", ";
  }
  cout << "]" << endl;
}

int main(int argc, char * argv[]) {

  Graph<string> g;
  GraphKey v1 = g.addVertex("v1 data");
  GraphKey v2 = g.addVertex("v2 data");
  GraphKey v3 = g.addVertex("v3 data");
  g.addEdge(v1, v2);
  g.addEdge(v2, v3);
  assert(g.connected(v1, v2));
  assert(g.connected(v2, v3));
  assert(!g.connected(v1, v3));
  printNeighbors(g, v1);
  printNeighbors(g, v2);
  printNeighbors(g, v3);
  g.removeVertex(v2);
  assert(g.neighbors(v1).size() == 0);
  assert(g.neighbors(v3).size() == 0);

  return 0;
}
