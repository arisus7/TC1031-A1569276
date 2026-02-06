#include "Registro.h"

Registro::Registro() {
  mes = "";
  dia = "";
  horas = "";
  minutos = "";
  segundos = "";
  ip = "";
  puerto = "";
  falla = "";
  fechaHora = 0;
}

Registro::Registro(std::string _mes, std::string _dia, std::string _horas, std::string _minutos, std::string _segundos, std::string _ip, std::string _puerto, std::string _falla) {
    mes = _mes;
    dia = _dia;
    horas = _horas;
    minutos = _minutos;
    segundos = _segundos;
    ip = _ip;
    puerto = _puerto;
    falla = _falla;
    // Convertir a Linux timestamp
    dateStruct.tm_hour = std::stoi(horas);
    dateStruct.tm_min = std::stoi(minutos);
    dateStruct.tm_sec = std::stoi(segundos);
    dateStruct.tm_mday = std::stoi(dia);
    // resuelve problemas de compatibilidad con Windows
    dateStruct.tm_isdst = 0;
    for (int i = 0; i < (int)meses.size(); i++) {
      if (meses[i] == mes)
        dateStruct.tm_mon = i;
    }
    dateStruct.tm_year = 2026 - 1900; // asumimos el año 2024
    // Obtener el Linux timestamp
    // https://cplusplus.com/reference/ctime/mktime/
    fechaHora = mktime(&dateStruct);
    //std::cout << "fechaHora: " << fechaHora << std::endl;
}

std::string Registro::getAll() {
  return mes + " " + dia + " " + horas + ":" + minutos + ":" + segundos + " " + ip + ":" + puerto + " " + falla;  
}

// sobrecarga de operadores de comparacion
bool Registro::operator ==(const Registro &other) const {
  return this->fechaHora == other.fechaHora;
}

bool Registro::operator !=(const Registro &other) const {
  return this->fechaHora != other.fechaHora;
}

bool Registro::operator  >(const Registro &other) const {
  return this->fechaHora > other.fechaHora;
}

bool Registro::operator  <(const Registro &other) const{
  return this->fechaHora < other.fechaHora;
}

bool Registro::operator >=(const Registro &other) const{
  return this->fechaHora >= other.fechaHora;
}

bool Registro::operator <=(const Registro &other) const{
  return this->fechaHora <= other.fechaHora;
}

std::ostream& operator<<(std::ostream& os, const Registro& reg) {
    os << reg.mes + " " + reg.dia + " " + reg.horas + ":" + reg.minutos + ":" + reg.segundos + " " + reg.ip + ":" + reg.puerto + " " + reg.falla << std::endl;
    return os;
}