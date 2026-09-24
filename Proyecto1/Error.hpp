#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>

enum class TipoError {
    LEXICO,
    SINTACTICO
};

struct ErrorCompilador {

    TipoError tipo;

    std::string mensaje;

    int linea;
    int columna;
};

#endif
