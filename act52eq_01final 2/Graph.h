#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <fstream>
#include <queue>
#include <limits>
#include "LinkedList.h"
#include "StackLL.h"
#include "MaxHeap.h"

template <class T> 
class Graph {
private:
  int numNodes;
  int numEdges;
  int directedGraph;  // 1 dirigido; 0 no-dirigido
  int weightedGraph;  // 1 ponderado; 0 no-ponderado
  int bootMasterIndex = -1; // índice del boot master
  int bootMasterDegree = -1; // grado del boot master
  std::string bootMasterIP = ""; // IP del boot master
  // Cada nodo tiene un id y un objeto de datos tipo T
  std::map<int, T> nodesInfo;
  // Lista de adyacencia (vector de listas de pares <nodo,peso>)
  std::vector<LinkedList<std::pair<int, int>>> adjList;

  void split(std::string line, std::vector<int> &res);

public:
  Graph();
  ~Graph();
  void readGraph(std::istream &input, int _directed, int _weighted);
  void print(int flagInfo = 0);
  void DFS(int v); // vertice cero basado
  // To-do act 4.1 y 4.2
  void BFS(int v);
  // https://www.geeksforgeeks.org/dsa/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
  // https://www.youtube.com/watch?v=K_1urzWrzLs&t=40s
  int getBootMasterIndex() const;
  std::string getBootMasterIP() const;
  void calcularDistanciasBootMaster(const std::string &outputFile);
  std::pair<std::vector<int>, std::vector<int>> shortestPath(int v); // Algoritmo de Dijkstra

  // Métodos para actividad de grafos
  void readGraphFromBitacora(std::string fileName);
  void calcularGradosSalida(std::string outputFile);
  void encontrarMayoresGrados(int k, std::string outputFile);
  std::string getNodeInfo(int nodeIndex);
  int getNumNodes() const;
  NodeLinkedList<std::pair<int,int>>* getAdjList(int index);
  std::vector<int> getInDegrees();
  int getOutDegree(int index);
};

// O(1)
template <class T> 
Graph<T>::Graph() {
  numNodes = 0;
  numEdges = 0;
  directedGraph = 1;
  weightedGraph = 1;
}

// O(1)
template <class T> 
Graph<T>::~Graph() {
  adjList.clear();
  numNodes = 0;
  numEdges = 0;
  directedGraph = 1;
  weightedGraph = 1;
}
// O(k), k - numero de elementos en la linea
template <class T>
void Graph<T>::split(std::string line, std::vector<int> &res) {
  size_t strPos = line.find(" ");
  size_t lastPos = 0;
  while (strPos != std::string::npos) {
    res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
    lastPos = strPos + 1;
    strPos = line.find(" ", lastPos);
  }
  res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

// O(n+m), n - numero de nodos, m - numero de aristas
template <class T>
void Graph<T>::readGraph(std::istream &input, int _directed, int _weighted) {
  directedGraph = _directed;
  weightedGraph = _weighted;
  std::string line;
  int i = 0;
  while (std::getline(input, line)) {
    if (i == 0) { // Ignorar primera linea de texto (comentario)
      i++;
      continue;
    }
    if (i == 1) { // Leemos numNodes y numEdges
      std::vector<int> res;
      split(line, res);
      numNodes = res[0];
      numEdges = res[1];
      // Reservar memoria para los numNodes renglones (cero basado) y 
      // listas vacias de pares (nodo, peso) 
      adjList.resize(numNodes, LinkedList<std::pair<int, int>>());
      i++;
      continue;
    }
    if (i > 1 && i < numNodes + 2) { // Para cada nodo se lee su informacion
      T data = line; // ATENCION: convertir al tipo de dato adecuado
      // map <key, data> con los nodos indexados cero basados
      nodesInfo.insert(std::make_pair(i - 2, data));
      i++;
      continue;
    }
    // Lee las aristas
    std::vector<int> res;
    split(line, res);
    // nodos cero basados
    int nodeU = res[0] - 1;
    int nodeV = res[1] - 1;
    // Si el grafo es ponderado se lee tambien el peso
    // grafo no ponderado entonces aristas con peso 1
    int weight = (weightedGraph == 1) ? res[2] : 1;
    // Siempre se agrega la arista (nodeU, nodeV)
    adjList[nodeU].addLast(std::make_pair(nodeV, weight));
    // Si el grafo es no dirigido agrega tambien la arista (nodeV, nodeU)
    if (directedGraph == 0)
      adjList[nodeV].addLast(std::make_pair(nodeU, weight));
    i++;
  }
}

// O(nm), n - numero de nodos, m - numero de aristas
template <class T> 
void Graph<T>::print(int flagInfo) {
  std::cout << "numNodes: " << numNodes << std::endl;
  std::cout << "numEdges: " << numEdges << std::endl;
  std::cout << "Adjacency List" << std::endl;
  for (int nodeU = 0; nodeU < numNodes; nodeU++) {
    if (flagInfo) // Se imprime la info del nodo
      std::cout << "vertex " << nodesInfo[nodeU] << ": ";
    else // Se imprime el numero de nodo
      std::cout << "vertex " << nodeU + 1 << ": ";
    NodeLinkedList<std::pair<int, int>> *ptr = adjList[nodeU].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      int nodeV = par.first;
      int weight = par.second;
      std::string nodeData = (flagInfo) ? nodesInfo[nodeV] + ", " : "";
      if (weightedGraph == 1) // grafo ponderado
        std::cout << "{" << nodeData << nodeV + 1 << ", " << weight << "} ";
      else
        std::cout << "{" << nodeData << nodeV + 1 << "} ";
      ptr = ptr->next;
    }
    std::cout << std::endl;
  }
}

