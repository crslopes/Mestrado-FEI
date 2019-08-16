#include <iostream>
// exceptions
#include "func.h"
//-------------------------------------------------------------------
//      PEL_216 2º. Semestre de 2019
//      Prof: Dr Reinaldo Bianchi
//      Aluno: Cristiano Lopes Moreira
//      RA: 119103-0
//
//      Descida de Gradiente
//
//-------------------------------------------------------------------

class gradiente {
public:
	gradiente(double txError, double txAprendizado, class Funcd* fx);				//constructor
	~gradiente();																	//desctuctor
	void calc(double x0);															//acessor function
	int qTpassos();																	//acessor function
	double inflexao();																//acessor function
	double funcFx();																//acessor function
private:																			//inicio da secao privada
	int passos;																		//member variable - conta número de passos para o resultado
	int maxPassos;																	//member variable - maximo de loops permitidos para evitar loop eterno
	double erro;																	//member variable - taxa de erro aceitável
	double aprendizado;																//member variable - taxa de aprendizado da funcao
	double vlInflexao;																//member variable - ponto x da inflexao
	double vlFxInflexao;															//member variable - valor da inflexao
	class Funcd* pointFx;															//member variable - ponteiro para a funcao

};
// constructor
// inicializa o objeto gradiente com os valores da taxa de erro; taxa de aprendizagem e a funcao que se deseja encontrar o minimo
gradiente::gradiente(double txError, double txAprendizado, class Funcd* fx) {
	passos = 0;
	maxPassos = 500001;
	erro = txError;
	aprendizado = txAprendizado;
	vlInflexao = 0;
	vlFxInflexao = 0;
	pointFx = fx;
}
// destructor
// finaliza o objeto
gradiente::~gradiente() {
	printf_s("\nfinaliza gradiente\n");
}
// acessor function
// recebe o valor do ponto inicial de x0 e inicia as interacoes para encontrar o ponto de minimo
void gradiente::calc(double x0) {
	double deriv;
	// calcula a derivada da funcao no ponto inicial, x0, para verificar se esta proximo da taxa de erro
	deriv = this->pointFx->derivada(x0);
	this->vlInflexao = x0;
	this->passos = 0;
	// realiza interacoes ateh que o modulo a taxa de variacao no ponto seja menor que a taxa de erro aceitavel
	while (fabs(deriv) > this->erro) {
		// a cada interacao calcula novo valor da derivada de 'x' a ser utilizada para calcular o novo 'x_i'
		deriv = this->pointFx->derivada(this->vlInflexao);
		// aproxima novo 'x' do ponto minimo, na direcao do gradiente, com passos do tamanho da variacao (derivada no ponto) ajustado pela taxa de aprendizado
		this->vlInflexao = this->vlInflexao- aprendizado * deriv;
		// obtem nova taxa de variacao, derivada no novo ponto, para o valor do novo ponteiro de 'x' 
		deriv = this->pointFx->derivada(this->vlInflexao);
		this->passos++;
		if (this->passos > this->maxPassos) { break; }
	}
	this->vlFxInflexao = this->pointFx->funcao(this->vlInflexao);
}
// acessor function
// retorna a quantidade de passos necessarios para encontrar o ponto de minimo da funcao
int gradiente::qTpassos() {
	return this->passos;
}
// acessor function
// retorna o ponto 'x' de minimo da funcao f(x)
double gradiente::inflexao() {
	return this->vlInflexao;
}
// acessor function
// retorna o valor da funcao f(x) no ponto de minimo da funcao
double gradiente::funcFx() {
	return this->vlFxInflexao;
}

#pragma once
