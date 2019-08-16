#include <iostream>
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
class Funcd {												// begin declaration of the class;
public:														// begin public section
	Funcd();												// constructor
	~Funcd();                                               // destructor
	virtual double funcao(double x);						// virtual acessor function to polymorph with other functions
	virtual double derivada(double x);						// virtual acessor function to polymorph with other functions
};

//Agent constructor
Funcd::Funcd() {
};

// destructor
Funcd::~Funcd() {
	printf("\nFinalizando Funcao\n");
}

double Funcd::funcao(double x) {
	return x;
};

double Funcd::derivada(double x) {
	return 1;
};
#pragma once
