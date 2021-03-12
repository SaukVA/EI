#include "tokenizador.h"

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
        this->delimitersAux = delimiters + " ";
        this->delimitersURL = Substraer(delimitersAux, "_:/.?&-=#@");
        this->delimitersNum = Substraer(delimitersAux, ",.%$") + "%$";
        this->delimitersMail = Substraer(delimitersAux, "@.-_");
        this->delimitersAcr = Substraer(delimitersAux, ".");
        this->delimitersMul = Substraer(delimitersAux, "-");
        this->casosEspeciales = tokenizador.casosEspeciales;
        this->pasarAminuscSinAcentos = tokenizador.pasarAminuscSinAcentos;
    }
}

Tokenizador::Tokenizador()
{
    this->delimiters = ",;:.-/+*\\ '\"{}[]()<>?!??&#=\t\n\r@";
    this->delimitersAux = ",;:.-/+*\\ '\"{}[]()<>?!??&#=\t\n\r@ ";
    this->delimitersURL = ",;+*\\ '\"{}[]()<>?!?\t\n\r ";
    this->delimitersNum = ";:-/+*\\ '\"{}[]()<>?!??&#=\t\n\r@ %$";
    this->delimitersMail = ",;:/+*\\ '\"{}[]()<>?!??&#=\t\n\r ";
    this->delimitersAcr = ",;:-/+*\\ '\"{}[]()<>?!??&#=\t\n\r@ ";
    this->delimitersMul = ",;:./+*\\ '\"{}[]()<>?!??&#=\t\n\r@ ";
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
        this->delimitersAux = delimiters + " ";
        this->delimitersURL = Substraer(delimitersAux, "_:/.?&-=#@");
        this->delimitersNum = Substraer(delimitersAux, ",.%$") + "%$";
        this->delimitersMail = Substraer(delimitersAux, "@.-_");
        this->delimitersAcr = Substraer(delimitersAux, ".");
        this->delimitersMul = Substraer(delimitersAux, "-");
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
        std::string::size_type lastPos = copia_str.find_first_not_of(delimitersAux, 0); // Posicion del primer caracter del Token
        std::string::size_type pos = copia_str.find_first_of(delimitersAux, lastPos);   // Posicion del primer delimitador

        while (std::string::npos != pos || std::string::npos != lastPos)
        {
            //Comprobamos si es una URL
            if (esURL(lastPos, copia_str))
            {
                //std::cout << "Soy una URL" << std::endl;
                pos = copia_str.find_first_of(delimitersURL, lastPos);
                tokens.push_back(copia_str.substr(lastPos, pos - lastPos));
            }

            //Comprobamos si es una Numero
            else if (esNumero(lastPos, copia_str, pos))
            {
                //std::cout << "Soy un Numero" << std::endl;
                if (copia_str[lastPos - 1] == '.' || copia_str[lastPos - 1] == ',')
                {
                    tokens.push_back('0' + copia_str.substr(lastPos - 1, pos - (lastPos - 1)));
                }
                else
                {
                    tokens.push_back(copia_str.substr(lastPos, pos - lastPos));
                }

                //Si se termina por '%' o '$' se a?ade eso como un token extra
                if (copia_str[pos] == '$' || copia_str[pos] == '%')
                {
                    std::string temp;
                    temp = copia_str[pos];
                    tokens.push_back(temp);
                    ++pos;
                }
            }

            //Comprobamos si es un Email
            else if (esEmail(lastPos, copia_str, pos))
            {
                //std::cout << "Soy un Email" << std::endl;
                pos = Encontrar_final(lastPos, copia_str, delimitersMail);
                tokens.push_back(copia_str.substr(lastPos, pos - lastPos));
            }

            //Comprobamos si es un Acronimo
            else if (esAcronimo(lastPos, copia_str, pos))
            {
                //std::cout << "Soy un Acronimo" << std::endl;
                tokens.push_back(copia_str.substr(lastPos, pos - lastPos));
            }

            //Comprobamos si es una Multipalabra
            else if (esMultPalab(lastPos, copia_str, pos))
            {
                //std::cout << "Soy una Multipalabra" << std::endl;
                tokens.push_back(copia_str.substr(lastPos, pos - lastPos));
            }

            //Si no se mete el token directamente
            else
            {
                //std::cout << "Soy otro tipo de Token" << std::endl;
                tokens.push_back(copia_str.substr(lastPos, pos - lastPos));
            }

            lastPos = copia_str.find_first_not_of(delimitersAux, pos);
            pos = copia_str.find_first_of(delimitersAux, lastPos);
        }
    }
}

