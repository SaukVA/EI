#ifndef __INDEXADORINFORMACION__
#define __INDEXADORINFORMACION__

#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <list>

using namespace std;

class InfTermDoc {
        friend ostream& operator<<(ostream& s, const InfTermDoc& p);
    public:
        InfTermDoc (const InfTermDoc &);
        InfTermDoc ();                                  // Inicializa ft = 0
        ~InfTermDoc ();                                 // Pone ft = 0
        InfTermDoc & operator= (const InfTermDoc &);    // Añadir cuantos métodos se consideren necesarios para manejar la parte privada de la clase
    private:
    int ft; // Frecuencia del término en el documento
    list<int> posTerm; 
            // Solo se almacenará esta información si el campo privado del indexador almacenarPosTerm == true
            // Lista de números de palabra en los que aparece el término en el
            // documento. Los números de palabra comenzarán desde cero (la primera
            // palabra del documento). Se numerarán las palabras de parada. Estará
            // ordenada de menor a mayor posición.
};

class InformacionTermino {
        friend ostream& operator<<(ostream& s, const InformacionTermino& p);
    public:
        InformacionTermino (const InformacionTermino &);
        InformacionTermino ();                                          // Inicializa ftc = 0
        ~InformacionTermino ();                                         // Pone ftc = 0 y vacía l_docs
        InformacionTermino & operator= (const InformacionTermino &);    // Añadir cuantos métodos se consideren necesarios para manejar la parte privada de la clase
    private:
        int ftc; // Frecuencia total del término en la colección
        unordered_map<long int, InfTermDoc> l_docs;
                // Tabla Hash que se accederá por el id del documento, devolviendo un
                // objeto de la clase InfTermDoc que contiene toda la información de
                // aparición del término en el documento
};

class InfDoc {
        friend ostream& operator<<(ostream& s, const InfDoc& p);
    public:
        InfDoc (const InfDoc &);
        InfDoc ();
        ~InfDoc ();
        InfDoc & operator= (const InfDoc &); // Añadir cuantos métodos se consideren necesarios para manejar la parte privada de la clase
    private:
        long int idDoc;          // Identificador del documento. El primer documento indexado en la colección será el identificador 1
        int numPal;              // Nº total de palabras del documento
        int numPalSinParada;     // Nº total de palabras sin stop-words del documento
        int numPalDiferentes;    // Nº total de palabras diferentes que no sean stop-words (sin acumular la frecuencia de cada una de ellas)
        int tamBytes;            // Tamaño en bytes del documento
        Fecha fechaModificacion; // Atributo correspondiente a la fecha y hora de modificación del documento. El tipo “Fecha/hora” lo elegirá/implementará el alumno
};