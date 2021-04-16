#include "indexadorInformacion.h"

/************************************************************/
/*															*/
/*				            FECHA	    					*/
/*															*/
/************************************************************/

Fecha::Fecha(){
    seg = 0;
    min = 0;
    hora = 0;
    dia = 0;
    mes = 0;
    anyo = 0;
}

Fecha::Fecha(const Fecha& f){
    seg = f.seg;
    min = f.min;
    hora = f.hora;
    dia = f.dia;
    mes = f.mes;
    anyo = f.anyo;
}

Fecha::Fecha(int seg, int min, int hora, int dia, int mes, int anyo){
    this->seg = seg;
    this->min = min;
    this->hora = hora;
    this->dia = dia;
    this->mes = mes;
    this->anyo = anyo;
}

Fecha::~Fecha(){
    seg = 0;
    min = 0;
    hora = 0;
    dia = 0;
    mes = 0;
    anyo = 0;
}


/************************************************************/
/*															*/
/*				         INFTERMDOC	    					*/
/*															*/
/************************************************************/

ostream& operator<<(ostream& s, const InfTermDoc& p){
    s << "ft: " << p.ft;
    for(auto t : p.posTerm){
        s << "\t" << t;
    }
    return s;
}

InfTermDoc::InfTermDoc (const InfTermDoc &inf){
    if(this != &inf){
        ft = inf.ft;
        posTerm = inf.posTerm;
    }
}

InfTermDoc::InfTermDoc (){
    ft = 0;
} 

InfTermDoc::~InfTermDoc (){
    ft = 0;
    posTerm.clear();
}

InfTermDoc & InfTermDoc::operator= (const InfTermDoc &inf){
     if(this != &inf){
        ft = inf.ft;
        posTerm.clear();
        posTerm = inf.posTerm;
    }
    return (*this);
}

int InfTermDoc::get_ft()const { return ft; }


/************************************************************/
/*															*/
/*				    INFORMACIONTERMINO	 					*/
/*															*/
/************************************************************/

ostream& operator<<(ostream& s, const InformacionTermino& p){
    s << "Frecuencia total: " << p.ftc << "\tdf: " << p.l_docs.size();
    for(auto t = p.l_docs.begin(); t != p.l_docs.end(); ++t){
        s << "\tId.Doc: " << t->first<< "\t" << t->second;
    }
    return s;
}

InformacionTermino::InformacionTermino (const InformacionTermino &info){
    if(this != &info){
        ftc = info.ftc;
        l_docs = info.l_docs;
    }
}

InformacionTermino::InformacionTermino (){
    ftc = 0;
}

InformacionTermino::~InformacionTermino (){
    ftc = 0;
    l_docs.clear();
}

InformacionTermino & InformacionTermino::operator= (const InformacionTermino &info){
    if(this != &info){
        ftc = info.ftc;
        l_docs = info.l_docs;
    }
    return *this;
}

InfTermDoc InformacionTermino::Devolver_Info(const long int &idDoc)const{
    InfTermDoc resul;

    if(ApareceEnDoc(idDoc)){
        resul = l_docs.find(idDoc)->second;
    }
    return resul;
}

bool InformacionTermino::ApareceEnDoc(const long int & idDoc)const{ return !(l_docs.find(idDoc) == l_docs.end()); }

void InformacionTermino::set_ftc(const int &ftc){ this->ftc = ftc; }

int InformacionTermino::get_ftc(){ return ftc; }


/************************************************************/
/*															*/
/*				            INFDOC	 					    */
/*															*/
/************************************************************/

ostream& operator<<(ostream& s, const InfDoc& p){
    s   << "idDoc: " << p.idDoc << "\tnumPal: " << p.numPal 
        << "\tnumPalSinParada: " << p.numPalSinParada
        << "\tnumPalDiferentes: " << p.numPalDiferentes
        << "\ttamBytes: " << p.tamBytes;
    return s; 
}

InfDoc::InfDoc (const InfDoc &info){
    if(this != &info){
        idDoc = info.idDoc;
        numPal = info.numPal;
        fechaModificacion = info.fechaModificacion;
        tamBytes = info.tamBytes;
        numPalDiferentes = info.numPalDiferentes;
        numPalSinParada = info.numPalSinParada;
    }
}

InfDoc::InfDoc (){
    idDoc = 0;
    numPal = 0;
    fechaModificacion = Fecha();
    tamBytes = 0;
    numPalDiferentes = 0;
    numPalSinParada = 0;
}

InfDoc::~InfDoc (){
    idDoc = 0;
    numPal = 0;
    fechaModificacion = Fecha();
    tamBytes = 0;
    numPalDiferentes = 0;
    numPalSinParada = 0;
}

InfDoc & InfDoc::operator= (const InfDoc &info){
    if(this != &info){
        idDoc = info.idDoc;
        numPal = info.numPal;
        fechaModificacion = info.fechaModificacion;
        tamBytes = info.tamBytes;
        numPalDiferentes = info.numPalDiferentes;
        numPalSinParada = info.numPalSinParada;
    }
    return *this;
}

long int InfDoc::Get_IdDoc()const{
    return idDoc;
}

int InfDoc::Get_numPal()const{
    return numPal;
}

int InfDoc::Get_numPalSinParada()const{
    return numPalSinParada;
}

