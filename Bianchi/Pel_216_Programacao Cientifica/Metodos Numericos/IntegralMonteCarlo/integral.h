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
    integral(class Funcd* fx, double *xlo ,double *xhi, int dimensoes, double txError);	//constructor
    ~integral();																	    //desctuctor
    void calc() {};															            //funcao para calcular a integral
    int qTpassos(){return this->passos;};												//funcao que retorna a quantidade de passos necessarios para realizar o calculo
    double respostaIntegral(){return this->vlFxIntegral;};                              //funcao que mostra o valor da integral
    double respostaErro(){return this->txAccurate;};                                //funcao que retorna o erro estimado do calculo
protected:																			//inicio da secao privada
    int passos;																		//member variable - conta número de passos para o resultado
    int dimensoesFx;                                                                //member variable - armazena a quantidade de dimensoes a funcao tem
    int maxPassos;																	//member variable - maximo de loops permitidos para evitar loop eterno
    double erro;																	//member variable - erro aceitável
    double txAccurate;                                                              //member variable - erro calculado
    double * lo;																    //member variable - limite inferior
    double * hi;																    //member variable - limite superior
    double vlFxIntegral;                                                            //member variable - resultado do calculo da integral
    class Funcd* pointFx;															//member variable - ponteiro para a funcao

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

// objeto monte_carlo, herda metodos do objeto integral e calcula a integral pelo metodo estocástico de monte carlo

class monte_carlo : public integral {
public:
    monte_carlo(class Funcd* fx, double *xlo ,double *xhi, int dimensoes, double txError);				//constructor
    ~monte_carlo();																	                    //desctuctor
    virtual void calc();															                    //funcao para calcular a integral
private:																			                    //inicio da secao privada
    double aleatorio(double a, double b);                                                               // funcao de gerar numeros aleatorios

};
// constructor
// inicializa o objeto monte_carlo com os valores do erro aceitavel; da funcao, dos limites e da quantidade de dimensoes
monte_carlo::monte_carlo(class Funcd* fx, double *xlo ,double *xhi, int dimensoes, double txError):
    integral(fx, xlo ,xhi, dimensoes, txError){
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
    double V = 1;               // variavel que armazena o volume pelas dimensoes de monte carlo
    double SomatorioFxyz = 0;   // variavel para calcular o erro
    double SomatorioFxyz2=0;    // variavel para calcular o erro
    double integrateResult=0;   // armazena o resultado da integral
    double *tmpVar;             // variável para carregar os valores aleatorios a serem utilizados no calculo da funcao
    tmpVar = (double*) malloc (dimensoesFx * sizeof(double));   // define o tamanho da variavel de acordo com os limites do objeto que se deseja calcular a integral
    int amostras=1000, n=0, i=0;    // amostras é a quantidade inicial para calculo de monte carlo , n e i variavis de apoio no loop for
    this->txAccurate = 0;   //variavel para armazenar o erro estimado no calculo da integral
    this->passos=1;
// o for calcula o volume referencia a ajustado pelas amostras da funcao, utiliza dos ponteiros hi (limite maximo) lo (limite minimo) de cada dimensao 'i'
    for (i =0; i<this->dimensoesFx;i++){
        V=V*(this->hi[i]-this->lo[i]);
    }
// realiza um loop de calculo das amostras sorteadas até que encontre um erro aceitavel ou o numero maximo de loops permitido
    do    {
        for (n=1;n<amostras;n++) {
            for (i =0; i<this->dimensoesFx;i++){
                tmpVar[i]=aleatorio(this->lo[i],this->hi[i]);
            }
            SomatorioFxyz = SomatorioFxyz + this->pointFx->funcao(tmpVar) ;
            SomatorioFxyz2 = SomatorioFxyz2 + pow(this->pointFx->funcao(tmpVar), 2) ;
            this->passos++;
            integrateResult=V*SomatorioFxyz/this->passos;
            this->txAccurate=V*sqrt((SomatorioFxyz2/this->passos- pow(SomatorioFxyz/this->passos,2))/this->passos);
        }
    } while (fabs(this->txAccurate)>=this->erro && this->passos < this->maxPassos);

    this->vlFxIntegral= integrateResult;
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
    //stepSize é a divisao dos pontos medios, inicializa com o intervalo completo
    double stepSize = (b - a);
    double step = 0;
    //calcula a integral com o intervalo completo
    double *x;             // variável para carregar os valores x a serem utilizados no calculo da funcao
    x = (double*) malloc (dimensoesFx * sizeof(double));   // define o tamanho da variavel de acordo com os limites do objeto que se deseja calcular a integral
    x[0]=(a + b) / 2;
    double integrateResult = (b - a) * this->pointFx->funcao(x);
    //calcula o erro pelo metodo da regra dos pontos medios
    this->txAccurate = pow((b - a),3)/24 *  this->pointFx->derivada(a, 2, (b - a));
    //a variavel passos conta os intervalos
    this->passos = 1;
    // realiza um loop, dividindo os intervalos pela metade, até que o erro estimado seja menor que o aceitavel pelo parametro encaminhado
    while (fabs(this->txAccurate)>=this->erro)
    {
        //realiza a divisao do stepSize por 2 para cada interacao
        stepSize = stepSize / 2;
        this->txAccurate = 0;
        integrateResult = 0;
        step = a;
        //faz um loop para somar todos os intervalos de 'a' ate 'b' e soma para obter o valor total da integral e do erro
        while (step < b)
        {
            x[0]=(step + (step+stepSize)) / 2;
            integrateResult = integrateResult + (stepSize) * this->pointFx->funcao(x);
            this->txAccurate = this->txAccurate + pow((stepSize), 3) / 24 * this->pointFx->derivada(a, 2, (stepSize));
            this->passos++;
            step = step + stepSize;
        }
    }
    //a variavel vlFxIntegral armazena o resultado da integral
    this->vlFxIntegral= integrateResult;
};
