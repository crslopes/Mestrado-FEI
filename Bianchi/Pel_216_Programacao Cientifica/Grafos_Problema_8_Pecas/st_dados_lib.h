#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
// exceptions
#include <iostream>

using namespace std;

//-------------------------------------------------------------------
//      PEL_216 1º. Semestre de 2019
//      Prof: Dr Reinaldo Bianchi
//      Aluno: Cristiano Lopes Moreira
//      RA: 119103-0
//
//      Lib: Estrutura de Dados, Lista, Pilha e Fila
//
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//
//                  Exercicio Templates
//
//-------------------------------------------------------------------
// uso do template T para tipo da unidade de memoria a ser armazenada
// unitMem,basic memory unit for linked list object
template <class T>
class unitMem{
    public:
        unitMem();                      // Constructor
        ~unitMem(){};
        T Conteudo;                     // member variable - tipo definido pelo template T
        int status;                     // 0 aberto, 1 explorando, 2 explorado
        int custoAcumulado;                 // custo acomulado para alcançar este elemento
        int index;
        class unitMem *anterior;        // member variable
        class unitMem *posterior ;      // member variable
        class unitMem *elo ;            // member variable
};
// constructor of unitMem,initialize private variable and allocate memory to valor
template <typename T>
unitMem<T>::unitMem(){
    status=0;
    custoAcumulado=0;
    anterior=NULL;
    posterior=NULL;
    elo=NULL;
};


template <typename T>
class Lista{                                    // begin declaration of the class;
    public:                                     // begin public section
        Lista(int cap);                         // constructor
        ~Lista();                               // destructor
        T PegaValor();                        // accessor function
        int PegaCusto();                        // accessor function
        int PegaIndex();                        // accessor function
        unitMem<T> * PegaNoh();                        // accessor function
        unitMem<T> * PegaElo();                        // accessor function
        int searching( T valor);                // accessor function
        int PrintLista(int direction);          // accessor function
        void AdicionaListaInicio( T valor, class unitMem<T> * ancora);    // accessor function
        void AdicionaListaFim(  T valor, class unitMem<T> * ancora);       // accessor function
        void AdicionaOrdenado(  T valor, class unitMem<T> * ancora, int custo, int index);       // accessor function
        int RemoveValorLista( T  valor);        // accessor function
        int RemoveInicioLista();                // accessor function
        int RemoveFimLista();                   // accessor function
        int Estado();                           // accessor function
        int posterior();                        // accessor function
        int anterior();                         // accessor function
        void inicia();
        int total();
    protected:                                  // begin private section
        class unitMem<T> *memoria;              // member object
        class unitMem<T> *inicio ;              // member object
        class unitMem<T> *fim ;                 // member object
        class unitMem<T> *ponteiroBusca;        // member object
        class unitMem<T> *ponteiroRetorno;      // member object
        class unitMem<T> *node;
        int quantidade;                         // member variable
};

//-------------------------------------------------------------------
//
//                  Exercicio Construtor
//
//-------------------------------------------------------------------

// constructor of Lista,initialize private variable and allocate memory to valor
template <typename T>
Lista<T>::Lista(int cap){
    quantidade=0;
    inicio=NULL;
    fim=NULL;
    memoria=inicio;
};

//-------------------------------------------------------------------
//
//                  Exercicio Destrutor
//
//-------------------------------------------------------------------


// destructor of Lista, free memory
template <typename T>
Lista<T>::~Lista(){
    unitMem<T> *node;
    while (inicio!=NULL){
        node=inicio->posterior;
        free(inicio);
        inicio=node;
    }
}

template <typename T>
void Lista<T>::inicia(){
    memoria=inicio;
};

template <typename T>
int Lista<T>::total(){
    return quantidade;
};

// PegaValor, Public accessor function
// returns value of Conteudo in memoria
template <typename T>
unitMem<T> * Lista<T>::PegaNoh(){
    if ( quantidade > 0 ){
        return this->memoria;
    }
}


// PegaValor, Public accessor function
// returns value of Conteudo in memoria
template <typename T>
unitMem<T> * Lista<T>::PegaElo(){
    if ( quantidade > 0 ){
        return this->memoria->elo;
    }
}

// PegaValor, Public accessor function
// returns value of Conteudo in memoria
template <typename T>
T Lista<T>::PegaValor(){
    if ( quantidade > 0 ){
        return (memoria->Conteudo);
    }
}

