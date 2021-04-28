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

    ifstream file;   //Declaramos los elementros que vamos a usar 
    string str;

    file.open(fichStopWords.c_str(),ios::binary);   // Intentamos abrir el ficheroStopWords de forma binaria

    if(file){
        this->ficheroStopWords = fichStopWords;     // Asignamos el nombre del fichero a la bariable
        stringstream strStream;                     // Creamos un stringstream para almacenar el fichero
        strStream << file.rdbuf();                  // Volcamos el fichore en la variable
        while (getline(strStream, str, '\n')){      // Recorremos por lineal el fichero
            if(str.length() != 0){
                stopWords.insert(str);              //??? Con esto sobra? // Guardamos la palabra de parada
            }
        }
    }

    file.close();                                   // Cerramos el fichero

    directorioIndice = dirIndice;                   // Guardamos el resto de datos
    if(dirIndice == ""){directorioIndice = "./";}
    indice.clear();
    indiceDocs.clear();
    indicePregunta.clear();
    tipoStemmer = tStemmer;
    almacenarEnDisco = almEnDisco;
    almacenarPosTerm = almPosTerm;
    tok.CasosEspeciales(detectComp);
    tok.DelimitadoresPalabra(delimitadores);
    tok.PasarAminuscSinAcentos(minuscSinAcentos);   
    
}

