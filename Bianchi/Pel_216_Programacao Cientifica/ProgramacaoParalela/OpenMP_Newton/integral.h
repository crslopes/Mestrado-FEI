#include <omp.h> // adiciona biblioteca do Open MP
#include <iostream>
#include<math.h>
#include <random>
#include <functional>
#include <chrono>
// exceptions
#include "func.h"
//-------------------------------------------------------------------
//      PEL_216 2º. Semestre de 2019
//      Prof: Dr Reinaldo Bianchi
//      Aluno: Cristiano Lopes Moreira
//      RA: 119103-0
//
//      Integral Newton OpenMP
//
//-------------------------------------------------------------------

class integral {
public:
    integral(class Funcd* fx, double *xlo ,double *xhi, int dimensoes, double txError);	//constructor
    ~integral();																	    //desctuctor
    void calc() {};															            //funcao para calcular a integral
    int qTpassos(){return this->passos;};												//funcao que retorna a quantidade de passos necessarios para realizar o calculo
    double respostaIntegral(){return this->vlFxIntegral;};                              //funcao que mostra o valor da integral
    double respostaErro(){return this->txAccurate;};                                    //funcao que retorna o erro estimado do calculo
protected:													    						//inicio da secao privada
    int passos;													    					//member variable - conta número de passos para o resultado
    int dimensoesFx;                                                                    //member variable - armazena a quantidade de dimensoes a funcao tem
    int maxPassos;															    		//member variable - maximo de loops permitidos para evitar loop eterno
    double erro;																    	//member variable - erro aceitável
    double txAccurate;                                                                  //member variable - erro calculado
    double * lo;																        //member variable - limite inferior
    double * hi;																        //member variable - limite superior
    double vlFxIntegral;                                                                //member variable - resultado do calculo da integral
    class Funcd* pointFx;															    //member variable - ponteiro para a funcao

};
// constructor
// inicializa o objeto monte_carlo com os valores do erro aceitavel; da funcao, dos limites e da quantidade de dimensoes
integral::integral(class Funcd* fx, double *xlo ,double *xhi, int dimensoes, double txError) {
    passos = 0;
    maxPassos = 5000000;
    dimensoesFx=dimensoes;
    erro = txError;
    txAccurate=0;
    lo = xlo;
    hi = xhi;
    vlFxIntegral=0;
    pointFx = fx;
}
// destructor
// finaliza o objeto
integral::~integral() {
    lo=NULL;
    hi=NULL;
    pointFx=NULL;
}

// objeto Pontos Medios - herda os metdos do objeto integral e realiza o calculo da integral pelo metodo da regra dos pontos medios
class pontos_medios : public integral {
public:
    pontos_medios(class Funcd* fx, double *xlo ,double *xhi, int dimensoes, double txError);				//constructor
    ~pontos_medios();																	                    //desctuctor
    virtual void calc();															                        //funcao para calcular a integral

};
// constructor
// inicializa o objeto pontos medios com os valores do erro aceitavel; da funcao, dos limites e da quantidade de dimensoes
pontos_medios::pontos_medios(class Funcd* fx, double *xlo ,double *xhi, int dimensoes, double txError):
        integral(fx, xlo ,xhi, dimensoes, txError){
}
// destructor
// finaliza o objeto
pontos_medios::~pontos_medios() {
    this->lo=NULL;
    this->hi=NULL;
    this->pointFx=NULL;
}

// acessor function
// Calcula a integral pelo metodo da regra dos pontos medios
void pontos_medios::calc() {
    // define os limites inferior 'a' e superior 'b' para o calculo da integral
    double a = lo[0];
    double b = hi[0];
    double steps = 0;
    double accurate=0;
    int start = (int)a;
    int end = (int)b;
    int step = 0;

    //stepSize é a divisao dos pontos medios, inicializa com o intervalo completo
    double stepSize = (b - a);
    //calcula a integral com o intervalo completo
    double *x;             // variável para carregar os valores x a serem utilizados no calculo da funcao
    x = (double*) malloc (dimensoesFx * sizeof(double));   // define o tamanho da variavel de acordo com os limites do objeto que se deseja calcular a integral
    x[0]=(a + b) / 2;
    double integrateResult = (b - a) * this->pointFx->funcao(x);
    //calcula o erro pelo metodo da regra dos pontos medios
    accurate = pow((b - a),3)/24 *  this->pointFx->derivada(a, 2, (b - a));
    //a variavel passos conta os intervalos
    this->passos = 1;
    // realiza um loop, dividindo os intervalos pela metade, até que o erro estimado seja menor que o aceitavel pelo parametro encaminhado
    while (fabs(accurate)>=this->erro)
    {
        //realiza a divisao do stepSize por 2 para cada interacao
        stepSize = stepSize / 2;
        end=(int)((b-a)/stepSize);
        accurate = 0;
        integrateResult = 0;
// inicializa o paralelismo no loop for, reduz as variaveis integrateResult e accurate para realizar o calculo final da integral de newton com todas as threads
#pragma omp parallel for private(step, steps) reduction (+:integrateResult) reduction (+:accurate)
        //faz um loop para somar todos os intervalos de 'a' ate 'b' e soma para obter o valor total da integral e do erro
        for (step=start;step<end;step++)
        {
            steps=((double)step+1.0)*stepSize;
            x[0]=(steps + (steps+stepSize)) / 2;
            integrateResult = integrateResult + (stepSize) * this->pointFx->funcao(x);
            accurate = accurate + pow((stepSize), 3) / 24 * this->pointFx->derivada(a, 2, (stepSize));
            this->passos++;
        }
    }
    //a variavel vlFxIntegral armazena o resultado da integral
    this->vlFxIntegral= integrateResult;
    this->txAccurate=accurate;
};