// O(n+m) donde n=|V| y m=|E|
// recibe un vertice cero basado
template <class T> 
void Graph<T>::DFS(int v) {
  // Declaramos un stack
  StackLL<int> stack;
  // Declaramos un conjunto (set) del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  // Marcar como visitado el vertice de partida y meterlo en el stack
  stack.push(v);
  std::cout << "Recorrido DFS: " << std::endl;
  while (!stack.isEmpty()) {
    // Extraer un vertice del stack
    v = stack.peek();
    stack.pop();
    // Procesar el vertice si no ha sido visitado
    bool isVisited = visited.find(v) != visited.end();
    if (!isVisited) { // No ha sido visitado
      visited.insert(v);
      std::cout << v+1 << ", ";
    }
    //Obtener vecinos del vertice v
    // Si estos no han sido visitados marcarlos como visitados
    // y los metemos al stack
    NodeLinkedList<std::pair<int, int>> *ptr = adjList[v].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      int u = par.first;
      bool isVisited = visited.find(u) != visited.end();
      if (!isVisited) { // No ha sido visitado
        stack.push(u);
      }
      ptr = ptr->next;
    }
  }
  std::cout << std::endl;
}

// Método para leer bitácora de grafos O(n+m)
template <class T>
void Graph<T>::readGraphFromBitacora(std::string fileName) {

  std::ifstream input(fileName);
  if (!input.is_open()) {
    throw std::runtime_error("No se pudo abrir el archivo: " + fileName);
  }

  directedGraph = 1;  // Grafo dirigido
  weightedGraph = 1;  // Grafo ponderado
  std::string line;
  int lineNum = 0;
  std::map<std::string, int> ipToIndex;

  while (std::getline(input, line)) {
    if (lineNum == 0) {
      // Primera línea: numNodos numAristas
      std::istringstream iss(line);
      iss >> numNodes >> numEdges;
      adjList.resize(numNodes, LinkedList<std::pair<int, int>>());
      lineNum++;
      continue;
    }

    if (lineNum > 0 && lineNum <= numNodes) {
      // Leer las IPs (nodos)
      T ip = line;
      int nodeIndex = lineNum - 1;
      nodesInfo.insert(std::make_pair(nodeIndex, ip));
      ipToIndex[ip] = nodeIndex;
      lineNum++;
      continue;
    }

    // Leer aristas
    std::istringstream iss(line);
    std::string mes, dia, hora, ipOrigenConPuerto, ipDestinoConPuerto;
    int peso;

    iss >> mes >> dia >> hora >> ipOrigenConPuerto >> ipDestinoConPuerto >> peso;

    // Extraer IP sin puerto
    size_t posOrigen = ipOrigenConPuerto.find(':');
    std::string ipOrigen = ipOrigenConPuerto.substr(0, posOrigen);

    size_t posDestino = ipDestinoConPuerto.find(':');
    std::string ipDestino = ipDestinoConPuerto.substr(0, posDestino);

    // Obtener índices y agregar arista
    if (ipToIndex.find(ipOrigen) != ipToIndex.end() && 
        ipToIndex.find(ipDestino) != ipToIndex.end()) {
      int nodeU = ipToIndex[ipOrigen];
      int nodeV = ipToIndex[ipDestino];
      adjList[nodeU].addLast(std::make_pair(nodeV, peso));
    }

    lineNum++;
  }
}

