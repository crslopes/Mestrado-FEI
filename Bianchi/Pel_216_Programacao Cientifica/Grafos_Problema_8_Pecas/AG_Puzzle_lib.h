#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
// exceptions
#include <iostream>
#include "st_dados_lib.h"

using namespace std;

//-------------------------------------------------------------------
//      PEL_216 1º. Semestre de 2019
//      Prof: Dr Reinaldo Bianchi
//      Aluno: Cristiano Lopes Moreira
//      RA: 119103-0
//
//      Lib: Agentes para Busca em Largura e Busca em Profundidade
//
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//      Exercício Agente BFS, DFS, HC e A* para Problema das 8 Peças
//     Tratativas de exceções dentro das rotidas com Try - catch
//          Hierarquia de Classes, Templates e Polimorfismo
//-------------------------------------------------------------------


//Objeto agente, metodos e variabeis base dos agentes de busca
class AGENTE{                                      // begin declaration of the class;
    public:                                                         // begin public section
        AGENTE(int inicia);                                         // constructor
        ~AGENTE();                                                  // destructor
//----------------------------- Actions--------------------------------------
//        int acao[4] = {0,1,2,3};// direita, esquerda, desce, sobe
//-------------------------Transition model----------------------------------
        int P(int valor, int a);                                    // accessor function
//---------------Função verifica se objetivo foi alcançado-------------------
        int GoalTest(int valor, int terminal);                      // accessor function
        virtual void expanding_node (int InicialState){printf("\nNada a Expandir");};
        void PrintPath();              // accessor function
        class unitMem<int> *resultado;
    protected:                                                      // begin private section
        int terminal;                                               // member variable
        int quantidade;                                             // member variable
        int custoPasso;

};
//Agent constructor
//Inicializa o agente DFS com o estado inicial do problema e ativa as acoes
AGENTE::AGENTE(int inicia){
    custoPasso=1;                                                        //custo do passo de busca
    terminal = 123456789;                                           //Resultado desejado
    quantidade=0;
};

// destructor of Lista, free memory
AGENTE::~AGENTE(){
    printf("\nFinalizando Agente\n");
}

//verifica se o objetivo foi alcançado

int AGENTE::GoalTest(int valor, int terminal){
    if (valor==terminal){return 1;}else{return 0;}
};


// imprime o caminho para alcançar o resultado desejado

void AGENTE::PrintPath(){
    int next=1;                                                         //variavel de controle de novo vertice
    int passos=0;                                                       //variavel de passos para o resultado final
    Pilha<int> PrintPassos(1);                                            //inicializa pilha para resultados de passos ao resultado
    printf ( "\n| %d Elementos explorados\n", this->quantidade);
    printf ( "\n Os Passos sao: ");
    if ( this->quantidade > 0 ){                                        // verifica quantidade de vertices
        while (next) {
            try{
                PrintPassos.AdicionaPilha(this->resultado->Conteudo, NULL);
            }
            catch (int param) { cout << "int exception"; }
            catch (char param) { cout << "char exception"; }
            passos++;
            if (this->resultado->elo!=NULL){
                this->resultado=this->resultado->elo;
            }else{
                next=0;
            }
        }
        printf ( "| %d passos para alcancar o objetivo, os passos sao:\n", passos);
        printf ( "\n<ENTER> para continuar\n");
        getch();
        PrintPassos.PrintPilha();
    }else{
        printf ("\nGame Over");
    }

};

