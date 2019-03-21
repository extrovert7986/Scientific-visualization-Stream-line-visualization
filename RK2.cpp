#include"Point.h"
#include"Vector.h"
#include<math.h>

vector_t compute_current_vector(const point_t r0, const vectorField_t vf);

point_t compute_next(const point_t r0, float h, const vectorField_t vf) {
	point_t rh;
	//step 1: compute r0's vector - u0
	vector_t u0 = compute_current_vector(r0, vf);
	point_t p1;
	//step 2: p1 = r0 + h*u0 
	p1.x = r0.x + fabs(h)*u0.x;
	p1.y = r0.y + fabs(h)*u0.y;
	//step 3: compute p1's vector - u1
	vector_t u1 = compute_current_vector(p1, vf);
	//step 4: rh = r0 + (h/2)*(u0 + u1)
	rh.x = r0.x + (h / 2)*(u0.x + u1.x);
	rh.y = r0.y + (h / 2)*(u0.y + u1.y);
	rh.next = nullptr;

	return rh;
}

vector_t compute_current_vector(const point_t r0, const vectorField_t vf) {
	vector_t curVec;
	int i, j;
	double deltaX;
	double deltaY;
	int LB, RB, LT, RT;

	i = floor(r0.x);
	j = floor(r0.y);
	deltaX = r0.x - i;
	deltaY = r0.y - j;

	LB = i + j*vf.column;
	RB = (i + 1) + j*vf.column;
	LT = i + (j + 1)*vf.column;
	RT = (i + 1) + (j + 1)*vf.column;
	curVec.x = 
		vf.vec[LB].x * (1 - deltaX) * (1 - deltaY) +
		vf.vec[RB].x *   deltaX     * (1 - deltaY) +
		vf.vec[LT].x * (1 - deltaX) *    deltaY    +
		vf.vec[RT].x *	 deltaX     *    deltaY;
	curVec.y =
		vf.vec[LB].y * (1 - deltaX) * (1 - deltaY) +
		vf.vec[RB].y *   deltaX     * (1 - deltaY) +
		vf.vec[LT].y * (1 - deltaX) *    deltaY +
		vf.vec[RT].y *	 deltaX     *    deltaY;

	return curVec;
}