IndexadorHash::IndexadorHash(const string& directorioIndexacion){
    
    ifstream documento;
    string nombre_fichero, linea, termino;
    unordered_map<long int,InfTermDoc> l_d;
    list<int> l;
    list<string> l_linea;
    stringstream datos, d_indice, d_indiceDoc, d_indicePregunta;
    InfTermDoc infTermDoc;
    InformacionTermino infTer;
    InformacionTerminoPregunta infTermPre;
    InfDoc infDoc;
    Tokenizador token;

    int temp, idDoc, ft;
    bool aux;

    nombre_fichero = "";
    linea = "";
    token.DelimitadoresPalabra("\t ");

    for (int i = 0; i < 4; i++){
        switch (i){
            case 0:     // datos_simples.txt
                nombre_fichero = directorioIndexacion + "/datos_simples.txt";
                documento.open(nombre_fichero.c_str(),ios::binary);
                if(documento){ datos << documento.rdbuf(); }
                else{ cerr << "ERROR!!!: No se ha podido abrir el archivo:\t" << nombre_fichero << endl; }
                documento.close();
                
                temp = 0;
                stopWords.clear();
                while (getline(datos, linea, '\n')){
                    switch (temp){
                        case 0:pregunta = linea; break;
                        case 1:ficheroStopWords = linea; break;
                        case 2:directorioIndice = linea; break;
                        case 3:tipoStemmer = stoi(linea); break;
                        case 4:istringstream(linea) >> almacenarEnDisco; break;
                        case 5:istringstream(linea) >> almacenarPosTerm; break;
                        case 6:informacionColeccionDocs.Set_numDocs(stoi(linea)); break;                        
                        case 7:informacionColeccionDocs.Set_numTotalPal(stoi(linea)); break;
                        case 8:informacionColeccionDocs.Set_numTotalPalSinParada(stoi(linea)); break;
                        case 9:informacionColeccionDocs.Set_numTotalPalDiferentes(stoi(linea)); break;
                        case 10:informacionColeccionDocs.Set_tamBytes(stoi(linea)); break;
                        case 11:infPregunta.set_numTotalPal(stoi(linea)); break;
                        case 12:infPregunta.set_numTotalPalSinParada(stoi(linea)); break;
                        case 13:infPregunta.set_numTotalPalDiferentes(stoi(linea)); break;
                        case 14:istringstream(linea) >> aux; tok.CasosEspeciales(aux); break;
                        case 15:istringstream(linea) >> aux; tok.PasarAminuscSinAcentos(aux); break;
                        case 16:tok.DelimitadoresPalabra(linea); break;                       
                        default: stopWords.insert(linea); break;
                    }
                    ++temp;
                }
                break;
            case 1:     // indice.txt
                nombre_fichero = directorioIndexacion + "/indice.txt";
                documento.open(nombre_fichero.c_str(),ios::binary);
                if(documento){ d_indice << documento.rdbuf(); }
                else{ cerr << "ERROR!!!: No se ha podido abrir el archivo:\t" << nombre_fichero << endl; }
                documento.close();

                indice.clear();
                while (getline(d_indice, linea, '\n')){
                    l.clear();
                    l_d.clear();
                    token.Tokenizar(linea, l_linea);
                    auto it = l_linea.begin();              // pal2	Frecuencia total: 3	fd: 2	Id.Doc: 2	ft: 2	0	2	Id.Doc: 1	ft: 1	2
                    termino = *it;                          // pal2
                    ++it; ++it; ++it;                       // Frecuencia total:
                    infTer.set_ftc(stoi((*it).c_str()));    // 3
                    ++it; ++it; ++it;                       // fd: 2
                    while(it != l_linea.end()){
                        l.clear();
                        ++it;                               // Id.Doc:
                        idDoc = stoi((*it).c_str());        // 2, 3
                        ++it; ++it;                         // ft:
                        ft = stoi((*it).c_str());           // 2, 1
                        ++it;
                        while(it != l_linea.end() && *it != "Id.Doc:"){
                            l.push_back(stoi((*it).c_str()));      // 0, 2, 2
                            ++it;
                        }
                        infTermDoc.set_ft(ft);
                        infTermDoc.set_posTerm(l);
                        l_d.insert({idDoc,infTermDoc});
                    }
                    infTer.set_l_docs(l_d);
                    indice.insert({termino, infTer});                    
                }
                break;
            case 2:     // indiceDocs.txt
                nombre_fichero = directorioIndexacion + "/indiceDocs.txt";
                documento.open(nombre_fichero.c_str(),ios::binary);
                if(documento){ d_indiceDoc << documento.rdbuf(); }
                else{ cerr << "ERROR!!!: No se ha podido abrir el archivo:\t" << nombre_fichero << endl; }
                documento.close();

                indiceDocs.clear();
                while (getline(d_indiceDoc,linea, '\n')){
                    token.Tokenizar(linea, l_linea);
                    auto it = l_linea.begin();              //corpus_corto/fichero2.txt	idDoc: 2	numPal: 5	numPalSinParada: 3	numPalDiferentes: 2	tamBytes: 23
                    termino = *it;                          //corpus_corto/fichero2.txt
                    ++it; ++it;                             //idDoc:
                    infDoc.Set_IdDoc(stoi((*it).c_str()));            // 2
                    ++it; ++it;                             // numPal:
                    infDoc.Set_numPal(stoi((*it).c_str()));           // 5
                    ++it; ++it;                             // numPalSinParada:
                    infDoc.Set_numPalSinParada(stoi((*it).c_str()));  // 3
                    ++it; ++it;                             // numPalDiferente:
                    infDoc.Set_numPalDiferentes(stoi((*it).c_str())); // 2
                    ++it; ++it;                             // tamBytes:
                    infDoc.Set_tamBytes(stoi((*it).c_str()));         // 23
                    indiceDocs.insert({termino,infDoc});
                }
                break;
            case 3:
                nombre_fichero = directorioIndexacion + "/indicePregunta.txt";
                documento.open(nombre_fichero.c_str(),ios::binary);
                if(documento){ d_indicePregunta << documento.rdbuf(); }
                else{ cerr << "ERROR!!!: No se ha podido abrir el archivo:\t" << nombre_fichero << endl; }
                documento.close();

                indiceDocs.clear();
                while (getline(d_indicePregunta,linea, '\n')){
                    l.clear();
                    token.Tokenizar(linea, l_linea);
                    auto it = l_linea.begin();              // hace?	ft: 4	2	5	8	11
                    termino = *it;                          // hace?
                    ++it; ++it;                             // ft:
                    infTermPre.set_ft(stoi((*it).c_str())); // 4
                    ++it;
                    while(it != l_linea.end()){
                        l.push_back(stoi((*it).c_str()));   // 2, 5, 8, 11
                        ++it;
                    }
                    infTermPre.set_posTerm(l);
                    indicePregunta.insert({termino, infTermPre});
                }
                break;
        }
    }
    
    
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
    return *this;
}

