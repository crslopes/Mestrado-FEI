#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
// exceptions
#include <iostream>
#include "AG_Puzzle_lib.h"

using namespace std;


//-------------------------------------------------------------------
//      PEL_216 1º. Semestre de 2019
//      Prof: Dr Reinaldo Bianchi
//      Aluno: Cristiano Lopes Moreira
//      RA: 119103-0
//
//      Relatorio 3: Exercicio - Problema das 8 Pecas (DFS e BFS)
//      Relatorio 4: Exercicio - Problema das 8 Pecas (HC  e A*)
//-------------------------------------------------------------------

int main(){
	int problema, valor, maxEstados, opcao, TotalAmostras, i;           // variáveis de apoio
	clock_t t;
//time.h para utilizar na medida de tempo do acesso a estrutura de dados
	double time_taken;
// 416328795 - problema do Dr Reinaldo Bianchi
// 946175238 - problema 02
// 892731645 - problema 03
// 964283571 - problema 04
// 964178352 - problema 05
// 754138296 - problema 06
// 923156478 - problema 07
// 672185394 - problema 08
// 235978146 - problema 09
// 235178496 - problema 10

    problema=416328795; // problema inicial entregue pelo Bianchi
    AGENTE *puzzle8;
    AG_DFS *DFS;
    AG_BFS *BFS;
    AG_HC *HC;
    AG_A *A;
    float tempos[4][40];

    //base_amostras = new unitMem<int>;
    unitMem<int> *base_amostras;
    AG_ESTADOS *ESTADOS; // possiveis estados para uso em estatistica


    printf( "\nProblema das 8 Pecas " );
    printf( "\nProblema Inicial \n| 4 | 1 | 6 |\n| 3 | 2 | 8 |\n| 7 | - | 5 |\n\n" );

	while( 1 ){ /* loop infinito para gerar menu de opçoes do uso da pilha*/
		printf("\n1: Puzzle 8 Solucao com Busca em Largura (BFS)\n");
		printf("2: Puzzle 8 Solucao com Busca em Profundidade (DFS)\n");
		printf("3: Puzzle 8 Solucao com Subida de Encosta\n");
		printf("4- Puzzle 8 Solucao com A*\n");
		printf("5- Entrar com novo Problema do Puzzle 8\n");
        printf("6- verificar tempos de execucao\n");
		printf("7- sair\n");
		printf("\ndigite uma opcao? ");
		scanf("%d", &opcao);
		switch (opcao){
			case 1: // Resolucao com BFS - Busca em Largura
			    printf( "\nInicializa Agente BFS Busca em Largura" );
			    t = clock();
                BFS=new AG_BFS(1);
//---------------Polimorfismo----------------------
//    Polimorfismo com Metodo Virtual puzzle8 obtem metodos do BFS
			    puzzle8=BFS;
			    try{
                    puzzle8->expanding_node(problema);
                }
                catch (int param) { cout << "int exception"; }
                catch (char param) { cout << "char exception"; }
                t = clock() -t;
                time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                printf("|%f|seconds to execute \n",  time_taken);
                try{
                    puzzle8->PrintPath();
                }
                catch (int param) { cout << "int exception"; }
                catch (char param) { cout << "char exception"; }
                puzzle8->~AGENTE();
                break;
			case 2: // Resolucao com DFS - Busca em Largura
                printf( "\nInicializa Agente DFS Busca em Profundidade" );
                t = clock();
                DFS=new AG_DFS(1);
//---------------Polimorfismo----------------------
//    Polimorfismo com Metodo Virtual puzzle8 obtem metodos do DFS
                puzzle8=DFS;
                try{
                    puzzle8->expanding_node(problema);
                }
                catch (int param) { cout << "int exception"; }
                catch (char param) { cout << "char exception"; }
                t = clock() -t;
                time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                printf("|%f|seconds to execute \n",  time_taken);
                try{
                    puzzle8->PrintPath();
                }
                catch (int param) { cout << "int exception"; }
                catch (char param) { cout << "char exception"; }
                puzzle8->~AGENTE();
				break;
			case 3: // Resolucao com Subida de Encosta
                printf( "\nInicializa Agente Subida de Encosta" );
			    t = clock();
			    HC=new AG_HC(1);
//---------------Polimorfismo----------------------
//    Polimorfismo com Metodo Virtual puzzle8 obtem metodos do HC
                puzzle8=HC;
                try{
                    puzzle8->expanding_node(problema);
                }
                catch (int param) { cout << "int exception"; }
                catch (char param) { cout << "char exception"; }
                t = clock() -t;
                time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                printf("|%f|seconds to execute \n",  time_taken);
                try{
                    puzzle8->PrintPath();
                }
                catch (int param) { cout << "int exception"; }
                catch (char param) { cout << "char exception"; }
                puzzle8->~AGENTE();
				break;
			case 4: // Resolucao com A*.
			    printf( "\nInicializa Agente A*" );
			    t = clock();
			    A=new AG_A(1);
//---------------Polimorfismo----------------------
//    Polimorfismo com Metodo Virtual puzzle8 obtem metodos do DFS
                puzzle8=A;
                try{
                    puzzle8->expanding_node(problema);
                }
                catch (int param) { cout << "int exception"; }
                catch (char param) { cout << "char exception"; }
                t = clock() -t;
                time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                printf("|%f|seconds to execute \n",  time_taken);
                try{
                    puzzle8->PrintPath();
                }
                catch (int param) { cout << "int exception"; }
                catch (char param) { cout << "char exception"; }
                puzzle8->~AGENTE();
				break;
			case 5: // Entrar com novo Problema do Puzzle 8
				printf("\nO 9 representa a Chave que move\nQuais Numeros do Problema?\n");
				scanf("%d", &problema);
				break;

			case 6: // testes para validação do tempo consumido pela interação com a estrutura de dados
                printf("\n\nDigite quantos elementos deseja testar: ");
                scanf("%d", &TotalAmostras);
                for (valor=0;valor<TotalAmostras;valor++){
                    printf( "\nInicializa Agente BFS Busca em Largura" );
                    t = clock();
                    BFS=new AG_BFS(1);
    //---------------Polimorfismo----------------------
    //    Polimorfismo com Metodo Virtual puzzle8 obtem metodos do BFS
                    puzzle8=BFS;
                    try{
                        puzzle8->expanding_node(problema);
                    }
                    catch (int param) { cout << "int exception"; }
                    catch (char param) { cout << "char exception"; }
                    t = clock() -t;
                    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                    tempos[0][valor]=time_taken;
                    printf("|%f|seconds to execute \n",  time_taken);
                    puzzle8->~AGENTE();


                    printf( "\nInicializa Agente DFS Busca em Profundidade" );
                    t = clock();
                    DFS=new AG_DFS(1);
    //---------------Polimorfismo----------------------
    //    Polimorfismo com Metodo Virtual puzzle8 obtem metodos do DFS
                    puzzle8=DFS;
                    try{
                        puzzle8->expanding_node(problema);
                    }
                    catch (int param) { cout << "int exception"; }
                    catch (char param) { cout << "char exception"; }
                    t = clock() -t;
                    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                    tempos[1][valor]=time_taken;
                    printf("|%f|seconds to execute \n",  time_taken);
                    puzzle8->~AGENTE();


                    printf( "\nInicializa Agente Subida de Encosta" );
                    t = clock();
                    HC=new AG_HC(1);
    //---------------Polimorfismo----------------------
    //    Polimorfismo com Metodo Virtual puzzle8 obtem metodos do HC
                    puzzle8=HC;
                    try{
                        puzzle8->expanding_node(problema);
                    }
                    catch (int param) { cout << "int exception"; }
                    catch (char param) { cout << "char exception"; }
                    t = clock() -t;
                    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                    tempos[2][valor]=time_taken;
                    printf("|%f|seconds to execute \n",  time_taken);
                    puzzle8->~AGENTE();

                    printf( "\nInicializa Agente A*" );
                    t = clock();
                    A=new AG_A(1);
    //---------------Polimorfismo----------------------
    //    Polimorfismo com Metodo Virtual puzzle8 obtem metodos do DFS
                    puzzle8=A;
                    try{
                        puzzle8->expanding_node(problema);
                    }
                    catch (int param) { cout << "int exception"; }
                    catch (char param) { cout << "char exception"; }
                    t = clock() -t;
                    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                    tempos[3][valor]=time_taken;
                    printf("|%f|seconds to execute \n",  time_taken);
                    puzzle8->~AGENTE();

                }

                tempos[0][TotalAmostras]=0;
                tempos[1][TotalAmostras]=0;
                tempos[2][TotalAmostras]=0;
                tempos[3][TotalAmostras]=0;

                for (valor=0;valor<TotalAmostras;valor++){
                        tempos[0][TotalAmostras]=tempos[0][TotalAmostras]+tempos[0][valor]/TotalAmostras;
                        tempos[1][TotalAmostras]=tempos[1][TotalAmostras]+tempos[1][valor]/TotalAmostras;
                        tempos[2][TotalAmostras]=tempos[2][TotalAmostras]+tempos[2][valor]/TotalAmostras;
                        tempos[3][TotalAmostras]=tempos[3][TotalAmostras]+tempos[3][valor]/TotalAmostras;
                }

                printf( "\nInicializa Agente BFS Busca em Largura %d amostras - tempo: %f", TotalAmostras, tempos[0][TotalAmostras] );
                printf( "\nInicializa Agente DFS Busca em Profundidade %d amostras - tempo: %f", TotalAmostras, tempos[1][TotalAmostras] );
                printf( "\nInicializa Agente Subida de Encosta %d amostras - tempo: %f", TotalAmostras, tempos[2][TotalAmostras] );
                printf( "\nInicializa Agente A* %d amostras - tempo: %f", TotalAmostras, tempos[3][TotalAmostras] );

                getch();

                break;

            case 7: // desconstruir objetos e sair
                exit(0);
			default: printf( "\nDigite uma opção! \n" );
		}
	}


    getch();
    exit(0);

}
