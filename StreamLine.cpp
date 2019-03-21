#include"StreamLine.h"
#include<stdlib.h>

void add_point(streamLine_t* line, point_t target,bool atTheEnd) {
	point_t* p = (point_t*)calloc(1, sizeof(point_t));
	p->x = target.x;
	p->y = target.y;
	if (line->pointsNum == 0) {
		line->head = line->tail = p;
	}
	else {
		if(atTheEnd){
			p->next = line->tail->next;
			line->tail->next = p;
			line->tail = p;
		}
		else {
			p->next = line->head;
			line->head = p;
		}
	}
	line->pointsNum++;
}

void add_line(streamLineTable_t* table, streamLine_t* target, bool atTheEnd) {
	if (table->linesNum == 0)
		table->first = table->last = target;
	else {
		if (atTheEnd) {
			target->next = table->last->next;
			table->last->next = target;
			table->last = target;
		}
		else {
			target->next = table->first;
			table->first = target;
		}
	}
	table->linesNum++;
}

streamLine_t* new_line(point_t seed) {
	streamLine_t* line = (streamLine_t*)calloc(1, sizeof(streamLine_t));
	add_point(line, seed, false);
	return line;
}

bool delete_line() {
	return true;
}