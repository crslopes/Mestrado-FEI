#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
// exceptions
#include <iostream>
#include "gradiente.h"
using namespace std;
//-------------------------------------------------------------------
//      PEL_216 2º. Semestre de 2019
//      Prof: Dr Reinaldo Bianchi
//      Aluno: Cristiano Lopes Moreira
//      RA: 119103-0
//
//      Descida de Gradiente
//
//-------------------------------------------------------------------

// Classe para Funcao f(x)=x^2, herda os metodos da funcao Funcd para polimorfismo dos metodos funcao e derivada
class X2 : public Funcd {
public:
	X2() :Funcd() {};										// constructor
	~X2() {};                                               // destructor
	virtual double funcao(double x);						// virtual acessor function to polymorph from Funcd
	virtual double derivada(double x);						// virtual acessor function to polymorph from Funcd
};

double X2::funcao(double x) {
	return pow(x, 2);
};

double X2::derivada(double x) {
	return 2 * x;
};
// Classe para Funcao f(x)=x^3-2x^2+2, herda os metodos da funcao Funcd para polimorfismo dos metodos funcao e derivada
class X3 : public Funcd {
public:
	X3() :Funcd() {};										// constructor
	~X3(){};												// destructor
	virtual double funcao(double x);						// virtual acessor function to polymorph from Funcd
	virtual double derivada(double x);						// virtual acessor function to polymorph from Funcd
};

double X3::funcao(double x) {
	return (pow(x, 3) - 2 * pow(x, 2) + 2);
};

double X3::derivada(double x) {
	return 3 * pow(x, 2) - 4 * x;
};


