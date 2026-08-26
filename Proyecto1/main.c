#include <stdio.h>

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

    if (tipo()) {
        printf("Tipo valido\n");
    } else {
        printf("Error de sintaxis\n");
    }

    return 0;
}