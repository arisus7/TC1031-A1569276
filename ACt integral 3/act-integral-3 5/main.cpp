#include "Bitacora.h"
#include <iostream>

int main() {
  try {
    Bitacora b;

    b.leerArchivo("bitacoraHeap.txt");          // 1) leer
    b.ordenarPorIPHeapSort();                   // 2) heapsort por IP
    b.guardarArchivo("bitacora_ordenada.txt");  // 3) guardar ordenada
    b.guardarTop10IPs("ips_con_mayor_acceso.txt"); // 4) top 10

  } catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  return 0;
}
