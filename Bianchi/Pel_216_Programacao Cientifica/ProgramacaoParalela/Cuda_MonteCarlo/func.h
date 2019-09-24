#include <iostream>
#include<math.h>

// exceptions
using namespace std;
//-------------------------------------------------------------------
//      PEL_216 2º. Semestre de 2019
//      Prof: Dr Reinaldo Bianchi
//      Aluno: Cristiano Lopes Moreira
//      RA: 119103-0
//
//      Funcao Base
//
//-------------------------------------------------------------------

// Classe para Funcoes, define estrutura para polimorfismo dos metodos funcao e derivada
class Funcd {																		// begin declaration of the class;
public:																				// begin public section
	Funcd();																		// constructor
	~Funcd();																		// destructor
	virtual double funcao(double x);                                                // virtual acessor function to polymorph with other functions
	virtual double derivada(double x, int ordem, double delta);                     // virtual acessor function to polymorph with other functions
	double rg_pmedio(double a, double b, double txError);                           // acessor functio
	double rg_trapezio(double a, double b, double txError);                         // acessor function
	double rg_simpson(double a, double b, double txError);                          // acessor function
	double prtAccurate();															// acessor function
	int qtPassos() { return this->passos; };										// acessor function
protected:
	int fat(int x);																	// private function
	double txAccurate;																// member variable
	int passos;																		// member variable 
};

//Agent constructor
Funcd::Funcd() {
	txAccurate = 0;
	passos = 0;
};

// destructor
Funcd::~Funcd() {
	printf("\nFinalizando Funcao\n");
}
//acessor virtual function
//funcao virtual utilizada para polimorfismo de objeto funcao
double Funcd::funcao(double x) {
	
	return 1;
};
//acessor function
//retorna a taxa de erro do calculo
double Funcd::prtAccurate() {
	return this->txAccurate;
};
//private function
//realiza calculo de fatorial
int Funcd::fat(int x) {
	if (x==0 || x==1)
	{
		return 1;
	}else{
		return (x * this->fat(x - 1));
	}
};

//acessor virtual function
//recebe os pontos da funcao, a ordem da derivada, e retorna a derivada numerica da funcao
double Funcd::derivada(double x, int ordem, double delta) {
	double fx[5];
	double dx[5];
	fx[0]= this->funcao(x);
	fx[1]= this->funcao(x + delta);
	fx[2] = this->funcao(x + 2 * delta);
	fx[3] = this->funcao(x + 3 * delta);
	fx[4] = this->funcao(x + 4 * delta);
	dx[0] = (fx[1] - fx[0]) / delta;
	dx[1] = (fx[2] - 2* fx[1] + fx[0]) / pow(delta,2);
	dx[2] = (fx[3] - 3 * fx[2] + 3* fx[1] - fx[0]) / pow(delta, 3);
	dx[3] = (fx[4] - 4 * fx[3] + 6* fx[2] -4 * fx[1] + fx[0]) / pow(delta, 4);
	return dx[(ordem - 1)];
};
//acessor function
//recebe os limites e taxa de error para calculo das derivada da funcao, pelo metodo pontos medios, carregada pelo objeto principal Funcd
double Funcd::rg_pmedio(double a, double b, double txError) {
	double stepSize = (b - a);
	double step = 0;
	double integrateResult = (b - a) * this->funcao((a + b) / 2);
	this->txAccurate = pow((b - a),3)/24 *  this->derivada(a, 2, (b - a));
	this->passos = 1;
	while (fabs(this->txAccurate)>=txError)
	{
		stepSize = stepSize / 2;
		this->txAccurate = 0;
		integrateResult = 0;
		step = a;
		while (step < b)
		{
			integrateResult = integrateResult + (stepSize) * this->funcao((step + (step+stepSize)) / 2);
			this->txAccurate = this->txAccurate + pow((stepSize), 3) / 24 * this->derivada(a, 2, (stepSize));
			this->passos++;
			step = step + stepSize;
		}
	}
	return integrateResult;
};
//acessor function
//recebe os limites e taxa de error para calculo das derivada da funcao, pelo metodo trapezio, carregada pelo objeto principal Funcd
double Funcd::rg_trapezio(double a, double b, double txError) {
	double stepSize = (b - a);
	double step = 0;
	double integrateResult = (b - a) * (this->funcao(a) + this->funcao(b)) / 2;
	this->txAccurate = -1*pow((b - a), 3) / 12 * this->derivada(a, 2, (b - a));
	this->passos = 1;
	while (fabs(this->txAccurate) >= txError)
	{
		stepSize = stepSize / 2;
		this->txAccurate = 0;
		integrateResult = 0;
		step = a;
		while (step < b)
		{
			integrateResult = integrateResult + (stepSize) * (this->funcao(step) + this->funcao((step+ stepSize))) / 2;
			this->txAccurate = this->txAccurate + -1*pow((stepSize), 3) / 12 * this->derivada(a, 2, (stepSize));
			this->passos++;
			step = step + stepSize;
		}
	}
	return integrateResult;
};
//acessor function
//recebe os limites e taxa de error para calculo das derivada da funcao, pelo metodo de simpson, carregada pelo objeto principal Funcd
double Funcd::rg_simpson(double a, double b, double txError) {
	double stepSize = (b - a);
	double step = 0;
	double integrateResult = (b - a) * (this->funcao(a) + 4 * this->funcao((a + b) / 2) + this->funcao(b)) / 6;
	this->txAccurate = -1* pow((b - a), 5) / 2880 * this->derivada(a, 4, (b - a));
	this->passos = 1;
	while (fabs(this->txAccurate) >= txError)
	{
		stepSize = stepSize / 2;
		this->txAccurate = 0;
		integrateResult = 0;
		step = a;
		while (step < b)
		{
			integrateResult = integrateResult + (stepSize) * (this->funcao(step) + 4 * this->funcao((step + step+stepSize) / 2) + this->funcao(step + stepSize)) / 6;
			this->txAccurate = this->txAccurate + -1* pow((stepSize), 5) / 2880 * this->derivada(a, 4, (stepSize));
			this->passos++;
			step = step + stepSize;
		}
	}
	return integrateResult;
};

#pragma once
