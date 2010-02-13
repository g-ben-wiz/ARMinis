#include <GL/glut.h>
#include <cstdlib>
#include <stdio.h>

#include <vector>

#include "ARMinisView.cpp"

void simpleDraw();
void normalKeyFoo(unsigned char key, int x, int y);
void reshapeFoo(int width, int height);

Terrain terrain;
ARMinisView view;

int main(int argc, char** argv)
{
	::view.setTerrain(&terrain);

    terrain.load_data("../terrain/dwarven-ruin.map");

	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 680);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 

	glutCreateWindow("ARMinis");

	glEnable(GL_DEPTH_TEST);

	glutIdleFunc(simpleDraw);
	glutReshapeFunc(reshapeFoo);

	glutKeyboardFunc(normalKeyFoo);	
	
	glutMainLoop();

	return 0;
}

void reshapeFoo(int width, int height)
{
	if (height == 0) 
		height = 1;

	GLfloat aspect_ratio = 1.0 * width / height;

	GLfloat eye_x = 0.0, eye_y = 3000, eye_z = 0.0;
	GLfloat center_x = 0.0, center_y = 0.0, center_z = 0.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, width, height); 
	gluPerspective(45, aspect_ratio, 1, 10000);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt( eye_x, eye_y, eye_z,
	       center_x, center_y, center_z, 
	       0.0f, 0.0f, 1.0f); //up-vector
}

void normalKeyFoo(unsigned char key, int x, int y) 
{
	if (key == 27) //esc
	{
		exit(0);
	}
}

void simpleDraw()
{
    view.simpleDraw();
}

