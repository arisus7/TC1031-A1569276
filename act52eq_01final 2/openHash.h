#ifndef _OPENHASH_H_
#define _OPENHASH_H_

#include "NodeOpenHash.h"
#include <iostream>
#include <stdexcept>
#include <vector>

template <class K, class T> class openHash {
private:
  std::vector<NodeOpenHash<K, T> *> table;
  int numElements;
  int maxSize;

  int getHashIndex(K keyValue);

public:
  openHash();
  openHash(int selectedMaxSize);
  ~openHash();
  void setMaxSize(int selectedMaxSize);
  int getNumElements();
  void print();
  void add(K keyValue, T dataValue);
  T find(K keyValue);
  void remove(K keyValue);
  double getAlfa();

  bool contains(K keyValue) const;
  openHash<K, T> unionWith (const openHash<K, T> &other);
  openHash<K, T> intersectionWith (const openHash<K, T> &other);
};

template <class K, class T> openHash<K, T>::openHash() {
  maxSize = 0;
  numElements = 0;
  table = std::vector<NodeOpenHash<K, T> *>(maxSize, nullptr);
}

template <class K, class T> openHash<K, T>::openHash(int selectedMaxSize) {
  maxSize = selectedMaxSize;
  numElements = 0;
  table = std::vector<NodeOpenHash<K, T> *>(maxSize, nullptr);
}

template <class K, class T> openHash<K, T>::~openHash() {
  for (int i = 0; i < maxSize; i++) {
    NodeOpenHash<K, T> *current = table[i];
    while (current != nullptr) {
      NodeOpenHash<K, T> *temp = current;
      current = current->getNext();
      delete temp;
    }
  }
  table.clear();
  maxSize = 0;
  numElements = 0;
}

template <class K, class T>
void openHash<K, T>::setMaxSize(int selectedMaxSize) {
  for (int i = 0; i < maxSize; i++) {
    NodeOpenHash<K, T> *current = table[i];
    while (current != nullptr) {
      NodeOpenHash<K, T> *temp = current;
      current = current->getNext();
      delete temp;
    }
  }

  maxSize = selectedMaxSize;
  numElements = 0;
  table = std::vector<NodeOpenHash<K, T> *>(maxSize, nullptr);
}

template <class K, class T> int openHash<K, T>::getHashIndex(K keyValue) {
  return keyValue % maxSize;
}

template <class K, class T> int openHash<K, T>::getNumElements() {
  return numElements;
}

//Complejidad 0(m + n) 
template <class K, class T> void openHash<K, T>::print() {
  std::cout << "Contenido de la tabla hash (Open Hashing)" << std::endl;
  for (int i = 0; i < maxSize; i++) {
    std::cout << "Bucket [" << i << "]: ";
    NodeOpenHash<K, T> *current = table[i];
    if (current == nullptr) {
      std::cout << "vacio";
    } else {
      while (current != nullptr) {
        std::cout << "(" << current->getKey() << ", " << current->getData()
                  << ")";
        if (current->getNext() != nullptr) {
          std::cout << " -> ";
        }
        current = current->getNext();
      }
    }
    std::cout << std::endl;
  }
}


//complejidad add: O(1) en promedio
template <class K, class T>
void openHash<K, T>::add(K keyValue, T dataValue) {
  if (maxSize == 0) {
    throw std::out_of_range("La tabla hash no ha sido inicializada");
  }

  int hashIndex = getHashIndex(keyValue);

  NodeOpenHash<K, T> *current = table[hashIndex];
  while (current != nullptr) {
    if (current->getKey() == keyValue) {
      throw std::out_of_range("El elemento ya existe en la tabla hash");
    }
    current = current->getNext();
  }

  NodeOpenHash<K, T> *newNode = new NodeOpenHash<K, T>(keyValue, dataValue);
  newNode->setNext(table[hashIndex]);
  table[hashIndex] = newNode;
  numElements++;
}

//complejidad find: O(1) en promedio, 0(n) en el peor caso
template <class K, class T> T openHash<K, T>::find(K keyValue) {
  if (maxSize == 0) {
    throw std::out_of_range("La tabla hash no ha sido inicializada");
  }

  int hashIndex = getHashIndex(keyValue);

  NodeOpenHash<K, T> *current = table[hashIndex];
  while (current != nullptr) {
    if (current->getKey() == keyValue) {
      return current->getData();
    }
    current = current->getNext();
  }

  throw std::out_of_range("El elemento no existe en la tabla hash");
}

template <class K, class T> double openHash<K, T>::getAlfa() {
  if (maxSize == 0) {
    return 0.0;
  }
  return (double)numElements / (double)maxSize;
}

/////

//complejidad remove: O(1) en promedio, O(n) en el peor caso
template <class K, class T>
void openHash<K, T>::remove(K keyValue) {
  if (maxSize == 0) {
    throw std::out_of_range("La tabla no ha sido inicializada");
  }
  int hashIndex = getHashIndex(keyValue);

  NodeOpenHash<K, T>* current = table[hashIndex];
  NodeOpenHash<K, T>* previous = nullptr;

  while (current != nullptr) {
    if (current -> getKey() == keyValue) {
      if (previous == nullptr) {
        table[hashIndex] = current -> getNext();
      } 
      else {
        previous -> setNext(current -> getNext());
      }
      delete current;
      numElements--;
      return;
    }
    previous = current;
    current = current -> getNext();
  }
  throw std::out_of_range("El elemento no existe en la tabla hash");
}

/////

//complejidad contains: O(1) en promedio, O(n) en el peor caso
template <class K, class T>
bool openHash<K, T>::contains(K keyValue) const{
  if (maxSize == 0) return false;

  int hashIndex = keyValue % maxSize;
  NodeOpenHash<K, T>* current = table[hashIndex];

  while (current != nullptr) {
    if (current -> getKey() == keyValue) return true;
    current = current -> getNext();
  }
  return false;
}

/////

//complejidad unionWith: O(m + n)
template <class K, class T>
openHash<K, T> openHash<K, T>::unionWith(const openHash<K, T>& other) {
  int newSize = (maxSize + other.maxSize) ? maxSize : other.maxSize;
  if (newSize <= 0) newSize = 1;

  openHash<K, T> result(newSize);

  for (int i = 0; i < maxSize; i++) {
    NodeOpenHash<K, T>* current = table[i];
    while (current != nullptr) {
        result.add(current -> getKey(), current -> getData());
        current = current -> getNext();
      }
    }

    for (int i = 0; i < other.maxSize; i++) {
      NodeOpenHash<K, T>* current = other.table[i];
      while (current != nullptr) {
        if (!result.contains(current -> getKey())) {
          result.add(current -> getKey(), current -> getData());
        }
        current = current -> getNext();
      }
    }
    return result;
  }

//////

//complejidad intersectionWith: O(m + n)
template <class K, class T>
openHash<K, T> openHash<K, T>::intersectionWith(const openHash<K, T>& other) {
  int newSize = (maxSize < other.maxSize) ? maxSize : other.maxSize;
  if (newSize <= 0) newSize = 1;

  openHash<K, T> result(newSize);

  const openHash <K, T>* small = this;
  const openHash <K, T>* large = &other;

  if (other.numElements < this -> numElements) {
    small = &other;
    large = this;
  }

  for (int i = 0; i < small ->maxSize; i++) {
    NodeOpenHash<K, T>* current = small -> table[i];
    while (current != nullptr) {
      if (large -> contains(current -> getKey())) {
        result.add(current -> getKey(), current -> getData());
      }
      current = current -> getNext();
    }
  }
  return result;
}


#endif