int InfDoc::Get_numPalDiferentes()const{
    return numPalDiferentes;
}

int InfDoc::Get_tamBytes()const{
    return tamBytes;
}



/************************************************************/
/*															*/
/*				       INFCOLECCIONDOCS	 					*/
/*															*/
/************************************************************/

ostream& operator<<(ostream& s, const InfColeccionDocs& p){
    s   << "numDocs: " << p.numDocs << "\tnumTotalPal: " << p.numTotalPal
        << "\tnumTotalPalSinParada: " << p.numTotalPalSinParada 
        << "\tnumTotalPalDiferentes: " << p.numTotalPalDiferentes
        << "\ttamBytes: " << p.tamBytes;
    return s;
}

InfColeccionDocs::InfColeccionDocs (const InfColeccionDocs &info){
    if(this != &info){
        numDocs = info.numDocs;
        numTotalPal = info.numTotalPal;
        numTotalPalSinParada = info.numTotalPalSinParada;
        numTotalPalDiferentes = info. numTotalPalDiferentes;
        tamBytes = info.tamBytes;
    }
}

InfColeccionDocs::InfColeccionDocs (){
    numDocs = 0;
    numTotalPal = 0;
    numTotalPalSinParada = 0;
    numTotalPalDiferentes = 0;
    tamBytes = 0;
}

InfColeccionDocs::~InfColeccionDocs (){
    numDocs = 0;
    numTotalPal = 0;
    numTotalPalSinParada = 0;
    numTotalPalDiferentes = 0;
    tamBytes = 0;
}

InfColeccionDocs & InfColeccionDocs::operator= (const InfColeccionDocs &info){
    if(this != &info){
        numDocs = info.numDocs;
        numTotalPal = info.numTotalPal;
        numTotalPalSinParada = info.numTotalPalSinParada;
        numTotalPalDiferentes = info. numTotalPalDiferentes;
        tamBytes = info.tamBytes;
    }
    return *this;
}

void InfColeccionDocs::EliminarInfDoc(const InfDoc &doc){
    --numDocs;
    numTotalPal           -= doc.Get_numPal();
    numTotalPalSinParada  -= doc.Get_numPalSinParada();
    numTotalPalDiferentes -= doc.Get_numPalDiferentes();
    tamBytes              -= doc.Get_tamBytes();
}


/************************************************************/
/*															*/
/*				  INFORMACIONTERMINOPREGUNTA	 			*/
/*															*/
/************************************************************/

ostream& operator<<(ostream& s, const InformacionTerminoPregunta& p){
    s << "ft: " << p.ft;
    for(auto t : p.posTerm){
        s << "\t" << t;
    }
    return s;
}

InformacionTerminoPregunta::InformacionTerminoPregunta (const InformacionTerminoPregunta& info){
    if(this != &info){
        ft = info.ft;
        posTerm = info.posTerm;
    }
}

InformacionTerminoPregunta::InformacionTerminoPregunta (){
    ft = 0;
}

InformacionTerminoPregunta::~InformacionTerminoPregunta (){
    ft = 0;
    posTerm.clear();
}

InformacionTerminoPregunta & InformacionTerminoPregunta::operator= (const InformacionTerminoPregunta& info){
    if(this != &info){
        ft = info.ft;
        posTerm = info.posTerm;
    }
    return *this;
}

void InformacionTerminoPregunta::ActualizarInfoTer(const int &pos, const bool &almacenar){  
    ++ft;
    if(almacenar){
        posTerm.push_back(pos);
    }
}

/************************************************************/
/*															*/
/*				  INFORMACIONTERMINOPREGUNTA	 			*/
/*															*/
/************************************************************/

ostream& operator<<(ostream& s, const InformacionPregunta& p){
    s   << "numTotalPal: " << p.numTotalPal << "\tnumTotalPalSinParada: "
        << p.numTotalPalSinParada << "\numTotlaPalDiferentes: " << p.numTotalPalDiferentes;
    return s;
}

InformacionPregunta::InformacionPregunta (const InformacionPregunta& info){
    if(this != &info){
        numTotalPal = info.numTotalPal;
        numTotalPalSinParada = info.numTotalPalSinParada;
        numTotalPalDiferentes = info.numTotalPalDiferentes;
    }
}

InformacionPregunta::InformacionPregunta (){
    numTotalPal = 0;
    numTotalPalSinParada = 0;
    numTotalPalDiferentes = 0;
}

InformacionPregunta::~InformacionPregunta (){
    numTotalPal = 0;
    numTotalPalSinParada = 0;
    numTotalPalDiferentes = 0;
}

InformacionPregunta & InformacionPregunta::operator= (const InformacionPregunta& info){
    if(this != &info){
        numTotalPal = info.numTotalPal;
        numTotalPalSinParada = info.numTotalPalSinParada;
        numTotalPalDiferentes = info.numTotalPalDiferentes;
    }
    return *this;
}


void InformacionPregunta::set_numTotalPal(const int &pal){
    numTotalPal = pal;
}

void InformacionPregunta::set_numTotalPalSinParada(const int &palSin){
    numTotalPalSinParada = palSin;
}

void InformacionPregunta::set_numTotalPalDiferentes(const int &palDif){
    numTotalPalDiferentes = palDif;
}
