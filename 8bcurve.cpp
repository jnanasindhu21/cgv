#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
float theta = 0, a = 3.14 / 180, r1 = 1, g1 = .5, b1 = 0, r2 = 1, g2 = 1, b2 = 1, r3 = 0, g3 = 1, b3 = 0;
struct point
{
	GLfloat x, y, z;
};
void bino(int n, int* C)
{
	int k, j;
	for (k = 0;k <= n;k++)
	{
		C[k] = 1;
		for (j = n;j >= k + 1;j--)	C[k] *= j;
		for (j = n - k;j >= 2;j--)	C[k] /= j;
	}
}
void cmpt(float u, point* pt1, int cPt, point* pt2, int* C)
{
	int k, n = cPt - 1;
	float bFcn;
	pt1->x = pt1->y = pt1->z = 0;
	for (k = 0;k < cPt;k++)
	{
		bFcn = C[k] * pow(u, k) * pow(1 - u, n - k);
		pt1->x += pt2[k].x * bFcn;
		pt1->y += pt2[k].y * bFcn;
		pt1->z += pt2[k].z * bFcn;
	}
}
void bez(point* pt1, int cPt, int bPt)
{
	point bcPt;
	float u;
	int* C, k;
	C = new int[cPt];
	bino(cPt - 1, C);
	glBegin(GL_LINE_STRIP);
	for (k = 0;k <= bPt;k++)
	{
		u = float(k) / float(bPt);
		cmpt(u, &bcPt, cPt, pt1, C);
		glVertex2f(bcPt.x, bcPt.y);
	}
	glEnd();
	delete[]C;
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int nCtrlPts = 4, nBCPts = 20;
	point ctrlPts[4] = { {100,400,0},{150,450,0},{250,350,0},{300,400,0} };
	ctrlPts[1].x += 50 * sin(theta * a);
	ctrlPts[1].y += 25 * sin(theta * a);
	ctrlPts[2].x -= 50 * sin((theta + 30) * a);
	ctrlPts[2].y -= 50 * sin((theta + 30) * a);
	ctrlPts[3].x -= 25 * sin((theta)*a);
	ctrlPts[3].y += sin((theta - 30) * a);
	theta += 0.2;
	glColor3f(1, 1, 1);
	glPushMatrix();
	glLineWidth(5);
	glColor3f(r1, g1, b1);
	for (int i = 0;i < 50;i++)
	{
		glTranslatef(0, -0.8, 0);
		bez(ctrlPts, nCtrlPts, nBCPts);
	}
	glColor3f(r2, g2, b2);
	for (int i = 0;i < 50;i++)
	{
		glTranslatef(0, -0.8, 0);
		bez(ctrlPts, nCtrlPts, nBCPts);
	}
	glColor3f(r3, g3, b3);
	for (int i = 0;i < 50;i++)
	{
		glTranslatef(0, -0.8, 0);
		bez(ctrlPts, nCtrlPts, nBCPts);
	}
	glPopMatrix();
	glColor3f(0.7, 0.5, 0.3);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(100, 400);
	glVertex2f(100, 40);
	glEnd();
	glutPostRedisplay();
	glutSwapBuffers();
}
void keyboard(unsigned char keys, int x4, int y4)
{
	switch (keys)
	{
	case 'a':
	case 'A':
		r1 = rand() * rand() % 10;
		g1 = rand() * rand() % 10;
		b1 = rand() * rand() % 10;
		r2 = rand() * rand() % 10;
		g2 = rand() * rand() % 10;
		b2 = rand() * rand() % 10;
		r3 = rand() * rand() % 10;
		g3 = rand() * rand() % 10;
		b3 = rand() * rand() % 10;
		break;
	case 27:
		exit(0);
		break;
	}
	glutPostRedisplay();
}
void dropmenu(int keys)
{
	keyboard((unsigned char)keys, 0, 0);
}
int main(int argc, char** argv)
{
	printf("\nPress \'a or A\' to randomize the flag color\nPress Esc to quit\n");
	getc(stdin);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1920, 1000);
	glutCreateWindow("Bezier curve");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
	glClearColor(.8, .8, .8, 1);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}
