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
}

IndexadorHash::IndexadorHash(const string& directorioIndexacion){
    //...
}

IndexadorHash::IndexadorHash(const IndexadorHash&){
    //...
}
        
IndexadorHash::~IndexadorHash(){
    //...
}
        
IndexadorHash& IndexadorHash::operator= (const IndexadorHash&){
    //...
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
    return true;
}
bool IndexadorHash::RecuperarIndexacion (const string& directorioIndexacion){
    return true;
}

void IndexadorHash::ImprimirIndexacion() const{
    //...
}

bool IndexadorHash::IndexarPregunta(const string& preg){
    //...
    return false;
}

bool IndexadorHash::DevuelvePregunta(string& preg) const{
    //...
    return false;
}

bool IndexadorHash::DevuelvePregunta(const string& word, InformacionTerminoPregunta& inf) const{
    //...
    return false;
}

bool IndexadorHash::DevuelvePregunta(InformacionPregunta& inf) const{
    //...
    return false;
}

void IndexadorHash::ImprimirIndexacionPregunta(){
    //...
}

void IndexadorHash::ImprimirPregunta(){
    //...
}

bool IndexadorHash::Devuelve(const string& word, InformacionTermino& inf) const{
    //...
    return false;
}

bool IndexadorHash::Devuelve(const string& word, const string& nomDoc, InfTermDoc& InfDoc)const{
    //...
    return false;
}

bool IndexadorHash::Existe(const string& word) const{
    //...
    return false;
}

bool IndexadorHash::Borra(const string& word){
    //...
    return false;
}

bool IndexadorHash::BorraDoc(const string& nomDoc){
    //...
    return false;
}

void IndexadorHash::VaciarIndiceDocs(){
    //...
}

void IndexadorHash::VaciarIndicePreg(){
    //...
}

bool IndexadorHash::Actualiza(const string& word, const InformacionTermino& inf){
    //...
    return false;
}

bool IndexadorHash::Inserta(const string& word, const InformacionTermino& inf){
    //...
    return false;
}

int IndexadorHash::NumPalIndexadas() const{
    //...
}

string IndexadorHash::DevolverFichPalParada () const{
    //...
}

void IndexadorHash::ListarPalParada() const{
    //...
}

int IndexadorHash::NumPalParada() const{
    //...
}

string IndexadorHash::DevolverDelimitadores () const{
    //...
}

bool IndexadorHash::DevolverCasosEspeciales () const{
    //...
    return false;
}

bool IndexadorHash::DevolverPasarAminuscSinAcentos () const{
    //...
    return false;
}

bool IndexadorHash::DevolverAlmacenarPosTerm () const{
    //...
    return false;
}

string IndexadorHash::DevolverDirIndice () const{
    //...
}

int IndexadorHash::DevolverTipoStemming () const{
    //...
}

bool IndexadorHash::DevolverAlmEnDisco () const{
    //...
    return false;
}

void IndexadorHash::ListarInfColeccDocs() const{
    //...
}

void IndexadorHash::ListarTerminos() const{
    //...
}

bool IndexadorHash::ListarTerminos(const string& nomDoc) const{
    //...
    return false;
}

void IndexadorHash::ListarDocs() const{
    //...
}

bool IndexadorHash::ListarDocs(const string& nomDoc) const{
    //...
    return false;
}

IndexadorHash::IndexadorHash(){
    //...
}