template <typename T>
int Lista<T>::PegaIndex(){
    if ( quantidade > 0 ){
        return (memoria->index);
    }
}

template <typename T>
int Lista<T>::PegaCusto(){
    if ( quantidade > 0 ){
        return (memoria->custoAcumulado);
    }
}

// EncontrarValor, Public accessor function
// returns memory address and number of incidences of value in list
template <typename T>
int Lista<T>::searching( T valor){
    int next=1;
    int encontrados=0;
    T VerificaValor;
    if ( quantidade > 0 ){
        ponteiroBusca=inicio;
        while (next) {
            VerificaValor=ponteiroBusca->Conteudo;
            if (VerificaValor==valor){
                return 1;
            }
            if (ponteiroBusca->posterior==NULL){
                next=0;
            }else{
                ponteiroBusca=ponteiroBusca->posterior;
            }
        }
    }
    return 0;
}


// PrintLista, Public accessor function
// Print all values in list, direction 0 from begging to end, direction 1 from end to begging
template <typename T>
int Lista<T>::PrintLista(int direction){
    int next=1;
    T valor;
    if ( quantidade > 0 ){
        if (direction==1){
            memoria=inicio;
        } else{
            memoria=fim;
        }
        printf ( "\nExistem %d elementos da lista Lista:|",quantidade);
        while (next) {
            valor=PegaValor();
            printf ( "%d|", valor);
            if (direction ==1){
                next=posterior();
            }else{
                next=anterior();
            }
        }
        printf ( "\n");
    }else{
        printf ("\nA lista esta vazia");
    }

}

// AdicionaListaInicio, public accessor function
// Add new value in begging of List
template <typename T>
void Lista<T>::AdicionaListaInicio(T valor, class unitMem<T> * ancora){
    unitMem<T> *node=new unitMem<T> ;
//    node = (unitMem<T>*) malloc (sizeof(unitMem<T>));
    node->anterior=NULL;
    node->posterior=inicio;
    node->Conteudo=valor;
    node->elo=ancora;
    node->status=0;
    if (quantidade>0){
        inicio->anterior=node;
    }else{
        fim=node;
    }
    inicio=node;
    memoria=inicio;
    quantidade++;
    return;
}

// AdicionaListaFim, public accessor function
// Add new value in end of List
template <typename T>
void Lista<T>::AdicionaListaFim( T valor, class unitMem<T> * ancora){
    unitMem<T> *node=new unitMem<T> ;
    //node = (unitMem<T>*) malloc (sizeof(unitMem<T>));
    node->anterior=fim;
    node->posterior=NULL;
    node->Conteudo=valor;
    node->elo=ancora;
    node->status=0;
    if (quantidade>0){
        fim->posterior=node;
    }else{
        inicio=node;
    }
    fim=node;
    memoria=fim;
    quantidade++;
    return;
}


// AdicionaOrdenado, public accessor function
// Add new value na lista em ordem crescente
template <typename T>
void Lista<T>::AdicionaOrdenado(  T valor, class unitMem<T> * ancora, int custo, int index){
    int i, j;
    i=0;
    T chave;
    unitMem<T> *node=new unitMem<T> ;
    unitMem<T> *ponteiroRetorno=new unitMem<T> ;
    //node = (unitMem<T>*) malloc (sizeof(unitMem<T>));
    ponteiroRetorno=this->PegaNoh();
    node->Conteudo=valor;
    node->elo=ancora;
    node->custoAcumulado=custo;
    node->index=index;
    node->status=0;
    if (quantidade>0){
        quantidade++;
        ///memoria=ancora;
        memoria=inicio;
        chave=memoria->index;
        if (chave >=index){
            while(chave >=index&&anterior()){chave=memoria->index;}
            node->posterior=memoria;
            if (memoria->anterior==NULL){
                node->anterior=NULL;
                inicio=node;
            }else{
                memoria->anterior->posterior=node;
                node->anterior=memoria->anterior;
            }
            node->posterior=memoria;
            memoria->anterior=node;
            if(index <= ponteiroRetorno->index){ponteiroRetorno=node;}
            return;
        }
        while(chave <=index&&posterior()){
            chave=memoria->index;
        }
        if (memoria->posterior==NULL){
            node->posterior=NULL;
            fim=node;
        }else{
            node->posterior=memoria->posterior;
            memoria->posterior->anterior=node;
        }
        node->anterior=memoria;
        memoria->posterior=node;
        if(index <= ponteiroRetorno->index){
            ponteiroRetorno=node;
        }
        return;
    }else{
        node->anterior=NULL;
        node->posterior=inicio;
        inicio=node;
        fim=node;
    }
    memoria=inicio;
    quantidade++;
    return;
}




