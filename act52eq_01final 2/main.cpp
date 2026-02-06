/**
 * Ejemplo que implementa Grafos representados como lista de adyacencia y el
 *recorrido DFS
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -g -o main *.cpp
 * Ejecucion con valgrind:
 *    modify hidden file replit.nix to add pkgs.valgrind
 *    valgrind --run-libc-freeres=no --leak-check=full ./main <
 *TestCases/graph01.txt
 *
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -O3 -o main *.cpp
 * Ejecucion:
 *    ./main < TestCases/graph01.txt
 **/

#include "Graph.h"
#include "HashTable.h"
#include <algorithm>
#include <iostream>
#include <sstream>

// Estructura de resumen de IP 
struct IPResumen {
  std::string ip;
  int outDegree;
  int inDegree;
};

//  Convertir IP (string) a llave numérica 
unsigned long long ipToKey(const std::string &ip) {
  unsigned long long key = 0;
  for (char c : ip) {
    if (c != '.') {
      key = key * 31 + (c - '0');
    }
  }
  return key;
}

int main() {
  try {

    // Leer bitácora y construir grafo
    Graph<std::string> grafo;

    std::cout << "\nLeyendo archivo de bitácora..." << std::endl;
    grafo.readGraphFromBitacora("bitacoraGrafos.txt");

    std::cout << "\n✓ Grafo cargado exitosamente!" << std::endl;
    std::cout << "Número de nodos (IPs únicas): " << grafo.getNumNodes() << std::endl;

    // Comentado: imprime TODO el grafo (13,000+ nodos), muy largo
    // std::cout << "\nInfo del grafo:" << std::endl;
    // grafo.print();


    //  Calcular grados de entrada

    std::vector<int> inDegree = grafo.getInDegrees();


    // Crear y llenar HashTable

    HashTable<unsigned long long, IPResumen> hashIPs;
    hashIPs.setMaxSize(26003); // número primo - factor de carga ~0.51

    std::cout << "\nInsertando IPs en tabla hash..." << std::endl;
    int insertadas = 0;
    int duplicadas = 0;

    for (int i = 0; i < grafo.getNumNodes(); i++) {
      IPResumen r;
      r.ip = grafo.getNodeInfo(i);
      r.outDegree = grafo.getOutDegree(i);
      r.inDegree = inDegree[i];

      unsigned long long key = ipToKey(r.ip);

      try {
        hashIPs.add(key, r);
        insertadas++;
      } catch (const std::out_of_range &e) {
        // IP duplicada en el archivo, ignorar
        duplicadas++;
      }
    }

    std::cout << "IPs insertadas: " << insertadas << std::endl;
    if (duplicadas > 0) {
      std::cout << "IPs duplicadas ignoradas: " << duplicadas << std::endl;
    }


    //  Mostrar colisiones

    std::cout << "\nColisiones totales: " << hashIPs.getColisiones() << std::endl;

    std::cout << "Factor de carga (α): " << hashIPs.getAlfa() << std::endl;


    //  getIPSummary()

    std::string ip;
    std::cout << "\nIngresa una IP para consultar: ";
    std::cin >> ip;

    unsigned long long key = ipToKey(ip);
    int pos = hashIPs.find(key);

    if (pos == -1) {
      std::cout << "IP no encontrada en la bitácora.\n";
    } else {
      IPResumen r = hashIPs.getDataAt(pos);

      std::cout << "\nResumen de IP: " << r.ip << std::endl;
      std::cout << "Grado de salida: " << r.outDegree << std::endl;
      std::cout << "Grado de entrada: " << r.inDegree << std::endl;

      // Obtener lista de IPs accedidas
      std::vector<std::string> accesos;

      // Buscar el índice del nodo correspondiente a esta IP
      int idx = -1;
      for (int i = 0; i < grafo.getNumNodes(); i++) {
        if (grafo.getNodeInfo(i) == ip) {
          idx = i;
          break;
        }
      }

      if (idx != -1) {
        NodeLinkedList<std::pair<int, int>> *ptr = grafo.getAdjList(idx);

        while (ptr != nullptr) {
          int destino = ptr->getData().first;
          accesos.push_back(grafo.getNodeInfo(destino)); 
          ptr = ptr->getNext();
        }

        // Ordenar descendente
        std::sort(accesos.begin(), accesos.end(), std::greater<std::string>());

        std::cout << "\nIPs accedidas (orden descendente):" << std::endl;
        for (const auto &s : accesos) {
          std::cout << s << std::endl;
        }
      }
    }


    //  Funcionalidad extra que ya teniamos

    std::cout << "\nCalculando grados de salida..." << std::endl;
    grafo.calcularGradosSalida("grados_ips.txt");

    std::cout << "\nBuscando las 7 IPs con mayor grado de salida..."
              << std::endl;
    grafo.encontrarMayoresGrados(7, "mayores_grados_ips.txt");

    std::cout << "\nCalculando distancias desde el boot master..." << std::endl;
    grafo.calcularDistanciasBootMaster("distancias_bootmaster.txt");

    std::cout << "\nArchivos generados correctamente.\n" << std::endl;

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}