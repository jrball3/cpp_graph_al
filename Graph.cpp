#ifndef GRAPH_H
#include "Vertex.h"
#include <algorithm>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>

typedef int GraphKey;

// Custom comparator that compares the string objects by length
template<typename T>
struct PtrKeyComparator
{
  bool operator()(const T* obj1, const T* obj2) const {
    return obj1->key == obj2->key;
  }
  bool operator()(const GraphKey& obj1, const T* obj2) const {
    return obj1 == obj2->key;
  }
  bool operator()(const T* obj1, const GraphKey& obj2) const {
    return obj1->key == obj2;
  }
};

template<class T>
class Graph {
  typedef Vertex<GraphKey, T> GVertex;
  typedef std::unordered_set<GVertex*> AdjacencyList;
private:
  std::map<GraphKey, GVertex> vertices;
  std::map<GraphKey, AdjacencyList> adjLists;
  GraphKey key;
  GraphKey generateKey() {
    return this->key++;
  }

public:
  Graph() : key(0) {};
  GraphKey addVertex(const T& data);
  bool removeVertex(const GraphKey& key);
  bool adjacent(const GraphKey& root, const GraphKey& target);
  bool connected(const GraphKey& key1, const GraphKey& key2);
  std::vector<GVertex> neighbors(const GraphKey& key);
  void addEdge(const GraphKey& key1, const GraphKey& key2);
};

template<class T>
GraphKey Graph<T>::addVertex(const T& data) {
  GraphKey k = this->generateKey();
  this->vertices[k] = GVertex(k, data);
  this->adjLists[k] = AdjacencyList();
  return k;
}

template<class T>
bool Graph<T>::removeVertex(const GraphKey& key) {
  if (key >= this->vertices.size())
    return false;

  for (GraphKey i = 0; i < this->vertices.size() ; ++i) {
    if (i == key)
      continue;
    auto remIt = find_if(this->adjLists[i].begin(),
                         this->adjLists[i].end(),
                         [key](GVertex* v){return v->key == key;});
    if (remIt != this->adjLists[i].end()) {
      this->adjLists[i].erase(remIt);
    }
  }
  this->vertices.erase(this->vertices.find(key));
  this->adjLists.erase(this->adjLists.find(key));
  return true;
}

template<class T>
void Graph<T>::addEdge(const GraphKey& key1, const GraphKey& key2) {
  // Find the set for n1
  if (!this->adjacent(key1, key2)) {
    this->adjLists[key1].insert(&this->vertices[key2]);
  }

  // Find the set for n2
  if (!this->adjacent(key2, key1)) {
    this->adjLists[key2].insert(&this->vertices[key1]);
  }
}

template<class T>
bool Graph<T>::connected(const GraphKey& key1, const GraphKey& key2) {
  return this->adjacent(key1, key2) && this->adjacent(key2, key1);
}

template<class T>
bool Graph<T>::adjacent(const GraphKey& root, const GraphKey& target) {
  auto got = find_if(this->adjLists[root].begin(),
                     this->adjLists[root].end(),
                     [target](GVertex * pv){return pv->key == target;});
  return got != this->adjLists[root].end();
}

template<class T>
std::vector<Vertex<GraphKey, T> > Graph<T>::neighbors(const GraphKey& key) {
  std::vector<GVertex> ret;
  for (auto it = this->adjLists[key].begin(); it != this->adjLists[key].end(); ++it) {
    ret.push_back(**it);
  }
  return ret;
}

#endif