bool IndexadorHash::Indexar(const string& ficheroDocumentos){

    ifstream file;                                          //Declaramos los elementros que vamos a usar 
    string nomFichero;
    struct stat buffer;
    int id;
    InfDoc inf;
    bool indexar;

    file.open(ficheroDocumentos.c_str(),ios::binary);       // Intentamos abrir el ficheroStopWords de forma binaria

    if(file){
        stringstream strStream;                             // Creamos un stringstream para almacenar el fichero
        strStream << file.rdbuf();                          // Volcamos el fichore en la variable
        while (getline(strStream, nomFichero, '\n')){       // Recorremos por lineal el fichero

            if(nomFichero.length() != 0 && stat(nomFichero.c_str(), &buffer) != -1 && !S_ISDIR(buffer.st_mode)){  //??? esta bien? // Comrpobamos que el nombre del ficher es correcto
                if(indiceDocs.find(nomFichero) == indiceDocs.end()){    //Si el documento no esta indexado
                    id = indiceDocs.size() + 1;
                    indexar = true;
                }
                else{                                                   //Si el documento estaba ya indexado 
                    if(indiceDocs.find(nomFichero)->second.Posterior()){        //??? Para comprobar la fecha estaria bien mirar los segundos // Si ya se ha indexado anteriormente
                        id = indiceDocs.find(nomFichero)->second.Get_IdDoc();   // Obtenemos el id
                        BorraDoc(nomFichero);                                   // Borramos los datos que teniamos de antes del documento
                        indexar = true;                                         // Indicamos que se tiene que reindexar el documento 
                    }else{ 
                        indexar = false;                                        // Indicamos que NO se tiene que reindexar 
                    }
                    cerr << "WARNING!!!: Este documento ya ha sido indexado:\t" << nomFichero << endl;
                }
                
                if(indexar){                                            // Si es necesario indexamos el documento
                    inf = InfDoc();                                     // Añadimos el documento
                    inf.Set_IdDoc(id);
                    indiceDocs.insert({nomFichero,inf});
                    IndexarDoc(nomFichero);                             // Indexamos el documento
                }

            }
            else{ cerr << "ERROR!!!: No se ha podido abrir el archivo:\t" << nomFichero << endl; }

        }
    }
    else{ cerr << "ERROR!!!: No se ha podido abrir el archivo :\t" << ficheroDocumentos << endl; }

    file.close();                                   // Cerramos el fichero

    return true;
}

void IndexadorHash::IndexarDoc(const string& nom) {
    
    ifstream documento;
    InfDoc *infDocumento;
    int idDoc, pal, palParada;
    struct stat doc_buffer;
    InformacionTermino infoTerm;
    InfTermDoc infTermDoc;
    list<string> tokens;
    string delimitadores;
    unordered_set<string>dif;

    infDocumento = &indiceDocs.find(nom)->second;               // Obtenemos el documento
    idDoc = (*infDocumento).Get_IdDoc();                        // Obtenemos el id del doucumento
    pal = 0;
    palParada = 0;
    delimitadores = tok.DelimitadoresPalabra();                 // ??? vale o lo tengo que hacer con los ficheros 
    tok.DelimitadoresPalabra(delimitadores + "\n");

    documento.open(nom.c_str(),ios::binary);                    // Abrimos el documento

    if(documento){
        stringstream strStream;                                 // Creamos un stringstream para almacenar el fichero
        strStream << documento.rdbuf();                         // Volcamos el fichore en la variable
        tok.Tokenizar(strStream.str(), tokens);                 // Sacamos los tokenes que contiene el documento 

        for(string token : tokens){                         // Recorremos el documento token a token 
            if(stopWords.find(token) == stopWords.end()){   // Si no es una stopWord
                if(Existe(token)){
                    indice.find(token)->second.nuevaReferencia(idDoc,pal,almacenarPosTerm);    //Añadimos la referencia
                }
                else{
                    infoTerm = InformacionTermino();                            // Creamos la informacion del termino
                    infoTerm.nuevaReferencia(idDoc,pal,almacenarPosTerm);       // Agregamos la referencia al nuevo termino
                    indice.insert({token,infoTerm});                            // Metemos el termino en el indice
                }
                if(dif.find(token) == dif.end()){ dif.insert(token); }          // Si no hemos visto la palabra la añadimos 
            }
            else{                                           // Si es una stopWord
                palParada++;
            }
            pal++;
        }

        stat(nom.c_str(), &doc_buffer);
        tok.DelimitadoresPalabra(delimitadores);

        (*infDocumento).Set_numPal(pal);                        //Colocamos los datos del documento
        (*infDocumento).Set_numPalSinParada(pal - palParada);
        (*infDocumento).Set_numPalDiferentes(dif.size());
        (*infDocumento).Set_tamBytes(doc_buffer.st_size);

        informacionColeccionDocs.NuevaInfDoc(pal, palParada, indice.size(), doc_buffer.st_size);    // Colocamos los datos del documento en la coleccion

    }else{ cerr << "ERROR!!!: No se ha podido abrir el archivo:\t" << nom << endl; }
    
    documento.close();

}

