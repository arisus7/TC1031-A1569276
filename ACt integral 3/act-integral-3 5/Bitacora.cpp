#include "Bitacora.h"
#include <fstream>
#include <sstream>

Bitacora::Bitacora() {}

Bitacora :: ~Bitacora(){
  listaRegistros.clear();
}
// Complejidad: O(n)
void Bitacora::leerArchivo(std::string filePath) {
  std::ifstream archivo(filePath);

  if (!archivo.is_open()){
    throw std::runtime_error( "No se pudo abrir el archivo :(" + filePath);
  }

  // logica de lectura 
  std::string linea;
  while (std::getline(archivo, linea)){

    std:: istringstream iss(linea); //para separar la linea en partes
    std::string mes, dia, hora, ip, falla;
    iss>> mes;
    iss>> dia;
    iss>> hora;
    iss>> ip;
    std:: string mensaje;
    std:: getline(iss, mensaje);
    if (!mensaje.empty() && mensaje[0] == ' '){ 
      mensaje.erase(0,1);
    }

    // Separar Horas, Minutos, Segundos
    size_t pos1 = hora.find(':');
    size_t pos2 = hora.find(':', pos1 + 1);
    std::string h = hora.substr(0, pos1);
    std::string m = hora.substr(pos1 + 1, pos2 - pos1 - 1);
    std::string s = hora.substr(pos2 + 1);

    // Separar IP y Puerto
    size_t posIp = ip.find(':');
    std::string soloIp = ip.substr(0, posIp);
    std::string puerto = (posIp != std::string::npos) ? ip.substr(posIp + 1) : "0";

    // Crear registro y agregar al vector (8 parámetros en total)
    Registro reg(mes, dia, h, m, s, soloIp, puerto, mensaje);
    listaRegistros.push_back(reg);
  }
  archivo.close();
  std::cout << "se leyeron" << listaRegistros.size() << "registros" << std::endl;
}



  // HEAP SORT POR IP (sin puerto) 
// Complejidad: O(log n)
  static void heapifyPorIP(std::vector<Registro>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2; 

 if (l < n && arr[largest].getIpKey() < arr[l].getIpKey()) {
        largest = l;
    }
    if (r < n && arr[largest].getIpKey() < arr[r].getIpKey()) {
        largest = r;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapifyPorIP(arr, n, largest);
    }
}
// Complejidad: O(n log n)
  void Bitacora::ordenarPorIPHeapSort() {
    int n = (int)listaRegistros.size();

    // construir heap (max-heap)
    for (int i = n / 2 - 1; i >= 0; i--) {
      heapifyPorIP(listaRegistros, n, i);
    }

    // heap sort
    for (int i = n - 1; i > 0; i--) {
      std::swap(listaRegistros[0], listaRegistros[i]);
      heapifyPorIP(listaRegistros, i, 0);
    }
  }

  //  TOP 10 IPs con más accesos 
// Complejidad: O(n log k)
  void Bitacora::guardarTop10IPs(std::string filePath) {
    std::ofstream out(filePath);
    if (!out.is_open()) {
      throw std::runtime_error("No se pudo abrir el archivo :(" + filePath);
    }

    // (accesos, ip)  priority_queue que saca el mayor primero
    std::priority_queue<std::pair<int, std::string>> pq;

    int n = (int)listaRegistros.size();
    int i = 0;

    while (i < n) {
      std::string ipActual = listaRegistros[i].getIp();
      int contador = 0;

      while (i < n && listaRegistros[i].getIp() == ipActual) {
        contador++;
        i++;
      }

      pq.push({contador, ipActual});
    }

    std::cout << "\nTop 10 IPs con mayor acceso:\n";
    for (int k = 0; k < 10 && !pq.empty(); k++) {
      auto top = pq.top();
      pq.pop();

      int accesos = top.first;
      std::string ip = top.second;

      std::cout << ip << " " << accesos << std::endl;
      out << ip << " " << accesos << "\n";
    }

    out.close();
  }


//para guardar archivo
// Complejidad: O(n)
void Bitacora::guardarArchivo(std::string filePath){
  std::ofstream archivo(filePath); 

  if (!archivo.is_open()){
    throw std::runtime_error("No se pudo abrir el archivo :(" + filePath);
  }

  for (const auto& registro : listaRegistros){
    archivo << registro;
  }

  archivo.close();
  std::cout << "Se guardaron los registros en el archivo" << std::endl;
}

// imprmir todo
void Bitacora:: imprimirTodo(){
  for (const auto& registro : listaRegistros){
    std::cout << registro;
  }
}

