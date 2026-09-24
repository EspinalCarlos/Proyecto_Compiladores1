#include "TablaSimbolos.hpp"

#include <iostream>

int TablaSimbolos::insertar(
    const std::string& lexema,
    const std::string& tipo
) {

    Simbolo simbolo;

    simbolo.id = simbolos.size();
    simbolo.lexema = lexema;
    simbolo.tipo = tipo;

    simbolos.push_back(simbolo);

    return simbolo.id;
}


void TablaSimbolos::imprimir() const {

    std::cout << "ID\tLEXEMA\t\tTIPO\n";
    std::cout << "--------------------------------\n";

    for (const Simbolo& simbolo : simbolos) {

        std::cout
            << simbolo.id << "\t"
            << simbolo.lexema << "\t\t"
            << simbolo.tipo
            << '\n';
    }
}


const std::vector<Simbolo>&
TablaSimbolos::obtenerSimbolos() const {

    return simbolos;
}