// RemoveIniciolista, public accessor function
// Delete value in begging of list, return 1 if value deleted and 0 if there is no value to delete
template <typename T>
int Lista<T>::RemoveInicioLista(){
    unitMem<T> *nodeVerificar;
    unitMem<T> *nodeTmpPosterior;
    if (quantidade>0){
        nodeVerificar=inicio;
        if(nodeVerificar->posterior==NULL){
            inicio=NULL;
            fim=NULL;
        }else{
            nodeTmpPosterior=nodeVerificar->posterior;
            inicio=nodeTmpPosterior;
            nodeTmpPosterior->anterior=NULL;
        }
        delete nodeVerificar;
        quantidade--;
        return 1;
    }else{
        return 0;
    }
}

// RemoveFimlista, public accessor function
// Delete value in end of list, return 1 if value deleted and 0 if there is no value to delete
template <typename T>
int Lista<T>::RemoveFimLista(){
    unitMem<T> *nodeVerificar;
    unitMem<T> *nodeTmpAnterior;
    if (quantidade>0){
        nodeVerificar=fim;
        if(nodeVerificar->anterior==NULL){
            inicio=NULL;
            fim=NULL;
        }else{
            nodeTmpAnterior=nodeVerificar->anterior;
            fim=nodeTmpAnterior;
            nodeTmpAnterior->posterior=NULL;
        }
        delete nodeVerificar;
        quantidade--;
        return 1;
    }else{
        return 0;
    }
}

// RemoveValorLista, public accessor function
// Delete value in list and return number of incidences of deleted values
template <typename T>
int Lista<T>::RemoveValorLista( T valor){
    int removidos=0;
    unitMem<T> *nodeVerificar;
    unitMem<T> *nodeTmpAnterior;
    unitMem<T> *nodeTmpPosterior;
    nodeVerificar=inicio;
    nodeTmpPosterior=nodeVerificar->posterior;
    while (1){

        if (nodeVerificar->Conteudo==valor){
                if (nodeVerificar->anterior==NULL){
                    if(nodeVerificar->posterior==NULL){
                            inicio=NULL;
                            fim=NULL;
                    }else{
                        inicio=nodeVerificar->posterior;
                    }
                }else if (nodeVerificar->posterior==NULL){
                        nodeVerificar->anterior->posterior=NULL;
                        fim=nodeVerificar->anterior;
                }else{
                    nodeVerificar->anterior->posterior=nodeVerificar->posterior;
                    nodeVerificar->posterior->anterior=nodeVerificar->anterior;
                }
                delete nodeVerificar;
                quantidade--;
                removidos++;
        }
        if(nodeTmpPosterior == NULL){break;}
        nodeVerificar=nodeTmpPosterior;
        nodeTmpPosterior=nodeVerificar->posterior;
    }
    printf("\n quantidade restante %d", quantidade);
//    memoria=inicio;
//    this->PrintLista();
    return removidos;

}

// Estado, public accessor function
// Check lista Status, empty (0), regular (1)
template <typename T>
int Lista<T>::Estado(){
    if (quantidade==0) {
        return 0; // lista vazia
    }
    return 1; // lista normal
}

// posterior, public accessor function
// move pointer to next element of list, return 0 if there is no next element and 1 if works property
template <typename T>
int Lista<T>::posterior(){
    if (memoria->posterior==NULL){
//            printf("\n NAO");
            return 0;
    }else{
        memoria=memoria->posterior;
//        printf("\n SIM");
        return 1;
    }
}

// posterior, public accessor function
// move pointer to previous element of list return, 0 if there is no next element and 1 if works property
template <typename T>
int Lista<T>::anterior(){
    if (memoria->anterior==NULL){
            return 0;
    }else{
        memoria=memoria->anterior;
        return 1;
    }
}

