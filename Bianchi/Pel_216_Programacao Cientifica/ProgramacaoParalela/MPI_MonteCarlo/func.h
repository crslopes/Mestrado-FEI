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
    virtual double funcao(double * x);                                               // virtual acessor function to polymorph with other functions
    virtual double funcao(double x, double y);                                                // virtual acessor function to polymorph with other functions
    virtual double funcao(double x, double y, double z);                                                // virtual acessor function to polymorph with other functions
    virtual double derivada(double x, int ordem, double delta);                     // virtual acessor function to polymorph with other functions
};

//Agent constructor
Funcd::Funcd() {

};

// destructor
Funcd::~Funcd() {
    printf("");
}
//acessor virtual function
//funcao virtual utilizada para polimorfismo de objeto funcao
double Funcd::funcao(double x) {
    printf("\n double");
    return 1;
};
double Funcd::funcao(double * x) {
    printf("\n ponteiro");
    return 1;
};
double Funcd::funcao(double x, double y) {

    return 1;
};
double Funcd::funcao(double x, double y, double z) {

    return 1;
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
