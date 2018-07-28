#ifndef VERTEX_H
#include <string>
#include <unordered_set>
#include <iostream>

template<typename K, typename V>
struct Vertex {
  V data;
  K key;
  Vertex() {}
  Vertex(const K& key, const V& data) {
    this->key = key;
    this->data = data;
  }
  bool operator== (const Vertex& rhs) {
    return this->key == rhs.key;
  }
};

#endif
