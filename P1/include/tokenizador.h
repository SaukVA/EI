#ifndef __Tokenizador__
#define __Tokenizador__


#include <iostream>
#include <string>
#include <list>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>

class Tokenizador {
    /* 
        cout << “DELIMITADORES: “ << delimiters << “ TRATA CASOS ESPECIALES: “ 
            << casosEspeciales << “ PASAR A MINUSCULAS Y SIN ACENTOS: “ << pasarAminuscSinAcentos;
        Aunque se modifique el almacenamiento de los delimitadores por temas de eficiencia, 
        el campo delimiters se imprimirá con el string con el que se inicializó el tokenizador
    */
    friend std::ostream& operator<<(std::ostream&, const Tokenizador&);

    public:

        /* 
            Inicializa delimiters a delimitadoresPalabra filtrando que no 
            se introduzcan delimitadores repetidos (de izquierda a derecha, 
            en cuyo caso se eliminarían los que hayan sido repetidos por la derecha);
            casosEspeciales a kcasosEspeciales; pasarAminuscSinAcentos a minuscSinAcentos
        */
        Tokenizador (const std::string& delimitadoresPalabra, const bool& kcasosEspeciales, const bool& minuscSinAcentos);
        
        Tokenizador (const Tokenizador&);

        /* 
            Inicializa delimiters=",;:.-/+*\\ '\"{}[]()<>¡!¿?&#=\t\n\r@"; 
            casosEspeciales a true; 
            pasarAminuscSinAcentos a false
        */
        Tokenizador ();

        // Pone delimiters=""
        ~Tokenizador (); 
        
        Tokenizador& operator= (const Tokenizador&);

        /*     
            Tokeniza str devolviendo el resultado en tokens. La lista tokens se
            vaciará antes de almacenar el resultado de la tokenización.
        */
        void Tokenizar (const std::string& str, std::list<std::string>& tokens) const;

        /* 
            Tokeniza el fichero i guardando la salida en el fichero f (una
            palabra en cada línea del fichero). Devolverá true si se realiza la
            tokenización de forma correcta; false en caso contrario enviando a cerr
            el mensaje correspondiente (p.ej. que no exista el archivo i)
        */
        bool Tokenizar (const std::string& i, const std::string& f) const;

        /* 
            Tokeniza el fichero i guardando la salida en un fichero de nombre i
            añadiéndole extensión .tk (sin eliminar previamente la extensión de i
            por ejemplo, del archivo pp.txt se generaría el resultado en pp.txt.tk),
            y que contendrá una palabra en cada línea del fichero. Devolverá true si
            se realiza la tokenización de forma correcta; false en caso contrario 
            enviando a cerr el mensaje correspondiente (p.ej. que no exista elarchivo i)
        */
        bool Tokenizar (const std::string & i) const;
        
        /* 
            Tokeniza el fichero i que contiene un nombre de fichero por línea
            guardando la salida en ficheros (uno por cada línea de i) cuyo nombre
            será el leído en i añadiéndole extensión .tk, y que contendrá una
            palabra en cada línea del fichero leído en i. Devolverá true si se
            realiza la tokenización de forma correcta de todos los archivos que
            contiene i; devolverá false en caso contrario enviando a cerr el mensaje
            correspondiente (p.ej. que no exista el archivo i, o que se trate de un
            directorio, enviando a “cerr” los archivos de i que no existan o que
            sean directorios; luego no se ha de interrumpir la ejecución si hay
            algún archivo en i que no exista)
        */
        bool TokenizarListaFicheros (const std::string& i) const;

        /* 
            Tokeniza todos los archivos que contenga el directorio i, incluyendo
            los de los subdirectorios, guardando la salida en ficheros cuyo nombre
            será el de entrada añadiéndole extensión .tk, y que contendrá una
            palabra en cada línea del fichero. Devolverá true si se realiza la
            tokenización de forma correcta de todos los archivos; devolverá false en
            caso contrario enviando a cerr el mensaje correspondiente (p.ej. que no
            exista el directorio i, o los ficheros que no se hayan podido tokenizar)
        */
        bool TokenizarDirectorio (const std::string& i) const;

        /* 
            Cambia “delimiters” por “nuevoDelimiters” comprobando que no hayan
            delimitadores repetidos (de izquierda a derecha), en cuyo caso se
            eliminarían los que hayan sido repetidos (por la derecha)
        */
        void DelimitadoresPalabra(const std::string& nuevoDelimiters);
        
        /* 
            Añade al final de “delimiters” los nuevos delimitadores que aparezcan
            en “nuevoDelimiters” (no se almacenarán caracteres repetidos)
        */
        void AnyadirDelimitadoresPalabra(const std::string& nuevoDelimiters);

        // Devuelve “delimiters”
        std::string DelimitadoresPalabra() const;

        // Cambia la variable privada “casosEspeciales”
        void CasosEspeciales (const bool& nuevoCasosEspeciales);

        // Devuelve el contenido de la variable privada “casosEspeciales”
        bool CasosEspeciales ();
        
        /* 
            Cambia la variable privada “pasarAminuscSinAcentos”. Atención al
            formato de codificación del corpus (comando “file” de Linux). Para la
            corrección de la práctica se utilizará el formato actual (ISO-8859).
        */
        void PasarAminuscSinAcentos (const bool& nuevoPasarAminuscSinAcentos);

        // Devuelve el contenido de la variable privada “pasarAminuscSinAcentos”
        bool PasarAminuscSinAcentos ();

    private:

        /* 
            Delimitadores de términos. Aunque se
            modifique la forma de almacenamiento interna para mejorar la eficiencia, este
            campo debe permanecer para indicar el orden en que se introdujeron los
            delimitadores
        */
        std::string delimiters;

        /* 
            Si true detectará palabras compuestas y casos especiales. Sino,
            trabajará al igual que el algoritmo propuesto en la sección “Versión del
            tokenizador vista en clase”
        */
        bool casosEspeciales;

        // Si true pasará el token a minúsculas y quitará acentos, antes de realizar la tokenización
        bool pasarAminuscSinAcentos;

        //Nos convierte un string a uno identico pero quita los acentos y las mayucaulas.
        std::string MinuscSinAcentos(const std::string& str) const;   

        //Devuelve un string con los delimitadores que nos sirven para delimitar los tokens
        std::string Substraer(const std::string& str, const std::string& delet) const;

        //Obtine la posicion del final del token
        std::string::size_type Encontrar_final(const std::string::size_type& lasPos, const std::string &str, const std::string &del)const;

        //Comprueba si el token es una URL
        bool esURL(const std::string::size_type &lasPos, const std::string &str) const;

        //Comprueba si el token es un Numero
        bool esNumero(const std::string::size_type &lasPos, const std::string &str, const std::string &del, const std::string &delAux, std::string::size_type &pos) const;

        //Comprueba si el token es un Email 
        bool esEmail(const std::string::size_type &pos, const std::string::size_type &lasPos, const std::string &str, const std::string &del)const;

        //Comprueba si el token es un Acronimo
        bool esAcronimo(const std::string::size_type &lastPos, const std::string &str, const std::string &del, const std::string &delAux, std::string::size_type &pos)const; 

        //Comprueba si el token es una Multipalabra
        bool esMultPalab(const std::string::size_type &lastPos, const std::string &str, const std::string &del, const std::string &delAux, std::string::size_type &pos)const;
};

#endif
