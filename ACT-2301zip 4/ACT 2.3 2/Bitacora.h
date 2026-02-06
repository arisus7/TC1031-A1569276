#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Registro.h"
#include "DoublyLinkedList.h"

class Bitacora {
  private:
    //std::vector<Registro> listaRegistros;
    DoublyLinkedList<Registro> listaRegistros;

    

    //void quickSort(int inicio, int fin);
    //int particion(int inicio, int fin);
    //void bubbleSort();

    //int busquedaBinaria(const Registro& objetivo);

  public:
    Bitacora();
    ~Bitacora();
    // TO-DO
    void leerArchivo(std::string filePath);
    void imprimirTodo();
    void ordenarQuicksort();

    //........................................................................
    std::pair<NodeDLL<Registro>*, NodeDLL<Registro>*> buscarRango (
      const Registro& inicio,
      const Registro& fin
    );

    void imprimirRango(
      NodeDLL<Registro>* inicio,
      NodeDLL<Registro>* fin
    );

    void guardarRango(
      std::string filePath,
      NodeDLL<Registro>* inicio,
      NodeDLL<Registro>* fin
    );

    void guardarArchivo(std::string filePath);
    //........................................................................

/*

    void ordenarBubbleSort();
    int buscarRegistro(const Registro& objetivo);
    void imprimirRango( int inicio, int fin);
    void guardarArchivo(std::string filePath);
    
    long long getComparaciones();
    long long getSwaps();
*/
};


#endif  // _BITACORA_H_
