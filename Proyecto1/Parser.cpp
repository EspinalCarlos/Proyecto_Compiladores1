#include "Parser.hpp"
using namespace std
Parser::Parser(
	const vector<Token>& tokens
) {
	this->tojens = tokens;
	posicion = 0;
}

Token Parser::actual() {

    return tokens[posicion];
}

Token Parser::anterior() {

    if (posicion == 0) {
        return tokens[0];
    }

    return tokens[posicion - 1];
}

bool Parser::fin() {

    return actual().tipo ==
        TokenType::END_OF_FILE;
}

void Parser::avanzar() {

    if (!fin()) {
        posicion++;
    }
}

bool Parser::verificar(
    TokenType tipo
) {

    if (fin()) {

        return tipo ==
            TokenType::END_OF_FILE;
    }

    return actual().tipo == tipo;
}

bool Parser::coincidir(
    TokenType tipo
) {

    if (verificar(tipo)) {

        avanzar();

        return true;
    }

    return false;
}


bool Parser::consumir(
    TokenType tipo,
    const std::string& mensaje
) {

    if (verificar(tipo)) {

        avanzar();

        return true;
    }

    errorSintactico(mensaje);

    return false;
}

void Parser::errorSintactico(
    const string& mensaje
) {

    ErrorCompilador error;

    error.tipo =
        TipoError::SINTACTICO;

    error.mensaje =
        mensaje;

    error.linea =
        actual().linea;

    error.columna =
        actual().columna;

    errores.push_back(error);
}

void Parser::sincronizar() {

    if (!fin()) {
        avanzar();
    }

    while (!fin()) {

        if (
            anterior().tipo ==
            TokenType::SEMICOLON
        ) {
            return;
        }


        if (
            actual().tipo == TokenType::LET ||
            actual().tipo == TokenType::IF ||
            actual().tipo == TokenType::WHILE ||
            actual().tipo == TokenType::FOR ||
            actual().tipo == TokenType::RETURN ||
            actual().tipo == TokenType::FN ||
            actual().tipo == TokenType::RIGHT_BRACE
        ) {
            return;
        }


        avanzar();
    }
}

// ==========================================
// PARSEAR
// ==========================================

Nodo* Parser::parsear() {

    return Programa();
}




// ==========================================
// PROGRAMA
// ==========================================



Nodo* Parser::Programa() {

    Nodo* nodo =
        new Nodo("PROGRAMA");


    while (!fin()) {

        if (
            verificar(TokenType::FN)
        ) {

            Nodo* funcion =
                Funcion();

            if (funcion != nullptr) {

                agregarHijo(
                    nodo,
                    funcion
                );
            }

        } else {

            errorSintactico(
                "Se esperaba una funcion"
            );

            sincronizar();
        }
    }


    return nodo;
}


// ==========================================
// FUNCION
// ==========================================
Nodo* Parser::Funcion() {

    Nodo* nodo =
        new Nodo("FUNCION");


    // fn

    Token tokenFn =
        actual();

    if (
        consumir(
            TokenType::FN,
            "Se esperaba fn"
        )
    ) {

        agregarHijo(
            nodo,
            new Nodo(tokenFn.lexema)
        );
    }


    // nombre de funcion

    Token nombre =
        actual();


    if (
        !consumir(
            TokenType::IDENTIFICADOR,
            "Se esperaba el nombre de la funcion"
        )
    ) {

        sincronizar();

        return nodo;
    }


    agregarHijo(
        nodo,
        new Nodo(nombre.lexema)
    );


    // Tabla de simbolos

    tablaSimbolos.insertar(
        nombre.lexema,
        ""
    );


    // (

    consumir(
        TokenType::LEFT_PAREN,
        "Se esperaba ("
    );


    // parametros

    Nodo* parametros =
        Parametros();

    agregarHijo(
        nodo,
        parametros
    );


    // )

    consumir(
        TokenType::RIGHT_PAREN,
        "Se esperaba )"
    );


    // -> tipo

    if (
        verificar(
            TokenType::ARROW
        )
    ) {

        avanzar();


        std::string retorno =
            Tipo();


        if (!retorno.empty()) {

            agregarHijo(
                nodo,
                new Nodo(
                    "RETORNO: " +
                    retorno
                )
            );
        }
    }


    // bloque

    Nodo* bloque =
        Bloque();

    agregarHijo(
        nodo,
        bloque
    );


    return nodo;
}

