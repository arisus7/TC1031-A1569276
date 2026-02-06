#ifndef _MAXHEAP_H_
#define _MAXHEAP_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>
#include <string>

// MaxHeap para almacenar pares (grado, IP)
// El heap se ordena por el grado (primer elemento del par)
class MaxHeap {
private:
    std::vector<std::pair<int, std::string>> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    MaxHeap();
    ~MaxHeap();

    void push(int grado, std::string ip);
    std::pair<int, std::string> top();
    void pop();
    bool isEmpty();
    int size();
};

// Constructor O(1)
MaxHeap::MaxHeap() {}

// Destructor O(1)
MaxHeap::~MaxHeap() {
    heap.clear();
}

// O(log n)
void MaxHeap::heapifyUp(int index) {
    if (index == 0) return;

    int p = parent(index);
    // Si el hijo es mayor que el padre, intercambiar
    if (heap[index].first > heap[p].first) {
        std::swap(heap[index], heap[p]);
        heapifyUp(p);
    }
}

// O(log n)
void MaxHeap::heapifyDown(int index) {
    int largest = index;
    int left = leftChild(index);
    int right = rightChild(index);

    // Encontrar el mayor entre padre, hijo izquierdo y derecho
    if (left < (int)heap.size() && heap[left].first > heap[largest].first)
        largest = left;

    if (right < (int)heap.size() && heap[right].first > heap[largest].first)
        largest = right;

    // Si el mayor no es el padre, intercambiar y continuar
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

// Insertar elemento O(log n)
void MaxHeap::push(int grado, std::string ip) {
    heap.push_back(std::make_pair(grado, ip));
    heapifyUp(heap.size() - 1);
}

// Obtener el máximo O(1)
std::pair<int, std::string> MaxHeap::top() {
    if (isEmpty())
        throw std::out_of_range("El heap esta vacio");
    return heap[0];
}

// Eliminar el máximo O(log n)
void MaxHeap::pop() {
    if (isEmpty())
        throw std::out_of_range("El heap esta vacio");

    // Mover el último elemento a la raíz
    heap[0] = heap.back();
    heap.pop_back();

    // Reorganizar el heap
    if (!isEmpty())
        heapifyDown(0);
}

// Verificar si está vacío O(1)
bool MaxHeap::isEmpty() {
    return heap.empty();
}

// Obtener tamaño O(1)
int MaxHeap::size() {
    return heap.size();
}

#endif // _MAXHEAP_H_