#include "../include/tokenizador.h"
//#include "tokenizador.h"

    std::ostream& operator<<(std::ostream& os, const Tokenizador& tokenizador){
        os<< "DELIMITADORES: " << tokenizador.delimiters << " TRATA CASOS ESPECIALES: " 
            << tokenizador.casosEspeciales << " PASAR A MINUSCULAS Y SIN ACENTOS: " << tokenizador.pasarAminuscSinAcentos;
        return os;
    }

    // Tokenizador (const std::string& delimitadoresPalabra, const bool& kcasosEspeciales, const bool& minuscSinAcentos);
    
    Tokenizador::Tokenizador (const Tokenizador& tokenizador){
        // Comprobamos que no se este igualando el objeto a si mismo 
        if(this != &tokenizador){
            this->delimiters = tokenizador.casosEspeciales;
            this->casosEspeciales = tokenizador.casosEspeciales;
            this->pasarAminuscSinAcentos = tokenizador.pasarAminuscSinAcentos;
        }
    }

    Tokenizador::Tokenizador (){
        this->delimiters = ",;:.-/+*\\ '\"{}[]()<>¡!¿?&#=\t\n\r@"; 
        this->casosEspeciales  = true; 
        this->pasarAminuscSinAcentos = false;
    }

    Tokenizador::~Tokenizador (){
        delimiters = "";
    }
    
    Tokenizador& Tokenizador::operator= (const Tokenizador& tokenizador){
        // Comprobamos que no se este igualando el objeto a si mismo 
        if(this != &tokenizador){
            this->delimiters = tokenizador.delimiters;
            this->casosEspeciales = tokenizador.casosEspeciales;
            this->pasarAminuscSinAcentos = tokenizador.pasarAminuscSinAcentos;
        }        
        return *this;
    }

    // void Tokenizar (const std::string& str, std::list<std::string>& tokens) const;
    // bool Tokenizar (const std::string& i, const std::string& f) const;
    // bool Tokenizar (const std::string & i) const;
    // bool TokenizarListaFicheros (const std::string& i) const;
    // bool TokenizarDirectorio (const std::string& i) const;
    // void DelimitadoresPalabra(const std::string& nuevoDelimiters);
    // void AnyadirDelimitadoresPalabra(const std::string& nuevoDelimiters);
    // std::string DelimitadoresPalabra() const;
    // void CasosEspeciales (const bool& nuevoCasosEspeciales);
    // bool CasosEspeciales ();
    // void PasarAminuscSinAcentos (const bool& nuevoPasarAminuscSinAcentos);
    // bool PasarAminuscSinAcentos ();
    // std::string delimiters;
    // bool casosEspeciales;
    // bool pasarAminuscSinAcentos;