// ==========================================
// PARAMETROS
// ==========================================


Nodo* Parser::Parametros() {

    Nodo* nodo =
        new Nodo("PARAMETROS");


    // función sin parámetros

    if (
        verificar(
            TokenType::RIGHT_PAREN
        )
    ) {

        return nodo;
    }


    while (!fin()) {

        Token identificador =
            actual();


        if (
            !consumir(
                TokenType::IDENTIFICADOR,
                "Se esperaba identificador del parametro"
            )
        ) {

            break;
        }


        consumir(
            TokenType::COLON,
            "Se esperaba :"
        );


        std::string tipo =
            Tipo();


        Nodo* parametro =
            new Nodo("PARAMETRO");


        agregarHijo(
            parametro,
            new Nodo(
                identificador.lexema
            )
        );


        if (!tipo.empty()) {

            agregarHijo(
                parametro,
                new Nodo(tipo)
            );
        }


        agregarHijo(
            nodo,
            parametro
        );


        // Tabla de símbolos

        tablaSimbolos.insertar(
            identificador.lexema,
            tipo
        );


        // Si no hay coma,
        // terminamos los parámetros

        if (
            !verificar(
                TokenType::COMMA
            )
        ) {

            break;
        }


        avanzar();
    }


    return nodo;
}

// ==========================================
// TIPO
// ==========================================

std::string Parser::Tipo() {

    if (
        verificar(TokenType::TYPE_I32) ||
        verificar(TokenType::TYPE_F64) ||
        verificar(TokenType::TYPE_BOOL) ||
        verificar(TokenType::TYPE_CHAR) ||
        verificar(TokenType::TYPE_STR)
    ) {

        std::string tipo =
            actual().lexema;

        avanzar();

        return tipo;
    }


    errorSintactico(
        "Se esperaba un tipo de dato"
    );


    return "";
}


// ==========================================
// BLOQUE
// ==========================================

Nodo* Parser::Bloque() {

    Nodo* nodo =
        new Nodo("BLOQUE");


    consumir(
        TokenType::LEFT_BRACE,
        "Se esperaba {"
    );


    while (
        !verificar(
            TokenType::RIGHT_BRACE
        ) &&
        !fin()
    ) {

        Nodo* sentencia =
            Sentencia();


        if (
            sentencia != nullptr
        ) {

            agregarHijo(
                nodo,
                sentencia
            );
        }
    }


    consumir(
        TokenType::RIGHT_BRACE,
        "Se esperaba }"
    );


    return nodo;
}


// ==========================================
// SENTENCIA
// ==========================================

Nodo* Parser::Sentencia() {

    if (
        verificar(
            TokenType::LET
        )
    ) {

        return Declaracion();
    }


    if (
        verificar(
            TokenType::IF
        )
    ) {

        return If();
    }


    if (
        verificar(
            TokenType::WHILE
        )
    ) {

        return While();
    }


    if (
        verificar(
            TokenType::FOR
        )
    ) {

        return For();
    }


    if (
        verificar(
            TokenType::RETURN
        )
    ) {

        return Return();
    }


    if (
        verificar(
            TokenType::LEFT_BRACE
        )
    ) {

        return Bloque();
    }


    errorSintactico(
        "Sentencia no reconocida"
    );


    sincronizar();


    return nullptr;
}


// ==========================================
// DECLARACION
// ==========================================

