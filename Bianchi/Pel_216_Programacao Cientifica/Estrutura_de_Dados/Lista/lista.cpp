#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
// exceptions
#include <iostream>
using namespace std;

// unitMem,basic memory unit for linked list object
class unitMem{
    public:
        unitMem();
        int Conteudo;                  // member variable
        class unitMem *anterior;                   // member variable
        class unitMem *posterior ;                   // member variable
};
// constructor of unitMem,initialize private variable and allocate memory to valor
unitMem::unitMem(){
    anterior=NULL;
    posterior=NULL;
};

class Lista{                                    // begin declaration of the class;
    public:                                     // begin public section
        Lista(int cap);                         // constructor
        ~Lista();                               // destructor
        int PegaValor();                        // accessor function
        int EncontraValor(int valor);           // accessor function
        int PrintLista(int direction);          // accessor function
        void AdicionaListaInicio(int valor);    // accessor function
        void AdicionaListaFim(int valor);       // accessor function
        int RemoveValorLista(int valor);        // accessor function
        int RemoveInicioLista();                // accessor function
        int RemoveFimLista();                   // accessor function
        int Estado();                           // accessor function
        int posterior();                        // accessor function
        int anterior();                         // accessor function
    protected:                                    // begin private section
        class unitMem *memoria;                 // member object
        class unitMem *inicio ;                 // member object
        class unitMem *fim ;                    // member object
        int quantidade;                         // member variable

};

// constructor of Lista,initialize private variable and allocate memory to valor
Lista::Lista(int cap){
    quantidade=0;
    inicio=NULL;
    fim=NULL;
    memoria=inicio;
};

// destructor of Lista, free memory
Lista::~Lista(){
    unitMem *node;
    while (inicio!=NULL){
        node=inicio->posterior;
        free(inicio);
        inicio=node;
    }
}

// PegaValor, Public accessor function
// returns value of Conteudo in memoria
int Lista::PegaValor(){
    if ( quantidade > 0 ){
        return (memoria->Conteudo);
    }
}

// EncontrarValor, Public accessor function
// returns memory address and number of incidences of value in list
int Lista::EncontraValor(int valor){
    int next=1;
    int encontrados=0;
    int VerificaValor;
    if ( quantidade > 0 ){
        memoria=inicio;
        while (next) {
            VerificaValor=memoria->Conteudo;
            if (VerificaValor==valor){
                encontrados++;
                if (encontrados==1){
                    printf ( "\nValor encontrado na Lista nos enderecos:|");
                }
                printf ( "%d|", &memoria->Conteudo);
            }
            next=posterior();
        }
        if (encontrados>0){
            printf ( "| no total de %d valores encontrados\n", encontrados);
        }else{
            printf ( "\nO valor %d nao se encontra na lista\n", valor);
        }
    }else{
        printf ("\nA lista esta vazia");
    }
    getch();

}

// PrintLista, Public accessor function
// Print all values in list, direction 0 from begging to end, direction 1 from end to begging
int Lista::PrintLista(int direction){
    int next=1;
    int valor;
    if ( quantidade > 0 ){
        if (direction==1){
            memoria=inicio;
        } else{
            memoria=fim;
        }
//        memoria=inicio;
        printf ( "\nExistem %d elementos da lista Lista:|",quantidade);
        while (next) {
            valor=PegaValor();
            printf ( "%d|", valor);
            if (direction ==1){
                next=posterior();
            }else{
                next=anterior();
            }
//            next=posterior();
        }
        printf ( "\n");
    }else{
        printf ("\nA lista esta vazia");
    }

}

