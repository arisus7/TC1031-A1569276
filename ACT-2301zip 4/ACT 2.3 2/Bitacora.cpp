#include "Bitacora.h"
#include <sstream>

Bitacora::Bitacora() {

}

Bitacora :: ~Bitacora(){
  //listaRegistros.clear();
}

void Bitacora::leerArchivo(std::string filePath) {
  std::ifstream archivo(filePath);

  if (!archivo.is_open()){
    throw std::runtime_error( "No se pudo abrir el archivo :(" + filePath);
  }
  
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
    //listaRegistros.push_back(reg);
    listaRegistros.addFirst(reg);
  }
  archivo.close();
  std::cout << "se leyeron " << listaRegistros.getNumElements() << " registros" << std::endl;
}

// imprmir todo
void Bitacora:: imprimirTodo() {
  listaRegistros.printList();
}

void Bitacora::ordenarQuicksort() {
  std::pair<long long, long long> resultados;
  resultados = listaRegistros.ordendaConQuickSort();
  //resultados.first comparacion
  //resultados.second swaps
  std::cout << "comparaciones: " << resultados.first << std::endl;
  std::cout << "swaps: " << resultados.second << std::endl;
  
}

/*
//AQUI VA BUBBLE SORT
//complejidad O(n^2)
void Bitacora::ordenarBubbleSort() {
  comparaciones = 0;
  swaps = 0;
  int n = listaRegistros.size();
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      comparaciones++;
      if (listaRegistros[j] > listaRegistros[j + 1]) {
        std::swap(listaRegistros[j], listaRegistros[j + 1]);
        swaps++;
      }
    }
  }
}



//complejidad O(n log n)
void Bitacora::quickSort(int inicio, int fin) {
  if (inicio < fin) {
    int pi = particion(inicio, fin);
    quickSort(inicio, pi - 1);
    quickSort(pi + 1, fin);
  }
}

//complejidad O(n)
int Bitacora::particion(int inicio, int fin) {
  Registro pivot = listaRegistros[fin];
  int i = (inicio - 1);
  for (int j = inicio; j < fin; j++) {
    comparaciones++;
    if (listaRegistros[j] <= pivot) {
      i++;
      std::swap(listaRegistros[i], listaRegistros[j]);
      swaps++;
    }
  }
  std::swap(listaRegistros[i + 1], listaRegistros[fin]);
  swaps++;
  return (i + 1);
}

int Bitacora::buscarRegistro(const Registro& objetivo) {
  return busquedaBinaria(objetivo);
}

//complejidad O(log n)
int Bitacora::busquedaBinaria(const Registro& objetivo) {
  int l = 0;
  int r = listaRegistros.size() - 1;
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (listaRegistros[m] == objetivo) return m;
    if (listaRegistros[m] < objetivo) l = m + 1;
    else r = m - 1;
  }
  return -1;
}

//imprimir rango
void Bitacora::imprimirRango(int inicio, int fin){
  std::cout << "\n=== Registros en el rango ===" << std::endl;
  for (int i = inicio; i <= fin && i < (int)listaRegistros.size(); i++) {
    std::cout << listaRegistros[i];
  }
}

//para guardar archivo
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



long long Bitacora::getComparaciones() {
  return comparaciones;
};
long long Bitacora::getSwaps() {
  return swaps;
};
*/