//Transition model state function - funcao de transicao de estados do agente puzzle 8
int AGENTE::P(int valor, int acao){
    char str[10];
    char tmpDig;
    int dimensao=3;
    int posicao, posicao2;
    sprintf(str,"%d",valor);
    for (posicao=0;posicao<=8;posicao++){
        if(str[posicao]=='9'){
            break;
        }
    }
    switch (acao){
        case 0: // move vazio (9) para direita
            posicao2=posicao+1;
            if (posicao2%dimensao!=0){
                tmpDig=str[posicao];
                str[posicao]=str[posicao2];
                str[posicao2]=tmpDig;
            }else{ sprintf(str,"%d",0);}
            break;
        case 1: // move vazio (9) para esquerda
            posicao2=posicao-1;
            if ((posicao)%dimensao!=0){
                tmpDig=str[posicao];
                str[posicao]=str[posicao2];
                str[posicao2]=tmpDig;
            }else{ sprintf(str,"%d",0);}
            break;
        case 2: // move vazio (9) para baixo
            posicao2=posicao+3;
            if (posicao<((dimensao*dimensao)-dimensao)){
                tmpDig=str[posicao];
                str[posicao]=str[posicao2];
                str[posicao2]=tmpDig;
            }else{ sprintf(str,"%d",0);}
            break;
        case 3:// move vazio (9) para cima
            posicao2=posicao-3;
            if (((posicao+1)-dimensao)>0){
                tmpDig=str[posicao];
                str[posicao]=str[(posicao-3)];
                str[(posicao-3)]=tmpDig;
            }else{ sprintf(str,"%d",0);}
            break;
        default:
            sprintf(str,"%d",0);
    }
    sscanf(str, "%d", &valor);
    return valor;
}

//Objeto agente Depth-first search - Busca em profundidade
class AG_BFS: public AGENTE {                                     // begin declaration of the class;
    public:                                                          // begin public section
        AG_BFS(int objetivo):AGENTE(objetivo){};                  // constructor
        virtual void expanding_node (int InicialState);
    protected:
        Fila<int> *Borda;
        Fila<int> *Explorado;

};


//expande os nos do grafo
void AG_BFS::expanding_node(int InicialState){
    int acao;
    int Aresta=0;
    int goal=0;
    unitMem<int> *ancora;
    Borda = new Fila<int>(1);
    Explorado = new Fila<int>(1);
    int Vertice;

    if(this->GoalTest(Vertice, this->terminal)){
        try{
            Explorado->AdicionaFila(InicialState,NULL);
            Vertice=0;
        }
        catch (int param) { cout << "int exception"; }
        catch (char param) { cout << "char exception"; }
    }else{

        try{
            Explorado->AdicionaFila(InicialState,NULL);
            Borda->AdicionaFila(InicialState,NULL);
            ancora=Explorado->PegaNoh();
            Vertice=Borda->PegaSaida();
        }
        catch (int param) { cout << "int exception"; }
        catch (char param) { cout << "char exception"; }
        this->quantidade=1;
    }

    while (Vertice){
//----------------------------- Actions--------------------------------------
//        acao = {0,1,2,3};// direita, esquerda, desce, sobe
        for (acao=0;acao<4;acao++){
//-------------------------Transition model----------------------------------
//---- recebe status atual e açao e retorna o valor do status da acao realizada, se valor é 0 a ação não muda o ambiente----------
            Aresta=this->P(Vertice,acao);
            if (Aresta>0){
                if (Explorado->searching(Aresta)==0){
                    try{
                        Explorado->AdicionaFila(Aresta,ancora);
                        Borda->AdicionaFila(Aresta,Explorado->PegaNoh());    //Armazena na Fila com o endereço do Vertice de Origem
                        this->quantidade++;
                    }
                    catch (int param) { cout << "int exception"; }
                    catch (char param) { cout << "char exception"; }
//---------------Função verifica se objetivo foi alcançado-------------------
                    if (this->GoalTest(Aresta,this->terminal)){         //verifica se alcançou o resultado
                        goal=1;
                        break;
                    }
                    if(this->quantidade%100==0){
                        printf(".", this->quantidade);
                    }
                }
            }
        }
        if(goal==1){break;}
        try{
            Borda->RemoveFila();
            Vertice=Borda->PegaSaida();
            ancora=Borda->PegaElo();
        }
        catch (int param) { cout << "int exception"; }
        catch (char param) { cout << "char exception"; }
    }
    printf("\n Total de Buscas/Vertices Abertos %d", this->quantidade);

    try{
        this->resultado=Explorado->PegaNoh();
//        this->PrintPath();
    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }
}


