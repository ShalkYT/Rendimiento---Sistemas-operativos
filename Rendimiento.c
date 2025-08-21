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

/*
Nombre: initMatrices
Descripcion: Funcion para asignarle valores fijos a 3 matrices de largo-ancho N
Entradas: Recibe el tamaño de la matrices y los apuntadores a las 3 matrices de tipo double
Salidas: no retorna nada pero se encarga de ingresar valores en las 3 matrices 
*/
void initMatrices(int N, double *matriz1, double *matriz2, double *matriz3){
	for(int i = 0;i<N*N;i++){
		matriz1[i] = i*5 +1;
		matriz2[i] = i*2 +2;
		matriz3[i] = 0;
	}
}


/*
Nombre: imprMatriz
Descripción: Función para imprimir una matriz si su largo-ancho es menor a 9, en caso contrario avisa que el tamaño es demasiado
Entradas: Recibe el tamaño de la matriz y un apuntador a una matriz de double
Salidas: no retorna nada pero imprime la matriz por consola
Importante: Si el tamaño de la matriz es mayor o igual a 9 la matriz no se imprime
*/
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


/*
Nombre: main
Descripción: contiene el codigo principal
Importante: comentarios dentro de la funcion
*/
int main(int argc, char *argv[]) {
    // Condicional para confirmar la cantidad de entradas e informar el formato para correr el ejecutable
    if(argc<2){
        printf("Numero argumentos incorrectos\n");
        printf("\n\t $ejecutable.exe DIM \n");
        return -1;
    }

    // Transformación del valor de consola a float con funcion ASCII to float (atof)
    int N = (int) atof(argv[1]);

    // Condicional para confirmar que el tamaño ingresado por consola es positivo y diferente de cero
    if(N<=0){
        printf("\n Valores deben ser mayor que cero\n");
        return -1;
    };

    // Asignación de memoria de todas las matrices dinamicas teniendo en cuenta:
    // (double *) --> cast para definir que el retorno es un apuntador a double ya que malloc regresa un void
    // malloc - calloc --> Funcion para asignar memoria dinamica
    // Diferencia entre malloc y calloc: calloc a diferencia de malloc asigna la memoria y establece los valores en 0
    // N*N*sizeof(double) --> multiplicación por el tamaño del tipo de dato
    mA = (double *) malloc(N*N*sizeof(double));
    mB = (double *) malloc(N*N*sizeof(double));
    mC = (double *) calloc(N*N,sizeof(double));	

    //Uso de funcion para llenar las matrices
   initMatrices(N,mA,mB,mC);

   // Uso de funcion para imprimir las 3 matrices
   imprMatriz(N,mA);
   imprMatriz(N,mB);
   imprMatriz(N,mC);

    // Ciclos anidados para realizar la multiplicación de matrices y guardarlos en otra
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

    // impresion de matriz 3 para confirmar la multiplicación de matrices
    imprMatriz(N, mC);


    printf("\n\tFin del programa.............!\n");

    // Liberacion de la memoria asignada para las 3 matrices
	free(mA);
	free(mB);
	free(mC);

    return 0;

}
