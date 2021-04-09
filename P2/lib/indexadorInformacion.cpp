#include "indexadorInformacion.h"

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
}


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
}
