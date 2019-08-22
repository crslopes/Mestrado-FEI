#include <stdio.h>
#include <stdlib.h>
// exceptions
#include <iostream>
#include "func.h"
using namespace std;
//-------------------------------------------------------------------
//      PEL_216 2º. Semestre de 2019
//      Prof: Dr Reinaldo Bianchi
//      Aluno: Cristiano Lopes Moreira
//      RA: 119103-0
//
//      Integral Numerica
//
//-------------------------------------------------------------------
void getch(void)
{
	system("read b");
}
// Classe para Funcao f(x)=e^x herda os metodos da funcao Funcd para polimorfismo dos metodos funcao e derivada
class ex : public Funcd {
public:
	ex() :Funcd() {};										// constructor
	~ex() {};                                               // destructor
	virtual double funcao(double x);						// virtual acessor function to polymorph from Funcd
};

double ex::funcao(double x) {
	return exp(x); 
};

// Classe para Funcao f(x)=(1-x^2)^(1/2) herda os metodos da funcao Funcd para polimorfismo dos metodos funcao e derivada
class raiz_1_x2 : public Funcd {
public:
	raiz_1_x2() :Funcd() {};								// constructor
	~raiz_1_x2() {};										// destructor
	virtual double funcao(double x);						// virtual acessor function to polymorph from Funcd
	virtual double derivada(double x, int ordem, double delta);	// virtual acessor function to polymorph from Funcd
};

double raiz_1_x2::funcao(double x) {
	return sqrt(1 - pow(x, 2));
};

double raiz_1_x2::derivada(double x, int ordem, double delta) {
	double dx[4];
	if (ordem > 4) { return 0; }
	dx[0] = -1*x/(sqrt((1-pow(x,2))));
	dx[1] = -1 / (pow( (1 - pow(x, 2) )  ,(3/4) ) ) ;
	dx[2] = -3*x / (pow((1 - pow(x, 2)), (5 / 2)));
	dx[3] = -(12 * pow(x,2)+3) / (pow((1 - pow(x, 2)), (7 / 2)));
	return dx[(ordem - 1)];
};

// Classe para Funcao f(x)=e^(-x^2) herda os metodos da funcao Funcd para polimorfismo dos metodos funcao e derivada
class ex_neg2 : public Funcd {
public:
	ex_neg2() :Funcd() {};									// constructor
	~ex_neg2() {};											// destructor
	virtual double funcao(double x);						// virtual acessor function to polymorph from Funcd
};

double ex_neg2::funcao(double x) {
	return exp(-pow(x,2));
};



int main() {
	int opcao=0;									//variavel utilizada na selecao do menu
	double x0 = 0;									//variavel com o limite inferior para calculo da integral
	double x1 = 1;									//variavel com o limite superior para calculo da integral
	double erro = 1;								//valor inicial da taxa de erro aceitavel
	double integral;								//valor da integral

	ex* fex;                                        //ponteiro para objeto f(x)=e^x
	raiz_1_x2* fraiz;								//ponteiro para objeto f(x)=(1-x^2)^(1/2)
	ex_neg2* fexneg;								//ponteiro para objeto f(x)=e^(-x^2)
	Funcd* fx;										//ponteiro para objeto Funcao
	fex = new ex();                                 //inicializa objeto funcao fex
	fraiz = new raiz_1_x2();                        //inicializa objeto funcao fraiz
	fexneg = new ex_neg2();                         //inicializa objeto funcao fexneg
	


	while (1) { /* loop infinito para gerar menu */
		printf("\n---Parametros para a solucao da integral---\ntxErro: %.15lf - x0: %.2lf - valor de x1: %.2lf \n\n", erro, x0, x1);
		printf("-----------------------------------------------------------");
		printf("\n1: Entre com nova taxa de erro\n");
		printf("2: Entre com novo valor do limite inferior X0\n");
		printf("3: Entre com novo valor do limite superior X1\n");
		printf("-----------------------------------------------------------\n");
		printf("4: Calculo da integral da funcao e^x\n");
		printf("5- Calculo da integral da funcao (1 - x^2)^1/2 \n");
		printf("6- Calculo da integral da funcao e^-x^2 \n");
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
		case 4: // calcula a integral numerica da funcao  f(x)=e^x
			fx = fex;
			printf("\nintegral da funcao f(x)=e^x");
			integral = fx->rg_pmedio(x0, x1, erro);
			printf("\n Integral Regra Metodo Pontos Medios: %.5lf", integral);
			printf("\n Taxa de erro %.15lf - Passos: %d\n", fx->prtAccurate(), fx->qtPassos());
			
			integral = fx->rg_trapezio(x0, x1,erro);
			printf("\n Integral Regra Trapezoidal: %.5lf", integral);
			printf("\n Taxa de erro %.15lf - Passos: %d\n", fx->prtAccurate(), fx->qtPassos());

			integral = fx->rg_simpson(x0, x1, erro);

			printf("\n Integral Regra de Simpson %.5lf", integral);
			printf("\n Taxa de erro %.15lf - Passos: %d\n", fx->prtAccurate(), fx->qtPassos());
			
			printf("\n Digite <ENTER> para continuar");
			printf("\n");
			getch();
			break;
		case 5:// calcula a integral numerica da funcao f(x)=(1-x^2)^(1/2)
			fx = fraiz;
			printf("\nintegral da funcao f(x)=(1-x^2)^(1/2)");
			integral = fx->rg_pmedio(x0, x1, erro);
			printf("\n Integral Regra Metodo Pontos Medios: %.5lf", integral);
			printf("\n Taxa de erro %.15lf - Passos: %d\n", fx->prtAccurate(), fx->qtPassos());

			integral = fx->rg_trapezio(x0, x1, erro);
			printf("\n Integral Regra Trapezoidal: %.5lf", integral);
			printf("\n Taxa de erro %.15lf - Passos: %d\n", fx->prtAccurate(), fx->qtPassos());

			integral = fx->rg_simpson(x0, x1, erro);

			printf("\n Integral Regra de Simpson %.5lf", integral);
			printf("\n Taxa de erro %.15lf - Passos: %d\n", fx->prtAccurate(), fx->qtPassos());

			printf("\n Digite <ENTER> para continuar");
			printf("\n");
			getch();
			break;
		case 6: // calcula a integral numerica da funcao f(x)=e^(-x^2)
			fx = fexneg;
			printf("\nintegral da funcao f(x)=e^(-x^2)");
			integral = fx->rg_pmedio(x0, x1, erro);
			printf("\n Integral Regra Metodo Pontos Medios: %.5lf", integral);
			printf("\n Taxa de erro %.15lf - Passos: %d\n", fx->prtAccurate(), fx->qtPassos());

			integral = fx->rg_trapezio(x0, x1, erro);
			printf("\n Integral Regra Trapezoidal: %.5lf", integral);
			printf("\n Taxa de erro %.15lf - Passos: %d\n", fx->prtAccurate(), fx->qtPassos());

			integral = fx->rg_simpson(x0, x1, erro);

			printf("\n Integral Regra de Simpson %.5lf", integral);
			printf("\n Taxa de erro %.15lf - Passos: %d\n", fx->prtAccurate(), fx->qtPassos());

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
