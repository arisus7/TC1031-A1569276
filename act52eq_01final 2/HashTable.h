#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <vector>
#include <iostream>
#include <stdexcept>
#include "NodeHashTable.h"

template <class K, class T>
class HashTable {
  private:
    std::vector<NodeHashTable<K, T>> table;
    int numElements;
    // Es preferible usar un numero primo
    // https://numerosprimos.org/numeros-primos-de-1-a-100000/
    int maxSize;
    double alfa; // factor de carga (numElements / maxSize)
    unsigned int colisiones; // colisiones totales hasta el momento

  public:
    HashTable();
    ~HashTable();
    void setMaxSize(int selectedMaxSize);
    // Funcion hash (metodo de residuales)
    int getHashIndex(K keyValue);
    int getNumElements();
    void print();
    void add(K keyValue, T dataValue);
    int find(K keyValue);
    T getDataAt(int index);
    void remove(K keyValue);
    double getAlfa();
    unsigned int getColisiones();

};
// O(1)
template<class K, class T>
HashTable<K,T>::HashTable() {
  maxSize = 0;
  numElements = 0;
  table = std::vector<NodeHashTable<K, T>>(maxSize);
  colisiones = 0;
  alfa = 0.0;
}
// O(1)
template<class K, class T>
HashTable<K,T>::~HashTable() {
  maxSize = 0;
  numElements = 0;
  table = std::vector<NodeHashTable<K, T>>(maxSize);
  colisiones = 0;
  alfa = 0.0;
}
// O(1)
template<class K, class T>
void HashTable<K,T>::setMaxSize(int selectedMaxSize) {
  maxSize = selectedMaxSize;
  numElements = 0;
  table = std::vector<NodeHashTable<K, T>>(maxSize);
  colisiones = 0;
  alfa = 0.0;
}
// Funcion hash (metodo de residuales) O(1)
template<class K, class T>
  int HashTable<K,T>::getHashIndex(K keyValue) {
    int index = (int)(keyValue % maxSize);
    if (index < 0) {
      index += maxSize;
    }
    return index;
  }

// O(1)
template<class K, class T>
int HashTable<K,T>::getNumElements() {
  return numElements;
}
// O(n)
template<class K, class T>
void HashTable<K,T>::print() {
  std::cout << "Contenido de la tabla hash" << std::endl;
  for (int i = 0; i < maxSize; i++) {
    // 0 empty,  1 used,  2 deleted
    if (table[i].getStatus() == 1) {
      std::cout << "Celda: " << i << " Key: " << table[i].getKey() << ", Value: " << table[i].getData() << ", Overflow.size: " << table[i].getOverflowSize() << std::endl;
    }
  }
}
// O(1/1-alpha) en promedio
template<class K, class T>
void HashTable<K,T>::add(K keyValue, T dataValue) {
  if (numElements == maxSize) {
    throw std::out_of_range("La hash table esta llena");
  }
  if (find(keyValue) != -1) {
    throw std::out_of_range("El elemento ya existe en la tabla hash");
  }
  // Calcular el index en la tabla hash
  int hashIndex = getHashIndex(keyValue);
  NodeHashTable<K, T> node = table[hashIndex];
  // 0 empty,  1 used,  2 deleted
  if (node.getStatus() != 1) { // la celda esta libre
    node.setKey(keyValue);
    node.setData(dataValue);
    table[hashIndex] = node;
  }
  else { // la celda NO esta libre (colision)
    // Muestreo cuadratico para manejo de colisiones
    colisiones++;
    int i = 1;
    int currentHashIndex = getHashIndex(hashIndex + i * i);
    NodeHashTable<K, T> currentNode = table[currentHashIndex];
    while (currentNode.getStatus() == 1) { // la celda esta ocupada
      i++;
      currentHashIndex = getHashIndex(hashIndex + i * i); // Muestreo cuadratico
      currentNode = table[currentHashIndex];
      colisiones++;
    }
    // Se ha encontrado una celda libre
    currentNode.setKey(keyValue);
    currentNode.setData(dataValue);
    node.addToOverflow(currentHashIndex);
    table[currentHashIndex] = currentNode;
    table[hashIndex] = node;
  }
  numElements++;
}
// O(1) en promedio
template<class K, class T>
int HashTable<K,T>::find(K keyValue) {
  // Calcular el index en la tabla hash
  int hashIndex = getHashIndex(keyValue);
  NodeHashTable<K, T> node = table[hashIndex];
  // 0 empty,  1 used,  2 deleted
  if (node.getStatus() == 1) {
    if (node.getKey() == keyValue)
      return hashIndex;
    for (int i = 0; i < (int)node.getOverflowSize(); i++) {
      int overflowIndex = node.getOverflowAt(i);
      if (table[overflowIndex].getKey() == keyValue)
        return overflowIndex;
    }
    return -1;
  }
  return -1;
}
// O(1)
template<class K, class T>
T HashTable<K,T>::getDataAt(int index) {
  return table[index].getData();
}
// O(1) en promedio
template<class K, class T>
void HashTable<K,T>::remove(K keyValue) {
  int pos, hashIndex;
  pos = find(keyValue);
  if (pos == -1) {
    throw std::out_of_range("El elemento no existe en la tabla hash");
  }
  hashIndex = getHashIndex(keyValue);
  if (pos != hashIndex) {
    NodeHashTable<K, T> node = table[hashIndex];
    node.removeFromOverflow(pos);
    table[hashIndex] = node;
  }
  table[pos].clearData();
  numElements--;
}
// O(1)
template<class K, class T>
double HashTable<K,T>::getAlfa() {
  double tmp = (double)numElements / (double)maxSize;
  return tmp;
}
// O(1)
template<class K, class T>
unsigned int HashTable<K,T>::getColisiones() {
  return colisiones;
}

#endif // _HASH_TABLE_H_