#ifndef _NODEOPENHASH_H_
#define _NODEOPENHASH_H_

template <class K, class T>
class NodeOpenHash {
  private:
    K key;
    T data;
    NodeOpenHash<K, T>* next;

  public:
    NodeOpenHash(K keyValue, T dataValue);
    ~NodeOpenHash();
    K getKey();
    T getData();
    NodeOpenHash<K, T>* getNext();
    void setNext(NodeOpenHash<K, T>* nextNode);
};

template<class K, class T>
NodeOpenHash<K,T>::NodeOpenHash(K keyValue, T dataValue) {
  key = keyValue;
  data = dataValue;
  next = nullptr;
}

template<class K, class T>
NodeOpenHash<K,T>::~NodeOpenHash() {
  next = nullptr;
}

template<class K, class T>
K NodeOpenHash<K,T>::getKey() {
  return key;
}

template<class K, class T>
T NodeOpenHash<K,T>::getData() {
  return data;
}

template<class K, class T>
NodeOpenHash<K, T>* NodeOpenHash<K,T>::getNext() {
  return next;
}

template<class K, class T>
void NodeOpenHash<K,T>::setNext(NodeOpenHash<K, T>* nextNode) {
  next = nextNode;
}

#endif  