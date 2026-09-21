#include <iostream>
#include <vector>

#include "Lexer.hpp"


std::string nombreToken(TokenType tipo) {

    switch (tipo) {

        case TokenType::IDENTIFICADOR:
            return "IDENTIFICADOR";

        case TokenType::ENTERO:
            return "ENTERO";

        case TokenType::DECIMAL:
            return "DECIMAL";

        case TokenType::STRING_LITERAL:
            return "STRING_LITERAL";

        case TokenType::CHAR_LITERAL:
            return "CHAR_LITERAL";

        case TokenType::LET:
            return "LET";

        case TokenType::FN:
            return "FN";

        case TokenType::IF:
            return "IF";

        case TokenType::ELSE:
            return "ELSE";

        case TokenType::WHILE:
            return "WHILE";

        case TokenType::FOR:
            return "FOR";

        case TokenType::RETURN:
            return "RETURN";

        case TokenType::TYPE_I32:
            return "TYPE_I32";

        case TokenType::TYPE_F64:
            return "TYPE_F64";

        case TokenType::TYPE_BOOL:
            return "TYPE_BOOL";

        case TokenType::TYPE_CHAR:
            return "TYPE_CHAR";

        case TokenType::TYPE_STR:
            return "TYPE_STR";

        case TokenType::PLUS:
            return "PLUS";

        case TokenType::MINUS:
            return "MINUS";

        case TokenType::MULTIPLY:
            return "MULTIPLY";

        case TokenType::DIVIDE:
            return "DIVIDE";

        case TokenType::AND:
            return "AND";

        case TokenType::OR:
            return "OR";

        case TokenType::NOT:
            return "NOT";

        case TokenType::ASSIGN:
            return "ASSIGN";

        case TokenType::EQUAL:
            return "EQUAL";

        case TokenType::NOT_EQUAL:
            return "NOT_EQUAL";

        case TokenType::LESS:
            return "LESS";

        case TokenType::LESS_EQUAL:
            return "LESS_EQUAL";

        case TokenType::GREATER:
            return "GREATER";

        case TokenType::GREATER_EQUAL:
            return "GREATER_EQUAL";

        case TokenType::ARROW:
            return "ARROW";

        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";

        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";

        case TokenType::LEFT_BRACE:
            return "LEFT_BRACE";

        case TokenType::RIGHT_BRACE:
            return "RIGHT_BRACE";

        case TokenType::LEFT_BRACKET:
            return "LEFT_BRACKET";

        case TokenType::RIGHT_BRACKET:
            return "RIGHT_BRACKET";

        case TokenType::COMMA:
            return "COMMA";

        case TokenType::SEMICOLON:
            return "SEMICOLON";

        case TokenType::COLON:
            return "COLON";

        case TokenType::END_OF_FILE:
            return "END_OF_FILE";

        case TokenType::ERROR:
            return "ERROR";
    }

    return "DESCONOCIDO";
}

int main() {

    std::string codigo = "let resultado = 25\n"
        "let nombre = \"hola mundo\"";

    Lexer lexer(codigo);

    std::vector<Token> tokens = lexer.tokenizar();

    for (Token token : tokens) {

        std::cout<< "Tipo: " << nombreToken(token.tipo) << " | Lexema: " << token.lexema << " | Linea: " << token.linea << " | Columna: " << token.columna << std::endl;
    }

    return 0;
}