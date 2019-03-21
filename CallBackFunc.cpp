#include<GL\freeglut.h>
#include<glm\gtc\matrix_transform.hpp>
#include<stdio.h>
#include<string.h>
#include"FileReader.h"
#include"StreamLine.h"
#include"RK2.h"

char fileName[200] = "./vec_data/1.vec";


#define NUM_LAYERS 3
int mesh[NUM_LAYERS] = { 150,150,150 };
#define STEP_SIZE 0.001
int fileCnt = 1;

point_t* seed = (point_t*)calloc(1, sizeof(point_t));
vectorField_t vf;
streamLineTable_t table;

int*** create_layers();
void generate_seeds(streamLineTable_t* table, const int rowSeeds, const int colSeeds, const vectorField_t vf);
double dist(point_t p0, point_t p1);
void init() {
	//Read vector field into the program
	vf = read_vector_field(fileName);
	//Initial the stream line layers
	int*** layers = create_layers();
	//initial seed point
	table.first = table.last = nullptr;
	table.linesNum = 0;
	generate_seeds(&table, 25, 25, vf);
	//first layer for loop
	for (int i = 0; i < 1; i++) {
		//compute gap of each level
		double gap = (vf.column - 1) / (double)mesh[i];
		int lineNO = 1;
		//trace stream line line by line
		for (streamLine_t* current = table.first; current!= nullptr; current = current->next) {
			point_t previous;
			//trace point by point from head
			previous.x = current->head->x;
			previous.y = current->head->y;
			while (1) {
				point_t next;
				next = compute_next(previous, -1*STEP_SIZE, vf);
				if (dist(previous, next) < 0.00001)
					break;
				if (next.x<0 || next.x>vf.column - 1)
					break;
				if (next.y<0 || next.y>vf.row - 1)
					break;
				if (layers[i][(int)floor(next.x / gap)][(int)floor(next.y / gap)] != 0
					&& layers[i][(int)floor(next.x / gap)][(int)floor(next.y / gap)] != lineNO)
					break;
				layers[i][(int)floor(next.x / gap)][(int)floor(next.y / gap)] = lineNO;
				add_point(current, next, false);
				previous = next;
			}
			//trace the point from the end
			previous.x = current->tail->x;
			previous.y = current->tail->y;
			while (1) {
				point_t next;
				next = compute_next(previous, STEP_SIZE, vf);
				if (dist(previous, next) < 0.00001)
					break;
				if (next.x<0 || next.x>vf.column - 1)
					break;
				if (next.y<0 || next.y>vf.row - 1)
					break;
				if (layers[i][(int)floor(next.x / gap)][(int)floor(next.y / gap)] != 0
					&& layers[i][(int)floor(next.x / gap)][(int)floor(next.y / gap)] != lineNO)
					break;
				add_point(current, next, true);
				previous = next;
			}

			lineNO++;
		}
	}

	
}

void display() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, vf.column, -1, vf.row );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//line 
	for (streamLine_t* cur = table.first; cur != nullptr; cur = cur->next) {
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		for (point_t* p = cur->head; p->next != nullptr; p = p->next) {
			glVertex2f(p->x, p->y);
			glVertex2f(p->next->x, p->next->y);
		}
		glEnd();
	}
	glFlush();
}

void reshape(int x, int y) {
	glViewport(0, 0, x, y);
	
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	//if (key == 'w'||key == 'w') {
	//	char* str = strrchr(filename, '//');
	//	char ch[6] = "1.vec";
	//	filecnt++;
	//	ch[0] = (char)(filecnt + 48);
	//	strcpy(str + 1, ch);
	//	init();
	//}
}

int*** create_layers() {
	int*** layers = (int***)calloc(NUM_LAYERS, sizeof(int**));
	for (int i = 0; i < NUM_LAYERS; i++) {
		layers[i] = (int**)calloc(mesh[i], sizeof(int*));
		for (int j = 0; j < mesh[i]; j++)
			layers[i][j] = (int*)calloc(mesh[i], sizeof(int));
	}
	return layers;
}

void generate_seeds(streamLineTable_t* table,const int rowSeeds,const int colSeeds,const vectorField_t vf) {
	double deltaX = (vf.column - 1) / ((float)(colSeeds * 2));
	double deltaY = (vf.row - 1) / ((float)(rowSeeds * 2));
	
	for (int j = 0; j < rowSeeds; j++)
		for (int i = 0; i < colSeeds; i++) {
			point_t cur;
			cur.x = (i * 2 + 1)*deltaX;
			cur.y = (j * 2 + 1)*deltaY;
			cur.next = nullptr;
			add_line(table, new_line(cur), true);
		}
}

double dist(point_t p0,point_t p1) {
	return sqrt((p0.x - p1.x)*(p0.x - p1.x) + (p0.y - p1.y)*(p0.y - p1.y));
}