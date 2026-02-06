#ifndef _REGISTRO_H_
#define _REGISTRO_H_

#include <string>
#include <vector>
#include <ctime>
#include <iostream>

class Registro {

  private:
    std::string mes;
    std::string dia;
    std::string horas;
    std::string minutos;
    std::string segundos;
    std::string ip;
    std::string puerto;
    std::string falla;

    std::vector<std::string> meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    // https://cplusplus.com/reference/ctime/tm/
    struct tm dateStruct;
    // Linux timestamp (segundos transcurridos desde el 1 de enero de 1970)
    time_t fechaHora;

  public:
    Registro();
    Registro(std::string _mes, std::string _dia, std::string _horas, std::string _minutos, std::string _segundos, std::string _ip, std::string _puerto, std::string _falla);
    std::string getAll();
    // sobrecarga de operadores de comparacion
    bool operator ==(const Registro &other) const;
    bool operator !=(const Registro &other) const;
    bool operator  >(const Registro &other) const;
    bool operator  <(const Registro &other) const;
    bool operator >=(const Registro &other) const;
    bool operator <=(const Registro &other) const;
    friend std::ostream& operator<<(std::ostream& os, const Registro &other);
};



#endif  // _REGISTRO_H_
