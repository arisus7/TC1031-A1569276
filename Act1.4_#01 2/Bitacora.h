#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Registro.h"

class Bitacora {
  private:
    std::vector<Registro> listaRegistros;
    long long comparaciones;
    long long swaps;

    void quickSort(int inicio, int fin);
    int particion(int inicio, int fin);
    void bubbleSort();

    int busquedaBinaria(const Registro& objetivo);

  public:
    Bitacora();
    ~Bitacora();
    // TO-DO
    void leerArchivo(std::string filePath);
    void ordenarQuicksort();
    void ordenarBubbleSort();
    int buscarRegistro(const Registro& objetivo);
    void imprimirRango( int inicio, int fin);
    void guardarArchivo(std::string filePath);
    void imprimirTodo();
    long long getComparaciones();
    long long getSwaps();
};


#endif  // _BITACORA_H_