bool IndexadorHash::IndexarDirectorio(const string& dirAIndexar){
    struct stat dir;
    // Compruebo la existencia del directorio
    int err = stat(dirAIndexar.c_str(), &dir);
    if(err==-1 || !S_ISDIR(dir.st_mode))
        return false;
    else {
        // Hago una lista en un fichero con find>fich
        std::string cmd="find "+ dirAIndexar +" -follow |sort > .lista_fich";
        system(cmd.c_str());
        return Indexar(".lista_fich");
    }
}

bool IndexadorHash::GuardarIndexacion() const{

    // ----> Datos a Guardar <----
    // Fichero: datos_simples.txt
    //      string pregunta;
    //      string ficheroStopWords;
    //      string directorioIndice;
    //      int tipoStemmer;
    //      bool almacenarEnDisco;
    //      bool almacenarPosTerm;
    //      InfColeccionDocs informacionColeccionDocs;
    //          |--->numDocs
    //          |--->numTotalPal
    //          |--->numTotalPalSinParada
    //          |--->numTotalPalDiferentes
    //          |--->tamBytes
    //      InformacionPregunta infPregunta;
    //          |--->numTotalPal
    //          |--->numTotalPalSinParada
    //          |--->numTotalPalDiferentes
    //      Tokenizador tok;
    //          |--->CasosEspeciales
    //          |--->PasarAminusculas
    //          |--->Delimitadores
    //      unordered_set<string> stopWords;
    //          |--->...
    // Fichero: indice.txt
    //      unordered_map<string, InformacionTermino> indice;
    // Fichero: indiceDocs.txt
    //      unordered_map<string, InfDoc> indiceDocs;
    // Fichero: indicePregunta.txt
    //      unordered_map<string, InformacionTerminoPregunta> indicePregunta;
        
    ofstream archivo;
    string temp, nombre_fichero;
    stringstream aux;
    struct stat dir;
    int err;

    temp = "";
    nombre_fichero = "";
    err = stat(directorioIndice.c_str(), &dir);

    if(err==-1 || !S_ISDIR(dir.st_mode)){       // Comprobamos que exista el directorio y si no lo creamos 
		string cmd="mkdir "+directorioIndice; 
		system(cmd.c_str()); 
	}

    for (size_t i = 0; i < 4; ++i){
        switch (i){
            case 0: // datos_simples.txt
                nombre_fichero = directorioIndice + "/datos_simples.txt";
                aux << pregunta + "\n";
                aux << ficheroStopWords + "\n";
                aux << directorioIndice + "\n";
                aux << to_string(tipoStemmer) + "\n";
                aux << to_string(almacenarEnDisco) + "\n";
                aux << to_string(almacenarPosTerm) + "\n";
                aux << informacionColeccionDocs.Get_Datos();
                aux << infPregunta.Get_Datos();
                aux << to_string(tok.CasosEspeciales()) + "\n";
                aux << to_string(tok.PasarAminuscSinAcentos()) + "\n";
                aux << tok.DelimitadoresPalabra() + "\n";
                for(string word : stopWords){
                    aux << word + "\n";
                }
                break;
            case 1: //indice.txt
                nombre_fichero = directorioIndice + "/indice.txt";
                for(auto it = indice.begin(); it != indice.end(); ++it){
                    aux << it->first << "\t" << it->second << endl;
                }
                break;
            case 2: // indiceDocs.txt
                nombre_fichero = directorioIndice + "/indiceDocs.txt";
                for(auto it = indiceDocs.begin(); it != indiceDocs.end(); ++it){
                    aux << it->first << "\t" << it->second << endl;
                }
                break;
            case 3: // indicePregunta.txt
                nombre_fichero = directorioIndice + "/indicePregunta.txt";
                for(auto it = indicePregunta.begin(); it != indicePregunta.end(); ++it){
                    aux << it->first << "\t" << it->second << endl;
                }
                break;
        }

        archivo.open(nombre_fichero, std::ios::binary);
        if(archivo){ archivo << aux.str(); }
        else{ cerr << "ERROR!!!: No se ha podido crear el fichero " + nombre_fichero; }
        archivo.close();
        aux.str("");

    }
    
    return true;
}

