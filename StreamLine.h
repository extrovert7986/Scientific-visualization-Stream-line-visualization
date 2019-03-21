#pragma once
#include"Point.h"

struct streamLine_t
{
	int pointsNum;
	point_t* head;
	point_t* tail;
	streamLine_t* next;
};

struct streamLineTable_t {
	int linesNum;
	streamLine_t* first;
	streamLine_t* last;
};

void add_point(streamLine_t* line, point_t p,bool atTheEnd);
void add_line(streamLineTable_t* table, streamLine_t* target, bool atTheEnd);
streamLine_t* new_line(point_t seed);
