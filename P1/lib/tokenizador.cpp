#include "tokenizador.h"
#include <bits/stdc++.h> 

    std::ostream& operator<<(std::ostream& os, const Tokenizador& tokenizador){
        os<< "DELIMITADORES: " << tokenizador.delimiters << " TRATA CASOS ESPECIALES: " 
            << tokenizador.casosEspeciales << " PASAR A MINUSCULAS Y SIN ACENTOS: " << tokenizador.pasarAminuscSinAcentos;
        return os;
    }

    Tokenizador::Tokenizador (const std::string& delimitadoresPalabra, const bool& kcasosEspeciales, const bool& minuscSinAcentos){
        this->DelimitadoresPalabra(delimitadoresPalabra);
        this->casosEspeciales        = kcasosEspeciales;
        this->pasarAminuscSinAcentos = minuscSinAcentos;
    }
    
    Tokenizador::Tokenizador (const Tokenizador& tokenizador){
        // Comprobamos que no se este igualando el objeto a si mismo 
        if(this != &tokenizador){
            this->delimiters             = tokenizador.casosEspeciales;
            this->casosEspeciales        = tokenizador.casosEspeciales;
            this->pasarAminuscSinAcentos = tokenizador.pasarAminuscSinAcentos;
        }
    }

    Tokenizador::Tokenizador (){
        this->delimiters             = ",;:.-/+*\\ '\"{}[]()<>¡!¿?&#=\t\n\r@"; 
        this->casosEspeciales        = true; 
        this->pasarAminuscSinAcentos = false;
    }

    Tokenizador::~Tokenizador (){
        delimiters = "";
    }
    
    Tokenizador& Tokenizador::operator= (const Tokenizador& tokenizador){
        // Comprobamos que no se este igualando el objeto a si mismo 
        if(this != &tokenizador){
            this->delimiters             = tokenizador.delimiters;
            this->casosEspeciales        = tokenizador.casosEspeciales;
            this->pasarAminuscSinAcentos = tokenizador.pasarAminuscSinAcentos;
        }        
        return *this;
    }

    void Tokenizador::Tokenizar (const std::string& str, std::list<std::string>& tokens) const{

        //Hacemos una copia del string que nos pasan
        std::string copia_str;
        copia_str = str;

        // Baciado de la lista de tokens
        tokens.clear();

        //Comprobar si tenemos que pasar a minusculas sin acento
        if(pasarAminuscSinAcentos){ copia_str = MinuscSinAcentos(str); }

        //Comprobamos si tenemos que detectar casos especiales
        if(!casosEspeciales){
            std::string::size_type lastPos  = copia_str.find_first_not_of(delimiters,0);    // Posicion del primer caracter del Token
            std::string::size_type pos      = copia_str.find_first_of(delimiters,lastPos);  // Posicion del primer delimitador

            while(std::string::npos != pos || std::string::npos != lastPos){
                tokens.push_back(copia_str.substr(lastPos, pos - lastPos));
                lastPos = copia_str.find_first_not_of(delimiters, pos);
                pos     = copia_str.find_first_of(delimiters, lastPos);
            }
        }
        else{
            std::string delimitersAux, delimitersURL, delimitersNum;
            delimitersAux = delimiters + " ";                                                  // Delimitadores que se comprueban el ultima instancia 
            delimitersURL = Substraer(delimitersAux, "_:/.?&-=#@");                            // Delimitadores que acepta la URL
            delimitersNum = Substraer(delimitersAux, ",.$%");                                  // Delimitadores que utiliza un numero
            std::string::size_type lastPos  = copia_str.find_first_not_of(delimitersAux,0);    // Posicion del primer caracter del Token
            std::string::size_type pos      = copia_str.find_first_of(delimitersAux,lastPos);  // Posicion del primer delimitador

            while(std::string::npos != pos || std::string::npos != lastPos){
                if(esURL(pos, lastPos, copia_str)){
                    pos     = copia_str.find_first_of(delimitersURL,lastPos);
                    tokens.push_back(copia_str.substr(lastPos, pos - lastPos));
                    lastPos = copia_str.find_first_not_of(delimitersAux, pos);
                    pos     = copia_str.find_first_of(delimitersAux, lastPos);
                }
                else if(esNumero(pos, lastPos, str, delimitersNum)){

                }
                else{
                    tokens.push_back(copia_str.substr(lastPos, pos - lastPos));
                    lastPos = copia_str.find_first_not_of(delimitersAux, pos);
                    pos     = copia_str.find_first_of(delimitersAux, lastPos);
                }
            }    
        }
    }

    // bool Tokenizar (const std::string& i, const std::string& f) const;
    // bool Tokenizar (const std::string & i) const;
    // bool TokenizarListaFicheros (const std::string& i) const;
    // bool TokenizarDirectorio (const std::string& i) const;

    void Tokenizador::DelimitadoresPalabra(const std::string& nuevoDelimiters){
        this->delimiters = ""; 
        this->AnyadirDelimitadoresPalabra(nuevoDelimiters);
    }
    
    void Tokenizador::AnyadirDelimitadoresPalabra(const std::string& nuevoDelimiters){

        uint16_t n;
        n = nuevoDelimiters.length();

        for (size_t i = 0; i < n; i++){
            if(!Contiene(delimiters, nuevoDelimiters[i])){
                this-> delimiters += nuevoDelimiters[i];
            }
        }
        //std::cout << "Delimitadores nuevo:\t" << delimiters << std::endl;
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


    /*
        FUNCIONES AUXILIARES CREADAS POR MI
    */

    bool Tokenizador::Contiene(const std::string& conjunto,const char& elemento){

        return (conjunto.find(elemento) != std::string::npos);

    }

    std::string Tokenizador::MinuscSinAcentos(const std::string& str)const {
        std::string minSin_str;
        minSin_str = "";

        for (size_t i = 0; i < str.length(); i++){
            unsigned char aux = str[i];
            switch (aux){
                case 209:   // 'Ñ'
                    minSin_str += 'ñ';
                    break;

                case 192:   // 'À'
                case 193:   // 'Á'
                case 224:   // 'à'
                case 225:   // 'á'
                    minSin_str += 'a';               
                    break;

                case 200:   // 'È'
                case 201:   // 'É' 
                case 232:   // 'è'
                case 233:   // 'é'
                    minSin_str += 'e';               
                    break;
                
                case 204:   // 'Ì'
                case 205:   // 'Í'
                case 236:   // 'ì'
                case 237:   // 'í'
                    minSin_str += 'i';               
                    break;

                case 210:   // 'Ò'
                case 211:   // 'Ó' 
                case 242:   // 'ò'
                case 243:   // 'ó'
                    minSin_str += 'o';               
                    break;

                case 217:   // 'Ù'
                case 218:   // 'Ú' 
                case 249:   // 'ù'
                case 250:   // 'ú'
                    minSin_str += 'u';               
                    break;
            
                default:
                    minSin_str += std::tolower(str[i]);
                    break;
            }
        }
        

        return minSin_str;
    }

    std::string Tokenizador::Substraer(const std::string& str, const std::string& delet) const{
        std::string result;
        result = str;

        for (size_t i = 0; i < delet.length(); i++){
             result.erase(remove(result.begin(), result.end(), delet[i]), result.end());
        }

        return result;
    }

    bool Tokenizador::esURL(const std::string::size_type& pos, const std::string::size_type& lastPos, const std::string& str)const{
        return  (
                    str.find("http:")  == lastPos ||
                    str.find("https:") == lastPos ||
                    str.find("ftp:")   == lastPos
                );
    }

    bool Tokenizador::esNumero(const std::string::size_type& pos, const std::string::size_type& lastPos, const std::string& str, const std::string& del)const{
        bool resul;
        resul = false;

        return resul;
    }

    