//Objeto agente Depth-first search - Busca em profundidade
class AG_DFS: public AGENTE {                                        // begin declaration of the class;
      public:
        AG_DFS(int objetivo):AGENTE(objetivo){};                     // constructor
        virtual void expanding_node (int InicialState);
    protected:
        int BuscaEmProfundidade (int Vertice, class unitMem<int> * ancora);
        Pilha<int> *Explorado;
};


//expande os nos do grafo
void AG_DFS::expanding_node(int InicialState){
    int a;
    unitMem<int> *ancora;
    Explorado = new Pilha<int>(1);
    if(this->GoalTest(InicialState, this->terminal)){
        try{
            Explorado->AdicionaPilha(InicialState,NULL);
            this->quantidade=1;
        }
        catch (int param) { cout << "int exception"; }
        catch (char param) { cout << "char exception"; }
    }else{
        try{
            Explorado->AdicionaPilha(InicialState,NULL);
            this->quantidade=1;
            ancora=Explorado->PegaNoh();
            a = BuscaEmProfundidade(InicialState, ancora);
        }
        catch (int param) { cout << "int exception"; }
        catch (char param) { cout << "char exception"; }
    }

    printf("\n Total de Buscas/Vertices Abertos %d", this->quantidade);

    try{
        this->resultado=Explorado->PegaNoh();
//        this->PrintPath();
    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }

}


//Busca o objetivo abrindo os ramos extremos até a profundidade máxima, retorna no eixo do ramo e reinicia até a profundidade maxima sucessivamente até o final ou encontrar o objetivo
int AG_DFS::BuscaEmProfundidade(int Vertice, class unitMem<int> * ancora){
    int acao;
    int acaoLoop=0;
    int next=0;
    int Aresta;
    class unitMem<int> * NewAncora;
    Pilha<int> Filho(1);
    if (this->GoalTest(Vertice,this->terminal)){                        //verifica se alcançou o resultado
            return 1;
    }
    while ( !(this->GoalTest(Vertice,this->terminal)) ){                //Print de conforto
        if(this->quantidade%100==0){printf(".", this->quantidade);}
    //----------------------------- Actions--------------------------------------
    //        acao = {0,1,2,3};// direita, esquerda, desce, sobe
        for (acao=acaoLoop;acao<4;acao++){
    //-------------------------Transition model----------------------------------
    //---- recebe status atual e açao e retorna o valor do status da acao realizada, se valor é 0 a ação não muda o ambiente----------
            Aresta=this->P(Vertice,acao);
            if (Aresta>0){
                if (Explorado->searching(Aresta)==0){
                    try{
                        Explorado->AdicionaPilha(Aresta,ancora);
                        this->quantidade++;
                        NewAncora=Explorado->PegaNoh();
                        Filho.AdicionaPilha(Aresta,NewAncora);          // PUSH to Filhos (Arestas)
                    }
                    catch (int param) { cout << "int exception"; }
                    catch (char param) { cout << "char exception"; }
                    break;
                }
            }
            if(Filho.PegaTopo()){Filho.SetStatus(acao);}                   //Marca Status do Vertice  - Status 3 é concluido
        }
        try{
            Vertice=Filho.PegaTopo();
            ancora=Filho.PegaElo();
            acaoLoop=Filho.GetStatus();
        }
        catch (int param) { cout << "int exception"; }
        catch (char param) { cout << "char exception"; }

        if(acaoLoop==3){
            if(!(Filho.RemovePilha())){break;}                          // POP
        }
    }
    return 0;
}


