#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits>
#include <cuda.h>
#include <curand_kernel.h>
#include <omp.h> // adiciona biblioteca do Open MP

using namespace std;
//-------------------------------------------------------------------
//      PEL_216 2º. Semestre de 2019
//      Prof: Dr Reinaldo Bianchi
//      Aluno: Cristiano Lopes Moreira
//      RA: 119103-0
//
//      Integral Numerica CUDA
//
//-------------------------------------------------------------------

using std::cout;
using std::endl;


const long mTHREADS = 32; // tamanho da thread


//  kernel cuda
__global__ void integralMontecarlo(long *totals, double*THREADS, long int*LOOPS) {
	// Define some shared memory: all threads in this block
	__shared__ long counter[mTHREADS];

	//ID da thread
	int tid = threadIdx.x + blockIdx.x * blockDim.x;

	// Initialize RNG
	curandState_t rng;
	curand_init(clock64(), tid, 0, &rng);

	// Initialize the counter
	counter[threadIdx.x] = 0;

	//loop
//	for (long int  i = 0; i < *LOOPS; i++) {
//
//		float x = curand_uniform(&rng); // Random x position in [0,1]
//		float y = curand_uniform(&rng); // Random y position in [0,1]
//		counter[threadIdx.x] += 1 - int(x * x + y * y); // Hit test

//	}


	for (long i = 0; i < *LOOPS; i++) {
		float x = 1.0 + 3.0 * curand_uniform(&rng); // Random x entre [1,4]
		float y = -3.0 + 7.0 * curand_uniform(&rng); // Random y entre [-3,4]
		float z = -1.0 + 2.0 * curand_uniform(&rng); // Random y entre [-1,1]
		//equaçao do toroide para contabilizar ocorrencias sorteadas no toroide
		if ((pow(z, 2) + pow(sqrt(pow(x, 2) + pow(y, 2)) - 3, 2)) <= 1 && (x >= 1) && (y >= -3)) {
			counter[threadIdx.x] += 1;
		}
	}


	// a thread 0 realiza o agrupamento dos resultados do bloco de processo
	if (threadIdx.x == 0) {
		// zera o contador dos resultados
		totals[blockIdx.x] = 0;
		// acumula os resultados
		for (int  i = 0; i < mTHREADS; i++) {
			totals[blockIdx.x] += counter[i];
		}
	}
}



int main(int argc, char** argv) {
	int numDev;
	long NBLOCKS = 5120;
	double threads = mTHREADS;
	long int loops = 5000;
	double* dTHREADS;
	long int* dLOOPS;

	cudaGetDeviceCount(&numDev);
	if (numDev < 1) {
		cout << "GPU nao encontrada\n";
		return 1;
	}

	if (argc < 2) {
		printf("Entre com o numero de interacoes e numero de cores  IntegralNumericaGPU <interacoes> <cores>\n");
		exit(1);
	}

	NBLOCKS = (double)atoi(argv[2]);

	long int tests = strtol(argv[1], NULL, 10);  //(long int)(argv[1]);

	loops = tests / NBLOCKS / mTHREADS/numDev;

	cout << "Inicializa com " << NBLOCKS << " Cuda Blocks, " << threads << " threads,  "<< tests << " interacoes e "<< numDev << " GPUs" << endl;


	long* hOut[2], * dOut[2];
	hOut[0] = new long[NBLOCKS]; // memoria do servidor
	hOut[1] = new long[NBLOCKS]; // memoria do servidor


	 
	cudaSetDevice(0);

	// alocaçao de memoria

	cudaMalloc(&dOut[0], sizeof(long) * NBLOCKS); // memoria da GPU

	cudaMalloc(&dTHREADS, sizeof(double)); // memoria da GPU
	cudaMemcpy(dTHREADS, &threads, sizeof(double), cudaMemcpyHostToDevice);
	cudaMalloc(&dLOOPS, sizeof(long int)); // memoria da GPU
	cudaMemcpy(dLOOPS, &loops, sizeof(long int), cudaMemcpyHostToDevice);

	// Launch kernel
	integralMontecarlo << <NBLOCKS, threads >> > (dOut[0], dTHREADS, dLOOPS);

	cudaSetDevice(1);
	cudaMalloc(&dOut[1], sizeof(long) * NBLOCKS); // memoria da GPU

	cudaMalloc(&dTHREADS, sizeof(double) ); // memoria da GPU
	cudaMemcpy(dTHREADS, &threads, sizeof(double), cudaMemcpyHostToDevice);
	cudaMalloc(&dLOOPS, sizeof(long int)); // memoria da GPU
	cudaMemcpy(dLOOPS, &loops, sizeof(long int), cudaMemcpyHostToDevice);

	integralMontecarlo << <NBLOCKS, threads >> > (dOut[1], dTHREADS, dLOOPS);

	// Copy back memory used on device and free
	cudaMemcpy(hOut[0], dOut[0], sizeof(long) * NBLOCKS, cudaMemcpyDeviceToHost);
	cudaMemcpy(hOut[1], dOut[1], sizeof(long) * NBLOCKS, cudaMemcpyDeviceToHost);
	cudaFree(dOut[0]);
	cudaFree(dOut[1]);

	// Compute total hits
	long total = 0;

#pragma omp parallel for private(i) reduction (+:total)

	for (int i = 0; i < NBLOCKS; i++) {
		total += hOut[0][i] + hOut[1][i];
	}


	std::cout.precision(150);


//	long tests = NBLOCKS * LOOPS * THREADS * 2;
	cout << "Volume aproximado do Toroide, Metodo de Monte Carlo, com  " << tests << " testes aleatorios\n";

	cout << "Volume Toroide ~= " << (4.0 - 1.0) * (4.0 - (-3.0)) * (1.0 - (-1.0)) * (double)total / (double)tests << endl;

	return 0;


//	cout << "PI ~= " << 4.0 * total /tests << endl;

//	return 0;
}