//-------------------------------------------------------------------
//
//                  Exercicio Herança/Hieraquia de Classes
//
//-------------------------------------------------------------------
// herança objeto Lista, reutiliza funções
template <typename T>
class Pilha : public Lista<T>{              // begin declaration of the class;
    public:                                 // begin public section
        Pilha(int direct);                  // constructor
        ~Pilha();                           // destructor
        T PegaTopo();                      // accessor function
        void AdicionaPilha(  T valor, class unitMem<T> * ancora);  // accessor function
        int RemovePilha();                  // accessor function
        void PrintPilha();                  // accessor function
        void SetStatus(int status);                  // accessor function
        int GetStatus();                  // accessor function
    private:                                // begin private section
        int direction;                      // member variable
};
// Construtor  - Inicializa a Pilha
template <typename T>
Pilha<T>::Pilha(int direct):
    Lista<T>::Lista(1)
{
    direction=direct;
};
// Destrutor  - Finaliza a Pilha
template <typename T>
Pilha<T>::~Pilha(){
    Lista<T>::~Lista();
};

// PegaTopo, Public accessor function
// returns value of top of stack
template <typename T>
T Pilha<T>::PegaTopo(){
    this->memoria=this->inicio;
    if ( this->quantidade > 0 ){
        try{
            return this->PegaValor();
        }
        catch (int param) { cout << "int exception"; }
        catch (char param) { cout << "char exception"; }
    }
};

// AdicionaPilha, public accessor function
// Add new value in top of stack
template <typename T>
void Pilha<T>::AdicionaPilha( T valor, class unitMem<T> * ancora){
    try{
        this->AdicionaListaInicio(valor, ancora);
    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }
};

// RemovePilha, public accessor function
// Delete value in top of stack
template <typename T>
int Pilha<T>::RemovePilha(){
    try{
        return this->RemoveInicioLista();
    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }
};

// PrintPilha, public accessor function
// Print all items in stack
template <typename T>
void Pilha<T>::PrintPilha(){
    try{
        this->PrintLista(direction);
    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }
};

// SetStatus, public accessor function
// Set status items in stack
template <typename T>
void Pilha<T>::SetStatus(int status){
    try{
        this->memoria->status=status;
    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }
};

// GetStatus, public accessor function
// Get status items in stack
template <typename T>
int Pilha<T>::GetStatus(){
    try{
        if(this->quantidade>0){
            return this->memoria->status;
        }else{
            return 0;
        }

    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }
};

//-------------------------------------------------------------------
//
//                  Exercicio Herança/Hieraquia de Classes
//
//-------------------------------------------------------------------
// herança objeto Lista, reutiliza funções
template <typename T>
class Fila : public Lista<T>{             // begin declaration of the class;
    public:                            // begin public section
        Fila(int direct);              // constructor
        ~Fila();                       // destructor
        T PegaSaida();               // accessor function
        void AdicionaFila(T valor, class unitMem<T> * ancora);  // accessor function
        int RemoveFila();              // accessor function
        void PrintFila();              // accessor function
    private:                           // begin private section
        int direction;                 // member variable
};
// Construtor  - Inicializa a Pilha
template <typename T>
Fila<T>::Fila(int direct):
    Lista<T>::Lista (1)
{
    direction=direct;
};
// Destrutor  - Finaliza a Fila
template <typename T>
Fila<T>::~Fila(){
    Lista<T>::~Lista();
    printf("\nOLLHA FILA");
};

// PegaSaida, Public accessor function
// returns value of top of queue
template <typename T>
T Fila<T>::PegaSaida(){
    if ( this->quantidade > 0 ){
        this->memoria=this->inicio;
        try{
            return this->PegaValor();
        }
        catch (int param) { cout << "int exception"; }
        catch (char param) { cout << "char exception"; }
    }
    //return ;
};

// AdicionaFila, public accessor function
// Add new value in queue
template <typename T>
void Fila<T>::AdicionaFila(T valor, class unitMem<T> * ancora){
    try{
        this->AdicionaListaFim(valor, ancora);
    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }
};

// RemoveFila, public accessor function
// Delete value in queue
template <typename T>
int Fila<T>::RemoveFila(){
    try{
        return this->RemoveInicioLista();
    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }
};

// PrintFila, public accessor function
// Print all items in queue
template <typename T>
void Fila<T>::PrintFila(){
    try{
        this->PrintLista(direction);
    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }
};