// Obtener información de un nodo O(1)
template <class T>
std::string Graph<T>::getNodeInfo(int nodeIndex) {
  if (nodeIndex >= 0 && nodeIndex < numNodes) {
    return nodesInfo[nodeIndex];
  }
  return "";
}

// Calcular grado de salida O(n+m)
template <class T>
void Graph<T>::calcularGradosSalida(std::string outputFile) {
  std::ofstream out(outputFile);
  if (!out.is_open()) {
    throw std::runtime_error("No se pudo abrir el archivo: " + outputFile);
  }

  std::cout << "\n=== Calculando grados de salida ===" << std::endl;

  for (int i = 0; i < numNodes; i++) {
    int gradoSalida = adjList[i].getNumElements();
    std::string ip = nodesInfo[i];
    out << ip << " " << gradoSalida << "\n";
  }

  out.close();
  std::cout << "Grados de salida guardados en: " << outputFile << std::endl;
}

// Encontrar k nodos con mayor grado usando MaxHeap O(n log k)
template <class T>
void Graph<T>::encontrarMayoresGrados(int k, std::string outputFile) {
  MaxHeap heap;

  std::cout << "\n=== Encontrando las " << k << " IPs con mayor grado de salida ===" << std::endl;

  // Insertar todos los nodos en el heap
  for (int i = 0; i < numNodes; i++) {
    int gradoSalida = adjList[i].getNumElements();
    std::string ip = nodesInfo[i];
    heap.push(gradoSalida, ip);
  }

  // Abrir archivo de salida
  std::ofstream out(outputFile);
  if (!out.is_open()) {
    throw std::runtime_error("No se pudo abrir el archivo: " + outputFile);
  }

  // Extraer los k elementos con mayor grado
  std::cout << "\nTop " << k << " IPs con mayor grado de salida:" << std::endl;

  std::pair<int, std::string> bootMaster;
  bool firstElement = true;

  for (int i = 0; i < k && !heap.isEmpty(); i++) {
    std::pair<int, std::string> top = heap.top();
    heap.pop();

    int grado = top.first;
    std::string ip = top.second;

    std::cout << (i+1) << ". " << ip << " - Grado: " << grado << std::endl;
    out << ip << " " << grado << "\n";

    if (firstElement) {
      bootMaster = top;
      firstElement = false;
    }
  }

  out.close();

  bootMasterIP = bootMaster.second;
  bootMasterDegree = bootMaster.first;

  bootMasterIndex = -1;
  for (const auto& pair : nodesInfo) {
    if (pair.second == bootMasterIP) {
      bootMasterIndex = pair.first;
      break;
    }
  }
  std::cout << "\nMayores grados guardados en: " << outputFile << std::endl;

  // Mostrar boot master
  std::cout << "\n=== BOOT MASTER IDENTIFICADO ===" << std::endl;
  std::cout << "La IP con mayor grado de salida (presunto boot master) es:" << std::endl;
  std::cout << "IP: " << bootMaster.second << std::endl;
  std::cout << "Grado de salida: " << bootMaster.first << std::endl;
  std::cout << "\nEsto significa que esta IP intentó conectarse a " << bootMaster.first 
            << " IPs diferentes," << std::endl;
  std::cout << "lo cual es indicativo de un comportamiento de boot master (ataque distribuido)." << std::endl;
}