//Objeto agente Busca HC*
class AG_HC: public AGENTE {                                        // begin declaration of the class;
      public:
        AG_HC(int objetivo):AGENTE(objetivo){};                     // constructor
        virtual void expanding_node (int InicialState);
    protected:
        virtual int heuristica (int valor);
        Fila<int> *Borda;
        Fila<int> *Explorado;
};


//expande os nos do grafo
void AG_HC::expanding_node(int InicialState){
    int acao;
    int atmp=-1;
    int Aresta=0;
    int Vertice=1;
    int BestVertice=1;
    int goal=0;
    int localGreedy;
    int actionGreedy;
    int tempera_silulada=1;
    unitMem<int> *ancora;
    Borda = new Fila<int>(1);                           //Fila de Arestas a serem exploradas na borda do grafo

    if(this->GoalTest(Vertice, this->terminal)){
        Borda->AdicionaFila(InicialState,NULL);     //inicializa Fila
        Vertice=0;
    }else{

        try{
//-Inicializa Lista de itens explorados e Fila de arestas a serem exploradas
            Borda->AdicionaFila(InicialState,NULL); //inicializa Fila
            this->quantidade=1;
            ancora=Borda->PegaNoh();
            Vertice=InicialState;
            localGreedy=heuristica(Vertice);
        }
        catch (int param) { cout << "int exception"; }
        catch (char param) { cout << "char exception"; }
        this->quantidade=1;
    }
    while (Vertice){
//----------------------------- Actions--------------------------------------
//        acao = {0,1,2,3};// direita, esquerda, desce, sobe
        for (acao=0;acao<4;acao++){
//-------------------------Transition model----------------------------------
//---- recebe status atual e açao e retorna o valor do status da acao realizada, se valor é 0 a ação não muda o ambiente----------
            Aresta=this->P(Vertice,acao);
//---------------Função verifica se objetivo foi alcançado-------------------
            if (this->GoalTest(Aresta,this->terminal)){         //verifica se alcançou o resultado
                BestVertice=Aresta;
                localGreedy=actionGreedy;
                goal=1;
                break;
            }
            if (Aresta>0){
                actionGreedy=heuristica(Aresta);
                if (tempera_silulada>0){
                    if(actionGreedy<localGreedy){
                        BestVertice=Aresta;
                        localGreedy=actionGreedy;
                        atmp=acao;
                    }else{
                        if (actionGreedy==localGreedy){
                            if((rand()&1) && atmp>=0){
                               BestVertice=this->P(Vertice,atmp);
                            }else{
                               BestVertice=Aresta;
                            }
                            localGreedy=actionGreedy;
                        }
                    }
                }else{
                    if(actionGreedy>localGreedy){
                        BestVertice=Aresta;
                        localGreedy=actionGreedy;
                        atmp=acao;
                    }else{
                        if (actionGreedy==localGreedy){
                            if((rand()&1) && atmp>=0){
                               BestVertice=this->P(Vertice,atmp);
                            }else{
                               BestVertice=Aresta;
                            }
                            localGreedy=actionGreedy;
                        }
                    }
                }
            }
        }

// simulação de tempera para sair de maximo local
        if (BestVertice==0){
            tempera_silulada=tempera_silulada*-1;
        }

        if(BestVertice>0){
                Borda->AdicionaFila(BestVertice,ancora);
                ancora=Borda->PegaNoh();
                Vertice=BestVertice;
                localGreedy=heuristica(Vertice);
                BestVertice=0;
                atmp=-1;
                if(this->quantidade%100==0){
                    printf(".");
                }
                this->quantidade++;
        }
        if(goal==1){break;}

    }

    if (goal==0){         //verifica se alcançou o resultado
        printf("\n\n\n----- ENCONTRADO SOMENTE MAXIMO LOCAL ------\n\n\n");
    }

    printf("\n Total de Buscas/Vertices Abertos %d", this->quantidade);

    try{
        this->resultado=Borda->PegaNoh();
//        this->PrintPath();
    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }

}

