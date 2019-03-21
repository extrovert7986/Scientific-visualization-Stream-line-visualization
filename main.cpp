#include<GL\glew.h>
#include<GL\freeglut.h>
#include<stdio.h>
#include"CallBackFunc.h"

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(50, 50);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutCreateWindow("Stream line");
	
	/*if (glewInit() != GLEW_OK) {
		printf("Glew initial failed.\n");
		system("pause");
		exit(0);
	}*/
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}