//
//  mpi4.c
//  ar4
//
//  Created by Kamil Moreński on 6.06.2017.
//  CopyB © 2017 Kamil Moreński. All Bs reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

double check_matrices_decomposition(int number_of_processes, int A_rows, int B_columns, int *nh, int *nv) {
	int nh_tmp = 0;
	int nv_tmp = 0;
	int optimal = A_rows * B_columns + 1;
	int a = 0;
	int b = 0;
	for (size_t i = 1; i <= number_of_processes; i++) {
		if(number_of_processes % i == 0) {
			if (i <= number_of_processes / 2) {
				nh_tmp = i;
				nv_tmp = number_of_processes / nh_tmp;
				if (A_rows % nh_tmp != 0 || B_columns % nv_tmp != 0) {
					nh_tmp = nv_tmp;
					nv_tmp = i;
					if ((A_rows % nv_tmp != 0 || B_columns % nh_tmp != 0)) {
						continue;
					} else {
						if(A_rows / nv_tmp * B_columns / nh_tmp < optimal) {
							optimal = A_rows / nv_tmp * B_columns / nh_tmp;
							*nv = nv_tmp;
							*nh = nh_tmp;
						}
						continue;
					}
				} else {
					if(A_rows / nv_tmp * B_columns / nh_tmp < optimal) {
						optimal = A_rows / nv_tmp * B_columns / nh_tmp;
						*nv = nv_tmp;
						*nh = nh_tmp;
					}
					continue;
				}
			}
			else break;
		}
	}
	if(optimal == A_rows * B_columns + 1) {
		printf("Dekompozycja sie nie udala\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
		return 0;
	} else{
		printf("Dekompozycja sie udala. \n");
		return 1;
	}
}

int main(int argc, char **argv) {

    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char *ProgFile;
    char *ProgFile1;
    ProgFile = argv[1];
    ProgFile1 = argv[2];

    double matrix_A[100];
    double matrix_B[100];
    //double * time = new double [7];

    int asciiCharacter = 0;
    int nh = 0;
    int nv = 0;
    int a = 0;
    int b = 0;

    FILE *file;
    if (rank == 0) {
      if (argc == 3) {
        printf("----- Wczytwany plik %s -----\n\n", argv[1]);
      } else {
        printf("Zle dane\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
      }
          file = fopen(ProgFile, "r");
          if(file == NULL) printf("W tym katalogu nie ma takiego pliku\n");
          else {
            for(size_t i = 0; i < 100; i++) {
              if(feof(file)) break;/*jeśli koniec pliku kończy pobieranie*/
              fscanf(file,"%lf",&matrix_A[i]);
              }
              printf("%.0f %.0f\n", matrix_A[0], matrix_A[1]);
              for (size_t i = 0; i < matrix_A[0]*matrix_A[1]; i++) {
                  printf("%.0lf ", matrix_A[i + 2]);
              }
              printf("\n");
            }
          printf("----- Wczytwany plik %s -----\n\n", argv[2]);
          file = fopen(ProgFile1, "r");
          if(file == NULL) printf("W tym katalogu nie ma takiego pliku\n");
          else {
            for(size_t i = 0; i < 100; i++) {
              if(feof(file)) break;/*jeśli koniec pliku kończy pobieranie*/
              fscanf(file,"%lf",&matrix_B[i]);
              }
              printf("%.0f %.0f\n", matrix_B[0], matrix_B[1]);
              for (size_t i = 0; i < matrix_B[0]*matrix_B[1]; i++) {
                  printf("%.0lf ", matrix_B[i + 2]);
              }
              printf("\n");
            }
      if (matrix_A[0] == matrix_B[1]){
        printf("Liczba kolumn macierzy A zgadza sie z liczba wierszy macierzy B\n");

        if(!check_matrices_decomposition(size, matrix_A[1], matrix_B[0], &nh, &nv)) return 0;
        a = matrix_A[1] / nv;
        b = matrix_B[0] / nh;

        printf("Wartosci dekompozycji: \n");
        printf("n: %d, p: %.0lf, r: %.0lf, n_h: %d, n_v: %d, a: %d, b: %d\n", size, matrix_A[1], matrix_B[0], nh, nv, a, b);

      } else {
        printf("Liczba kolumn macierzy A nie zgadza sie z liczba wierszy macierzy B\n");
        }
      }
    MPI_Finalize();
    return 0;
}
