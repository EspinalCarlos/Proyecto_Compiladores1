#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include "Token.hpp"

class Lexer {

private:

    std::string codigo;

    int posicion;
    int linea;
    int columna;

    std::vector<Token> tokens;

    char actual();
    void avanzar_cadena();

    void agregarToken(TokenType tipo,const std::string& lexema,int lineaInicio,int columnaInicio);

    void Identificador();
    void Numero();
    void String();
    void Char();
    void Delimitador();
    void Operador();

    TokenType verificarPalabraReservada(const std::string& palabra);

public:

    Lexer(const std::string& codigo);

    std::vector<Token> tokenizar();
};

#endif