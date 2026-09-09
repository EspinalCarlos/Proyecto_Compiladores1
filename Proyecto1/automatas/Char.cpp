#include "../Automatas.hpp"

bool esChar(const std::string& cadena) {

    enum Estado {
        q0,
        q1,
        q2,
        qEscape,
        qFinal,
        error
    };

    Estado estado = q0;

    for (char c : cadena) {

        switch (estado) {

            case q0:

                if (c == '\'') {
                    estado = q1;
                } else {
                    estado = error;
                }

                break;

            case q1:

                if (c == '\\') {
                    estado = qEscape;
                }
                else if (
                    c != '\'' &&
                    c != '\n' &&
                    c != '\r'
                ) {
                    estado = q2;
                }
                else {
                    estado = error;
                }

                break;

            case qEscape:

                switch (c) {

                    case 'n':
                    case 't':
                    case 'r':
                    case '0':
                    case '\\':
                    case '\'':
                    case '"':
                        estado = q2;
                        break;

                    default:
                        estado = error;
                        break;
                }

                break;

            case q2:

                if (c == '\'') {
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

    return estado == qFinal;
}
