/** 
* Ejemplo que implementa objetos de la clase Registro
* que contienen una fecha-hora convertida a Linux timestamp
* para realizar comparaciones (sobrecarga de operadores)
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main
**/
//Mariana Aguilar Requena A01569276
//Valeria Salazar Pinto A01736652
//Santiago Martin del Campo A01713396
//Fecha: 2026-01-20

#include <iostream>
#include <sstream>
#include <string>
#include "Bitacora.h"

int main() {
    // Instanciar la bitácora
    Bitacora miBitacora;

    // lee el archivo de texto
    std::cout << "Leyendo archivo 'bitacora.txt'..." << std::endl;
    try {
        miBitacora.leerArchivo("bitacora.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    Bitacora bitacoraOriginal;
    miBitacora.leerArchivo("bitacora.txt");

    // Copias independientes
    Bitacora bitacoraQuick = miBitacora;
    Bitacora bitacoraBubble = miBitacora;
    bitacoraQuick.ordenarQuicksort();
    bitacoraBubble.ordenarBubbleSort();

    // ordena los datos
    std::cout << "Ordenando datos con QuickSort..." << std::endl;
    miBitacora.ordenarQuicksort();
  
    // guarda los datos ordenados en un archivo nuevo
    std::cout << "Guardando datos ordenados en 'bitacora_ordenada.txt'..." << std::endl;
    miBitacora.guardarArchivo("bitacora_ordenada.txt");

    // solicita búsqueda por rango al usuario
    std::string mesInicio, diaInicio, mesFin, diaFin, horaInicio, horaFin;

    std::cout << "\n--- Busqueda de registros por fecha ---" << std::endl;
    std::cout << "Ingrese fecha de INICIO (Mes Dia Hora:Minuto:Segundo)\n";
    std::cin >> mesInicio >> diaInicio >> horaInicio;

    std::cout << "\nIngrese fecha de FIN (Mes Dia Hora:Minuto:Segundo)\n";
    std::cin >> mesFin >> diaFin >> horaFin;

    int h, m, s;
    char colon;

    std::stringstream Hora(horaInicio);
    Hora >> h >> colon >> m >> colon >> s;         

    int hF, mF, sF;

    std::stringstream HoraF(horaFin);
    HoraF >> hF >> colon >> mF >> colon >> sF;    


    // Creamos objetos Registro temporales para usar la busqueda binaria
    // Se usan valores minimos de hora para el inicio y maximos para el fin

    Registro registroInicio(mesInicio, diaInicio, std::to_string(h), std::to_string(m),std::to_string(s), "0.0.0.0", "0", "inicio");
    Registro registroFin(mesFin, diaFin, std::to_string(hF), std::to_string(mF), std::to_string(sF), "255.255.255.255", "9999",             "fin");

    // Buscamos los indices
    int idxInicio = miBitacora.buscarRegistro(registroInicio);
    int idxFin = miBitacora.buscarRegistro(registroFin);

    // muestra resultados del rango
    if (idxInicio != -1 && idxFin != -1) {
        std::cout << "\nRegistros encontrados en ese rango:" << std::endl;
        miBitacora.imprimirRango(idxInicio, idxFin);
    } else {
        std::cout << "\nNo se encontraron registros en el rango de fechas proporcionado." << std::endl;
    }
  
    std::cout << "\n--- Comparaciones y Swaps ---" << std::endl;
    std::cout << "Bubble Sort:" << std::endl;
    std::cout << "Comparaciones: "<< bitacoraBubble.getComparaciones() <<std::endl;
    std::cout << "Swaps: " << bitacoraBubble.getSwaps() << std::endl; 

    std::cout << "\nQuick Sort:" << std::endl;
    std::cout << "Comparaciones: "<< bitacoraQuick.getComparaciones() <<std::endl;
    std::cout << "Swaps: " << bitacoraQuick.getSwaps() << std::endl; 

    return 0;
}