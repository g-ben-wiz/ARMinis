#include <GL/glut.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>

#include <vector>

#include "ARMinisView.cpp"

void render();
void normal_key_foo(unsigned char key, int x, int y);
void special_key_foo(int key, int x, int y);
void reshape(int width, int height);
void refresh_camera();

Terrain terrain;
ARMinisView view;

int main(int argc, char** argv)
{
	::view.setTerrain(&terrain);

    terrain.load_data("../terrain/dwarven-ruin.map");

    Piece *dwarf = new Piece();
    dwarf->load_data("../model/dwarf.mod");
    ::view.piece_list.push_back(dwarf);

    dwarf->position.x = 100.0;
    dwarf->position.y = 20.0;
    dwarf->position.z = -45.0;
    dwarf->position.w = 1.0;

    
    Piece *dwarf2 = new Piece();
    dwarf2->load_data("../model/dwarf.mod");
    ::view.piece_list.push_back(dwarf2);

    dwarf2->position.x = -100.0;
    dwarf2->position.y = 20.0;
    dwarf2->position.z = -45.0;
    dwarf2->position.w = 1.0;

	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 680);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE); 

	glutCreateWindow("ARMinis");

	glEnable(GL_DEPTH_TEST);

	glutIdleFunc(render);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(normal_key_foo);	
    glutSpecialFunc(special_key_foo);
	
	glutMainLoop();

	return 0;
}

void reshape(int width, int height)
{
	if (height == 0) 
		height = 1;

    ::view.cam.aspect_ratio = 1.0 * width/height;
	glViewport(0, 0, width, height); 

    refresh_camera();

}

void refresh_camera()
{
    Camera *cam = new Camera;
    *cam = ::view.cam; 

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(cam->fov_y, cam->aspect_ratio, cam->near, cam->far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float center_x = cam->eye_x + cam->los_x;
    float center_y = cam->eye_y + cam->los_y;
    float center_z = cam->eye_z + cam->los_z;

    gluLookAt( cam->eye_x, cam->eye_y, cam->eye_z,
	       center_x, center_y, center_z, 
	       cam->up_x, cam->up_y, cam->up_z); //up-vector
    delete(cam);
}

void normal_key_foo(unsigned char key, int x, int y) 
{
    switch (key)
    {
        case 27:
            exit(0);
            break;
        case 'z': 
            ::view.zoom(1, 1);
            break;
        case 'x':
            ::view.zoom(-1, -1);
            break;
    }
}

void special_key_foo(int key, int x, int y)
{
    int mod = glutGetModifiers();
    float distance = 300.0;
    switch (key)
    {
        case GLUT_KEY_LEFT :
            if (mod == GLUT_ACTIVE_CTRL) 
            {
                ::view.cam.h_angle -= .03;
                ::view.turn_cam();                       
            }
            else
            {
            }
            break;
        case GLUT_KEY_RIGHT:
            if (mod == GLUT_ACTIVE_CTRL) 
            {
                ::view.cam.h_angle += .03;
                ::view.turn_cam();                       
            }
            else 
            {
            }
            break;
        case GLUT_KEY_UP:
            if (mod == GLUT_ACTIVE_CTRL) 
            {
                ::view.cam.v_angle -= .03;
                ::view.turn_cam();
            }
            else 
            {
            }
            break;
        case GLUT_KEY_DOWN:
            if (mod == GLUT_ACTIVE_CTRL) 
            {
                ::view.cam.v_angle += .03;
                ::view.turn_cam();
            }
            else
            {
            }
    }
}

void render()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    //draw map
    view.drawTerrain();

    //draw all pieces in view.piece_list)
    view.drawPieces();

    glutSwapBuffers();
}