bool Tokenizador::Tokenizar(const std::string &i, const std::string &f) const
{
    bool resul;
    std::ifstream i_file;
    std::ofstream f_file;
    std::list<std::string> tokens;
    std::string str, temp;

    resul = false;
    i_file.open(i.c_str(), std::ios::binary);
    f_file.open(f.c_str(), std::ios::binary);

    if (!i_file)
    {
        std::cerr << "ERROR: No existe el archivo: " << i << std::endl;
    }

    else
    {
        std::stringstream strStream;
        strStream << i_file.rdbuf();
        while (std::getline(strStream, str, '\n'))
        {
            Tokenizar(str, tokens);
            for (std::string const &token : tokens){ 
                temp += token + "\n";
            }
        }
        f_file << temp;
        resul = true;
    }

    i_file.close();
    f_file.close();

    return resul;
}

bool Tokenizador::Tokenizar(const std::string &i) const
{
    return Tokenizar(i, i + ".tk");
}

bool Tokenizador::TokenizarListaFicheros(const std::string &i) const{

    std::ifstream i_file;
    std::string cadena;
    bool resul;
    resul = true;

    i_file.open(i.c_str(), std::ios::binary);

    if (!i_file){
        std::cerr << "ERROR: No existe el archivo: " << i << std::endl;
        return false;
    }
    else{
        std::stringstream strStream;
        strStream << i_file.rdbuf();
        while(getline(strStream, cadena, '\n')){
            if(cadena.length() != 0){
                if(!Tokenizar(cadena)){ resul = false; }
            }
        }
    }

    i_file.close();
    return resul;
}

bool Tokenizador::TokenizarDirectorio (const std::string& i) const{
    struct stat dir;
    // Compruebo la existencia del directorio
    int err = stat(i.c_str(), &dir);
    if(err==-1 || !S_ISDIR(dir.st_mode))
        return false;
    else {
        // Hago una lista en un fichero con find>fich
        std::string cmd="find "+i+" -follow |sort > .lista_fich";
        system(cmd.c_str());
        return TokenizarListaFicheros(".lista_fich");
    }
}

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
        if (delimiters.find_first_of(nuevoDelimiters[i],0) == std::string::npos){
            this->delimiters += nuevoDelimiters[i];
        }
    }
    this->delimitersAux = delimiters + " ";
    this->delimitersURL = Substraer(delimitersAux, "_:/.?&-=#@");
    this->delimitersNum = Substraer(delimitersAux, ",.%$") + "%$";
    this->delimitersMail = Substraer(delimitersAux, "@.-_");
    this->delimitersAcr = Substraer(delimitersAux, ".");
    this->delimitersMul = Substraer(delimitersAux, "-");
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

std::string Tokenizador::MinuscSinAcentos(const std::string &str) const
{
    std::string minSin_str;
    minSin_str.resize(str.length());
    //minSin_str = str;

    for (int i = str.length()-1; i >= 0 ; --i)
    {
        unsigned char aux = str[i];
        switch (aux)
        {
        case 209: // '?'
            minSin_str[i] = '�';
            break;

        case 192: // '?'
        case 193: // '?'
        case 224: // '?'
        case 225: // '?'
            minSin_str[i] = 'a';
            break;

        case 200: // '?'
        case 201: // '?'
        case 232: // '?'
        case 233: // '?'
            minSin_str[i] = 'e';
            break;

        case 204: // '?'
        case 205: // '?'
        case 236: // '?'
        case 237: // '?'
            minSin_str[i] = 'i';
            break;

        case 210: // '?'
        case 211: // '?'
        case 242: // '?'
        case 243: // '?'
            minSin_str[i] = 'o';
            break;

        case 217: // '?'
        case 218: // '?'
        case 249: // '?'
        case 250: // '?'
            minSin_str[i] = 'u';
            break;

        default:
            minSin_str[i] = std::tolower(str[i]);
            break;
        }
    }

    return minSin_str;
}

