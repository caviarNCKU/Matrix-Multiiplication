#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void multiply(int row, int **matrix, int **matrix2, int **result);
void strassen(int row, int **matrix, int **matrix2, int **result);


int main(){
	int token, row , col, i, j, k, sum, row2 ,col2;
	int **matrix, **matrix2, **result;

	clock_t start_time, end_time;
	float total_time = 0;

	scanf("%d",&row);
	scanf("%d",&col);
	
	matrix = (int**)malloc(row*sizeof(int *));
	matrix2 = (int**)malloc(row*sizeof(int *));
	result = (int**)malloc(row*sizeof(int *));


	for(i = 0; i != row; i++){
		matrix[i]  = (int*)malloc(col*sizeof(int *));
		matrix2[i] = (int*)malloc(col*sizeof(int *));
		result[i]  = (int*)malloc(col*sizeof(int *));
	}
	for(i = 0; i < row ; i++)
		for(j = 0; j < col; j ++)
			scanf("%d",&matrix[i][j]);
	scanf("%d",&row2);
	scanf("%d",&col2);
	for(i = 0; i < row2 ; i++)
		for(j = 0; j < col2; j ++)
			scanf("%d",&matrix2[i][j]);

	start_time = clock();
	multiply(row,matrix,matrix2,result);
	end_time = clock();
	total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
	printf("Original Parallel Time: %f sec \n", total_time);
	
	start_time = clock();
	strassen(row,matrix,matrix2,result);
	end_time = clock();
	total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
	printf("Strassen Parallel Time: %f sec \n", total_time);

	for(i = 0; i != row; i++){
		free(matrix[i]);
		free(matrix2[i]);
		free(result[i]) ;
	}

	free(matrix);
	free(matrix2);
	free(result);
}

void multiply(int row, int **matrix, int **matrix2, int **result){
		int i, j, k, sum;
		#pragma omp parallel for
		for(i = 0; i < row; i++)
		for(j = 0; j < row; j++){
			for(k = 0; k < row; k++){
				sum = sum + matrix[i][k] * matrix2[k][j];
			}
			result[i][j] = sum;
			sum = 0;
		}
}

void add(int row, int **matrix, int **matrix2, int **result){
	int i,j;
	//#pragma omp parallel for
	for(i = 0; i < row; i++)
		for(j = 0; j < row; j++)
			result[i][j] = matrix[i][j] + matrix2[i][j];
}

void sub(int row, int **matrix, int **matrix2, int **result){
	int i,j;
	//#pragma omp parallel for
	for(i = 0; i < row; i++)
		for(j = 0; j < row; j++)
			result[i][j] = matrix[i][j] - matrix2[i][j];
}

