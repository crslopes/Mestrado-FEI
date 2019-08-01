#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>

class Pilha{                            // begin declaration of the class;
    public:                             // begin public section
        Pilha(int memInicial);          // constructor
        ~Pilha();                       // destructor
        int PegaTopo();                 // accessor function
        void AdicionaPilha(int valor);  // accessor function
        int RemovePilha();              // accessor function
        int Estado();                   // accessor function
        void dimensiona(int memoria);   // accessor function
    private:                            // begin private section
        int *ponteiroPilha;             // member variable
        int capacidade;                 // member variable
        int topo;                       // member variable
};

// constructor of Pilha,initialize private variable and allocate memory to ponteiroPilha
Pilha::Pilha(int memInicial){
    ponteiroPilha = (int*) malloc (memInicial * sizeof(int));
    capacidade=memInicial;
    topo=0;
}

// destructor of Pilha, free memory
Pilha::~Pilha(){
    free(ponteiroPilha);
}

// PegaTopo, Public accessor function
// returns value of top of stack
int Pilha::PegaTopo(){
    if ( topo > 0 ){
        return (ponteiroPilha[(topo-1)]);
    }
}

// AdicionaPilha, public accessor function
// Add new value in top of stack
void Pilha::AdicionaPilha(int valor){
    if( topo == capacidade ){
        printf("\nPilha cheia, aumente a memoria! \n");
        printf("\nDigite [enter] para continuar \n");
        getch();
    }else{
        ponteiroPilha[topo]=valor;
        topo++;
    }
}

// RemovePilha, public accessor function
// Delete value in top of stack
int Pilha::RemovePilha(){
    if ( topo < 1 )
            printf( "\nNao existem valores! \n" );
    else{
        topo--;
        return ponteiroPilha[topo];
    }
}

// Estado, public accessor function
// Check Pilha Status, empty, regular, full
int Pilha::Estado(){
    if (topo==0) {
        return 0; // pilha vazia
    } else if (topo >= capacidade) {
        return 2; // pilha cheia
    }
    return 1; // pilha normal
}

// dimensiona, public accessor function
// increase size of stack
void Pilha::dimensiona(int memoria){
    ponteiroPilha= (int*) realloc (ponteiroPilha, memoria * sizeof(int));
    if (ponteiroPilha==NULL) {
       free (ponteiroPilha);
       printf ("Fallha realocando memoria");
       exit (1);
    }
    capacidade=memoria;
}

int main(){
	int capacidade, valor, opcao, saida;           // variáveis de apoio
	clock_t t;
//time.h para utilizar na medida de tempo do acesso a estrutura de dados
	double time_taken;
	printf( "\nCapacidade da pilha? " );
	scanf( "%d", &capacidade );
	Pilha Pil(capacidade);                  // inicializa a pilha com número inicial de registros igual a capacidade solicitada


	while( 1 ){ /* loop infinito para gerar menu de opçoes do uso da pilha*/
		printf("\n1: Adicionar um numero a pilha\n");
		printf("2: Remover um numero da pilha\n");
		printf("3: Aumentar o tamanho da pilha\n");
		printf("4- Mostrar o topo da pilha \n");
		printf("5- Imprime toda pilha\n");
        printf("6- verificar tempos de execucao\n");
		printf("7- sair\n");
		printf("\ndigite uma opcao? ");
		scanf("%d", &opcao);
		switch (opcao){
			case 1: // Add to Stack
				printf("\nQual valor deve adicionar a Pilha? ");
				scanf("%d", &valor);
				Pil.AdicionaPilha(valor);
				break;
			case 2: //remove from stack
                    if (Pil.Estado()){
                        valor=Pil.RemovePilha();
                        printf ( "\nRemovido no Obj Pilha valor: %d\n", valor);
                    } else {
                        printf ( "\nNao existem itens para remover no Obj Pilha");
                    }
				break;
			case 3: // increase stack
                printf("\n\nDigite quantos itens quer ampliar na pilha: ");
                scanf("%d", &valor);
                capacidade = valor+capacidade;
                Pil.dimensiona(capacidade);
                printf("\nNova capacidade da Pilha: %d", capacidade);
				break;

			case 4: // mostrar o topo
			    if (Pil.Estado()>0){
                    saida=Pil.PegaTopo();
                    printf( "\nTopo do Objeto Pilha: %d\n", saida);
                }else{
                    printf( "\nNao existem valores na pilha\n" );
                }
                printf("\nDigite [enter] para continuar \n");
                getch();
				break;
			case 5: // obtem e mostra todos os itens da pilha
			    if(Pil.Estado()>0){
                    printf ( "\nPilha:|");
                    while (Pil.Estado()>0) {
                        valor=Pil.RemovePilha();
                        printf ( "%d|", valor);
                    }
                    printf ( "\n");
                }else{
                     printf ("\nA pilha esta vazia");
                }
				break;
			case 6: // testes para validação do tempo consumido pela interação com a estrutura de dados
                printf("\n\nDigite quantos elementos deseja testar: ");
                scanf("%d", &valor);
                capacidade = valor;

                for ( int j=0; j!= 101; j++){
                    Pil.~Pilha();
                    Pilha Pil((capacidade*j));
                    t = clock();
                    for( int i = 0; i != (capacidade*j); ++i ){
                        Pil.AdicionaPilha(i);
                    }
                    for( int i = 0; i != (capacidade*j); ++i ){
                        Pil.RemovePilha();
                    }
                    t = clock() -t;
                    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                    printf("%d|%f|seconds to execute \n", (capacidade*j), time_taken);
                }
                break;
            case 7: // desconstruir a pilha e sair
                Pil.~Pilha();
                exit(0);
			default: printf( "\nDigite uma opção! \n" );
		}
	}
}
