#ifndef _REGISTRO_H_
#define _REGISTRO_H_

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

class Registro {
private:
  std::string mes;
  std::string dia;
  std::string hora;
  std::string ip;     // sin puerto
  std::string puerto; // solo numero
  std::string mensaje;

  // Convierte IP "10.15.175.231" a "010.015.175.231" para comparar bien
// Complejidad: O(1)
  std::string ipKey() const {
    std::stringstream ss(ip);
    std::string parte;
    std::string key = "";

    while (std::getline(ss, parte, '.')) {
      int num = std::stoi(parte);
      std::ostringstream out;
      out << std::setw(3) << std::setfill('0') << num;
      if (!key.empty()) key += ".";
      key += out.str();
    }
    return key;
  }

public:
  Registro() {}

  Registro(std::string mes, std::string dia,
           std::string h, std::string m, std::string s,
           std::string soloIp, std::string puerto,
           std::string mensaje) {
    this->mes = mes;
    this->dia = dia;
    this->hora = h + ":" + m + ":" + s;
    this->ip = soloIp;
    this->puerto = puerto;
    this->mensaje = mensaje;
  }

  std::string getIp() const { return ip; }
  std::string getIpKey() const { return ipKey(); }

  friend std::ostream& operator<<(std::ostream& os, const Registro& r) {
    os << r.mes << " " << r.dia << " " << r.hora << " "
       << r.ip << ":" << r.puerto << " " << r.mensaje << "\n";
    return os;
  }
};

#endif
