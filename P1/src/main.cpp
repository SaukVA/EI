#include <iostream>
#include <string>
#include <list>
#include <sys/resource.h>

#include "tokenizador.h"

using namespace std;

double getcputime(void) {
    struct timeval tim;
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    tim=ru.ru_utime;
    double t=(double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
    tim=ru.ru_stime;
    t+=(double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
    return t;
}

main() {
    // long double aa=getcputime();
    // Tokenizador a("\t ,;:.-+/*_`'{}[]()!?&#\"\\<>", true, true);
    // a.TokenizarListaFicheros("listaFicheros.txt");
    // cout << "Ha tardado " << getcputime() - aa << " segundos" << endl;

    Tokenizador a(",.", true, false);
    std::list<std::string> tokens;
    a.Tokenizar("3..2$ 4,,,5$ ..35", tokens);
    std::cout << "Numero de tokens:\t" << tokens.size() << std::endl;
    std::cout << "Tokens: " << std::endl;
    for (auto b = tokens.begin(), e = tokens.end(); b != e; ++b){
        cout<< "\t" <<*b<<endl;
    }
    

    return 0;

}
