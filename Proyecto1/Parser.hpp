#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

#include "Token.hpp"
#include "Arbol.hpp"
#include "Error.hpp"
#include "TablaSimbolos.hpp"

class Parser {

private:

    std::vector<Token> tokens;
    int posicion;
    std::vector<ErrorCompilador> errores;
    TablaSimbolos tablaSimbolos;

    // Manejo Tokens

    Token actual();
    Token anterior();
    bool fin();
    void avanzar();
    bool verificar(TokenType tipo);
    bool coincidir(TokenType tipo);
    bool consumir(TokenType tipo,const std::string& mensaje);

    // Errores

    void errorSintactico(const std::string& mensaje);

    void sincronizar();

    // Gramatica

    Nodo* Programa();
    Nodo* Funcion();
    Nodo* Parametros();
    std::string Tipo();
    Nodo* Bloque();
    Nodo* Sentencia();
    Nodo* Declaracion();
    Nodo* If();
    Nodo* While();
    Nodo* Return();
    Nodo* For();

    // Expresiones

    Nodo* Expresion();
    Nodo* LogicoOr();
    Nodo* LogicoAnd();
    Nodo* Igualdad();
    Nodo* Comparacion();
    Nodo* Termino();
    Nodo* Factor();
    Nodo* Unario();
    Nodo* Primario();


public:

    Parser(const std::vector<Token>& tokens);
    Nodo* parsear();
    std::vector<ErrorCompilador>
    obtenerErrores();
    const TablaSimbolos&
    obtenerTablaSimbolos() const;
};

#endif
