#include<cstdlib>
#include<GL\freeglut.h>
#include<iostream>
#include<Windows.h>
#include<cmath>

using namespace std;

GLsizei width, height;
static int menu, submenu, colormenu;
int value = 0;
int numberOfSegments = 50;

struct Position
{
	Position() :x(0), y(0) {}
	float x;
	float y;
};

Position points[100];
int p = 0;
int pcount = 0;

void Menu(int num)
{
	value = num;
	glutPostRedisplay();
}

void createMenu(void)
{
	submenu = glutCreateMenu(Menu);
	glutAddMenuEntry("Triangle", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Rectangle", 3);
	glutAddMenuEntry("Circle", 4);
	glutAddMenuEntry("Polygon", 5);
	menu = glutCreateMenu(Menu);
	glutAddSubMenu("Draw", submenu);
	glutAddMenuEntry("Clear", 0);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void ClearScreen()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	glutSwapBuffers();
	p = 0;
	pcount = 0;
}

void DrawPoints()
{
	if (p != 0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		for (int i = 0; i < p; i++)
		{
			glVertex2f(points[i].x, height - points[i].y);
		}
		glEnd();
	}
}

void DrawRectangle()
{
	if (p != 0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		for (int i = 1; i < p; i += 2)
		{
			glVertex2f(points[i-1].x, height - points[i].y);
			glVertex2f(points[i].x, height - points[i-1].y);
		}
	}
	glEnd();
	glColor3f(0.0f, 0.0f, 1.0f);
	for (int i = 1; i < p; i+=2)
	{
		glRectf(points[i-1].x, height - points[i-1].y, points[i].x, height - points[i].y);
	}
}

void DrawTriangle()
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < p; i++)
	{
		glVertex2f(points[i].x, height - points[i].y);
	}
	glEnd();
}

void DrawLine()
{
	glColor3f(0.0f, 1.0f, 1.0f);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	for (int i = 0; i < p; i++)
	{
		glVertex2f(points[i].x, height - points[i].y);
	}
	glEnd();
}

void DrawCircle()
{
	glColor3f(1.0f, 1.0f, 0.0f);
	if (p == 2)
	{
		glLineWidth(5.0f);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i <= numberOfSegments; i++)
		{
			float angle = 2 * 3.14 * (float)i / (float)numberOfSegments;
			float r = sqrt(abs((points[1].x - points[0].x) * (points[1].x - points[0].x) - 
				((height - points[1].y) - (height - points[0].y)) * 
				((height - points[1].y) - (height - points[0].y))));
			float x = r * cosf(angle);
			float y = r * sinf(angle);
			glVertex2f(x + points[0].x, y + (height - points[0].y));
		}
		glEnd();
		p = 0;
	}
}

void DrawPolygon()
{
	glColor3f(0.5f, 1.0f, 0.5f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < p; i++)
	{
		glVertex2f(points[i].x, height - points[i].y);
	}
	glEnd();
}

void CheckValue()
{
	if (value != pcount)
		p = 0;
	pcount = value;
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0f);
	
	if (value == 0)
	{
		ClearScreen();
		return;
	}
	if (value == 1)
	{
		CheckValue();
		glutSwapBuffers();
		DrawPoints();
		DrawTriangle();
	}
	if (value == 2)
	{
		CheckValue();
		glutSwapBuffers();
		DrawPoints();
		DrawLine();
	}
	if (value == 3)
	{
		CheckValue();
		glutSwapBuffers();
		DrawPoints();
		DrawRectangle();
	}
	if (value == 4)
	{
		CheckValue();
		glutSwapBuffers();
		DrawPoints();
		DrawCircle();
	}

	if (value == 5)
	{
		CheckValue();
		glutSwapBuffers();
		DrawPoints();
		DrawPolygon();
	}

	glFlush();
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	//reshaping code
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0.0, (float)w, 0.0, (float)h);
	width = w;
	height = h;
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void Mouse(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				points[p].x = x;
				points[p].y = y;
				p++;
			}
			break;
			glutPostRedisplay();
	}
}

void Setup()
{
	createMenu();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ASSIGNMENT");

	Setup();
	
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}