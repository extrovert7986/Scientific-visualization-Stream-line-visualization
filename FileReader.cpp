#include<stdio.h>
#include<stdlib.h>
#include"Vector.h"

vectorField_t read_vector_field(const char* fileName) {
	vectorField_t vf;
	//open the file
	FILE* fp = fopen(fileName, "r");
	if (!fp) {
		fprintf(stderr, "File %s open failed.\n", fileName);
		system("pause");
		exit(0);
	}
	fscanf(fp, "%d %d", &(vf.column), &(vf.row));
	printf("column: %d row: %d\n", vf.column, vf.row);
	//allocate memory space for vector array
	vf.vec = (vector_t*)calloc(vf.column * vf.row, sizeof(vector_t));
	for (int j = 0; j < vf.row; j++) 
		for (int i = 0; i < vf.column; i++) {
			int index = i + j*vf.column;
			fscanf(fp, "%lf %lf", &(vf.vec[index].x), &(vf.vec[index].y));
			//printf("[ %d,%d ]: %lf %lf\n", j, i, vf.vec[index].x, vf.vec[index].y);
		}
	fclose(fp);

	return vf;
}