Nodo* Parser::Declaracion() {

    Nodo* nodo =
        new Nodo("DECLARACION");


    // let

    Token tokenLet =
        actual();


    consumir(
        TokenType::LET,
        "Se esperaba let"
    );


    agregarHijo(
        nodo,
        new Nodo(
            tokenLet.lexema
        )
    );


    // identificador

    Token identificador =
        actual();


    if (
        !consumir(
            TokenType::IDENTIFICADOR,
            "Se esperaba un identificador"
        )
    ) {

        sincronizar();

        return nodo;
    }


    agregarHijo(
        nodo,
        new Nodo(
            identificador.lexema
        )
    );


    // tipo opcional

    std::string tipo = "";


    if (
        verificar(
            TokenType::COLON
        )
    ) {

        avanzar();


        tipo =
            Tipo();


        if (!tipo.empty()) {

            agregarHijo(
                nodo,
                new Nodo(tipo)
            );
        }
    }


    // tabla de símbolos

    tablaSimbolos.insertar(
        identificador.lexema,
        tipo
    );


    // =

    consumir(
        TokenType::ASSIGN,
        "Se esperaba ="
    );


    // expresión

    Nodo* expresion =
        Expresion();


    if (
        expresion != nullptr
    ) {

        agregarHijo(
            nodo,
            expresion
        );
    }


    // ;

    if (
        !consumir(
            TokenType::SEMICOLON,
            "Se esperaba ;"
        )
    ) {

        sincronizar();
    }


    return nodo;
}


// ==========================================
// IF
// ==========================================

Nodo* Parser::If() {

    Nodo* nodo =
        new Nodo("IF");


    Token tokenIf =
        actual();


    if (
        consumir(
            TokenType::IF,
            "Se esperaba if"
        )
    ) {

        agregarHijo(
            nodo,
            new Nodo(
                tokenIf.lexema
            )
        );
    }


    // condición

    Nodo* condicion =
        Expresion();


    if (
        condicion != nullptr
    ) {

        agregarHijo(
            nodo,
            condicion
        );
    }


    // bloque if

    Nodo* bloqueIf =
        Bloque();


    agregarHijo(
        nodo,
        bloqueIf
    );


    // else opcional

    if (
        verificar(
            TokenType::ELSE
        )
    ) {

        Token tokenElse =
            actual();

        avanzar();


        Nodo* nodoElse =
            new Nodo("ELSE");


        agregarHijo(
            nodoElse,
            new Nodo(
                tokenElse.lexema
            )
        );


        Nodo* bloqueElse =
            Bloque();


        agregarHijo(
            nodoElse,
            bloqueElse
        );


        agregarHijo(
            nodo,
            nodoElse
        );
    }


    return nodo;
}


// ==========================================
// WHILE
// ==========================================

Nodo* Parser::While() {

    Nodo* nodo =
        new Nodo("WHILE");


    Token tokenWhile =
        actual();


    if (
        consumir(
            TokenType::WHILE,
            "Se esperaba while"
        )
    ) {

        agregarHijo(
            nodo,
            new Nodo(
                tokenWhile.lexema
            )
        );
    }


    Nodo* condicion =
        Expresion();


    agregarHijo(
        nodo,
        condicion
    );


    Nodo* bloque =
        Bloque();


    agregarHijo(
        nodo,
        bloque
    );


    return nodo;
}


// ==========================================
// FOR
// ==========================================

Nodo* Parser::For() {

    Nodo* nodo =
        new Nodo("FOR");


    Token tokenFor =
        actual();


    consumir(
        TokenType::FOR,
        "Se esperaba for"
    );


    agregarHijo(
        nodo,
        new Nodo(
            tokenFor.lexema
        )
    );


    // variable del for

    Token variable =
        actual();


    if (
        consumir(
            TokenType::IDENTIFICADOR,
            "Se esperaba identificador despues de for"
        )
    ) {

        agregarHijo(
            nodo,
            new Nodo(
                variable.lexema
            )
        );


        tablaSimbolos.insertar(
            variable.lexema,
            ""
        );
    }


    /*
        Por ahora el lexer reconoce "in"
        como IDENTIFICADOR porque todavía
        no tenemos un TokenType::IN.
    */

    if (
        verificar(
            TokenType::IDENTIFICADOR
        ) &&
        actual().lexema == "in"
    ) {

        Token tokenIn =
            actual();

        avanzar();


        agregarHijo(
            nodo,
            new Nodo(
                tokenIn.lexema
            )
        );

    } else {

        errorSintactico(
            "Se esperaba in"
        );
    }


    Nodo* expresion =
        Expresion();


    agregarHijo(
        nodo,
        expresion
    );


    Nodo* bloque =
        Bloque();


    agregarHijo(
        nodo,
        bloque
    );


    return nodo;
}


