//-------------------------------------------------------------------
//      PEL_216 2º. Semestre de 2019
//      Prof: Dr Reinaldo Bianchi
//      Aluno: Cristiano Lopes Moreira
//      RA: 119103-0
//
//      Programação distribuida
//
//-------------------------------------------------------------------
#include <stdio.h>
// exceptions
#include <iostream>
#include <mpi.h>
#include "integral.h"
#define  MASTER		0
#define CICLOS 100000      /* de ciclos de execucao de montecarlo */

using namespace std;


// Classe para Funcao do toro - herda os metodos da funcao Funcd para polimorfismo dos metodos funcao e derivada
class toroide : public Funcd {
public:
    toroide() :Funcd() {};									// constructor
    ~toroide() {};											// destructor
    virtual double funcao(double * x);    // virtual acessor function to polymorph from Funcd
};
// metodo funcao calcula a funcao do toroide e retorna se a coordenada estiver dentro do objeto, 0 se estiver fora do objeto
double toroide::funcao(double * x) {
    if( (pow(x[2],2)+pow(sqrt(pow(x[0],2)+pow(x[1],2))-3,2))<=1 && (x[0]>=1)&&(x[1]>=-3)){
        return 1;
    }else{
        return 0;
    }
};


int main(int argc, char *argv[]) {
    double erro = 0.04;								//valor inicial da taxa de erro aceitavel
    double integral,                                //valor da integral
        Accurate,                                   //valor estimativa de erro
        vfx,                                        //valor da funcao
        vfx2,                                       //valor da funcao ao quadrado para calculo do erro
        vfxTotal,                                   //somatoria de todos processos fx
        vfx2Total;                                  //somatoria de todos processos fx^2
    double xlo[3];                                  //variavel para limite inferior (low) das funcoes que se deseja calcular
    double xhi[3];                                  //variavel para limite superior (high) das funcoes que se deseja calcular
    int	taskid;	                                    //variavel para identificacao da task task ID
    int numtasks;                                   //variavel com numero de tasks
    int rc;                                         //variavel para codigo de retorno

    int vFxn,
        len,
        totalCiclos,
        sorteios;


    Funcd* fx;										//ponteiro para objeto Funcao
    monte_carlo *fxMontecarlo;                      //ponteiro para o objeto monte carlo

    // inicializa MPI para multiplos processos
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&taskid);

    //variavel sorteio divide a quantidade de ciclos para cada processo
    sorteios=CICLOS/numtasks;

    //inicializa os limites do toroide para a funcao
    xlo[0] = 1;
    xhi[0] = 4;
    xlo[1] = -3;
    xhi[1] = 4;
    xlo[2] = -1;
    xhi[2] = 1;

    try {
        //inicializa objeto funcao toroide
        fx = new toroide();
    }
    catch (int) { cout << "int exception"; }
    catch (char) { cout << "char exception"; }
    try {
        //inicializa o objeto integral monte carlo e envia os parametros, funcao , limite inferior, limite superior, e erro aceitavel
        fxMontecarlo = new monte_carlo(fx, xlo, xhi, 3, erro, sorteios);
    }
    catch (int) { cout << "int exception"; }
    catch (char) { cout << "char exception"; }

    try {
        fxMontecarlo->geraDados();
    }
    catch (int) { cout << "int exception"; }
    catch (char) { cout << "char exception"; }

    try{
        //obter a quantidade de ciclos de numeros randomicos realizados no objeto fxMontecarlo
        vFxn=fxMontecarlo->qTpassos();
    }
    catch (int) { cout << "int exception"; }
    catch (char) { cout << "char exception"; }


    // utiliza MPI_Reduce para somar todos os valores dos ciclos e retornar ao master;
    rc = MPI_Reduce(&vFxn, &totalCiclos, 1, MPI_INT, MPI_SUM, MASTER, MPI_COMM_WORLD);
    if (rc != MPI_SUCCESS){
        printf("%d: failure on mpc_reduce\n", taskid);
    }

    try{
        //obter o valor de fx no objeto fxMontecarlo para cada processo
        vfx=fxMontecarlo->ParcialFx();
    }
    catch (int) { cout << "int exception"; }
    catch (char) { cout << "char exception"; }

    // utiliza MPI_Reduce para somar todos os valores dos fx e retornar ao master;
    rc = MPI_Reduce(&vfx, &vfxTotal, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);
    if (rc != MPI_SUCCESS){
        printf("%d: failure on mpc_reduce\n", taskid);
    }

    try{
        //obter o valor de fx^2 no objeto fxMontecarlo para cada processo
        vfx2=fxMontecarlo->ParcialFx2();
    }
    catch (int) { cout << "int exception"; }
    catch (char) { cout << "char exception"; }

    // utiliza MPI_Reduce para somar todos os valores dos fx^2 e retornar ao master;
    rc = MPI_Reduce(&vfx2, &vfx2Total, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);

    if (rc != MPI_SUCCESS){
        printf("%d: failure on mpc_reduce\n", taskid);
    }

    /* Master calcula a integral com todas as informacoes juntas */
    if (taskid == MASTER) {
        integral = fxMontecarlo->Volume() * vfxTotal / totalCiclos;
        Accurate = fxMontecarlo->Volume() * sqrt((vfx2Total / totalCiclos - pow(vfxTotal / totalCiclos, 2)) / totalCiclos);
        printf("\n\n#############################################################");
        printf("\n Metodo Acumulado Integral de Monte Carlo : %.10lf", integral);
        printf("\n Erro %.15lf - Passos: %d", Accurate, totalCiclos);
        printf("\n#############################################################\n\n");

    }

    //finaliza os objetos monte_carlo e funcao
    fxMontecarlo->~monte_carlo();
    fx->~Funcd();

    MPI_Finalize();
    return 0;
}

