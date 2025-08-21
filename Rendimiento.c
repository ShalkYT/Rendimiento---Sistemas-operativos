/**************************************************************************************
 * Fecha: 21 de Agosto de 2025
 * Autor: Andres Eduardo Meneses Rincon
 * Materia: Sistemas Operativos
 * Tema: Rendimiento y concurrencia
 * Objetivo: Hacer una metodología para la implementación de la multiplicación de matrices.
 * La idea principal, es construir paso a paso la implementación para hacer uso de la
 * biblioteca PTHREAD. Se implementa el Algoritmo Clásico de multiplicación de matrices, para
 * matrices cuadradas, es decir, la dimensión de filas es igual a la de columnas.
 * A continuación se describen los paso
 *  - Reserva de memoria
 *      - Creación de punteros para matrices del tipo doble
 *      - Asignación de memoria
 *      - Ingreso de argumentos de entrada (Dimensión matriz, número de hilos)
 *      - Validación argumentos de entrada
 *      - Inicializar las matrices
 *      - Imprimir las matrices
 *      - Función para inicializar las matrices
 *      - Función para imprimir las matrices
 *      - Algoritmo clásico de multiplicación matrices
 *  - Se verifica el resultado
 *      - Función para multiplicación las matrices
 *      - Declaración vector de hilos
 *      - Creación de hilos según tamaño de vector de hilos
 *      - Crear estructura de datos que encapsule los argumentos de entrada de la función MM
 * Implementación de paralelismo: resolución de la multiplicación de matrices
 *  - Se crea el vector de hilos
 *  - Se tiene pendiente la exclusión de los hilos
 *  - Se pasa a globales las matrices
 *  - Encapsular los datos para enviarlos a la función MxM
 *  - Se desencapsulan los datos dentro de la función MxM (descomprimen)
*************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


/*Se declaran los punteros para las matrices, 3 punteros de tipo double*/
double *mA, *mB, *mC;

/*Funcion para asignarle valores fijos a 3 matrices de largo-ancho N*/
void initMatrices(int N, double *matriz1, double *matriz2, double *matriz3){
	for(int i = 0;i<N*N;i++){
		matriz1[i] = i*5 +1;
		matriz2[i] = i*2 +2;
		matriz3[i] = 0;
	}
}


/*Función para imprimir una matriz si su largo-ancho es menor a 9, en caso contrario avisa que el tamaño es demasiado*/
void imprMatriz(int N, double *matriz){
    if(N<9){
	for(int i=0; i<N*N; i++){
                if(i%N==0) printf("\n");
        printf(" %f ", matriz[i]);
   	}	
	printf("\n#######################################################\n");
    } else {
	printf("\nEl tamaño de la matriz es muy grande\n");
        printf("\n#######################################################\n");
    }
};

int main(int argc, char *argv[]) {
    if(argc<2){
        printf("Numero argumentos incorrectos\n");
        printf("\n\t $ejecutable.exe DIM \n");
        return -1;
    }

    int N = (int) atof(argv[1]);
    if(N<=0){
        printf("\n Valores deben ser mayor que cero\n");
        return -1;
    };

    mA = (double *) malloc(N*N*sizeof(double));
    mB = (double *) malloc(N*N*sizeof(double));
    mC = (double *) calloc(N*N,sizeof(double));	

   initMatrices(N,mA,mB,mC);
   imprMatriz(N,mA);
   imprMatriz(N,mB);
   imprMatriz(N,mC);

        for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            double sumaTemp, *pA, *pB;
            sumaTemp = 0.0;
            pA = mA + i*N;
            pB = mB + j;
            for(int k=0; k<N; k++, pA++, pB+=N){
                sumaTemp += *pA * *pB;
            }
            mC[j+i*N] = sumaTemp;
        }
    }


        printf("\n\tFin del programa.............!\n");

	free(mA);
	free(mB);
	free(mC);

        return 0;

}
