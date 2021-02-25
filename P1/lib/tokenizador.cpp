#include "tokenizador.h"
#include <bits/stdc++.h>

std::ostream &operator<<(std::ostream &os, const Tokenizador &tokenizador)
{
    os << "DELIMITADORES: " << tokenizador.delimiters << " TRATA CASOS ESPECIALES: "
       << tokenizador.casosEspeciales << " PASAR A MINUSCULAS Y SIN ACENTOS: " << tokenizador.pasarAminuscSinAcentos;
    return os;
}

Tokenizador::Tokenizador(const std::string &delimitadoresPalabra, const bool &kcasosEspeciales, const bool &minuscSinAcentos)
{
    this->DelimitadoresPalabra(delimitadoresPalabra);
    this->casosEspeciales = kcasosEspeciales;
    this->pasarAminuscSinAcentos = minuscSinAcentos;
}

Tokenizador::Tokenizador(const Tokenizador &tokenizador)
{
    // Comprobamos que no se este igualando el objeto a si mismo
    if (this != &tokenizador)
    {
        this->delimiters = tokenizador.casosEspeciales;
        this->casosEspeciales = tokenizador.casosEspeciales;
        this->pasarAminuscSinAcentos = tokenizador.pasarAminuscSinAcentos;
    }
}

Tokenizador::Tokenizador()
{
    this->delimiters = ",;:.-/+*\\ '\"{}[]()<>?!??&#=\t\n\r@";
    this->casosEspeciales = true;
    this->pasarAminuscSinAcentos = false;
}

Tokenizador::~Tokenizador()
{
    delimiters = "";
}

Tokenizador &Tokenizador::operator=(const Tokenizador &tokenizador)
{
    // Comprobamos que no se este igualando el objeto a si mismo
    if (this != &tokenizador)
    {
        this->delimiters = tokenizador.delimiters;
        this->casosEspeciales = tokenizador.casosEspeciales;
        this->pasarAminuscSinAcentos = tokenizador.pasarAminuscSinAcentos;
    }
    return *this;
}

void Tokenizador::Tokenizar(const std::string &str, std::list<std::string> &tokens) const
{

    //Hacemos una copia del string que nos pasan
    std::string copia_str;
    copia_str = str;

    // Baciado de la lista de tokens
    tokens.clear();

    //Comprobar si tenemos que pasar a minusculas sin acento
    if (pasarAminuscSinAcentos)
    {
        copia_str = MinuscSinAcentos(str);
    }

    //Comprobamos si tenemos que detectar casos especiales
    if (!casosEspeciales)
    {
        std::string::size_type lastPos = copia_str.find_first_not_of(delimiters, 0); // Posicion del primer caracter del Token
        std::string::size_type pos = copia_str.find_first_of(delimiters, lastPos);   // Posicion del primer delimitador

        while (std::string::npos != pos || std::string::npos != lastPos)
        {
            tokens.push_back(copia_str.substr(lastPos, pos - lastPos));
            lastPos = copia_str.find_first_not_of(delimiters, pos);
            pos = copia_str.find_first_of(delimiters, lastPos);
        }
    }
    else
    {
        std::string delimitersAux, delimitersURL, delimitersNum, delimitersMail;
        delimitersAux = delimiters + " ";                                               // Delimitadores que se comprueban el ultima instancia
        delimitersURL = Substraer(delimitersAux, "_:/.?&-=#@");                         // Delimitadores que acepta la URL
        delimitersNum = Substraer(delimitersAux, ",.%$") + "%$";                        // Delimitadores que acepta un numero
        delimitersMail = Substraer(delimitersAux, "@.-_");                              // Delimitadores que acepta un Email
        std::string::size_type lastPos = copia_str.find_first_not_of(delimitersAux, 0); // Posicion del primer caracter del Token
        std::string::size_type pos = copia_str.find_first_of(delimitersAux, lastPos);   // Posicion del primer delimitador

        while (std::string::npos != pos || std::string::npos != lastPos)
        {
            //Comprobamos si es una URL
            if (esURL(lastPos, copia_str)){
                pos = copia_str.find_first_of(delimitersURL, lastPos);
                tokens.push_back(copia_str.substr(lastPos, pos - lastPos));
            }

            //Comprobamos si es una Numero
            else if (esNumero(lastPos, copia_str, delimitersNum, delimitersAux)){
                
                pos = Encontrar_final(lastPos, copia_str, delimitersNum, delimitersAux);
                if (copia_str[lastPos - 1] == '.' || copia_str[lastPos - 1] == ','){
                    tokens.push_back('0' + copia_str.substr(lastPos - 1, pos - (lastPos - 1)));
                }
                else{
                    tokens.push_back(copia_str.substr(lastPos, pos - lastPos));
                }

                //Si se termina por '%' o '$' se añade eso como un token extra
                if (copia_str[pos] == '$' || copia_str[pos] == '%'){
                    std::string temp;
                    temp = copia_str[pos];
                    tokens.push_back(temp);
                    ++pos;
                }
            }

            //Comprobamos si es un Email
            else if (esEmail(pos, lastPos, copia_str, delimitersMail)){
                pos = Encontrar_final(lastPos,copia_str, delimitersMail, delimitersAux);
                std::cout << "Soy un Email:\t" << copia_str.substr(lastPos, pos - lastPos) << std::endl;
                tokens.push_back(copia_str.substr(lastPos, pos - lastPos));
            }

            //Si no se mete el token directamente
            else{
                tokens.push_back(copia_str.substr(lastPos, pos - lastPos));
            }

            lastPos = copia_str.find_first_not_of(delimitersAux, pos);
            pos = copia_str.find_first_of(delimitersAux, lastPos);
        }
    }
}

