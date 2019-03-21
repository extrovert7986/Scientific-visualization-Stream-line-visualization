#pragma once
struct vector_t {
	double x;
	double y;
};

struct vectorField_t {
	int column;
	int row;
	vector_t* vec;
};