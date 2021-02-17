#include "tokenizador.h"
#include <bits/stdc++.h> 

    std::ostream& operator<<(std::ostream& os, const Tokenizador& tokenizador){
        os<< "DELIMITADORES: " << tokenizador.delimiters << " TRATA CASOS ESPECIALES: " 
            << tokenizador.casosEspeciales << " PASAR A MINUSCULAS Y SIN ACENTOS: " << tokenizador.pasarAminuscSinAcentos;
        return os;
    }

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

    // Tokenizador (const std::string& delimitadoresPalabra, const bool& kcasosEspeciales, const bool& minuscSinAcentos);
    // void Tokenizar (const std::string& str, std::list<std::string>& tokens) const;
    // bool Tokenizar (const std::string& i, const std::string& f) const;
    // bool Tokenizar (const std::string & i) const;
    // bool TokenizarListaFicheros (const std::string& i) const;
    // bool TokenizarDirectorio (const std::string& i) const;

    void Tokenizador::DelimitadoresPalabra(const std::string& nuevoDelimiters){
        std::cout << "Primeros delimitadores:\t" << delimiters << std::endl;
        this->delimiters = ""; 
        this->AnyadirDelimitadoresPalabra(nuevoDelimiters);
    }
    
    void Tokenizador::AnyadirDelimitadoresPalabra(const std::string& nuevoDelimiters){

        //std::cout << "Delimitadores actuales:\t" << this->delimiters << std::endl;

        uint16_t n;
        n = nuevoDelimiters.length();

        for (size_t i = 0; i < n; i++){
            if(!this->Repetido(nuevoDelimiters[i])){
                this-> delimiters += nuevoDelimiters[i];
            }
        }

        //std::cout << "Delimitadores nuevos:\t" << this->delimiters << std::endl;
    }

    std::string Tokenizador::DelimitadoresPalabra() const{
        return this->delimiters;
    }
    
    void Tokenizador::CasosEspeciales (const bool& nuevoCasosEspeciales){
        this->casosEspeciales = nuevoCasosEspeciales;
    }

    bool Tokenizador::CasosEspeciales (){
        return this->casosEspeciales;
    }

    void Tokenizador::PasarAminuscSinAcentos (const bool& nuevoPasarAminuscSinAcentos){
        this->pasarAminuscSinAcentos = nuevoPasarAminuscSinAcentos;
    }

    bool Tokenizador::PasarAminuscSinAcentos (){
        return this->pasarAminuscSinAcentos;
    }

    bool Tokenizador::Repetido(const char& delimitador){
        bool sol;
        sol = false;

        if(this->delimiters.find(delimitador) != std::string::npos){ sol = true; }

        return sol;
    }