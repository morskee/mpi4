//
//  mpi4.c
//  ar4
//
//  Created by Kamil Moreński on 6.06.2017.
//  Copyright © 2017 Kamil Moreński. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

int main(int argc, char **argv) {

    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char *ProgFile;
    char *ProgFile1;
    int asciiCharacter = 0;

    FILE *file;
    double tab1[100];
    double tab2[100];
    if (rank == 0) {
      ProgFile = argv[1];
      ProgFile1 = argv[2];
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
              fscanf(file,"%lf",&tab1[i]);
              //printf("%lf\n", tab1[i]);
              }
              printf("%.0f %.0f\n", tab1[0], tab1[1]);
              for (size_t i = 0; i < tab1[0]*tab1[1]; i++) {
                  printf("%.0lf ", tab1[i + 2]);
              }
              printf("\n");
            }
          printf("----- Wczytwany plik %s -----\n\n", argv[2]);
          file = fopen(ProgFile1, "r");
          if(file == NULL) printf("W tym katalogu nie ma takiego pliku\n");
          else {
            for(size_t i = 0; i < 100; i++) {
              if(feof(file)) break;/*jeśli koniec pliku kończy pobieranie*/
              fscanf(file,"%lf",&tab2[i]);
              //printf("%lf\n", tab2[i]);
              }
              printf("%.0f %.0f\n", tab2[0], tab2[1]);
              for (size_t i = 0; i < tab2[0]*tab2[1]; i++) {
                  printf("%.0lf ", tab2[i + 2]);
              }
            }
            printf("\n");
      if (tab1[0] == tab2[1]){
        printf("Liczba kolumn maciaerzy A zgadza sie z liczba wierszy macierzy B\n");
      } else {
        printf("Liczba kolumn macierzy A nie zgadza sie z liczba wierszy macierzy B\n");
      }
      }
    MPI_Finalize();
    return 0;
}
