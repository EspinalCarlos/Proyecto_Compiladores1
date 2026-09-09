#include "../Automatas.hpp"

bool esDelimitador(const std::string& cadena) {

    enum Estado {
        q0,
        q1,
        error
    };

    Estado estado = q0;

    for (char c : cadena) {

        switch (estado) {

            case q0:

                switch (c) {

                    case '{':
                    case '}':
                    case '(':
                    case ')':
                    case '[':
                    case ']':
                    case ',':
                    case ';':
                        estado = q1;
                        break;

                    default:
                        estado = error;
                        break;
                }

                break;

            case q1:

                estado = error;
                break;

            case error:

                return false;
        }
    }

    return estado == q1;
}
