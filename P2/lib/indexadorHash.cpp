#include "indexadorHash.h"


ostream& operator<<(ostream& s, const IndexadorHash& p) {
    s << "Fichero con el listado de palabras de parada: " << p.ficheroStopWords << endl;
    s << "Tokenizador: " << p.tok << endl;
    s << "Directorio donde se almacenara el indice generado: " << p.directorioIndice << endl;
    s << "Stemmer utilizado: " << p.tipoStemmer << endl;
    s << "Informacion de la coleccion indexada: " << p.informacionColeccionDocs << endl;
    s << "Se almacenara parte del indice en disco duro: " << p.almacenarEnDisco << endl;
    s << "Se almacenaran las posiciones de los terminos: " << p.almacenarPosTerm;
    return s;
}

IndexadorHash::IndexadorHash(const string& fichStopWords, const string& delimitadores, const bool& detectComp, const bool& minuscSinAcentos, const string& dirIndice, const int& tStemmer, const bool& almEnDisco, const bool& almPosTerm){
    //...
    // ifstream file;
    // string str;

    // file.open(fichStopWords.c_str(),ios::binary);

    // if(file){
    //     this->ficheroStopWords = fichStopWords;
    //     std::stringstream strStream;
    //     strStream << file.rdbuf();
    //     while (getline(strStream, str, '\n')){

    //     }
    // }

    // file.close();
    
}

IndexadorHash::IndexadorHash(const string& directorioIndexacion){
    //...
}

IndexadorHash::IndexadorHash(const IndexadorHash& index){
    if(this != &index){
        indice = index.indice;
        indiceDocs = index.indiceDocs;
        informacionColeccionDocs = index.informacionColeccionDocs;
        infPregunta = index.infPregunta;
        almacenarEnDisco =index.almacenarEnDisco;
        almacenarPosTerm = index.almacenarPosTerm;
        tipoStemmer = index.tipoStemmer;
        directorioIndice = index.directorioIndice;
        pregunta = index.pregunta;
        indicePregunta = index.indicePregunta;
        ficheroStopWords = index.ficheroStopWords;
        stopWords = index.stopWords;
        tok = index.tok;
    }
}
        
IndexadorHash::~IndexadorHash(){
    indice.clear();
    indiceDocs.clear();
    almacenarEnDisco = false;
    almacenarPosTerm = false;
    tipoStemmer = 0;
    directorioIndice = "";
    pregunta = "";
    indicePregunta.clear();
    ficheroStopWords = "";
}
        
IndexadorHash& IndexadorHash::operator= (const IndexadorHash& index){
    if(this != &index){
        indice = index.indice;
        indiceDocs = index.indiceDocs;
        informacionColeccionDocs = index.informacionColeccionDocs;
        infPregunta = index.infPregunta;
        almacenarEnDisco =index.almacenarEnDisco;
        almacenarPosTerm = index.almacenarPosTerm;
        tipoStemmer = index.tipoStemmer;
        directorioIndice = index.directorioIndice;
        pregunta = index.pregunta;
        indicePregunta = index.indicePregunta;
        ficheroStopWords = index.ficheroStopWords;
        stopWords = index.stopWords;
        tok = index.tok;
    }
}

bool IndexadorHash::Indexar(const string& ficheroDocumentos){
    //...
    return false;
}

bool IndexadorHash::IndexarDirectorio(const string& dirAIndexar){
    //...
    return false;
}

bool IndexadorHash::GuardarIndexacion() const{
    //...
    return false;
}

bool IndexadorHash::RecuperarIndexacion (const string& directorioIndexacion){
    //...
    return false;
}

void IndexadorHash::ImprimirIndexacion() const{
    cout << "Terminos indexados: " << endl;
    for(auto it = indiceDocs.begin(); it != indiceDocs.end(); ++it){
        cout << it->first << "\t" << it->second << endl;
    }

    cout << "Documentos indexados: " << endl;
    for(auto it = indice.begin(); it != indice.end(); ++it){
        cout << it->first << "\t" << it->second << endl;
    }
}

bool IndexadorHash::IndexarPregunta(const string& preg){
    //...
    return false;
}

bool IndexadorHash::DevuelvePregunta(string& preg) const{
    if(!pregunta.empty()){
        preg = pregunta;
        return true;
    }
    return false;
}

bool IndexadorHash::DevuelvePregunta(const string& word, InformacionTerminoPregunta& inf) const{
    if(indicePregunta.find(word) == indicePregunta.end()){
        return false;
    }
    else{
        inf = indicePregunta.find(word)->second;
        return true;
    }
}