//getters boot master
template <class T>
int Graph<T>::getBootMasterIndex() const {
  return bootMasterIndex;
}

template <class T>
std::string Graph<T>::getBootMasterIP() const {
  return bootMasterIP;
}

//////////////////

// Método para calcular distancias desde el boot master usando Dijkstra
template <class T>
void Graph<T>::calcularDistanciasBootMaster(const std::string &outputFile) {

  if (bootMasterIndex == -1) {
    int bestDegree = -1;
    int bestIndex = -1;

    for (int i = 0; i < numNodes; i++) {
      int deg = adjList[i].getNumElements();
      if (deg > bestDegree) {
        bestDegree = deg;
        bestIndex = i;
      }
    }

    bootMasterIndex = bestIndex;
    bootMasterDegree = bestDegree;
    bootMasterIP = (bestIndex != -1) ? nodesInfo[bestIndex] : "";
  }

  if (bootMasterIndex == -1) {
    throw std::runtime_error("Boot master no identificado.");
  }

  const long long INF = std::numeric_limits<long long>::max() / 4;
  std::vector<long long> dist(numNodes, INF);
  dist[bootMasterIndex] = 0;

  using P = std::pair<long long, int>;
  std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
  pq.push({0, bootMasterIndex});

  while (!pq.empty()) {
    auto [currentDist, u] = pq.top();
    pq.pop();
    if (currentDist != dist[u]) continue;

    NodeLinkedList<std::pair<int, int>> *ptr = adjList[u].getHead();
    while (ptr != nullptr) {
      int v = ptr->data.first;
      int w = ptr->data.second;

      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        pq.push({dist[v], v});
      }
      ptr = ptr->next;
    }
  }

  std::ofstream out(outputFile);
  if (!out.is_open()) {
    throw std::runtime_error("No se pudo abrir el archivo: " + outputFile);
  }

  for (int i = 0; i < numNodes; i++) {
    long long d = (dist[i] >= INF/2) ? -1 : dist[i];
    out << nodesInfo[i] << " " << d << "\n";
    }
    out.close();

  std::cout << "\n Distancias desde el boot master guardadas en: " << outputFile << std::endl;

  long long maxD = -1;
  int idxMax = -1;

  for (int i = 0; i < numNodes; i++) {
    if (i == bootMasterIndex) continue;
    if (dist[i] < INF/2 && dist[i] > maxD) {
      maxD = dist[i];
      idxMax = i;
    }
  }

  if (idxMax != -1) {
    std::cout << "La IP que requiere más esfuerzo para que el boot master la ataque es: "
              << nodesInfo[idxMax] << " ... distancia total = " << maxD << std::endl;
  } else {
    std::cout << "Todos los nodos son inalcanzables desde el boot master." << std::endl;
  }
}

template <class T>
int Graph<T>::getNumNodes() const {
  return numNodes;
}

template <class T>
std::vector<int> Graph<T>::getInDegrees() {
  std::vector<int> inDegree(numNodes, 0);

  for (int u = 0; u < numNodes; u++) {
    NodeLinkedList<std::pair<int,int>>* ptr = adjList[u].getHead();
    while (ptr != nullptr) {
      int v = ptr->data.first;
      inDegree[v]++;
      ptr = ptr->next;
      }
    }
    return inDegree;
  }

template <class T>
int Graph<T>::getOutDegree(int index) {
  if (index < 0 || index >= numNodes) return 0;
  return adjList[index].getNumElements();
}

// MÉTODO CORREGIDO: getAdjList debe retornar el head de la lista de adyacencia
template <class T>
NodeLinkedList<std::pair<int,int>>* Graph<T>::getAdjList(int index) {
  if (index < 0 || index >= numNodes)
    return nullptr;
  return adjList[index].getHead();
}

#endif // _GRAPH_H_
