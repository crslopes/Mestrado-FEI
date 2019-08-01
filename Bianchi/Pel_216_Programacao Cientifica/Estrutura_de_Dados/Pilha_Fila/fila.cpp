#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>

class Fila{                            // begin declaration of the class;
    public:                            // begin public section
        Fila(int memInicial);          // constructor
        ~Fila();                       // destructor
        int PegaSaida();               // accessor function
        void AdicionaFila(int valor);  // accessor function
        int RemoveFila();              // accessor function
        int Estado();                  // accessor function
        void dimensiona(int memoria);  // accessor function
    private:                           // begin private section
        int *ponteiroFila;             // member variable
        int idxAdd;                    // member variable
        int idxRem;                    // member variable
        int capacidade;                // member variable
        int quantidade;                // member variable
};

// constructor of Fila,initialize private variable and allocate memory to ponteiroFila
Fila::Fila(int memInicial){
    ponteiroFila = (int*) malloc (memInicial * sizeof(int));
    idxAdd=0;
    idxRem=0;
    quantidade=0;
    capacidade=memInicial;
}

// destructor of Fila, free memory
Fila::~Fila(){
    free(ponteiroFila);
}

// PegaSaida, Public accessor function
// returns value of out of queue
int Fila::PegaSaida(){
    if (Estado()==0){
        printf( "\nA lista esta fazia! \n" );
        printf("\nDigite [enter] para continuar \n");
        getch();
    }else{
        return(ponteiroFila[idxRem]);
    }
}

// AdicionaFila, public accessor function
// Add new value in queue
void Fila::AdicionaFila(int valor){

    if ( quantidade == capacidade ){
        printf("\nFila cheia, aumente a memoria! o Valor %d nao foi adicionado\n", valor);
        printf("\nDigite [enter] para continuar \n");
        getch();
    }else{
        if (idxAdd==(capacidade)){
            idxAdd=0;
        }
        ponteiroFila[idxAdd]=valor;
        quantidade++;
        idxAdd++;
    }

}

// RemoveFila, public accessor function
// Delete value in queue
int Fila::RemoveFila(){
    int idxtmp=idxRem;
    if (quantidade==0){
        printf( "\nNao existem valores para remover! \n" );
        printf("\nDigite [enter] para continuar \n");
        getch();
    }else {
        if (idxRem==(capacidade-1)){
            idxRem=0;
        }else{
            idxRem++;
        }
        quantidade--;
        if (quantidade==0){
            idxAdd=0;
            idxRem=0;
        }
        return(ponteiroFila[idxtmp]);
    }
}


// Estado, public accessor function
// Check Fila Status, empty, regular, full
int Fila::Estado(){
    if (quantidade==0) {
        return 0; // fila vazio
    } else if (quantidade >= capacidade) {
        return 2; // fila cheia
    }
    return 1; // fila normal
}

// dimensiona, public accessor function
// increase size of queue
void Fila::dimensiona(int memoria){
    ponteiroFila= (int*) realloc (ponteiroFila, memoria * sizeof(int));
    if (ponteiroFila==NULL) {
       free (ponteiroFila);
       printf ("Fallha realocando memoria");
       exit (1);
    }
    capacidade=memoria;
}

int main(){

	int capacidade, valor, opcao, outFila;           // variáveis de apoio
//time.h para utilizar na medida de tempo do acesso a estrutura de dados
	clock_t t;
	double time_taken;

	printf( "\nCapacidade da Fila? " );
	scanf( "%d", &capacidade );
	Fila Fil(capacidade);                  // inicializa a fila com número inicial de registros igual a capacidade solicitada



	while( 1 ){ /* loop infinito para gerar menu de opçoes do uso da fila*/
		printf("\n1: Adicionar um numero a Fila\n");
		printf("2: Remover um numero da Fila\n");
		printf("3: Aumentar o tamanho da Fila\n");
		printf("4- Mostrar o saida da Fila \n");
        printf("5- Imprimir toda a Fila\n");
		printf("6- verificar tempos de execucao\n");
		printf("7- sair\n");
		printf("\ndigite uma opcao? ");
		scanf("%d", &opcao);

		switch (opcao){
			case 1: // Add to queue
					printf("\nQual valor deve adicionar a Fila? ");
					scanf("%d", &valor);
					Fil.AdicionaFila(valor);
				break;
			case 2: //remove from queue
                    if(Fil.Estado()>0){
                        outFila=Fil.RemoveFila();
                        printf ( "\nRemovido no Obj Fila valor: %d\n", outFila);
					}else{
                        printf ( "\nNao existem itens para remover no Obj Fila\n");
                    }
				break;
			case 3:// increase queue size
                printf("\n\nDigite quantos itens quer ampliar na Fila: ");
                scanf("%d", &valor);
                capacidade = valor+capacidade;
                Fil.dimensiona(capacidade);
                printf("\nNova capacidade da Filha: %d", capacidade);
				break;
			case 4: // show exit of queue
                    outFila=Fil.PegaSaida();
                    if (Fil.Estado()>0){
                        printf( "\nSaida do Objeto Fila: %d", outFila);
                        printf("\nDigite [enter] para continuar \n");
                        getch();
                    }
				break;
			case 5:// obtem e mostra todos os itens da fila
			    if(Fil.Estado()>0){
                    printf ( "\nFila:|");
                    while (Fil.Estado()) {
                        outFila=Fil.RemoveFila();
                        printf ( "%d|", outFila);
                    }
                    printf ( "\n");
                }else{
                     printf ("\nA fila esta vazia");
                }
				break;
			case 6: // testes para validação do tempo consumido pela interação com a estrutura de dados
                printf("\n\nDigite quantos elementos deseja testar: ");
                scanf("%d", &valor);
                capacidade = valor;

                for ( int j=0; j!= 101; j++){
                    Fil.~Fila();
                    Fila Fil((capacidade*j));
                    t = clock();
                    for( int i = 0; i != (capacidade*j); ++i ){
                        Fil.AdicionaFila(i);
                    }
                    for( int i = 0; i != (capacidade*j); ++i ){
                        Fil.RemoveFila();
                    }
                    t = clock() -t;
                    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                    printf("%d|%f|seconds to execute \n", (capacidade*j), time_taken);
                }
                break;
			case 7: // desconstruir a fila e sair
			    Fil.~Fila();
				exit(0);
			default: printf( "\nDigite uma opção! \n" );
		}
	}
}

