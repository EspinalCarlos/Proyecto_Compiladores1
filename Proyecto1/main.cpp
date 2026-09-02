#include <iostream>
#include "Automatas.hpp"
using namespace std;
typedef enum {
    TOKEN_I32,
    TOKEN_F64,
    TOKEN_BOOL,
    TOKEN_CHAR,
    TOKEN_STR,
    TOKEN_EOF
} TipoToken;

TipoToken tokens[] = {
    TOKEN_CHAR,
    TOKEN_EOF
};

int posicion = 0;

/*
    Gramatica:

    <TIPO> ::= i32
             | f64
             | bool
             | char
             | str
*/

int tipo() {
    switch (tokens[posicion]) {

        case TOKEN_I32:
        case TOKEN_F64:
        case TOKEN_BOOL:
        case TOKEN_CHAR:
        case TOKEN_STR:
            posicion++;
            return 1;

        default:
            return 0;
    }
}

int main() {

    /*if (tipo()) {
        printf("Tipo valido\n");
    } else {
        printf("Error de sintaxis\n");
    }*/
    cout<<"Prueba de automatas\n";
    cout <<"Identificadores:\n";
    cout << "hola: "<< esIdentificador("hola") << '\n';
    cout << "_variable: "<< esIdentificador("_variable") << '\n';
    cout << "3variable: "<< esIdentificador("3variable") << '\n';

    cout<<"Numeros:\n";
    cout << "123: "<< esNumero("123") << '\n';
    cout << "3.14: "<< esNumero("3.14") << '\n';
    cout << "12.34.56: "<< esNumero("12.34.76") << '\n';
    cout << "abc: "<< esNumero("abc") << '\n';

    cout<<"Strings:\n";
    cout << "\"hola\": "<< esString("\"hola\"") << '\n';
    cout << "\"hola mundo\": "<< esString("\"hola mundo\"") << '\n';
    cout << "\"hola\\nmundo\": " << esString("\"hola\\nmundo\"") << '\n';
    cout << "\"hola\\z\": "<< esString("\"hola\\z\"") << '\n';
    return 0;
}