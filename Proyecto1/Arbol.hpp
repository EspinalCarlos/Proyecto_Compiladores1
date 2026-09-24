#ifndef ARBOL_HPP
#define ARBOL_HPP

#include <string>

struct Nodo {
    std::string valor;
    Nodo* hijoIzquierdo;
    Nodo* hermanoDerecho;
    Nodo(const std::string& valor) {
        this->valor = valor;
        hijoIzquierdo = nullptr;
        hermanoDerecho = nullptr;
    }
};
void agregarHijo(Nodo* padre, Nodo* hijo);
void imprimirArbol(Nodo* nodo,int nivel = 0);
#endif
