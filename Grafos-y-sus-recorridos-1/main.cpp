/** 
* Ejemplo que implementa Grafos representados como lista de adyacencia y el recorrido DFS
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    modify hidden file replit.nix to add pkgs.valgrind
*    valgrind --run-libc-freeres=no --leak-check=full ./main < TestCases/graph01.txt
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main < TestCases/graph01.txt
**/

#include <iostream>
#include <sstream>
#include "Graph.h"

/*
  int main() {
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf();
  // Construye un grafo
  Graph<std::string> g1;
  // Lee de archivo un grafo, directed=1, weighted=1
  // lista de adyacencia
  g1.readGraph(inputInfo, 1, 1);
  g1.print();
  g1.DFS(3); // nodo es cero basado
  std::cout << std::endl;
  return 0;
}
//*/

int main() {
  try {

    Graph<std::string> grafo;                               // Crear grafo

    std::cout << "\n Leyendo archivo de bitácora..." << std::endl;
    grafo.readGraphFromBitacora("bitacoraGrafos.txt");                 // 1) Leer archivo y construir grafo

    std::cout << "\n Calculando grados de salida de cada IP" << std::endl;
    grafo.calcularGradosSalida("grados_ips.txt");          // 3) Calcular y guardar grados de salida

    std::cout << "\n Buscando las 7 IPs con mayor grado de salida..." << std::endl;
    grafo.encontrarMayoresGrados(7, "mayores_grados_ips.txt"); // 4) Encontrar top 7 con MaxHeap

    std::cout << "\n Calculando distancias desde el boot master..." << std::endl;
    grafo.calcularDistanciasBootMaster("distancias_bootmaster.txt"); // 5) Calcular distancias desde boot master

    std::cout << "\nArchivos generados:" << std::endl;
    std::cout << "  - grados_ips.txt (todos los grados de salida)" << std::endl;
    std::cout << "  - mayores_grados_ips.txt (top 7 IPs)" << std::endl;
    std::cout << "\n" << std::endl;

  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}