//heuristica de manhatam, a quantidade de passos para cada elemento alcançar seu destino final
int AG_HC::heuristica(int valor){
    int h2=0;
    int Manhattan=0;
    int hReal=0;
    int hObj=0;
    int posicao, fn, hn;
    char str[10];
    char strManhattan[10];


    sprintf(str,"%d",valor);
    sprintf(strManhattan,"%d",this->terminal);

    for (posicao=0;posicao<=8;posicao++){
        if(str[posicao]!=strManhattan[posicao]&&str[posicao]!='9'){
            valor = (int)str[posicao] - 48;
            hObj=(valor-1)/3;
            hReal=posicao/3;
            h2=abs(((hReal-hObj)*3+valor)-(posicao+1))+abs((hReal-hObj));
            Manhattan=Manhattan+h2;
        }
    }
    hn= Manhattan;
    fn = hn;
    return fn;

}


//Objeto agente Busca A*
class AG_A: public AGENTE {                                        // begin declaration of the class;
      public:
        AG_A(int objetivo):AGENTE(objetivo){};                     // constructor
        virtual void expanding_node (int InicialState);
    protected:
        virtual int heuristica (int valor, int custo);
        Fila<int> *Borda;
        Fila<int> *Explorado;
};


//expande os nos do grafo
void AG_A::expanding_node(int InicialState){
    int acao;
    int custoAcumulado=0;
    int Aresta=0;
    int Vertice=1;
    int goal=0;
    unitMem<int> *ancora;
    Borda = new Fila<int>(1);                           //Fila de Arestas a serem exploradas na borda do grafo
    Explorado = new Fila<int>(1);                       //Lista de Vertices abertos

    if(this->GoalTest(Vertice, this->terminal)){
        try{
            Explorado->AdicionaFila(InicialState,NULL);     //inicializa Fila
        }
        catch (int param) { cout << "int exception"; }
        catch (char param) { cout << "char exception"; }
        Vertice=0;
    }else{

        try{
//-Inicializa Lista de itens explorados e Fila de arestas a serem exploradas
            Explorado->AdicionaFila(InicialState,NULL); //inicializa Fila
            Borda->AdicionaOrdenado(InicialState,Explorado->PegaNoh(),0,heuristica(InicialState,0)); //inicializa Arestas
        }
        catch (int param) { cout << "int exception"; }
        catch (char param) { cout << "char exception"; }
        this->quantidade=1;
    }
    while (Vertice){
            try{
                Vertice=Borda->PegaSaida();             //Pega valor no inicio da Fila e seta vertice a ser explorado
                custoAcumulado=Borda->PegaCusto();      //obtem custo acumulado deste vertice
                ancora=Borda->PegaElo();                //Cria ancora para retorno e rastreio dos vertices filhos/pais
                Borda->RemoveFila();                    //remove da Fila o Vertice que esta sendo trabalhado
            }
            catch (int param) { cout << "int exception"; }
            catch (char param) { cout << "char exception"; }
//----------------------------- Actions--------------------------------------
//        acao = {0,1,2,3};// direita, esquerda, desce, sobe
        for (acao=0;acao<4;acao++){
//-------------------------Transition model----------------------------------
//---- recebe status atual e açao e retorna o valor do status da acao realizada, se valor é 0 a ação não muda o ambiente----------
            Aresta=this->P(Vertice,acao);
            if (Aresta>0){
                if (Explorado->searching(Aresta)==0){
//---------------Adiciona Aresta como novo vertice na lista de vertices e adiciona na fila (Borda) na ordem, de acordo com a heuristica, de arestas a serem
                    try{
                        Explorado->AdicionaFila(Aresta,ancora);
                        Borda->AdicionaOrdenado(Aresta,Explorado->PegaNoh(),(custoAcumulado+this->custoPasso),heuristica(Aresta,custoAcumulado));
                    }
                    catch (int param) { cout << "int exception"; }
                    catch (char param) { cout << "char exception"; }
                    this->quantidade++;
//---------------Função verifica se objetivo foi alcançado-------------------
                    if (this->GoalTest(Aresta,this->terminal)){         //verifica se alcançou o resultado
                        goal=1;
                        break;
                    }
                    if(this->quantidade%100==0){
                        printf(".", this->quantidade);
                    }
                }
            }
        }
        if(goal==1){break;}

    }

    printf("\n Total de Buscas/Vertices Abertos %d", this->quantidade);

    try{
        this->resultado=Explorado->PegaNoh();
//        this->PrintPath();
    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }

}