// ==========================================
// RETURN
// ==========================================

Nodo* Parser::Return() {

    Nodo* nodo =
        new Nodo("RETURN");


    Token tokenReturn =
        actual();


    if (
        consumir(
            TokenType::RETURN,
            "Se esperaba return"
        )
    ) {

        agregarHijo(
            nodo,
            new Nodo(
                tokenReturn.lexema
            )
        );
    }


    // return;
    // o
    // return expresion;

    if (
        !verificar(
            TokenType::SEMICOLON
        )
    ) {

        Nodo* expresion =
            Expresion();


        agregarHijo(
            nodo,
            expresion
        );
    }


    if (
        !consumir(
            TokenType::SEMICOLON,
            "Se esperaba ; despues de return"
        )
    ) {

        sincronizar();
    }


    return nodo;
}


// ==========================================
// EXPRESION
// ==========================================

Nodo* Parser::Expresion() {

    return LogicoOr();
}


// ==========================================
// OR
// ==========================================

Nodo* Parser::LogicoOr() {

    Nodo* izquierda =
        LogicoAnd();


    while (
        verificar(
            TokenType::OR
        )
    ) {

        Token operador =
            actual();

        avanzar();


        Nodo* derecha =
            LogicoAnd();


        Nodo* nodo =
            new Nodo(
                operador.lexema
            );


        agregarHijo(
            nodo,
            izquierda
        );


        agregarHijo(
            nodo,
            derecha
        );


        izquierda =
            nodo;
    }


    return izquierda;
}


// ==========================================
// AND
// ==========================================

Nodo* Parser::LogicoAnd() {

    Nodo* izquierda =
        Igualdad();


    while (
        verificar(
            TokenType::AND
        )
    ) {

        Token operador =
            actual();

        avanzar();


        Nodo* derecha =
            Igualdad();


        Nodo* nodo =
            new Nodo(
                operador.lexema
            );


        agregarHijo(
            nodo,
            izquierda
        );


        agregarHijo(
            nodo,
            derecha
        );


        izquierda =
            nodo;
    }


    return izquierda;
}


// ==========================================
// == !=
// ==========================================

Nodo* Parser::Igualdad() {

    Nodo* izquierda =
        Comparacion();


    while (
        verificar(
            TokenType::EQUAL
        ) ||
        verificar(
            TokenType::NOT_EQUAL
        )
    ) {

        Token operador =
            actual();

        avanzar();


        Nodo* derecha =
            Comparacion();


        Nodo* nodo =
            new Nodo(
                operador.lexema
            );


        agregarHijo(
            nodo,
            izquierda
        );


        agregarHijo(
            nodo,
            derecha
        );


        izquierda =
            nodo;
    }


    return izquierda;
}


// ==========================================
// < <= > >=
// ==========================================

Nodo* Parser::Comparacion() {

    Nodo* izquierda =
        Termino();


    while (
        verificar(TokenType::LESS) ||
        verificar(TokenType::LESS_EQUAL) ||
        verificar(TokenType::GREATER) ||
        verificar(TokenType::GREATER_EQUAL)
    ) {

        Token operador =
            actual();

        avanzar();


        Nodo* derecha =
            Termino();


        Nodo* nodo =
            new Nodo(
                operador.lexema
            );


        agregarHijo(
            nodo,
            izquierda
        );


        agregarHijo(
            nodo,
            derecha
        );


        izquierda =
            nodo;
    }


    return izquierda;
}


// ==========================================
// + -
// ==========================================