int main() {
	int opcao = 0;						//variavel utilizada na selecao do menj
	double x0 = 2;						//variavel com o ponto de partida das busca par ao minimo da funcao
	double erro = 0.0000001;			//valor inicial da taxa de erro aceitavel 
	double aprendizado = 0.1;			//valor inicial da taxa de aprendizado
	double varApdr = 0.1;				//steps para variacao da taxa de aprendizado

	X2 *fX2;							//ponteiro para objeto f(x)=x^2
	X3* fX3;							//ponteiro para objeto f(x)=x^3-2x^2+2
	fX2 = new X2();						//inicializa objeto funcao Fx2
	fX3 = new X3();						//inicializa objeto funcao Fx3
	gradiente* Grx;						//ponteiro para objeto gradiente de x



	while (1) { /* loop infinito para gerar menu */
		printf("\n\n\n---Parametros para a solucao do problema---\ntxErro: %.7lf - txAprendizado: %.2lf - valor de x0: %.3lf\n\n", erro, aprendizado, x0);
		printf("-----------------------------------------------------------");
		printf("\n1: Entre com nova taxa de enrro\n");
		printf("2: Entre com nova taxa de aprendizagem\n");
		printf("3: Entre com novo valor para X0\n");
		printf("-----------------------------------------------------------\n");
		printf("4: Calculo do ponto de inferencia da funcao X^2\n");
		printf("5- Calculo do ponto de inferencia da funcao X^3 -2*X^2 +2 \n");
		printf("6- Variacao da taxa de aprendizado entre 0.1 e 1.0 \n");
		printf("\n-----------------------------------------------------------\n");
		printf("7- sair\n");
		printf("-----------------------------------------------------------");
		printf("\ndigite uma opcao? ");
		scanf_s("%d", &opcao);

		switch (opcao) {
		case 1: // Seta nota taxa erro
			printf("\nQual o valor da taxa de erro? ");
			scanf_s("%lf", &erro);
			break;
		case 2: // Seta nota taxa de aprendizado
			printf("\nQual o valor da taxa de aprendizado? ");
			scanf_s("%lf", &aprendizado);
			break;
		case 3:// Seta novo ponto inicial de busca
			printf("\nQual o valor do X0? ");
			scanf_s("%lf", &x0);

			break;
		case 4: // calcula o gradiente e ponto de minimo da funcao  x^2
			//inicializa o objeto gradiente de 'x' com a taxa de erro, taxa de aprendizado e funcao fx2
			Grx = new gradiente(erro, aprendizado, fX2);
			try {
			// chama o metodo de calculo do ponto de minimo pelo objeto gradiente de 'x'
				Grx->calc(x0);
			}
			catch (int) { cout << "int exception"; }
			catch (char) { cout << "char exception"; }
			try {
				// chama o metodo para retornar os valores resultados das interacoes realizadas com o metodo calc
				printf_s("\n f(x) = x^2 total de passos: %d - ponto de inflexao: %.5lf - valor da funcao na inflexao:%.5lf", Grx->qTpassos(), Grx->inflexao(), Grx->funcFx());
			}
			catch (int) { cout << "int exception"; }
			catch (char) { cout << "char exception"; }
			try {
				// finaliza o objeto gradiente
				Grx->~gradiente();
			}
			catch (int) { cout << "int exception"; }
			catch (char) { cout << "char exception"; }
			printf("\n\n<ENTER> para retornar.\n\n");
			opcao=_getch();
			break;
		case 5:// calcula o gradiente e ponto de minimo da funcao  x^3 - 2 * x^2 +2
			//inicializa o objeto gradiente de 'x' com a taxa de erro, taxa de aprendizado e funcao fx3
			Grx = new gradiente(erro, aprendizado, fX3);
			try {
				// chama o metodo de calculo do ponto de minimo pelo objeto gradiente de 'x'
				Grx->calc(x0);
			}
			catch (int) { cout << "int exception"; }
			catch (char) { cout << "char exception"; }
			try {
				// chama o metodo para retornar os valores resultados das interacoes realizadas com o metodo calc
				printf_s("\n f(x) = x^3 - 2 * x^2 +2 total de passos: %d - ponto de inflexao: %.5lf - valor da funcao na inflexao:%.5lf", Grx->qTpassos(), Grx->inflexao(), Grx->funcFx());
			}
			catch (int) { cout << "int exception"; }
			catch (char) { cout << "char exception"; }
			try {
				// finaliza o objeto gradiente
				Grx->~gradiente();
			}
			catch (int) { cout << "int exception"; }
			catch (char) { cout << "char exception"; }
			printf("\n\n<ENTER> para retornar.\n\n");
			opcao = _getch();
			break;
			
		case 6: // realiza interacoes alterando o valor da taxa de aprendizado

			printf_s("\n f(x) = x^2\n");
			//altera a taxa de aprendizado entre 0.1 e 1 e obtem valores de passos e pontos de inflexao para cada taxa
			for (varApdr = 0.1; varApdr < 1.0; varApdr = varApdr + 0.1) {
				//inicializa o objeto gradiente de 'x' com a taxa de erro, taxa de aprendizado e funcao fx2
				Grx = new gradiente(erro, varApdr, fX2);
				try {
					// chama o metodo para retornar os valores resultados das interacoes realizadas com o metodo calc
					Grx->calc(x0);
				}
				catch (int) { cout << "int exception"; }
				catch (char) { cout << "char exception"; }
				try {
					// chama o metodo para retornar os valores resultados das interacoes realizadas com o metodo calc
					printf_s("\n Aprendizado : %.1lf - passos: %d - ponto de inflexao: %.5lf - valor da funcao na inflexao:%.5lf", varApdr, Grx->qTpassos(), Grx->inflexao(), Grx->funcFx());
				}
				catch (int) { cout << "int exception"; }
				catch (char) { cout << "char exception"; }
				try {
					// finaliza o objeto gradiente
					Grx->~gradiente();
				}
				catch (int) { cout << "int exception"; }
				catch (char) { cout << "char exception"; }
			}

			printf_s("\n\n\n f(x) = x^3 - 2 * x^2 +2\n");
			//altera a taxa de aprendizado entre 0.1 e 1 e obtem valores de passos e pontos de inflexao para cada taxa
			for (varApdr = 0.1; varApdr < 1.0; varApdr = varApdr + 0.1) {
				//inicializa o objeto gradiente de 'x' com a taxa de erro, taxa de aprendizado e funcao fx3
				Grx = new gradiente(erro, varApdr, fX3);
				try {
					// chama o metodo para retornar os valores resultados das interacoes realizadas com o metodo calc
					Grx->calc(x0);
				}
				catch (int) { cout << "int exception"; }
				catch (char) { cout << "char exception"; }
				try {
					// chama o metodo para retornar os valores resultados das interacoes realizadas com o metodo calc
					printf_s("\n Aprendizado : %.1lf - passos: %d - ponto de inflexao: %.5lf - valor da funcao na inflexao:%.5lf", varApdr, Grx->qTpassos(), Grx->inflexao(), Grx->funcFx());
				}
				catch (int) { cout << "int exception"; }
				catch (char) { cout << "char exception"; }
				try {
					// finaliza o objeto gradiente
					Grx->~gradiente();
				}
				catch (int) { cout << "int exception"; }
				catch (char) { cout << "char exception"; }
			}
			
			break;
		case 7: // sair
			exit(0);
		default: printf("\nDigite uma opção! \n");
		}
	}
}