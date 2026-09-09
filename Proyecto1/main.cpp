#include <iostream>
#include <vector>

#include "Lexer.hpp"

int main() {

    std::string codigo = "let resultado = 25\n"
        "let nombre = \"hola mundo\"";

    Lexer lexer(codigo);

    std::vector<Token> tokens = lexer.tokenizar();

    for (Token token : tokens) {

        std::cout<< "Tipo: " << static_cast<int>(token.tipo) << " | Lexema: " << token.lexema << " | Linea: " << token.linea << " | Columna: " << token.columna << std::endl;
    }

    return 0;
}