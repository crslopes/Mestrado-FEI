#include <stdio.h>
#include <stdlib.h>

// exceptions
#include <iostream>
#include "integral.h"
using namespace std;
//-------------------------------------------------------------------
//      PEL_216 2º. Semestre de 2019
//      Prof: Dr Reinaldo Bianchi
//      Aluno: Cristiano Lopes Moreira
//      RA: 119103-0
//
//      Integral Newton OpenMP
//
//-------------------------------------------------------------------
// Classe para Funcao f(x)=4/(1+x^2) herda os metodos da funcao Funcd para polimorfismo dos metodos funcao e derivada
class fx1 : public Funcd {
public:
    fx1() :Funcd() {};										// constructor
    ~fx1() {};                                              // destructor
    virtual double funcao(double x);						// virtual acessor function to polymorph from Funcd
    virtual double funcao(double *x);						// virtual acessor function to polymorph from Funcd
};
// metodo funcao calcula a funcao f(x)=4/(1+x^2)
double fx1::funcao(double x) {
    return 4/(1+pow(x,2));
};
// metodo funcao calcula a funcao f(x)=4/(1+x^2) com x como ponteiro
double fx1::funcao(double *x) {
    return 4/(1+pow(x[0],2));
};

int main() {
    double x0 = 0;									//variavel com o limite inferior para calculo da integral
    double x1 = 1;									//variavel com o limite superior para calculo da integral
    double erro = 0.00000000000001;								//valor inicial da taxa de erro aceitavel
    double integral;								//valor da integral
    double xlo[3];                                  //variavel para limite inferior (low) das funcoes que se deseja calcular
    double xhi[3];                                  //variavel para limite superior (high) das funcoes que se deseja calcular

    Funcd* fx;										//ponteiro para objeto Funcao
    pontos_medios *fxPontosMedios;                  //ponteiro para o objeto pontos medios

    printf("\nIntegral da funcao f(x)=4/(1+x^2)");
    try {
        //inicializa objeto funcao f1
        fx = new fx1();
    }
    catch (int) { cout << "int exception"; }
    catch (char) { cout << "char exception"; }
    //define os limites das coordenadas da funcao
    xlo[0] = x0;
    xhi[0] = x1;
    //inicializa o objeto integral por pontos medios envia os parametros, funcao , limite inferior, limite superior, e erro aceitavel
    try {
        fxPontosMedios = new pontos_medios(fx, xlo, xhi, 1, erro);
    }
    catch (int) { cout << "int exception"; }
    catch (char) { cout << "char exception"; }

    try {
        //aciona o metodo de calculo da integral do objeto pontos medios
        fxPontosMedios->calc();
    }
    catch (int) { cout << "int exception"; }
    catch (char) { cout << "char exception"; }
    try {
        //aciona o metodo respostaIntegral e recebe o valor do calculo
        integral = fxPontosMedios->respostaIntegral();
    }
    catch (int) { cout << "int exception"; }
    catch (char) { cout << "char exception"; }

    printf("\n Metodo da Regra dos Pontos Medios: %.10lf", integral);
    printf("\n Erro %.20lf - Passos: %d\n", fxPontosMedios->respostaErro(), fxPontosMedios->qTpassos());

    try {
        fxPontosMedios->~pontos_medios();
    }
    catch (int) { cout << "int exception"; }
    catch (char) { cout << "char exception"; }

    return 0;
}
