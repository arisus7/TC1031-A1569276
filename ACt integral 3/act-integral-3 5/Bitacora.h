#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <queue>
#include <utility>


#include "Registro.h"

class Bitacora {
  private:
    std::vector<Registro> listaRegistros;


    int busquedaBinaria(const Registro& objetivo);

  public:
    Bitacora();
    ~Bitacora();
    // TO-DO
    void leerArchivo(std::string filePath);
void ordenarPorIPHeapSort(); 
void guardarTop10IPs(std::string filePath);


    void imprimirRango( int inicio, int fin);
    void guardarArchivo(std::string filePath);
    void imprimirTodo();

};


#endif  // _BITACORA_H_
