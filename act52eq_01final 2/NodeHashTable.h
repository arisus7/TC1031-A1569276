#ifndef _NODEHASHTABLE_H_
#define _NODEHASHTABLE_H_

#include <vector>
#include <algorithm>
#include <iterator>

template <class K, class T>
class NodeHashTable {
  private:
    K key;
    T data;
    int status; 
    std::vector<int> overflow; 

  public:
    NodeHashTable();
    ~NodeHashTable();
    K getKey();
    T getData();
    int getStatus();
    void setKey(K keyValue);
    void setData(T dataValue);
    void setStatus(int statusValue);
    void clearData();
    void addToOverflow(int hashIndex);
    int getOverflowSize();
    int getOverflowAt(int index);
    void removeFromOverflow(int index);
};

template<class K, class T>
NodeHashTable<K,T>::NodeHashTable() {
  data = {};
  status = 0;  // empty
  overflow.clear();
}
template<class K, class T>
NodeHashTable<K,T>::~NodeHashTable() {
  data = {};
  status = 0;  // empty
  overflow.clear();
}
template<class K, class T>
K NodeHashTable<K,T>::getKey() {
  return key;
}
template<class K, class T>
T NodeHashTable<K,T>::getData() {
  return data;
}
template<class K, class T>
int NodeHashTable<K,T>::getStatus() {
  return status;
}
template<class K, class T>
void NodeHashTable<K,T>::setKey(K keyValue) {
  key = keyValue;
}
template<class K, class T>  
void NodeHashTable<K,T>::setData(T dataValue) {
  data = dataValue;
  status = 1; // 1 es used
}
template<class K, class T>  
void NodeHashTable<K,T>::setStatus(int statusValue) {
  status = statusValue;
}
template<class K, class T>
void NodeHashTable<K,T>::clearData() {
  data = {};
  status = 2; // 2 es deleted
}
template<class K, class T>
void NodeHashTable<K,T>::addToOverflow(int hashIndex) {
  overflow.push_back(hashIndex);
}
template<class K, class T>
int NodeHashTable<K,T>::getOverflowSize() {
  return overflow.size();
}
template<class K, class T>
int NodeHashTable<K,T>::getOverflowAt(int index) {
  return overflow[index];
}
template<class K, class T>
void NodeHashTable<K,T>::removeFromOverflow(int index) {
  std::vector<int>::iterator it = std::find(overflow.begin(), overflow.end(), index);
  // if index was found
  if (it != overflow.end()) {
    overflow.erase(overflow.begin()+(it-overflow.begin()));
  }
}

#endif  // _NODEHASHTABLE_H_