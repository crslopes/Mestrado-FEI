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
//      Integral Monte Carlo
//
//-------------------------------------------------------------------

class integral {
public:
    integral(class Funcd* fx, double *xlo ,double *xhi, int dimensoes, double txError, int ciclos);	//constructor
    ~integral();																	    //desctuctor
    void calc() {};															            //funcao para calcular a integral
    void geraDados() {};															    //funcao para gerar dados randomicos para a integral
    int qTpassos(){return this->passos;};												//funcao que retorna a quantidade de passos necessarios para realizar o calculo
    double respostaIntegral(){return this->vlFxIntegral;};                              //funcao que mostra o valor da integral
    double ParcialFx(){return this->SomatorioFxyz;};                                    //funcao que mostra o valor da ParcialFx SomatorioFxyz
    double ParcialFx2(){return this->SomatorioFxyz2;};                                    //funcao que mostra o valor da ParcialFx^2 SomatorioFxyz2
    double respostaErro(){return this->txAccurate;};                                //funcao que retorna o erro estimado do calculo
    double Volume();                                           //funcao que retorna o volume pelas dimensoes de monte carlo
protected:																			//inicio da secao privada
    int passos;																		//member variable - conta número de passos para o resultado
    int dimensoesFx;                                                                //member variable - armazena a quantidade de dimensoes a funcao tem
    int amostras;																	//member variable - numero de sorteios
    double erro;																	//member variable - erro aceitável
    double txAccurate;                                                              //member variable - erro calculado
    double * lo;																    //member variable - limite inferior
    double * hi;																    //member variable - limite superior
    double vlFxIntegral;                                                            //member variable - resultado do calculo da integral
    double SomatorioFxyz;                                                           //member variable - somatoria do resultado da funcao com os sorteios randomicos
    double SomatorioFxyz2;                                                          //member variable - somatoria do resultado quadra da funcao para calculo do erro
    class Funcd* pointFx;															//member variable - ponteiro para a funcao
};
// constructor
// inicializa o objeto monte_carlo com os valores do erro aceitavel; da funcao, dos limites e da quantidade de dimensoes
integral::integral(class Funcd* fx, double *xlo ,double *xhi, int dimensoes, double txError, int ciclos) {
    passos = 0;
    amostras=ciclos;
    dimensoesFx=dimensoes;
    erro = txError;
    txAccurate=0;
    lo = xlo;
    hi = xhi;
    vlFxIntegral=0;
    SomatorioFxyz=0;
    SomatorioFxyz2=0;
    pointFx = fx;
}
// destructor
// finaliza o objeto
integral::~integral() {
    lo=NULL;
    hi=NULL;
    pointFx=NULL;
}

double integral::Volume(){
    int i;
    double V = 1;               // variavel que armazena o volume pelas dimensoes de monte carlo
    for (i = 0; i < this->dimensoesFx; i++) {
        V = V * (this->hi[i] - this->lo[i]);
    }
    return V;
}


// objeto monte_carlo, herda metodos do objeto integral e calcula a integral pelo metodo estocástico de monte carlo

class monte_carlo : public integral {
public:
    monte_carlo(class Funcd* fx, double *xlo ,double *xhi, int dimensoes, double txError, int ciclos);				//constructor
    ~monte_carlo();																	                    //desctuctor
    virtual void calc();															                    //funcao para calcular a integral
    virtual void geraDados();															                //funcao para calcular a integral
private:																			                    //inicio da secao privada
    double aleatorio(double a, double b);                                                               // funcao de gerar numeros aleatorios

};
// constructor
// inicializa o objeto monte_carlo com os valores do erro aceitavel; da funcao, dos limites e da quantidade de dimensoes
monte_carlo::monte_carlo(class Funcd* fx, double *xlo ,double *xhi, int dimensoes, double txError, int ciclos):
        integral(fx, xlo ,xhi, dimensoes, txError, ciclos){
}
// destructor
// finaliza o objeto
monte_carlo::~monte_carlo() {
    this->lo=NULL;
    this->hi=NULL;
    this->pointFx=NULL;
}

//acessor function
//recebe o intervalo e retorna um numero aleatorio dentro de uma distribuicao uniforme utilizando o algoritmo Mersenne Twister
double monte_carlo::aleatorio(double a, double b) {
// ############# gerador de números aleatórios mersenne twister ###########################################
// utiliza uma semente (seed) com base temporal para aumentar a pseudo aleatoridade
    mt19937::result_type seed = chrono::high_resolution_clock::now().time_since_epoch().count();
// realiza o sorteio dentro de uma distribuicao uniforme entre a e b
    auto real_rand = std::bind(std::uniform_real_distribution<double>(a,b), mt19937(seed));
// ########################################################################################################
    return real_rand();
}
// acessor function
// calcula a integral pela regra de monte carlo, por metodos estatisticos (estocástico)
void monte_carlo::calc() {
// Calcula o resultado da integral com a somatoria de todos os processos
    this->vlFxIntegral = this->Volume() * this->SomatorioFxyz / this->passos;
    this->txAccurate = this->Volume() * sqrt((this->SomatorioFxyz2 / this->passos - pow(this->SomatorioFxyz / this->passos, 2)) / this->passos);
}

// acessor function - uso em multiplos processos
// calcula e acumula Fx e Fx^22 pela regra de monte carlo, por metodos estatisticos (estocástico) para uso em multiplos processos
void monte_carlo::geraDados() {
    double *tmpVar;             // variável para carregar os valores aleatorios a serem utilizados no calculo da funcao
    tmpVar = (double*) malloc (dimensoesFx * sizeof(double));   // define o tamanho da variavel de acordo com os limites do objeto que se deseja calcular a integral
    int n=0, i=0;    // amostras é a quantidade inicial para calculo de monte carlo , n e i variavis de apoio no loop for
    this->txAccurate = 0;   //variavel para armazenar o erro estimado no calculo da integral
    this->passos=1;
// realiza um loop de calculo das amostras sorteadas até o numero maximo de loops permitido
    for (n = 1; n < this->amostras; n++) {
        for (i = 0; i < this->dimensoesFx; i++) {
            tmpVar[i] = aleatorio(this->lo[i], this->hi[i]);
        }
        this->SomatorioFxyz = this->SomatorioFxyz + this->pointFx->funcao(tmpVar);
        this->SomatorioFxyz2 = this->SomatorioFxyz2 + pow(this->pointFx->funcao(tmpVar), 2);
        this->passos++;
    }

}