// AdicionaListaInicio, public accessor function
// Add new value in begging of List
void Lista::AdicionaListaInicio(int valor){
    unitMem *node=new unitMem ;
    node->anterior=NULL;
    node->posterior=inicio;
    node->Conteudo=valor;
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
void Lista::AdicionaListaFim(int valor){
    unitMem *node=new unitMem ;
    node->anterior=fim;
    node->posterior=NULL;
    node->Conteudo=valor;
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

// RemoveIniciolista, public accessor function
// Delete value in begging of list, return 1 if value deleted and 0 if there is no value to delete
int Lista::RemoveInicioLista(){
    unitMem *nodeVerificar;
    unitMem *nodeTmpPosterior;
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
int Lista::RemoveFimLista(){
    unitMem *nodeVerificar;
    unitMem *nodeTmpAnterior;
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
int Lista::RemoveValorLista(int valor){
    int removidos=0;
    unitMem *nodeVerificar;
    unitMem *nodeTmpAnterior;
    unitMem *nodeTmpPosterior;
    nodeVerificar=inicio;
    while (1){
        nodeTmpPosterior=nodeVerificar->posterior;
        if (nodeVerificar->Conteudo==valor){
                if (nodeVerificar->anterior==NULL){
                    if(nodeVerificar->posterior==NULL){
                            inicio=NULL;
                            fim=NULL;
                    }else{
                        inicio=nodeTmpPosterior;
                        if (nodeTmpPosterior != NULL){
                            nodeTmpPosterior->anterior=NULL;
                        }
                    }
                }else if (nodeVerificar->posterior==NULL){
                    if(nodeVerificar->anterior==NULL){
                            inicio=NULL;
                            fim=NULL;
                    }else{
                        nodeTmpAnterior=nodeVerificar->anterior;
                        fim=nodeTmpAnterior;
                        if (nodeTmpAnterior != NULL){
                            nodeTmpAnterior->posterior=NULL;
                        }
                    }
                }else{
                    nodeTmpAnterior=nodeVerificar->anterior;
                    nodeTmpAnterior->posterior=nodeTmpPosterior;
                    if (nodeTmpPosterior != NULL){
                        nodeTmpPosterior->anterior=nodeTmpAnterior;
                    }
                }
                delete nodeVerificar;
                quantidade--;
                removidos++;
        }
        if(nodeTmpPosterior == NULL){break;}
        nodeVerificar=nodeTmpPosterior;
    }
    return removidos;

}

// Estado, public accessor function
// Check lista Status, empty (0), regular (1)
int Lista::Estado(){
    if (quantidade==0) {
        return 0; // lista vazia
    }
    return 1; // lista normal
}

// posterior, public accessor function
// move pointer to next element of list, return 0 if there is no next element and 1 if works property
int Lista::posterior(){
    if (memoria->posterior==NULL){
            return 0;
    }else{
        memoria=memoria->posterior;
        return 1;
    }
}

// posterior, public accessor function
// move pointer to previous element of list return, 0 if there is no next element and 1 if works property
int Lista::anterior(){
    if (memoria->anterior==NULL){
            return 0;
    }else{
        memoria=memoria->anterior;
        return 1;
    }
}


// herança objeto Lista, reutiliza funções
class Pilha : public Lista{             // begin declaration of the class;
    public:                             // begin public section
        Pilha(int direct);              // constructor
        ~Pilha();                       // destructor
        int PegaTopo();                 // accessor function
        void AdicionaPilha(int valor);  // accessor function
        int RemovePilha();              // accessor function
        void PrintPilha();              // accessor function
    private:                            // begin private section
        int direction;                  // member variable
};
Pilha::Pilha(int direct):
    Lista (1)
{
    direction=direct;
};

Pilha::~Pilha(){
    printf("destruct Pilha");
    //direction=direct;
};

// PegaTopo, Public accessor function
// returns value of top of stack
int Pilha::PegaTopo(){
    memoria=inicio;
    if ( quantidade > 0 ){
        return PegaValor();
    }
};

// AdicionaPilha, public accessor function
// Add new value in top of stack
void Pilha::AdicionaPilha(int valor){
        AdicionaListaInicio(valor);
};

// RemovePilha, public accessor function
// Delete value in top of stack
int Pilha::RemovePilha(){
    return RemoveInicioLista();
};

// PrintPilha, public accessor function
// Print all items in stack
void Pilha::PrintPilha(){
    PrintLista(direction);
};


// herança objeto Lista, reutiliza funções
class Fila : public Lista{             // begin declaration of the class;
    public:                            // begin public section
        Fila(int direct);              // constructor
        ~Fila();                       // destructor
        int PegaSaida();               // accessor function
        void AdicionaFila(int valor);  // accessor function
        int RemoveFila();              // accessor function
        void PrintFila();              // accessor function
    private:                           // begin private section
        int direction;                 // member variable
};
Fila::Fila(int direct):
    Lista (1)
{
    direction=direct;
};

Fila::~Fila(){
    printf("destruct Fila");
    //direction=direct;
};

// PegaSaida, Public accessor function
// returns value of top of queue
int Fila::PegaSaida(){
    memoria=inicio;
    if ( quantidade > 0 ){
        return PegaValor();
    }
};

// AdicionaFila, public accessor function
// Add new value in queue
void Fila::AdicionaFila(int valor){
        AdicionaListaFim(valor);
};

// RemoveFila, public accessor function
// Delete value in queue
int Fila::RemoveFila(){
    return RemoveInicioLista();
};

// PrintFila, public accessor function
// Print all items in queue
void Fila::PrintFila(){
    PrintLista(direction);
};


int main(){
	int quantidade, valor, opcao, saida, menu, opcaoMenu;           // variáveis de apoio
	const char *tipo[3];
    tipo[0] = "N/D";
    tipo[1] = "Pilha";
    tipo[2] = "Fila";
	clock_t t;
//time.h para utilizar na medida de tempo do acesso a estrutura de dados
	double time_taken;
	printf( "\nInicializa Lista" );
	Lista listaAula(1);                  // inicializa a lista com número inicial de registros igual a quantidade solicitada


	while( 1 ){ /* loop infinito para gerar menu de opçoes do uso da lista*/
		printf("\n0: Sair");
		printf("\n1: Adicionar um numero no inicio da Lista\n");
		printf("2: Adicionar um numero no final da Lista\n");
		printf("3: Remover um numero da Lista\n");
		printf("4: Remover um valor do inicio da Lista\n");
		printf("5: Remover um valor do final da Lista\n");
		printf("6- Imprime toda Lista\n");
        printf("7- Encontrar valor\n");
		printf("8- Inicializa Pilha ou Fila\n");
		printf("\ndigite uma opcao? ");
		scanf("%d", &opcao);
		switch (opcao){
            case 0: // desconstruir a lista e sair
                listaAula.~Lista();
                exit(0);
			case 1: // Add to begging of list
			    try {
                    printf("\nQual valor deve adicionar na Lista? ");
                    scanf("%d", &valor);
                    listaAula.AdicionaListaInicio(valor);
			    }
			    catch (int param) { cout << "int exception"; }
                catch (char param) { cout << "char exception"; }
				break;
			case 2: // Add to end of list
				try {
                    printf("\nQual valor deve adicionar na Lista? ");
                    scanf("%d", &valor);
                    listaAula.AdicionaListaFim(valor);
			    }
			    catch (int param) { cout << "int exception"; }
                catch (char param) { cout << "char exception"; }
				break;
			case 3: //remove value from list
				try {
                    printf("\nQual valor deve remover na Lista? ");
                    scanf("%d", &valor);

                    if (listaAula.Estado()>0){
                        quantidade=listaAula.RemoveValorLista(valor);
                        printf ( "\nRemovido %d items da Lista com o valor: %d\n", quantidade, valor);
                    } else {
                        printf ( "\nNao existem itens para remover no Obj Lista");
                    }
			    }
			    catch (int param) { cout << "int exception"; }
                catch (char param) { cout << "char exception"; }
				break;
			case 4: // delete from begging of list
				try {
                    quantidade=listaAula.RemoveInicioLista();
                    printf ( "\nRemovido %d item da Lista\n", quantidade);

			    }
			    catch (int param) { cout << "int exception"; }
                catch (char param) { cout << "char exception"; }
				break;
			case 5: // delete from end of list
				try {
                    quantidade=listaAula.RemoveFimLista();
                    printf ( "\nRemovido %d item da Lista\n", quantidade);
			    }
			    catch (int param) { cout << "int exception"; }
                catch (char param) { cout << "char exception"; }
				break;
			case 6: // mostrar a lista
				try {
                    printf("\nDigite 1 para Pilha ou 2 para Fila? ");
                    scanf("%d", &valor);
                    listaAula.PrintLista(valor);
			    }
			    catch (int param) { cout << "int exception"; }
                catch (char param) { cout << "char exception"; }
                printf("\nDigite [enter] para continuar \n");
                getch();
				break;
			case 7: // testes para validação do tempo consumido pela interação com a estrutura de dados
				try {
                    printf("\nQual valor deseja encontrar na Lista? ");
                    scanf("%d", &valor);
                    listaAula.EncontraValor(valor);
			    }
			    catch (int param) { cout << "int exception"; }
                catch (char param) { cout << "char exception"; }
				break;
            case 8: // Inicializa Pilha ou Fila
                printf("\nDigite 1 para Pilha ou 2 para Fila? ");
                scanf("%d", &menu);
                Pilha Pil(1);
                Fila  Fil(1);
                while( menu>0 ){ /* loop infinito para gerar menu de opçoes do uso da pilha*/
                    printf("\n1: Adicionar um numero a %s\n", tipo[menu]);
                    printf("2: Remover um numero da %s\n", tipo[menu]);
                    printf("3- Mostrar o valor a ser retirado da %s \n", tipo[menu]);
                    printf("4- Imprime toda %s\n", tipo[menu]);
                    printf("5- Verificar tempos de execucao da %s\n", tipo[menu]);
                    printf("6- sair\n");
                    printf("\ndigite uma opcao? ");
                    scanf("%d", &opcaoMenu);
                    opcaoMenu=opcaoMenu+((menu-1)*10);

                    switch (opcaoMenu){
                        case 1: // Add to Stack
                            try {
                                printf("\nQual valor deve adicionar a Pilha? ");
                                scanf("%d", &valor);
                                Pil.AdicionaPilha(valor);
                            }
                            catch (int param) { cout << "int exception"; }
                            catch (char param) { cout << "char exception"; }
                            break;
                        case 2: //remove from stack
                            try {
                                if (Pil.Estado()){
                                    quantidade=Pil.RemovePilha();
                                    printf ( "\nRemovido %d valores  da Pilha \n", quantidade);
                                } else {
                                    printf ( "\nNao existem itens para remover no Obj Pilha");
                                }
                            }
                            catch (int param) { cout << "int exception"; }
                            catch (char param) { cout << "char exception"; }
                            break;
                        case 3: // mostrar o topo
                            try {
                                if (Pil.Estado()>0){
                                    saida=Pil.PegaTopo();
                                    printf( "\nTopo do Objeto Pilha: %d\n", saida);
                                }else{
                                    printf( "\nNao existem valores na pilha\n" );
                                }
                                printf("\nDigite [enter] para continuar \n");
                                getch();
                            }
                            catch (int param) { cout << "int exception"; }
                            catch (char param) { cout << "char exception"; }
                            break;
                        case 4: // obtem e mostra todos os itens da pilha
                            try {
                                if(Pil.Estado()>0){
                                    Pil.PrintPilha();
                                }else{
                                     printf ("\nA pilha esta vazia");
                                }
                            }
                            catch (int param) { cout << "int exception"; }
                            catch (char param) { cout << "char exception"; }
                            break;

                        case 5: // testes para validação do tempo consumido pela interação com a estrutura de dados
                            printf("\n\nDigite quantos elementos deseja testar: ");
                            scanf("%d", &valor);
                            quantidade = valor;

                            for ( int j=0; j!= 51; j++){
                                Pil.~Pilha();
                                t = clock();
                                for( int i = 0; i != (quantidade*j); ++i ){
                                    Pil.AdicionaPilha(i);
                                }
                                for( int i = 0; i != (quantidade*j); ++i ){
                                    Pil.RemovePilha();
                                }
                                t = clock() -t;
                                time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                                printf("|%d|%f|seconds to execute \n", (quantidade*j), time_taken);
                            }
                            break;

                            case 6: // desconstruir a pilha e sair
                                Pil.~Pilha();
                                menu=0;
                                break;


                            case 11: // Add to Queue
                                try {
                                    printf("\nQual valor deve adicionar a Fila? ");
                                    scanf("%d", &valor);
                                    Fil.AdicionaFila(valor);
                                }
                                catch (int param) { cout << "int exception"; }
                                catch (char param) { cout << "char exception"; }
                                break;
                            case 12: //remove from queue
                                try {
                                    if (Fil.Estado()){
                                        quantidade=Fil.RemoveFila();
                                        printf ( "\nRemovido %d valores  da Fila \n", quantidade);
                                    } else {
                                        printf ( "\nNao existem itens para remover no Obj Fila");
                                    }
                                }
                                catch (int param) { cout << "int exception"; }
                                catch (char param) { cout << "char exception"; }
                                break;
                            case 13: // mostrar o Saida
                                try {
                                    if (Fil.Estado()>0){
                                        saida=Fil.PegaSaida();
                                        printf( "\nPrimeiro Objeto da Fila: %d\n", saida);
                                    }else{
                                        printf( "\nNao existem valores na Fila\n" );
                                    }
                                    printf("\nDigite [enter] para continuar \n");
                                    getch();
                                }
                                catch (int param) { cout << "int exception"; }
                                catch (char param) { cout << "char exception"; }
                                break;
                            case 14: // obtem e mostra todos os itens da Fila
                                try {
                                    if(Fil.Estado()>0){
                                        Fil.PrintFila();
                                    }else{
                                         printf ("\nA Fila esta vazia");
                                    }
                                }
                                catch (int param) { cout << "int exception"; }
                                catch (char param) { cout << "char exception"; }
                                break;

                            case 15: // testes para validação do tempo consumido pela interação com a estrutura de dados
                                printf("\n\nDigite quantos elementos deseja testar: ");
                                scanf("%d", &valor);
                                quantidade = valor;

                                for ( int j=0; j!= 51; j++){
                                    Fil.~Fila();
                                    Fila Fil((quantidade*j));
                                    t = clock();
                                    for( int i = 0; i != (quantidade*j); ++i ){
                                        Fil.AdicionaFila(i);
                                    }
                                    for( int i = 0; i != (quantidade*j); ++i ){
                                        Fil.RemoveFila();
                                    }
                                    t = clock() -t;
                                    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                                    printf("|%d|%f|seconds to execute \n", (quantidade*j), time_taken);
                                }
                                break;


                                case 16: // desconstruir a Fila e sair
                                    Fil.~Fila();
                                    menu=0;
                                    break;
                        default: printf( "\nDigite uma opçao! \n" );
                    }
                }
                break;

		}
	}
}