bool IndexadorHash::RecuperarIndexacion (const string& directorioIndexacion){
    (*this) = IndexadorHash(directorioIndice);
    return true;
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

    list<string> tokens;    // Definimos los elementos que vamos a usar
    int pal, palParada;           
    pal = 0;                // Inicimos los elementos a usar
    palParada = 0;


    indicePregunta.clear();             // Vaciamos el contenido de indicePregunta
    infPregunta.~InformacionPregunta(); // Vaciamos el contenido de infPregunta
    pregunta = preg;                    // Guardamos la pregunta

    tok.Tokenizar(preg, tokens);        // Tokenizamos la pregunta 

    for(string const &token : tokens){                                                      // Recorremos los tokens de la pregunta
        if(stopWords.find(token) != stopWords.end()){                                       // Si el token es una palabra de parada
            ++palParada;
        }
        else{                                                                               // Si el token no es una palabra de parada 
            if(indicePregunta.find(token) == indicePregunta.end()){                         // Registramos el token si es nuevo 
                InformacionTerminoPregunta info;
                indicePregunta.insert({token,info});
            }
            indicePregunta.find(token)->second.ActualizarInfoTer(pal,almacenarPosTerm);     // Actualizamos los datos del termino
        }
        ++pal;
    }

    infPregunta.set_numTotalPal(pal);                                                       // Actualizamos los datos de infPregunta
    infPregunta.set_numTotalPalSinParada(pal - palParada); 
    infPregunta.set_numTotalPalDiferentes(indicePregunta.size());

    return true;
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
    if(!pregunta.empty()){
        inf = infPregunta;
        return true;
    }
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
    if(Existe(word) && indiceDocs.find(nomDoc) != indiceDocs.end()){
        long int idDoc = indiceDocs.find(nomDoc)->second.Get_IdDoc();   // Obtenemos el id del documendo;
        InfDoc = indice.find(word)->second.Devolver_Info(idDoc);        // Buscamos la Informacion del termino
        if(InfDoc.get_ft() > 0){ return true; }                         // Si aparece una vez o mas devolvemos true
    }
    return false;
}

bool IndexadorHash::Existe(const string& word) const{
    return (indice.find(word) != indice.end());
}

bool IndexadorHash::Borra(const string& word){
    return (indice.erase(word) != 0);
}

bool IndexadorHash::BorraDoc(const string& nomDoc){
    if(indiceDocs.find(nomDoc) != indiceDocs.end()){
        long int idDoc = indiceDocs.find(nomDoc)->second.Get_IdDoc();                       // Sacamos el id del documento
        InfDoc docInfo = indiceDocs.find(nomDoc)->second;                                   // Sacamos los datos del doumento 

        for(auto it = indice.begin(); it != indice.end(); ++it){                            // Recorremos cada uno de los terminos
            if(it->second.ApareceEnDoc(idDoc)){                                             // Si el termino aparece en el documento
                it->second.eliminarReferencia(idDoc);
            }
        }

        reset:                                                                              //Borramos los terminos que ya no son necesarios 
        for(auto it2 = indice.begin(); it2 != indice.end(); ++it2){
            if(it2->second.get_ftc() == 0){ Borra(it2->first); goto reset; }
        }

        informacionColeccionDocs.EliminarInfDoc(docInfo,indice.size());                                   // Eliminamos los datos del documento del registro
        return (indiceDocs.erase(nomDoc) != 0);                                             // Eliminamos el documento
    }
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
    
    if(indiceDocs.find(nomDoc) != indiceDocs.end()){
        long int idDoc = indiceDocs.find(nomDoc)->second.Get_IdDoc();
        for(auto it = indice.begin(); it != indice.end(); ++it){
            if(it->second.ApareceEnDoc(idDoc)){
                cout << it->first << "\t" << it->second << endl;        //??? preguntar si es asi o tengo que poner otra cosa como termino
            }
        }
        return true;
    }
    return false;
}

void IndexadorHash::ListarDocs() const{
    for(auto it = indiceDocs.begin(); it != indiceDocs.end(); ++it){
        cout << it->first << "\t" << it->second << endl;
    }
}

bool IndexadorHash::ListarDocs(const string& nomDoc) const{
    if(indiceDocs.find(nomDoc) != indiceDocs.end()){
        cout << indiceDocs.find(nomDoc)->first << "\t" << indiceDocs.find(nomDoc)->second << endl;
        return true;
    }
    return false;
}

IndexadorHash::IndexadorHash(){
    pregunta = "";
    ficheroStopWords = "";
    directorioIndice= "";
    tipoStemmer = 0;
    almacenarEnDisco = false;
    almacenarPosTerm = false;
}