#!/bin/bash
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]){
	if (argc != 2){
		return 1;
	}

	FILE *f = fopen(argv[1], "r");
	if(!f){
		return 1;
	}

	int N, M;
	if (fscanf(f, "%d" "%d", &N, &M) != 2){
		fclose(f);
		return 1;
	}

	int **matrix = (int **)malloc(N*sizeof(int*));
	for (int i = 0; i < N; i++){
		matrix[i] = (int *)malloc(M*sizeof(int));
	}

	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			if (fscanf(f, "%d", &matrix[i][j]) != 1){
                        	fclose(f);
                        	return 1;
			}
		}
	}
	fclose(f);

	int S = 1;
	for(int i = 0; i < N; i++){
		S *= matrix[i][i];
	}

	if(N < 3){
		return 1;
	}
	int wal = matrix[2][0];
	int st = 0;
	for (int j = 1; j < M; j++){
		if (matrix[2][j] < wal){
			wal = matrix[2][j];
			st = j;
	}
		}
	matrix[2][st] = S;

	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			printf("%d", matrix[i][j]);
		}
	}
}