Nodo* Parser::Termino() {

    Nodo* izquierda =
        Factor();


    while (
        verificar(
            TokenType::PLUS
        ) ||
        verificar(
            TokenType::MINUS
        )
    ) {

        Token operador =
            actual();

        avanzar();


        Nodo* derecha =
            Factor();


        Nodo* nodo =
            new Nodo(
                operador.lexema
            );


        agregarHijo(
            nodo,
            izquierda
        );


        agregarHijo(
            nodo,
            derecha
        );


        izquierda =
            nodo;
    }


    return izquierda;
}


// ==========================================
// * /
// ==========================================

Nodo* Parser::Factor() {

    Nodo* izquierda =
        Unario();


    while (
        verificar(
            TokenType::MULTIPLY
        ) ||
        verificar(
            TokenType::DIVIDE
        )
    ) {

        Token operador =
            actual();

        avanzar();


        Nodo* derecha =
            Unario();


        Nodo* nodo =
            new Nodo(
                operador.lexema
            );


        agregarHijo(
            nodo,
            izquierda
        );


        agregarHijo(
            nodo,
            derecha
        );


        izquierda =
            nodo;
    }


    return izquierda;
}


// ==========================================
// ! y - unario
// ==========================================

Nodo* Parser::Unario() {

    if (
        verificar(
            TokenType::NOT
        ) ||
        verificar(
            TokenType::MINUS
        )
    ) {

        Token operador =
            actual();

        avanzar();


        Nodo* nodo =
            new Nodo(
                operador.lexema
            );


        Nodo* derecha =
            Unario();


        agregarHijo(
            nodo,
            derecha
        );


        return nodo;
    }


    return Primario();
}


// ==========================================
// PRIMARIO
// ==========================================

Nodo* Parser::Primario() {

    // =========================
    // NUMEROS / STRING / CHAR
    // =========================

    if (
        verificar(TokenType::ENTERO) ||
        verificar(TokenType::DECIMAL) ||
        verificar(TokenType::STRING_LITERAL) ||
        verificar(TokenType::CHAR_LITERAL)
    ) {

        Token token =
            actual();

        avanzar();


        return new Nodo(
            token.lexema
        );
    }


    // =========================
    // IDENTIFICADOR
    // =========================

    if (
        verificar(
            TokenType::IDENTIFICADOR
        )
    ) {

        Token identificador =
            actual();

        avanzar();


        // llamada de funcion

        if (
            verificar(
                TokenType::LEFT_PAREN
            )
        ) {

            Nodo* llamada =
                new Nodo("LLAMADA");


            agregarHijo(
                llamada,
                new Nodo(
                    identificador.lexema
                )
            );


            avanzar();


            // argumentos

            if (
                !verificar(
                    TokenType::RIGHT_PAREN
                )
            ) {

                while (!fin()) {

                    Nodo* argumento =
                        Expresion();


                    agregarHijo(
                        llamada,
                        argumento
                    );


                    if (
                        !verificar(
                            TokenType::COMMA
                        )
                    ) {

                        break;
                    }


                    avanzar();
                }
            }


            consumir(
                TokenType::RIGHT_PAREN,
                "Se esperaba ) en llamada de funcion"
            );


            return llamada;
        }


        return new Nodo(
            identificador.lexema
        );
    }


    // =========================
    // ( EXPRESION )
    // =========================

    if (
        verificar(
            TokenType::LEFT_PAREN
        )
    ) {

        avanzar();


        Nodo* expresion =
            Expresion();


        consumir(
            TokenType::RIGHT_PAREN,
            "Se esperaba )"
        );


        return expresion;
    }


    // =========================
    // ERROR
    // =========================

    errorSintactico(
        "Se esperaba una expresion"
    );


    /*
        Avanzamos para evitar
        quedarnos pegados en el
        mismo token.
    */

    return new Nodo(
        "ERROR"
    );
}


// ==========================================
// RESULTADOS
// ==========================================

std::vector<ErrorCompilador>
Parser::obtenerErrores() {

    return errores;
}


const TablaSimbolos&
Parser::obtenerTablaSimbolos() const {

    return tablaSimbolos;
}
