#include "../Automatas.hpp"

bool esOperador(const std::string& cadena) {

    enum Estado {
        q0,
        qSimple,
        qAnd,
        qOr,
        qFinal,
        error
    };

    Estado estado = q0;

    for (char c : cadena) {

        switch (estado) {

            case q0:

                switch (c) {

                    case '+':
                    case '-':
                    case '*':
                    case '/':
                    case '!':
                        estado = qSimple;
                        break;

                    case '&':
                        estado = qAnd;
                        break;

                    case '|':
                        estado = qOr;
                        break;

                    default:
                        estado = error;
                        break;
                }

                break;

            case qSimple:

                estado = error;
                break;

            case qAnd:

                if (c == '&') {
                    estado = qFinal;
                } else {
                    estado = error;
                }

                break;

            case qOr:

                if (c == '|') {
                    estado = qFinal;
                } else {
                    estado = error;
                }

                break;

            case qFinal:

                estado = error;
                break;

            case error:

                return false;
        }
    }

    return estado == qSimple || estado == qFinal;
}