void strassen(int row, int **matrix, int **matrix2, int **result){
	int **matrix_11,  **matrix_12, **matrix_21, **matrix_22;
	int **matrix2_11, **matrix2_12, **matrix2_21, **matrix2_22;
	int **result_11, **result_12, **result_21, **result_22;

	int **p1, **p2, **p3, **p4, **p5, **p6, **p7;
	int **temp1, **temp2;
	int i,j;

	matrix_11 = (int**)malloc(row*sizeof(int *));
	matrix_12 = (int**)malloc(row*sizeof(int *));
	matrix_21 = (int**)malloc(row*sizeof(int *));
	matrix_22 = (int**)malloc(row*sizeof(int *));

	matrix2_11 = (int**)malloc(row*sizeof(int *));
	matrix2_12 = (int**)malloc(row*sizeof(int *));
	matrix2_21 = (int**)malloc(row*sizeof(int *));
	matrix2_22 = (int**)malloc(row*sizeof(int *));

	result_11 = (int**)malloc(row*sizeof(int *));
	result_12 = (int**)malloc(row*sizeof(int *));
	result_21 = (int**)malloc(row*sizeof(int *));
	result_22 = (int**)malloc(row*sizeof(int *));

	p1 = (int**)malloc(row*sizeof(int *));
	p2 = (int**)malloc(row*sizeof(int *));	
	p3 = (int**)malloc(row*sizeof(int *));
	p4 = (int**)malloc(row*sizeof(int *));
	p5 = (int**)malloc(row*sizeof(int *));
	p6 = (int**)malloc(row*sizeof(int *));
	p7 = (int**)malloc(row*sizeof(int *));

	temp1 = (int**)malloc(row*sizeof(int *));
	temp2 = (int**)malloc(row*sizeof(int *));
	//#pragma omp parallel for
	for(i = 0; i != row; i++){
		matrix_11[i] = (int*)malloc(row*sizeof(int *));
		matrix_12[i] = (int*)malloc(row*sizeof(int *));
		matrix_21[i] = (int*)malloc(row*sizeof(int *));
		matrix_22[i] = (int*)malloc(row*sizeof(int *));

		matrix2_11[i] = (int*)malloc(row*sizeof(int *));
		matrix2_12[i] = (int*)malloc(row*sizeof(int *));
		matrix2_21[i] = (int*)malloc(row*sizeof(int *));
		matrix2_22[i] = (int*)malloc(row*sizeof(int *));

		result_11[i] = (int*)malloc(row*sizeof(int *));
		result_12[i] = (int*)malloc(row*sizeof(int *));
		result_21[i] = (int*)malloc(row*sizeof(int *));
		result_22[i] = (int*)malloc(row*sizeof(int *));

		p1[i] = (int*)malloc(row*sizeof(int *));
		p2[i] = (int*)malloc(row*sizeof(int *));	
		p3[i] = (int*)malloc(row*sizeof(int *));
		p4[i] = (int*)malloc(row*sizeof(int *));
		p5[i] = (int*)malloc(row*sizeof(int *));
		p6[i] = (int*)malloc(row*sizeof(int *));
		p7[i] = (int*)malloc(row*sizeof(int *));

		temp1[i] = (int*)malloc(row*sizeof(int *));
		temp2[i] = (int*)malloc(row*sizeof(int *));
	}

	if(row <= 16){
		multiply(row,matrix,matrix2,result);
	}
	else{
		//#pragma omp parallel for
		for(i = 0 ; i < row/2; i++){
			for(j = 0; j < row/2; j++){
				matrix_11[i][j] = matrix[i][j];
				matrix_12[i][j] = matrix[i][j+row/2];
				matrix_21[i][j] = matrix[i+row/2][j];
				matrix_22[i][j] = matrix[i+row/2][j+row/2];

				matrix2_11[i][j] = matrix2[i][j];
				matrix2_12[i][j] = matrix2[i][j+row/2];
				matrix2_21[i][j] = matrix2[i+row/2][j];
				matrix2_22[i][j] = matrix2[i+row/2][j+row/2];
			}
		}
		//	p1 = a(f - h)
		sub(row/2,matrix2_12,matrix2_22,temp2);
		strassen(row/2,matrix_11,temp2,p1);
		//	p2 = (a + b)h
		add(row/2,matrix_11,matrix_12,temp1);
		strassen(row/2,temp1,matrix2_22,p2);
		//	p3 = (c + d)e
		add(row/2,matrix_21,matrix_22,temp1);
		strassen(row/2,temp1,matrix2_11,p3);
		//	p4 = d(g - e)
		sub(row/2,matrix2_21,matrix2_11,temp2);
		strassen(row/2,matrix_22,temp2,p4);
		//	p5 = (a + d)(e + h)
		add(row/2,matrix_11,matrix_22,temp1);
		add(row/2,matrix2_11,matrix2_22,temp2);
		strassen(row/2,temp1,temp2,p5);
		//  p6 = (b - d)(g + h)
		sub(row/2,matrix_12,matrix_22,temp1);
		for(i = 0; i != row; i++){
 			free(matrix_12[i]);
			free(matrix_22[i]);
		}
		free(matrix_12);
		free(matrix_22);

		add(row/2,matrix2_21,matrix2_22,temp2);
		for(i = 0; i != row; i++){
 			free(matrix2_21[i]);
			free(matrix2_22[i]);
		}
		free(matrix2_21);
		free(matrix2_22);
		strassen(row/2,temp1,temp2,p6);
		//	p7 = (a - c)(e + f)
		sub(row/2,matrix_11,matrix_21,temp1);
		for(i = 0; i != row; i++){
 			free(matrix_11[i]);
			free(matrix_21[i]);
		}
		free(matrix_11);
		free(matrix_21);
		add(row/2,matrix2_11,matrix2_12,temp2);
		for(i = 0; i != row; i++){
 			free(matrix2_11[i]);
			free(matrix2_12[i]);
		}
		free(matrix2_11);
		free(matrix2_12);
		strassen(row/2,temp1,temp2,p7);

		//c0 = p5 + p4 - p2 + p6
		add(row, p5, p4 , temp1);
		sub(row, temp1, p2, temp2);
		add(row, temp2, p6, result_11);
		for(i = 0; i != row; i++){
 			free(p6[i]);
		}
		free(p6);
		//c1 = p1 + p2
		add(row, p1, p2, result_12);
		for(i = 0; i != row; i++){
 			free(p2[i]);
		}
		free(p2);
		//c2 = p3 + p4
		add(row, p3, p4, result_21);
		for(i = 0; i != row; i++){
 			free(p4[i]);
		}
		free(p4);
		//c3 = p1 + p5 - p3 -p7
		add(row, p1, p5, temp1);
		sub(row, temp1, p3, temp2);
		sub(row, temp2, p7, result_22);
		for(i = 0; i != row; i++){
 			free(p1[i]);
 			free(p3[i]);
 			free(p5[i]);
 			free(p7[i]);
 			free(temp1[i]);
 			free(temp2[i]);
		}
		free(p1);
		free(p3);
		free(p5);
		free(p7);
		free(temp1);
		free(temp2);
		//#pragma omp parallel for
		for(i = 0; i < row/2; i++){
			for(j = 0; j < row/2; j++){
				result[i][j] = result_11[i][j];
				result[i][j+row/2] = result_12[i][j];
				result[i+row/2][j] = result_21[i][j];
				result[i+row/2][j+row/2] = result_22[i][j];			
			}
		}

	for(i = 0; i != row; i++){
		free(result_11[i]); 
		free(result_12[i]);
		free(result_21[i]);
		free(result_22[i]);
	}

	}

	free(result_11); 
	free(result_12); 
	free(result_21); 
	free(result_22);

}


