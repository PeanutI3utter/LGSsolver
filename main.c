#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printMatrix(double* matrix, int height, int width);
void swapColumn(double *matrix, int column1, int column2, int height, int width);
void swapRow(double *matrix, int row1, int row2, int width);
int* eulerAlgFullSearch(double *matrix, double *vector,  int height, int width);
void printMatrixVector(double *matrix, double *vector, int height, int width);
int lengthAsString(double number);
void addRowToRow(double *matrix, int to, int add, double factor, int width);
void printVector(double *vector, int height);

int main(){
	double matrix[] = {-1, 1, 1, 1, -3, -2, 5, 1, 4};
	double vector[] = {0, 5, 3};
	eulerAlgFullSearch(matrix, vector, 3, 3);
	printf("\n");
	printf("\n");
	/*swapRow(matrix, 2, 3, 4);
	swapRow(vector, 2, 3, 1);
	printMatrixVector(matrix, vector, 4, 4);
	printf("\n");
	printf("\n");
	swapColumn(matrix, 2, 3, 4, 4);
	printMatrixVector(matrix, vector, 4, 4);
	printf("\n");
	printf("\n");
	*/
	return 0;
}

int* eulerAlgFullSearch(double *matrix, double *vector,  int height, int width){
	printMatrixVector(matrix, vector, height, width);
	printf("\n\n\n");
	double resultVector[height];
	double *x = malloc(sizeof(int) * height);
	for(int i = 0; i < height; i++){
		x[i] = i;
	} 
	for(int a = 0; a < height; a++){
		int highestElementRow = a;
		int highestElementColumn = a;
		double highestElement = fabs(matrix[highestElementRow * width + highestElementColumn]);
		for(int i = a; i < height; i++){
			for(int j = a; j < width; j++){
				double element = fabs(matrix[i * width + j]);
				if(element > highestElement){
					highestElementRow = i;
					highestElementColumn = j;
					highestElement = element;
				}
			}
		}
		if(a != highestElementRow){
			printf("swap %d row with %d row:\n\n", a, highestElementRow);
			swapRow(matrix, a, highestElementRow, width);
			swapRow(vector, a, highestElementRow, 1);
			printMatrixVector(matrix, vector, height, width);
			printf("\n\n\n");
		}
		if(a != highestElementColumn){
			printf("swap %d column with %d column:\n\n", a, highestElementColumn);
			swapColumn(matrix, a, highestElementColumn, height, width);
			swapRow(x, a, highestElementColumn, 1);
			printMatrixVector(matrix, vector, height, width);
			printf("\n\n\n");
		}
		double dominant = matrix[a * width + a];
		for(int row = a + 1; row < height; row++){
			float factor = (matrix[row * width + a] / dominant) * -1;
			printf("add %f * row %d to row %d\n", factor, a, row);
			addRowToRow(matrix, row, a, factor, width);
			addRowToRow(vector, row, a, factor, 1);
		}
		printf("\n\n\n");
		printMatrixVector(matrix, vector, height, width);
		printf("\n\n\n");
		for(int i = height - 1; i >= 0; i--){
			int xNum = x[i];
			double tempRes = vector[i];
			for(int j = i + 1; j < height; j++){
				int jj = x[j];
				tempRes = tempRes - matrix[i * height + j] * resultVector[jj];
			}
			resultVector[xNum] = tempRes / matrix[i * width + i];
		}
	}
	printf("\n\nresult:\n\n");
	printVector(resultVector, height);
}

void swapRow(double *matrix, int row1, int row2, int width){
	int row1Offset = row1 * width;
	int row2Offset = row2 * width;
	for(int i = 0; i < width; i++){
		double temp = matrix[row1Offset + i];
		matrix[row1Offset + i] = matrix[row2Offset + i];
		matrix[row2Offset + i] = temp;
	}
}

void swapColumn(double *matrix, int column1, int column2, int height, int width){
	for(int i = 0; i < height; i++){
		double temp = matrix[i * width + column1];
		matrix[i * width + column1] = matrix[i * width + column2];
		matrix[i * width + column2] = temp;
	}
}

void addRowToRow(double *matrix, int to, int add, double factor, int width){
	for(int i = 0; i < width; i++){
		matrix[to * width + i] = matrix[to * width + i] + factor * matrix[add * width + i];
	}
}

void printMatrix(double *matrix, int height, int width){
	int longest = 4;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			int stringlength = lengthAsString(matrix[i * width + j]);
			longest =  stringlength > longest ? stringlength : longest;
		}
	}
	for(int i = 0; i < height; i++){
		int spaces = (longest - lengthAsString(matrix[i * width])) + 4;
		printf("|%.2f", matrix[i * width]);
		for(int space = 0; space < spaces; space++){
			printf(" ");
		}
		for(int j = 1; j < width - 1; j++){
			spaces = (longest - lengthAsString(matrix[i * width + j])) + 4;
			
			printf("%.2f  ", matrix[i * width + j]);
			for(int space = 0; space < spaces; space++){
				printf(" ");
			}
		}
		spaces = (longest - lengthAsString(matrix[(i + 1) * width - 1]));
		printf("%.2f", matrix[(i + 1) * width - 1]);
		for(int space = 0; space < spaces; space++){
				printf(" ");
		}
		printf("|\n");
	}
}

void printVector(double *vector, int height){
	int longest = 4;
	for(int i = 0; i < height; i++){
		int stringlength = lengthAsString(vector[i]);
		longest =  stringlength > longest ? stringlength : longest;
	}
	for(int i = 0; i < height; i++){
		int spaces = (longest - lengthAsString(vector[i]));
		printf("|%.2f", vector[i]);
		for(int space = 0; space < spaces; space++){
				printf(" ");
		}
		printf("|\n");
	}
}

void printMatrixVector(double *matrix, double *vector, int height, int width){
	int longest = 4;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			int stringlength = lengthAsString(matrix[i * width + j]);
			longest =  stringlength > longest ? stringlength : longest;
		}
	}
	for(int i = 0; i < height; i++){
		int spaces = (longest - lengthAsString(matrix[i * width])) + 4;
		printf("|%.2f", matrix[i * width]);
		for(int space = 0; space < spaces; space++){
			printf(" ");
		}
		for(int j = 1; j < width - 1; j++){
			spaces = (longest - lengthAsString(matrix[i * width + j])) + 4;
			
			printf("%.2f  ", matrix[i * width + j]);
			for(int space = 0; space < spaces; space++){
				printf(" ");
			}
		}
		spaces = (longest - lengthAsString(matrix[(i + 1) * width - 1]));
		printf("%.2f", matrix[(i + 1) * width - 1]);
		for(int space = 0; space < spaces; space++){
				printf(" ");
		}
		printf("|  %.2f\n", vector[i]);
	}
}


int lengthAsString(double number){
	int num = (int)number;
	int digit = 1;
	int divider = 10;
	while(num / divider){
		divider *= 10;
		digit++;
	}
	if(number < 0){
		digit++;
	}
	return digit + 3;
}