std::string Tokenizador::Substraer(const std::string &str, const std::string &delet) const
{
    std::string result;
    result = str;

    for (size_t i = 0; i < delet.length(); i++){
        result.erase(remove(result.begin(), result.end(), delet[i]), result.end());
    }

    return result;
}

std::string::size_type Tokenizador::Encontrar_final(const std::string::size_type &lasPos, const std::string &str, const std::string &del) const
{
    std::string::size_type pos, aux1, aux2;
    pos = str.find_first_of(del, lasPos);
    aux1 = str.find_first_of(delimitersAux, lasPos);
    aux2 = str.find_first_of(delimitersAux, aux1 + 1);

    while (aux1 <= pos && aux1 != std::string::npos)
    {
        if (aux1 == aux2 - 1)
        {
            pos = aux1;
        }
        aux1 = aux2;
        aux2 = str.find_first_of(delimitersAux, aux1 + 1);
    }
    if (pos == std::string::npos && delimiters.find_first_of(str[str.length() - 1], 0) != std::string::npos){
        pos = str.length() - 1;
    }

    return pos;
}

bool Tokenizador::esURL(const std::string::size_type &lastPos, const std::string &str) const
{
    return (
        str.substr(lastPos, lastPos+5).find("http:") == 0  && str.length() > 5 ||   //Comprobamos si empriza por http: y tiene algo a continuaci�n
        str.substr(lastPos, lastPos+6).find("https:") == 0 && str.length() > 6 ||   //Comprobamos si empriza por https: y tiene algo a continuaci�n
        str.substr(lastPos, lastPos+4).find("ftp:") == 0   && str.length() > 4);    //Comprobamos si empriza por ftp: y tiene algo a continuaci�n
}

bool Tokenizador::esNumero(const std::string::size_type &lastPos, const std::string &str, std::string::size_type &pos) const
{
    if( 
        str[pos] == '.' || str[pos] == ',' ||           // Comprobamos que contenga una coma o un punto
        str[lastPos-1] == ',' || str[lastPos-1] == '.'  // o que empiece por coma o punto 
    ){
        std::string::size_type posAux;
        posAux = Encontrar_final(lastPos, str, delimitersNum);
        if (posAux <= str.find_first_not_of("0123456789,.", lastPos)){  // Comprobamos que esta formado solo por numeros putos y comas
            pos = posAux;
            return true;
        }
    }
    return false;
}

bool Tokenizador::esEmail(const std::string::size_type &lasPos, const std::string &str, const std::string::size_type &pos) const
{

    std::string::size_type posAux, posAux2, posAux3;
    posAux = str.find_first_of("@", pos + 1);
    posAux2 = str.find_first_of(" ", pos + 1);
    posAux3 = str.find_first_of(delimitersMail + ".-_", pos + 1);

    return (
        str[pos] == '@' &&                                   //Comprobamos que el delimitador que se ha encontrado es un '@'
        (posAux == std::string::npos || posAux2 < posAux) && //Comprobamos que no hayan '@' despues del primer '@'
        posAux3 != pos + 1                                   //Comprobamos que despues del '@' no venga ningun delimitador
    );
}

bool Tokenizador::esAcronimo(const std::string::size_type &lastPos, const std::string &str, std::string::size_type &pos) const
{

    if(str[pos] == '.'){
        std::string::size_type posAux;
        posAux = Encontrar_final(lastPos, str, delimitersAcr);
        if (
            delimiters.find_first_of(".", 0) != std::string::npos &&    // Comprobamos que se este utilizando el '.' como delimitador
            posAux > str.find_first_of(".", lastPos)                    // y que haya algo detras del punto                     
        ){
            pos = posAux;
            return true;
        }
    }
    return false;
}

bool Tokenizador::esMultPalab(const std::string::size_type &lastPos, const std::string &str, std::string::size_type &pos) const
{
    if(str[pos] == '-'){
        std::string::size_type posAux;
        posAux = Encontrar_final(lastPos, str, delimitersMul);
        if(
            delimiters.find_first_of("-", 0) != std::string::npos &&    // Comprobamos que se este utilizando el '-'
            posAux > str.find_first_of("-", lastPos)                    // y que haya algo despues del guion
        ){
            pos = posAux;
            return true;
        }
    }
    return false;
}