bool IndexadorHash::DevuelvePregunta(InformacionPregunta& inf) const{
    //...
    return false;
}

void IndexadorHash::ImprimirIndexacionPregunta(){
    cout << "Pregunta indexada: " << pregunta << endl;
    cout << "Terminos indexados en la pregunta: " << endl;
    for(auto it = indicePregunta.begin(); it != indicePregunta.end(); ++it){
        cout << it->first << "\t" << it->second << endl;
    }
    cout << "Informacion de la pregunta: " << infPregunta << endl;
}

void IndexadorHash::ImprimirPregunta(){
    cout << "Pregunta indexada: " << pregunta << endl;
    cout << "Informacion de la pregunta: " << infPregunta << endl;
}

bool IndexadorHash::Devuelve(const string& word, InformacionTermino& inf) const{
    if(Existe(word)){
        inf = indice.find(word)->second;
        return true;
    }
    return false;
}

bool IndexadorHash::Devuelve(const string& word, const string& nomDoc, InfTermDoc& InfDoc)const{
    //...
    return false;
}

bool IndexadorHash::Existe(const string& word) const{
    return (indice.find(word) != indice.end());
}

bool IndexadorHash::Borra(const string& word){
    return (indice.erase(word) != 0);
}

bool IndexadorHash::BorraDoc(const string& nomDoc){
    //...
    return false;
}

void IndexadorHash::VaciarIndiceDocs(){
    indice.clear();
    indiceDocs.clear();
}

void IndexadorHash::VaciarIndicePreg(){
    indicePregunta.clear();
}

bool IndexadorHash::Actualiza(const string& word, const InformacionTermino& inf){
    
    if(Existe(word)){
        indice[word] = inf;
        return true;
    }
    return false;
}

bool IndexadorHash::Inserta(const string& word, const InformacionTermino& inf){
    if(!Existe(word)){
        indice[word] = inf;
        return true;
    }
    return false;
}

int IndexadorHash::NumPalIndexadas() const{
    return indice.size();
}

string IndexadorHash::DevolverFichPalParada () const{
    return ficheroStopWords;
}

void IndexadorHash::ListarPalParada() const{
    for(auto it = stopWords.begin(); it != stopWords.end(); ++it){
        cout << (*it) << endl;
    }
}

int IndexadorHash::NumPalParada() const{
    return stopWords.size();
}

string IndexadorHash::DevolverDelimitadores () const{
    return tok.DelimitadoresPalabra();
}

bool IndexadorHash::DevolverCasosEspeciales () const{
    return tok.CasosEspeciales();
}

bool IndexadorHash::DevolverPasarAminuscSinAcentos () const{
    return tok.PasarAminuscSinAcentos();
}

bool IndexadorHash::DevolverAlmacenarPosTerm () const{
    return almacenarPosTerm;
}

string IndexadorHash::DevolverDirIndice () const{
    return directorioIndice;
}

int IndexadorHash::DevolverTipoStemming () const{
    return tipoStemmer;
}

bool IndexadorHash::DevolverAlmEnDisco () const{
    return almacenarEnDisco;
}

void IndexadorHash::ListarInfColeccDocs() const{
    cout << informacionColeccionDocs << endl;
}

void IndexadorHash::ListarTerminos() const{
    for(auto it = indice.begin(); it != indice.end(); ++it){
        cout << it->first << "\t" << it->second << endl;
    }
}

bool IndexadorHash::ListarTerminos(const string& nomDoc) const{
    if(indiceDocs.find(nomDoc) == indiceDocs.end()){
        return false;
    }
    else{
        //...
        return true;
    }
}

void IndexadorHash::ListarDocs() const{
    for(auto it = indiceDocs.begin(); it != indiceDocs.end(); ++it){
        cout << it->first << "\t" << it->second << endl;
    }
}

bool IndexadorHash::ListarDocs(const string& nomDoc) const{
    if(indiceDocs.find(nomDoc) == indiceDocs.end()){
        return false;
    }
    else{
        cout << indiceDocs.find(nomDoc)->first << "\t" << indiceDocs.find(nomDoc)->second << endl;
        return true;
    }
}

IndexadorHash::IndexadorHash(){
    pregunta = "";
    ficheroStopWords = "";
    directorioIndice= "";
    tipoStemmer = 0;
    almacenarEnDisco = false;
    almacenarPosTerm = false;
}