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
//      Integral Monte Carlo
//
//-------------------------------------------------------------------
void getch(void)
{
    system("read b");
}
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

// Classe para a funcao f(x)=(x + (x)^1/2)^1/2 herda os metodos da funcao Funcd para polimorfismo dos metodos funcao e derivada
class fx2 : public Funcd {
public:
    fx2() :Funcd() {};										// constructor
    ~fx2() {};                                              // destructor
    virtual double funcao(double x);						// virtual acessor function to polymorph from Funcd
    virtual double funcao(double *x);						// virtual acessor function to polymorph from Funcd
};

// metodo funcao calcula a funcao f(x)=(x + (x)^1/2)^1/2
double fx2::funcao(double x) {
    return sqrt(x+sqrt(x));
};
// metodo funcao calcula a funcao f(x)=(x + (x)^1/2)^1/2  com x como ponteiro
double fx2::funcao(double *x) {
    return sqrt(x[0]+sqrt(x[0]));
};



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

int main() {
    int opcao=0;									//variavel utilizada na selecao do menu
    double x0 = 0;									//variavel com o limite inferior para calculo da integral
    double x1 = 1;									//variavel com o limite superior para calculo da integral
    double erro = 1;								//valor inicial da taxa de erro aceitavel
    double integral;								//valor da integral
    double xlo[3];                                  //variavel para limite inferior (low) das funcoes que se deseja calcular
    double xhi[3];                                  //variavel para limite superior (high) das funcoes que se deseja calcular

    Funcd* fx;										//ponteiro para objeto Funcao
    monte_carlo *fxMontecarlo;                      //ponteiro para o objeto monte carlo
    pontos_medios *fxPontosMedios;                  //ponteiro para o objeto pontos medios

    while (1) { /* loop infinito para gerar menu */
        printf("\n---Parametros para a solucao da integral---\ntxErro: %.15lf - x0: %.2lf - valor de x1: %.2lf \n\n", erro, x0, x1);
        printf("-----------------------------------------------------------");
        printf("\n1: Entre com nova taxa de erro\n");
        printf("2: Entre com novo valor do limite inferior X0\n");
        printf("3: Entre com novo valor do limite superior X1\n");
        printf("-----------------------------------------------------------\n");
        printf("4: Calculo da integral da funcao f(x)=4/(1+x^2)\n");
        printf("5- Calculo da integral da funcao f(x)=(x + (x)^1/2)^1/2 \n");
        printf("6- Calculo da integral do toroide \n");
        printf("\n-----------------------------------------------------------\n");
        printf("7- sair\n");
        printf("-----------------------------------------------------------");
        printf("\ndigite uma opcao? ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Seta nota taxa erro
                printf("\nQual o valor da taxa de erro? ");
                scanf("%lf", &erro);
                break;
            case 2: // Seta limite inferior para calculo da integral
                printf("\nQual o valor do limite inferior x0? ");
                scanf("%lf", &x0);
                break;
            case 3:// Seta limite superior para calculo da integral
                printf("\nQual o valor do limite superior x1? ");
                scanf("%lf", &x1);

                break;
            case 4: // calcula a integral numerica da funcao f(x)=4/(1+x^2)
                printf("\nIntegral da funcao f(x)=4/(1+x^2)");
                try{
                //inicializa objeto funcao f1
                    fx = new fx1();
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }
                //define os limites das coordenadas da funcao
                xlo[0]=x0;xhi[0]=x1;
                //inicializa o objeto integral por pontos medios envia os parametros, funcao , limite inferior, limite superior, e erro aceitavel
                try {
                    fxPontosMedios = new pontos_medios(fx,xlo, xhi,1, erro);
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }

                try {
                //aciona o metodo de calculo da integral do objeto pontos medios
                    fxPontosMedios->calc();
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }
                try{
                //aciona o metodo respostaIntegral e recebe o valor do calculo
                    integral=fxPontosMedios->respostaIntegral();
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }

                printf("\n Metodo da Regra dos Pontos Medios: %.10lf", integral);
                printf("\n Erro %.15lf - Passos: %d\n", fxPontosMedios->respostaErro(), fxPontosMedios->qTpassos());

                try{
                    fxPontosMedios->~pontos_medios();
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }

                try{
                //inicializa o objeto integral monte carlo e envia os parametros, funcao , limite inferior, limite superior, e erro aceitavel
                    fxMontecarlo = new monte_carlo(fx,xlo, xhi,1, erro);
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }

                try{
                //aciona o metodo de calculo da integral do objeto monte carlo
                    fxMontecarlo->calc();
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }

                try{
                //aciona o metodo respostaIntegral e recebe o valor do calculo
                    integral=fxMontecarlo->respostaIntegral();
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }

                printf("\n Metodo de Monte Carlo: %.10lf", integral);
                printf("\n Erro %.15lf - Passos: %d\n", fxMontecarlo->respostaErro(), fxMontecarlo->qTpassos());
                //finaliza os objetos monte_carlo e funcao
                fxMontecarlo->~monte_carlo();
                fx->~Funcd();

                printf("\n Digite <ENTER> para continuar");

                printf("\n");
                getch();
                break;
            case 5:// calcula a integral numerica da funcao f(x)=(x + (x)^1/2)^1/2
                printf("\nIntegral da funcao f(x)=(x+(x)^1/2)^1/2");
                //inicializa objeto funcao f2

                try{
                    fx = new fx2();
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }

                //define os limites das coordenadas da funcao
                xlo[0]=x0;xhi[0]=x1;

                try{
                //inicializa o objeto integral por pontos medios envia os parametros, funcao , limite inferior, limite superior, e erro aceitavel
                    fxPontosMedios = new pontos_medios(fx,xlo, xhi,1, erro);
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }
                try{
                //aciona o metodo de calculo da integral do objeto pontos medios
                    fxPontosMedios->calc();
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }

                try{
                //aciona o metodo respostaIntegral e recebe o valor do calculo
                    integral=fxPontosMedios->respostaIntegral();
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }

                printf("\n Metodo da Regra dos Pontos Medios: %.10lf", integral);
                printf("\n Erro %.15lf - Passos: %d\n", fxPontosMedios->respostaErro(), fxPontosMedios->qTpassos());

                fxPontosMedios->~pontos_medios();

                try{
                //inicializa o objeto integral monte carlo e envia os parametros, funcao , limite inferior, limite superior, e erro aceitavel
                    fxMontecarlo = new monte_carlo(fx,xlo, xhi,1, erro);
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }
                try{
                //aciona o metodo de calculo da integral do objeto monte carlo
                    fxMontecarlo->calc();
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }

                try{
                //aciona o metodo respostaIntegral e recebe o valor do calculo
                    integral=fxMontecarlo->respostaIntegral();
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }

                printf("\n Metodo de Monte Carlo: %.10lf", integral);
                printf("\n Erro %.15lf - Passos: %d\n", fxMontecarlo->respostaErro(), fxMontecarlo->qTpassos());
                //finaliza os objetos monte_carlo e funcao
                fxMontecarlo->~monte_carlo();
                fx->~Funcd();

                printf("\n Digite <ENTER> para continuar");

                printf("\n");
                getch();
                break;

            case 6: // calcula a integral numerica do toroide
                printf("\nIntegral do Toroide");
                //define os limites das coordenadas do toroide
                xlo[0]=1;xhi[0]=4;
                xlo[1]=-3;xhi[1]=4;
                xlo[2]=-1;xhi[2]=1;

                try{
                //inicializa objeto funcao toroide
                    fx = new toroide();
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }
                try{
                //inicializa o objeto integral monte carlo e envia os parametros, funcao , limite inferior, limite superior, e erro aceitavel
                    fxMontecarlo = new monte_carlo(fx,xlo, xhi,3, erro);
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }
                try{
                //aciona o metodo de calculo da integral do objeto monte carlo
                    fxMontecarlo->calc();
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }

                try{
                //aciona o metodo respostaIntegral e recebe o valor do calculo
                    integral=fxMontecarlo->respostaIntegral();
                }
                catch (int) { cout << "int exception"; }
                catch (char) { cout << "char exception"; }

                printf("\n Metodo de Monte Carlo: %.10lf", integral);
                printf("\n Erro %.15lf - Passos: %d\n", fxMontecarlo->respostaErro(), fxMontecarlo->qTpassos());
                //finaliza os objetos monte_carlo e funcao
                fxMontecarlo->~monte_carlo();
                fx->~Funcd();

                printf("\n Digite <ENTER> para continuar");

                printf("\n");
                getch();
                break;
            case 7: // sair
                exit(0);
            default: printf("\nDigite uma opção! \n");
        }
    }
}