// bool Tokenizar (const std::string& i, const std::string& f) const;
// bool Tokenizar (const std::string & i) const;
// bool TokenizarListaFicheros (const std::string& i) const;
// bool TokenizarDirectorio (const std::string& i) const;

void Tokenizador::DelimitadoresPalabra(const std::string &nuevoDelimiters)
{
    this->delimiters = "";
    this->AnyadirDelimitadoresPalabra(nuevoDelimiters);
}

void Tokenizador::AnyadirDelimitadoresPalabra(const std::string &nuevoDelimiters)
{

    uint16_t n;
    n = nuevoDelimiters.length();

    for (size_t i = 0; i < n; i++)
    {
        if (!Contiene(delimiters, nuevoDelimiters[i]))
        {
            this->delimiters += nuevoDelimiters[i];
        }
    }
    //std::cout << "Delimitadores nuevo:\t" << delimiters << std::endl;
}

std::string Tokenizador::DelimitadoresPalabra() const
{
    return this->delimiters;
}

void Tokenizador::CasosEspeciales(const bool &nuevoCasosEspeciales)
{
    this->casosEspeciales = nuevoCasosEspeciales;
}

bool Tokenizador::CasosEspeciales()
{
    return this->casosEspeciales;
}

void Tokenizador::PasarAminuscSinAcentos(const bool &nuevoPasarAminuscSinAcentos)
{
    this->pasarAminuscSinAcentos = nuevoPasarAminuscSinAcentos;
}

bool Tokenizador::PasarAminuscSinAcentos()
{
    return this->pasarAminuscSinAcentos;
}

    /*
        FUNCIONES AUXILIARES CREADAS POR MI
    */

bool Tokenizador::Contiene(const std::string &conjunto, const char &elemento)
{

    return (conjunto.find(elemento) != std::string::npos);
}

std::string Tokenizador::MinuscSinAcentos(const std::string &str) const
{
    std::string minSin_str;
    minSin_str = "";

    for (size_t i = 0; i < str.length(); i++)
    {
        unsigned char aux = str[i];
        switch (aux)
        {
        case 209: // '?'
            minSin_str += 'ñ';
            break;

        case 192: // '?'
        case 193: // '?'
        case 224: // '?'
        case 225: // '?'
            minSin_str += 'a';
            break;

        case 200: // '?'
        case 201: // '?'
        case 232: // '?'
        case 233: // '?'
            minSin_str += 'e';
            break;

        case 204: // '?'
        case 205: // '?'
        case 236: // '?'
        case 237: // '?'
            minSin_str += 'i';
            break;

        case 210: // '?'
        case 211: // '?'
        case 242: // '?'
        case 243: // '?'
            minSin_str += 'o';
            break;

        case 217: // '?'
        case 218: // '?'
        case 249: // '?'
        case 250: // '?'
            minSin_str += 'u';
            break;

        default:
            minSin_str += std::tolower(str[i]);
            break;
        }
    }

    return minSin_str;
}

std::string Tokenizador::Substraer(const std::string &str, const std::string &delet) const
{
    std::string result;
    result = str;

    for (size_t i = 0; i < delet.length(); i++)
    {
        result.erase(remove(result.begin(), result.end(), delet[i]), result.end());
    }

    return result;
}

std::string::size_type Tokenizador::Encontrar_final(const std::string::size_type& lasPos, const std::string& str, const std::string& del, const std::string& delAux)const{
    std::string::size_type pos, aux1, aux2;
    pos = str.find_first_of(del, lasPos);
    aux1 = str.find_first_of(delAux, lasPos);
    aux2 = str.find_first_of(delAux, aux1 + 1);

    while(aux1 <= pos && aux1 != std::string::npos){
        if(aux1 == aux2 - 1){
            pos = aux1;
        }
        aux1 = aux2;
        aux2 = str.find_first_of(delAux, aux1 + 1);
    }
    if(pos == std::string::npos && delimiters.find_first_of(str[str.length()-1],0) != std::string::npos){
        pos = str.length()-1;
    }

    return pos;
}

bool Tokenizador::esURL(const std::string::size_type &lastPos, const std::string &str) const
{
    return (
        str.find("http:") == lastPos ||
        str.find("https:") == lastPos ||
        str.find("ftp:") == lastPos);
}

bool Tokenizador::esNumero(const std::string::size_type &lastPos, const std::string &str, const std::string &del, const std::string &delAux) const{
    
    std::string::size_type posAux;
    posAux = Encontrar_final(lastPos, str, del, delAux);

    return (posAux <= str.find_first_not_of("0123456789,.",lastPos));
}

bool Tokenizador::esEmail(const std::string::size_type &pos, const std::string::size_type &lasPos, const std::string &str, std::string &del) const{
    
    std::string::size_type posAux, posAux2, posAux3;
    posAux = str.find_first_of("@", pos + 1);
    posAux2 = str.find_first_of(" ", pos + 1);
    posAux3 = str.find_first_of(del + ".-_", pos+1);

    return  (
                str[pos] == '@' &&                                   //Comprobamos que el delimitador que se ha encontrado es un '@'
                (posAux == std::string::npos || posAux2 < posAux) && //Comprobamos que no hayan '@' despues del primer '@'
                posAux3 != pos+1                                     //Comprobamos que despues del '@' no venga ningun delimitador
            );
}