//heuristica de manhatam, a quantidade de passos para cada elemento alcançar seu destino final
int AG_A::heuristica(int valor, int custo){
    int h1=0;
    int h2=0;
    int Manhattan=0;
    int hReal=0;
    int hObj=0;
    int posicao, fn, gn, hn;
    char str[10];
    char strManhattan[10];

    gn=custo + this->custoPasso;

    sprintf(str,"%d",valor);
    sprintf(strManhattan,"%d",this->terminal);

    for (posicao=0;posicao<=8;posicao++){
        if(str[posicao]!=strManhattan[posicao]&&str[posicao]!='9'){
            valor = (int)str[posicao] - 48;
            hObj=(valor-1)/3;
            hReal=posicao/3;
            h2=abs(((hReal-hObj)*3+valor)-(posicao+1))+abs((hReal-hObj));
            Manhattan=Manhattan+h2;
            h1++;
        }
    }
    hn= Manhattan;
    fn = gn+ hn;
    return fn;

}

//Objeto agente Depth-first search - Busca em profundidade
class AG_ESTADOS: public AGENTE {                                     // begin declaration of the class;
    public:                                                          // begin public section
        AG_ESTADOS(int objetivo):AGENTE(objetivo){};                  // constructor
        virtual void expanding_node (int InicialState);
    protected:
        Fila<int> *Borda;
        Fila<int> *Explorado;

};


//expande os nos do grafo
void AG_ESTADOS::expanding_node(int InicialState){
    int acao;
    int Aresta=0;
    int novo=1;
    unitMem<int> *ancora;
    Explorado = new Fila<int>(1);
    Borda = new Fila<int>(1);
    int Vertice;

    try{
        Explorado->AdicionaFila(InicialState,NULL);
        Vertice=InicialState;
    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }
    this->quantidade=1;


    while (Vertice){
//----------------------------- Actions--------------------------------------
//        acao = {0,1,2,3};// direita, esquerda, desce, sobe
        for (acao=0;acao<4;acao++){
//-------------------------Transition model----------------------------------
//---- recebe status atual e açao e retorna o valor do status da acao realizada, se valor é 0 a ação não muda o ambiente----------
            Aresta=this->P(Vertice,acao);
            if (Aresta>0){
                if (Explorado->searching(Aresta)==0){
                    this->quantidade++;
                        if(this->quantidade%100==0){
                        printf(".", this->quantidade);
                    }
                    try{
                        Explorado->AdicionaFila(Aresta,NULL);
                    }
                    catch (int param) { cout << "int exception"; }
                    catch (char param) { cout << "char exception"; }
                    try{
                        Borda->AdicionaFila(Aresta,NULL);
                    }
                    catch (int param) { cout << "int exception"; }
                    catch (char param) { cout << "char exception"; }
                }
            }
        }
        try{
            Vertice=Borda->PegaSaida();
        }
        catch (int param) { cout << "int exception"; }
        catch (char param) { cout << "char exception"; }

        try{
            Borda->RemoveFila();
        }
        catch (int param) { cout << "int exception"; }
        catch (char param) { cout << "char exception"; }

    }
    printf("\n Total de Estadps/Vertices Abertos %d", this->quantidade);

    try{
        this->resultado=Explorado->PegaNoh();
    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }
}



